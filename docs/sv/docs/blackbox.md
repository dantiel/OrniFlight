# Blackbox-loggning

Blackbox registrerar flygdata för analys, inställning och felsökning efter flygning. OrniFlight stöder loggning till inbyggt flash-chip eller extern OpenLog-enhet.

## Vad loggas

- **Gyro** — rå och filtrerad 3-axlig vinkelhastighet
- **Accelerometer** — 3-axlig acceleration
- **PID Output** — P, I, D, F-bidrag per axel
- **ONDAS** — Cadence, Ferocity P/D och andra flaxspecifika parametrar
- **RC Kommandon** — stickpositioner efter kurser/expo
- **Servoutgång** — slututgång till varje servokanal
- **Batteri** — spänning och ström per iteration
- **GPS** — position, hastighet, höjd (när tillgängligt)

## Inställning

### Onboard Flash (OMNIBUSF4)

Zzz34zzz inkluderar 16 MB inbyggd blixt för Blackbox-loggning. Aktivera i Configurator:

1. Fliken **Blackbox** → Ställ in `Blackbox logging device` till `Onboard flash`
2. Ställ in loggningshastighet (rekommenderar: `1/N` med N=2-4 för F4-mål)
3. Tilldela en omkopplare för att starta/stoppa loggning

### Extern OpenLog

Anslut OpenLog till en ledig UART TX pin:

1. Fliken **Portar** → Ställ in UART på `Blackbox logging` på 115200 baud
2. Anslut OpenLog: FC TX → OpenLog RX, plus 5V/GND

## Analysverktyg

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — webbaserad loggvisare
- `blackbox_decode` — konvertera till CSV för anpassad analys

## ONDAS-specifik

Blackbox är viktigt för att ställa in ONDAS parametrar. Loggade ONDAS-data inkluderar:
- `ondas_cadence_phase` — moduleringsfönstertiming
- `ondas_ferocity_p` / `ondas_ferocity_d` — asymmetriska dragkraftskomponenter
- `ondas_balance` — vänster/höger vingbalans
- Per servoutgång vid varje iteration

Detta möjliggör exakt analys av flaxande mekanik och vingasymmetrikorrigeringar.