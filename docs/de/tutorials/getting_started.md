# Erste Schritte

Willkommen bei OrniFlight! Diese Anleitung führt Sie durch die Ersteinrichtung Ihres Ornithopter-Flugcontrollers.

## Was Sie brauchen

- **OrniFlight Konfigurator** — Download von [orniflight.org](https://orniflight.org)
- **USB-Kabel** — zum Anschluss des Flugcontrollers an den Computer
- **Ornithopter** mit:
  - Unterstützter Flugcontroller (OMNIBUSF4, TINYFISH)
  - Servos zur Flügelbetätigung
  - Empfänger an Ihren Sender gebunden
  - Batterie (2S–4S LiPo)

## Schnellstart

### 1. Flash-Firmware

1. Öffnen Sie den **OrniFlight-Konfigurator**
2. Gehen Sie zur Registerkarte **Firmware-Flasher**
3. Wählen Sie Ihr Board-Ziel (OMNIBUSF4 oder TINYFISH)
4. Wählen Sie die neueste stabile Version
5. Klicken Sie auf **Firmware laden** und dann auf **Firmware flashen**

### 2. Erstkonfiguration

Nach dem Flashen werden Sie vom Konfigurator aufgefordert, benutzerdefinierte Standardeinstellungen anzuwenden. **Immer akzeptieren.**

### 3. Empfänger-Setup

1. Gehen Sie zur Registerkarte **Ports** → und stellen Sie den richtigen UART auf `Serial RX` ein
2. Gehen Sie zur Registerkarte **Konfiguration** → und wählen Sie Ihr Empfängerprotokoll aus (CRSF, SBUS usw.).
3. Gehen Sie zur Registerkarte **Empfänger** → und überprüfen Sie, ob die Bewegungen des Steuerknüppels mit den erwarteten Kanälen übereinstimmen
4. Stellen Sie die Kanalendpunkte ein: 1000–2000 mit 1500 Mitte

### 4. Servo-Setup

1. Gehen Sie zur Registerkarte **Servos**
2. Überprüfen Sie, ob die Servozuordnung mit der Flügelkonfiguration Ihres Ornithopters übereinstimmt
3. Testen Sie bei Bedarf die Servorichtung — umgekehrt
4. Mittelstellung einstellen (Flügel horizontal = 1500)

### 5. Modus-Setup

1. Gehen Sie zur Registerkarte **Modi**
2. Weisen Sie ARM einem AUX-Switch zu
3. Flugmodi (ANGLE / ACRO / HORIZON) nach Wunsch zuweisen
4. Weisen Sie INDEPENDENT und GLIDE Ersatzschaltern zu
5. Konfigurieren Sie BEEPER für die Suche nach verlorenen Modellen

### 6. Erster Flug

1. **Trennen Sie die Flügelverbindung zum Testen auf dem Prüfstand**
2. Aktivieren Sie die Servobewegungsrichtung und überprüfen Sie sie
3. Überprüfen Sie die Gasannahme
4. Für den ersten tatsächlichen Flug: ANGLE-Modus verwenden, niedrige Tarife
5. Bewegen Sie den Mauszeiger auf Augenhöhe und schneiden Sie ihn nach Bedarf

## Nächste Schritte

- [Grundlegendes Setup](basic_setup.html) — detaillierte Konfigurationsanleitung
- [ONDAS Tuning](../../tutorials/ondas_tuning.html) — Melodie der Schlagdynamik
- [PID Tuning](../../tutorials/tuning.html) — Flugeigenschaften anpassen