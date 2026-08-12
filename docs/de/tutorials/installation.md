# Installation

So installieren Sie die OrniFlight-Firmware auf Ihrem Flugcontroller.

## Voraussetzungen

- **OrniFlight Konfigurator** (neueste Version)
- Datenkabel USB (nicht nur zum Laden)
- Unterstützte Flugsteuerungsplatine

## Unterstützte Boards

| Vorstand | Ziel | Blitz | Notizen |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16 MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256 KB | STM32F411, MPU6000 |

## Blinkende Schritte

### 1. Rufen Sie den DFU/Bootloader-Modus auf

**OMNIBUSF4**: Halten Sie die BOOT-Taste gedrückt, während Sie USB verbinden. Rot LED bleibt durchgehend — Sie befinden sich im DFU-Modus.

**TINYFISH**: Halten Sie die BOOT-Taste gedrückt, während Sie USB verbinden.

### 2. Flash über Konfigurator

1. Öffnen Sie den OrniFlight-Konfigurator
2. Gehen Sie zur Registerkarte **Firmware-Flasher**
3. Wählen Sie Ihr Ziel aus der Dropdown-Liste aus
4. Wählen Sie die Firmware-Version (neueste stabile Version empfohlen)
5. Klicken Sie auf **Firmware laden (Online)** oder wählen Sie eine lokale Hex-Datei aus
6. Klicken Sie auf **Flash-Firmware**
7. Warten Sie auf „Programmierung: ERFOLGREICH“

### 3. Erste Verbindung

Nach dem Flashen:
1. USB trennen und wieder verbinden (ohne BOOT-Taste)
2. Der Konfigurator sollte sich automatisch verbinden
3. Akzeptieren Sie die Aufforderung „Benutzerdefinierte Standardeinstellungen anwenden“.
4. Überprüfen Sie die Board-Informationen auf der Registerkarte „Setup“.

## Fehlerbehebung

### Kein DFU-Port

**macOS/Linux**: DFU sollte automatisch erscheinen. Wenn nicht:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: Installieren Sie [Zadig](https://zadig.akeo.ie/), um den Treiber STM32 DFU zu ersetzen:
1. Führen Sie Zadig aus
2. Optionen → Alle Geräte auflisten
3. Wählen Sie „STM32 BOOTLOADER“
4. Ersetzen Sie den Treiber durch „WinUSB“

### Flash schlägt fehl

- Versuchen Sie es mit einem anderen USB-Kabel (datenfähig, nicht nur zum Laden)
- Versuchen Sie es mit einem anderen USB-Port (direkt, nicht Hub)
- Halten Sie die BOOT-Taste während des gesamten Flash-Vorgangs gedrückt
- **OMNIBUSF4**: Möglicherweise ist eine vollständige Chiplöschung erforderlich. — aktivieren Sie die Option „Vollständige Chiplöschung“.

### Konfigurator stellt keine Verbindung her

- Stellen Sie sicher, dass das USB-Kabel datenfähig ist
- Überprüfen Sie, ob sich die Platine nicht im DFU-Modus befindet (LED blinkt = Normalmodus)
- Konfigurator neu starten
- Probieren Sie einen anderen USB-Port aus

## CLI Flash (Fortgeschritten)

Für fortgeschrittene Benutzer: Flashen über STM32CubeProgrammer oder st-Flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Überprüfen Sie nach dem Flashen Folgendes:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```