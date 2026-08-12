# PID Tuning

OrniFlight använder en PID (Proportional-Integral-Derivative) styrenhet anpassad för flaxande vingflyg. Tuning skiljer sig avsevärt från konventionella flygplan på grund av den periodiska karaktären av flaxande dragkraft.

## Ornithopter PID Grunderna

Till skillnad från konventionella flygplan där dragkraften är nästan kontinuerlig, svänger ornithopterkraften med varje vingslag. Detta skapar:

- **Trivningsrippel** vid flaxande frekvens (vanligtvis 5–15 Hz)
- **Fasberoende kontrollmyndighet** — samma PID-utgång har olika effekt beroende på var i slagcykeln den appliceras
- **Kopplad roll-yaw-dynamik** — asymmetrisk vingkraft påverkar båda axlarna samtidigt

## PID Villkor

| Term | Effekt | Ornithopter Note |
|------|--------|----------------|
| **P** | Proportionell — omedelbar korrigering | Använd konservativa värderingar; svängningen är flaxande synkron |
| **Jag** | Integral — ihållande felkorrigering | Viktigt för att bibehålla attityden under glidningar |
| **D** | Derivat — dämpar svängningar | Inställd på vingslagfrekvens, inte ramsvängningar |
| **F** | Mata framåt — direkt stick-to-output | Användbar för skarp respons på rullaxeln |

## Startvärden

För en medelstor ornithopter (1–1,5m vingspann):

| Axel | P | jag | D | F |
|------|---|---|---|---|
| Rulla | 25 | 30 | 15 | 30 |
| Pitch | 30 | 35 | 20 | 35 |
| Jaja | 40 | 35 | 10 | 20 |

## Trimprocedur

### 1. Rate Tuning först

Innan PID ställer in, ställ in hastigheter som känns bekväma:
- Börja med RC Rate 0,90, Super Rate 0,65, Expo 0,30
- Justera för din flygstil och ornithopterstorlek

### 2. P Vinst

Öka P tills du ser oscillation vid flaxande frekvens, backa sedan 20 %:
- Rullsvängning: vingsvängning vid slaghastighet
- Pitch oscillation: fram-bak gupp
- Yaw oscillation: svansvifta synkroniserat med slag

### 3. D Vinst

Öka D för att dämpa tillbakastudsningen efter vassa stickingångar:
- För mycket: servojitter, överhettning
- För lite: ringer efter rullnings-/pitchstopp

### 4. Jag vinner

Jag får räknare ihållande drift:
- Öka tills driften elimineras
- För mycket: långsam oscillation vid 1–2 Hz (under flaxande hastighet)

## ONDAS Integration

ONDAS (Ornithopter Nolinear Dynamic Aerodynamic System) modulerar PID-utgången inom varje vingslag. Efter grundläggande PID-inställning:

1. Ställ in **Cadence Gain** — skiftar moduleringsfönstret till aerodynamiskt optimal fas
2. Ställ in **Ferocity P** — omedelbar asymmetrisk dragkraftsförstärkning
3. Ställ in **Ferocity D** — förutseende dragexploatering
4. Finjustera **Balance** — vänster-/högersymmetri

Se [ONDAS Tuning Guide](ondas_tuning.html) för detaljerad procedur.

## Blackbox-analys

Aktivera Blackbox-loggning för att visualisera PID-prestanda. Leta efter:
- **P-term oscillation** vid flaxande frekvens → minska P
- **I-term windup** under ihållande svängar → minska I eller öka I-term relax
- **D-term buller** från vibrationer → kontrollera först den mekaniska balansen och minska sedan D

## Flygprofiler

OrniFlight stöder 3 flygprofiler som kan bytas mellan flyg:

| Profil | Användningsfall |
|--------|--------|
| 1 | Standardkryssning |
| 2 | Hög smidighet / aggressiv |
| 3 | Effektivitet / termisk skyhöghet |