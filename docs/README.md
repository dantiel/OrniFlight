# OrniFlight Website — Magnum Opus Glassmorphism

**Live at `docs/` → GitHub Pages compatible.**

## Architecture

```
docs/
├── index.haml              ← Landing Page (HAML template)
├── _lang/{en,de}.json      ← i18n strings
├── assets/
│   ├── css/style.sass      ← Glassmorphism SASS → CSS
│   └── images/             ← Logos, textures, icons (from Configurator)
├── en/                     ← English content
│   ├── wiki/               ← ONDAS Theory, MSP Protocol, Flight Profiles
│   ├── docs/               ← 16 reference docs (Battery, CLI, Failsafe, GPS, ...)
│   └── tutorials/          ← 6 tutorials (Getting Started, Installation, Tuning, ...)
├── de/                     ← German (structure ready, content follows)
├── Rakefile                ← Build: HAML→HTML, SASS→CSS, MD→HTML
├── Gemfile                 ← haml, sass-embedded, kramdown, rake, webrick
└── watch.sh                ← Auto-rebuild on change
```

## Design

- **Glassmorphism**: Nav, Main, Cards, Footer — layered blur + saturate
- **Feather Pattern**: 140px repeating background
- **Logo**: Breathing glow animation (6s cycle)
- **Dark/Light**: CSS `prefers-color-scheme` with RGB-tuple CSS variables
- **Assets**: Shared with OrniFlight Configurator — consistent branding

## Build

```bash
cd docs
bundle install
bundle exec rake build       # Full build
bundle exec rake server      # http://localhost:8000
./watch.sh                   # Auto-rebuild
```

## Add Content

Drop `.md` files into:
- `en/wiki/` — knowledge base
- `en/docs/` — reference documentation
- `en/tutorials/` — step-by-step guides

The first line (`# Title`) becomes the page title. Appears automatically in section indices.

## Pages (30 total)

### Wiki (3)
ONDAS Theory, MSP Protocol, Flight Profiles

### Docs (16)
Battery, Blackbox, Buzzer, CLI Reference, Controls, Failsafe, GPS, Hardware, LED Strip, Mixer, Modes, OSD, Receiver, RSSI, Safety, Serial, Telemetry, VTX

### Tutorials (6)
Getting Started, Installation, First Flash, Basic Setup, ONDAS Tuning, PID Tuning

## Live Preview

```bash
cd docs
bundle exec rake server
```

→ Öffne **http://localhost:8000** im Browser.

Dark/Light folgt deiner Systemeinstellung (`prefers-color-scheme`).
Die Landing Page liegt bei `/` — Subpages unter `/en/wiki/`, `/en/docs/`, `/en/tutorials/`.

```bash
./watch.sh   # Auto-Rebuild bei Änderungen
```

GitHub Pages dient aus `docs/` heraus — Aktivierung in den Repo-Settings.