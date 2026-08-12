# Hardware supportato

OrniFlight funziona con i controllori di volo commodity STM32F3/F4/F7. La linea di base è **STM32F3** — qualsiasi bersaglio F3 con perni timer con funzionalità servo volerà.

## Controllori di volo

| Consiglio | MCU | IMU | Flash | Ricevitore | Stato |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256KB | FrSky D8 (integrato) | ✅ Primario |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Supportato |

### TINYFISH — Il bersaglio OrniFlight più leggero

Progettato da fishpepper, TINYFISH è il controllore di volo ideale per gli ornitotteri: leggero come una piuma, basato su F3 e dotato di un **ricevitore FrSky D8 integrato** a bordo. Nessun RX esterno, nessun cablaggio aggiuntivo — solo alimentazione, servi e volo.

- **MCU**: STM32F303CCT6 @ 72 MHz
- **Giroscopio**: MPU6000 (SPI, compatibile con 8 kHz)
- **Flash**: 256 KB sul chip
- **RAM**: 40 KB
- **Ricevitore**: FrSky D8 integrato (SBUS instradato internamente a UART2)
- **UART**: VCP + 2 UART hardware (UART1 gratuito per il componente aggiuntivo GPS/CRSF)
- **Ingresso**: 2-4S LiPo (potenza servo diretta)
- **Peso**: ~2,5 g

TINYFISH dimostra che il controllo trascendente del battito delle ali non ha bisogno di uno F7. Lo STM32F303 gestisce l'intera pipeline ONDAS — 10 canali di modulazione, ala trapezoidale ODE, 4 profili di volo — entro 256 KB.

### OMNIBUSF4 — Il cavallo di battaglia accessibile

Il classico bersaglio F4. Economico, onnipresente, completo di funzionalità con OSD e ampio flash SPI per la registrazione Blackbox. Il punto di riferimento per lo sviluppo e le build più grandi.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Giroscopio**: MPU6000 (SPI, compatibile con 8 kHz)
- **Flash**: 1 MB su chip + 16 MB SPI (scatola nera)
- **RAM**: 192 KB
- **OSD**: AT7456E (compatibile con MAX7456)
- **UART**: VCP + 5 UART hardware
- **Barometro**: BMP280 (alcune varianti)
- **Ingresso**: 2-6S LiPo

---

## Anatomia dell'ornitottero

### Servi delle ali

OrniFlight controlla lo sbattimento attraverso i servi PWM. Specifiche chiave:

| Parametro | Gamma tipica |
|-----------|--------------|
| Larghezza impulso | 500–2500 µs |
| Centro | 1500 µs |
| Frequenza | 50–330 Hz |
| Angolo di corsa | ±15–45° |

Per gli ornitotteri ad alte prestazioni si consigliano servi digitali con frequenza di aggiornamento di 330 Hz. I servi analogici funzionano a 50 Hz ma hanno una precisione inferiore.

### Ricevitore

È supportato qualsiasi protocollo di ricevitore seriale. CRSF (TBS Crossfire / ExpressLRS) è consigliato per:
- Bassa latenza (fondamentale per il controllo dello sbattimento)
- Telemetria integrata
- RSSI su protocollo (nessun cablaggio aggiuntivo)

### Batteria

- **2S (7.4V)**: Piccoli ornitotteri, servoalimentati direttamente
- **3S (11,1 V)**: ornitotteri medi, BEC richiesto per i servi
- **4S (14,8 V)**: Ornitotteri di grandi dimensioni, consigliato BEC esterno

---

## Periferiche supportate

| Periferico | Via | Note |
|-----------|-----|-------|
| GPS | UART | UBlox M8N o compatibile |
| VTX | UART TX | Vagabondo, SmartAudio |
| Macchina fotografica | — | Qualsiasi fotocamera analogica FPV |
| Cicalino | BUZZ pad | Cicalino attivo 5V |
| LED Striscia | LED pad | WS2812 / SK6812 |
| OpenLog | UART TX | Registrazione nella scatola nera |
| Bluetooth | UART | MSP passthrough per l'ottimizzazione mobile |

---

## Obiettivi futuri

OrniFlight mira a supportare ulteriori target STM32F4/F7 dove sono disponibili risorse UART e timer sufficienti per il controllo del servo battente. Contributi benvenuti.