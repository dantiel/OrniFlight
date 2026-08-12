# Komma igång

Välkommen till OrniFlight! Den här guiden leder dig genom den första installationen av din ornithopterflygkontroll.

## Vad du behöver

- **OrniFlight Configurator** — nedladdning från [orniflight.org](https://orniflight.org)
- **USB-kabel** — för att ansluta flygkontrollen till datorn
- **Ornithopter** med:
  - Flygkontroller som stöds (OMNIBUSF4, TINYFISH)
  - Servon för vingmanövrering
  - Mottagare bunden till din sändare
  - Batteri (2S–4S LiPo)

## Snabbstart

### 1. Flash-firmware

1. Öppna **OrniFlight Configurator**
2. Gå till fliken **Firmware Flasher**
3. Välj ditt brädmål (OMNIBUSF4 eller TINYFISH)
4. Välj den senaste stabila versionen
5. Klicka på **Load Firmware** och sedan på **Flash Firmware**

### 2. Initial konfiguration

Efter att ha blinkat kommer konfiguratorn att uppmana dig att tillämpa anpassade standardinställningar. **Acceptera alltid.**

### 3. Mottagarinställningar

1. Gå till fliken **Portar** → ställ in rätt UART till `Serial RX`
2. Gå till fliken **Konfiguration** → välj ditt mottagarprotokoll (CRSF, SBUS, etc.)
3. Gå till fliken **Receiver** → verifiera att stickrörelserna matchar förväntade kanaler
4. Ställ in kanalslutpunkter: 1000–2000 med 1500 center

### 4. Servoinstallation

1. Gå till fliken **Servos**
2. Kontrollera att servomappningen matchar din ornithopters vingkonfiguration
3. Testa servoriktningen — back om det behövs
4. Ställ in mittposition (vingarna horisontellt = 1500)

### 5. Lägesinställningar

1. Gå till fliken **Lägen**
2. Tilldela ARM till en AUX switch
3. Tilldela flyglägen (ANGLE / ACRO / HORIZON) efter önskemål
4. Tilldela INDEPENDENT och GLIDE till reservomkopplare
5. Konfigurera BEEPER för att hitta förlorad modell

### 6. Första flygningen

1. **Koppla bort vinglänkaget för bänktestning**
2. Aktivera och kontrollera servorörelseriktning
3. Kontrollera gasresponsen
4. För första faktiska flygningen: använd ANGLE-läget, låga priser
5. Håll muspekaren i ögonhöjd, trimma efter behov

## Nästa steg

- [Basic Setup](basic_setup.html) — detaljerad konfigurationsgenomgång
- [ONDAS Tuning](../../tutorials/ondas_tuning.html) — låt flaxande dynamik
- [PID Tuning](../../tutorials/tuning.html) — justera flygegenskaper