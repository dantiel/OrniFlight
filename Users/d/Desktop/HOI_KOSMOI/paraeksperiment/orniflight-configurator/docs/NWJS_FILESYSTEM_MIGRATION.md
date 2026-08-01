# OrniFlight Configurator — NW.js File System Migration

> *The old API crumbles; the new form arises from the native soil. What Chromium took away, the DOM restores.*
> *`chrome.fileSystem` → `<input type="file">` — a return to first principles, a purification of the I/O soul.*

## Cross-Reference

| What | File | Lines |
|------|------|-------|
| `load_file` handler | `src/js/tabs/firmware_flasher.js` | 638–730 |
| `save_firmware` handler | `src/js/tabs/firmware_flasher.js` | 872–937 |
| Hex parser (Web Worker) | `src/js/tabs/firmware_flasher.js` | 698 (`parse_hex` call) |
| Config cleaner | `src/js/tabs/firmware_flasher.js` | 713 (`cleanUnifiedConfigFile` call) |
| Build system | `gulpfile.js` | — |

---

## 1. Problem

`chrome.fileSystem.chooseEntry` — part of the deprecated Chrome Apps API — is **unstable in Chromium 130+**. NW.js bundles this Chromium version. The existing comment in `main_nwjs.html` already warned:

> *"Chrome App APIs are unstable in Chromium 130+"*

### Symptoms

- File dialog fails to open on some platforms / NW.js versions
- `chrome.runtime.lastError` set but unhandled
- Silent failures — no user feedback, no fallback

### Affected Code (pre-migration)

```
chrome.fileSystem.chooseEntry({type: 'openFile', accepts: [...]}, callback)
chrome.fileSystem.getDisplayPath(entry)
chrome.fileSystem.chooseEntry({type: 'saveFile', suggestedName: ...}, callback)
```

---

## 2. Solution: Native `<input type="file">`

NW.js exposes the full DOM API including native file inputs. These use the OS-native dialog, require no permissions, and are immune to Chrome App API deprecation.

### Architecture

```
User Click → Create hidden <input> → trigger click() → OS dialog opens
                                                    ↓
                            User selects file (or cancels)
                                                    ↓
                        change event fires → File object available
                                                    ↓
                        FileReader (async) → parse_hex / cleanUnifiedConfigFile
```

### Why This Pattern

| Approach | Verdict |
|----------|---------|
| `<input type="file">` + `FileReader` | ✅ Native, stable, zero dependencies |
| `nw.Shell.showItemInFolder` | ❌ Display only, cannot read file contents |
| Node.js `fs.readFile` + NW.js Dialog | ❌ Requires manual dialog construction, fragile path resolution |

---

## 3. Implementation

### 3.1 Load Handler (`a.load_file`, L638–730)

**Before**: `chrome.fileSystem.chooseEntry({type:'openFile',...})`  
**After**: Dynamic `<input type="file" accept=".hex,.config">`

```
Flow:
  Click → guard (_fileDialogOpen flag)
       → enableFlashing(false)
       → analytics: FIRMWARE_SOURCE='file'
       → create hidden <input type="file" accept=".hex,.config">
       → append to body
       → trigger('click') → OS dialog
       → on change:
           file = e.target.files[0]
           if !file → cleanup, return (user cancelled)
           FileReader.readAsText(file)
           onloadend:
               if .hex extension → parse_hex() → self.parsed_hex → flashingMessageLocal()
               else → cleanUnifiedConfigFile() → self.unifiedTargetConfig → flashingMessageLocal()
               cleanupDialog()
           onerror:
               flash "HEX corrupted" message
               cleanupDialog()
```

#### Guards (Purificatio + Validatio)

| ID | Severity | Guard | Location |
|----|----------|-------|----------|
| DG-01 | MEDIUM | `_fileDialogOpen` flag — prevents double-click race condition | L639–642 |
| DG-02 | MEDIUM | `reader.onerror` handler — surfaces FileReader failures | L674–678 |
| DG-03 | CRITICAL | `reader.error` check in `onloadend` — prevents crash on failed read | L681–683 |
| DG-04 | LOW | `e.total === 0` branch — handles empty files | L714–717 |
| DG-05 | HIGH | `.toLowerCase()` on extension — handles `.HEX`, `.Hex`, etc. | L687 |
| DG-06 | HIGH | `cleanupDialog()` in all exit paths (success, empty, error) | L698, L701, L718 |
| DG-07 | LOW | `accept=".hex,.config"` — OS-level file type filter | L650 |

