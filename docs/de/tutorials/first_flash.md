# Erster Blitz

> *Schritt für Schritt OrniFlight auf Ihren Flugcontroller — übertragen.*

## Was Sie brauchen

- STM32F4-basierter Flugcontroller (OMNIBUSF4, TINYFISH, MATEKF405 usw.)
- USB-Kabel
- [dfu-util](http://dfu-util.sourceforge.net/) oder STM32CubeProgrammer
- OrniFlight `.hex`-Datei von der [Release-Seite](https://github.com/dantiel/OrniFlight/releases)

## Schritt 1: Rufen Sie den DFU-Modus auf

1. **Halten Sie die BOOT-Taste** auf Ihrem Flugcontroller gedrückt
2. **Zzz26zzz einstecken**, während Sie die Taste gedrückt halten
3. **Nach 2 Sekunden loslassen**

Überprüfen Sie unter macOS/Linux:

```
dfu-util -l
```

Sollte `Found DFU: [0483:df11]` anzeigen

## Schritt 2: Flashen

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Schritt 3: Erster Start

1. Ziehen Sie USB ab
2. Stecken Sie USB wieder ein (halten Sie BOOT nicht gedrückt)
3. Stellen Sie eine Verbindung über den OrniFlight-Konfigurator her

## Schritt 4: Grundkonfiguration

Im Konfigurator:

1. **Registerkarte „Anschlüsse“**: Konfigurieren Sie UART für Ihren Receiver (seriell RX)
2. **Registerkarte „Konfiguration“**: Empfängerprotokoll auswählen (CRSF empfohlen)
3. **Registerkarte „Modi“**: Richten Sie die Schalter ARM, GLIDE/INDEPENDENT und PROFILE ein
4. **Erweiterte Registerkarte → ONDAS**: Überprüfen Sie die Standardeinstellungen und optimieren Sie zuerst Cadence

## Fehlerbehebung

| Problem | Fix |
|---------|-----|
| DFU Gerät nicht gefunden | Probieren Sie ein anderes USB-Kabel aus, überprüfen Sie die Schaltfläche BOOT |
| Flash schlägt fehl | Überprüfen Sie die dfu-util-Installation, USB-Berechtigungen |
| Kein Booten nach Flash | Erneut flashen, prüfen, ob Hexadezimalwert mit Ihrem Ziel übereinstimmt |
| Konfigurator stellt keine Verbindung her | Überprüfen Sie den COM-Port und die Baudrate |

---

*Weiter: [Grundlegende Einrichtung](basic_setup.html) →*