### 3.2 Save Handler (`a.save_firmware`, L872–937)

**Before**: `chrome.fileSystem.chooseEntry({type:'saveFile',...})`  
**After**: Dynamic `<input type="file" nwsaveas="filename.hex">`

The `nwsaveas` attribute is an NW.js extension that transforms the file input into a save dialog.

```
Flow:
  Click → guard: (!summary || !summary.file) → return
       → guard: (!self.intel_hex) → return, log error
       → create hidden <input nwsaveas="filename.hex" accept=".hex">
       → append to body
       → trigger('click') → OS save dialog
       → on change:
           savePath = e.target.value
           if !savePath → cleanup, return (user cancelled)
           new Blob([self.intel_hex])
           FileReader.readAsArrayBuffer(blob)
           onloadend:
               guard: (reader.error || !reader.result) → cleanup
               Buffer.from(new Uint8Array(reader.result))
               fs.writeFile(savePath, buffer, callback)
                   success → log, cleanup
                   error → GUI.log("Write permissions"), cleanup
           onerror:
               GUI.log("Write permissions")
               cleanup
```

#### Guards

| ID | Severity | Guard | Location |
|----|----------|-------|----------|
| SG-01 | MEDIUM | `!summary \|\| !summary.file` — prevents `nwsaveas="undefined"` | L879–882 |
| SG-02 | MEDIUM | `!self.intel_hex` — prevents `new Blob([undefined])` | L883–887 |
| SG-03 | MEDIUM | `reader.onerror` handler — surfaces FileReader failures | L894–898 |
| SG-04 | LOW | `reader.error \|\| !reader.result` in `onloadend` — prevents `Buffer.from(null)` | L901–904 |
| SG-05 | LOW | `saveInput.remove()` in all exit paths (cancel, error, write success, write failure) | L889, L899, L909, L912 |

---

## 4. Invariant Preservation

All 20 critical symbols preserved through migration:

| Symbol | Type | Count | Status |
|--------|------|-------|--------|
| `parse_hex` | Worker call | 3 | ✓ |
| `cleanUnifiedConfigFile` | Sync call | 2 | ✓ |
| `flashingMessageLocal` | UI update | 3 | ✓ |
| `enableFlashing` | State control | 8 | ✓ |
| `clearBufferedFirmware` | State reset | 3 | ✓ |
| `self.localFirmwareLoaded` | Flag | 10 | ✓ |
| `self.parsed_hex` | State | 22 | ✓ |
| `self.intel_hex` | State | 10 | ✓ |
| `self.unifiedTargetConfig` | State | 22 | ✓ |
| `self.isConfigLocal` | Flag | 13 | ✓ |
| `analytics.setFirmwareData` | Telemetry | 13 | ✓ |
| `FileReader` | Browser API | 2 | ✓ |
| `nwsaveas` | NW.js API | 2 | ✓ |
| `readAsText` | Reader method | 1 | ✓ |
| `readAsArrayBuffer` | Reader method | 1 | ✓ |
| `Buffer.from` | Node API | 1 | ✓ |
| `fs.writeFile` | Node API | 1 | ✓ |
| `GUI.log` | Logging | 4 | ✓ |
| `i18n.getMessage` | Localization | 6 | ✓ |
| `self.flashingMessage` | UI | 5 | ✓ |

---

## 5. Chrome API Removal

Zero functional `chrome.fileSystem` calls remain. Two **documentation-only** references persist as comments:

- L648: `// Use native <input type="file"> instead of chrome.fileSystem (unstable in Chromium 130+)`
- L890: `// Use native NW.js nwsaveas input instead of chrome.fileSystem (unstable in Chromium 130+)`

These are intentional — they explain *why* to future maintainers encountering the unusual `<input>`-based pattern.

---

## 6. Testing

### Build Verification

```bash
npx gulp              # Clean build → NW.js app assembled
node -c src/js/tabs/firmware_flasher.js  # Syntax check: PASS
```

### Functional Test Matrix

| Scenario | Expected | Status |
|----------|----------|--------|
| Click "Load Firmware (Local)" | Native file dialog opens, filtered to `.hex,.config` | ✓ |
| Select `.hex` file | Parsed via Web Worker, flash button enables | ✓ |
| Select `.config` file | `cleanUnifiedConfigFile` runs, local flag set | ✓ |
| Cancel dialog | Clean no-op, no errors, DOM cleaned | ✓ |
| Select `.HEX` (uppercase) | Treated as hex (case-insensitive via `.toLowerCase()`) | ✓ |
| Select empty file (0 bytes) | Error message shown, no crash | ✓ |
| Rapid double-click | Only one dialog opens (`_fileDialogOpen` guard) | ✓ |
| Save firmware | NW.js save dialog with suggested filename, writes to disk | ✓ |
| Save with no firmware loaded | Error logged, no dialog | ✓ |
| Save with no version selected | Error logged, no dialog | ✓ |

### Performance

| Operation | Mechanism | Blocking? |
|-----------|-----------|-----------|
| `parse_hex` (large hex) | Web Worker (`hex_parser.js`) | No |
| `cleanUnifiedConfigFile` (~100KB) | Synchronous O(n) | Yes — negligible |
| `FileReader.readAsText` | Async browser API | No |
| `FileReader.readAsArrayBuffer` | Async browser API | No |
| `fs.writeFile` | Async Node.js API | No |

### Security

| Vector | Mitigation |
|--------|------------|
| XSS via file content | Content never interpolated into DOM — only parsed by worker/config-cleaner |
| Path traversal | Browser `<input type="file">` returns filename only; `nwsaveas` returns user-chosen path |
| File type bypass | `accept=".hex,.config"` restricts OS dialog; extension re-checked in code |
| Code injection | Content passes through `parse_hex` (structured parser) or `cleanUnifiedConfigFile` (validator) |
| Unsafe eval | None — `Buffer.from` on ArrayBuffer, no string-to-code paths |

---

## 7. Known Limitations (Accepted)

| ID | Limitation | Risk | Rationale |
|----|------------|------|-----------|
| LIM-01 | DOM-leaked `<input>` if user navigates away before selecting file | Negligible (~100 bytes) | Only occurs on explicit tab switch during dialog; cleanup runs on selection |
| LIM-02 | Non-hex files renamed to `.hex` produce misleading "Config corrupted" | Low | User must deliberately bypass OS-level filter |
| LIM-03 | No file size pre-validation before `readAsText()` | Low | Typical firmware hex files < 2MB; NW.js handles 100MB+ strings |
| LIM-04 | Full filesystem path logged to console in save handler | Info leak (dev) | Consistent with `backup_restore.js` pattern; development utility |

---

## 8. Files Not Modified

These files also use `chrome.fileSystem` but are **out of scope** for this migration:

| File | API Usage | Priority |
|------|-----------|----------|
| `src/js/tabs/logging.js` | `chrome.fileSystem.chooseEntry` for log export | Separate task |
| `src/js/tabs/onboard_logging.js` | `chrome.fileSystem` for blackbox export | Separate task |
| `src/js/tabs/vtx.js` | `chrome.fileSystem` for VTX table import | Separate task |
| `src/js/tabs/osd.js` | `chrome.fileSystem` for OSD font upload | Separate task |

The pattern established here (`<input type="file">` for load, `<input nwsaveas>` for save) can be replicated for all four.

---

## 9. Migration Pattern (Reusable)

For any future `chrome.fileSystem` migration in this codebase:

### Load (read file from disk)

```javascript
var input = $('<input type="file" accept=".ext1,.ext2" style="display:none">');
$('body').append(input);
input.on('change', function(e) {
    var file = e.target.files[0];
    if (!file) { input.remove(); return; }
    var reader = new FileReader();
    reader.onerror = function(err) { /* handle error */ input.remove(); };
    reader.onloadend = function(e) {
        if (reader.error) { input.remove(); return; }
        if (e.total !== 0 && e.total === e.loaded) {
            // process reader.result
        }
        input.remove();
    };
    reader.readAsText(file); // or readAsArrayBuffer for binary
});
input.trigger('click');
```

### Save (write file to disk)

```javascript
var input = $('<input type="file" nwsaveas="filename.ext" accept=".ext" style="display:none">');
$('body').append(input);
input.on('change', function(e) {
    var savePath = e.target.value;
    if (!savePath) { input.remove(); return; }
    var reader = new FileReader();
    reader.onerror = function(err) { /* handle */ input.remove(); };
    reader.onloadend = function() {
        if (reader.error || !reader.result) { input.remove(); return; }
        var buf = Buffer.from(new Uint8Array(reader.result));
        require('fs').writeFile(savePath, buf, function(err) {
            if (err) { /* handle */ }
            input.remove();
        });
    };
    reader.readAsArrayBuffer(new Blob([content]));
});
input.trigger('click');
```

---

*Thus the file dialog returns to its native form — no Chrome App wrappers, no unstable APIs, no silent failures. The code breathes closer to the metal, and the metal holds.*
