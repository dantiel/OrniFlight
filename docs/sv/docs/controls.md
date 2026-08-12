# Kontroller

OrniFlight använder standard RC stickmapping med ornithopter-specifika tillägg.

## Stick Mapping

| Stick | Axel | Primär effekt |
|-------|------|--------------|
| Gasreglage (vänster, vertikal) | Gasspjäll | Klaffande amplitud/dragkraft |
| Yaw (vänster, horisontell) | Jaja | Differential vingtryck för svängning |
| Pitch (höger, vertikal) | Pitch | Tilt framåt/bakåt |
| Rulla (höger, horisontell) | Rulla | Vänster/höger banking |

## Flyglägen

| Läge | Stickbeteende |
|------|---------------|
| **ACRO** | Sticks kontrollera vinkelhastighet — ingen automatisk nivå |
| **ANGLE** | Håller kontrollvinkeln — automatisk nivå när den släpps |
| **HORIZON** | ANGLE nära centrum, ACRO vid full avböjning |

ACRO rekommenderas för erfarna piloter. ANGLE är bra för första flygningar och termisk flygning.

## Ornithopter-specifika kontroller

### INDEPENDENT-läge

När INDEPENDENT-läget är aktivt svarar varje vingservo oberoende:
- **Vänster pinne** → vänstervingsservon
- **Höger pinne** → högervinge servon
- Möjliggör asymmetrisk flaxning för aggressiva manövrar

### GLIDE-läge

GLIDE-läget låser båda vingarna i horisontellt läge. Ornithoptern blir ett segelflygplan:
- **Gas** har ingen effekt på vingens position
- **Pitch/Roll/Yaw** påverkar fortfarande svanskontrollytor (om utrustad)

### Profilbyte

Profilbyte under flygning via AUX-kanalen gör det möjligt att ändra parametrar för PID/ONDAS mitt under flygningen:
- **Profil 1**: Standardinställningar för kryssning
- **Profil 2**: Inställningar för hög smidighet
- **Profil 3**: Effektivitet/glidinställningar

## Priser

Konfigurera priser på fliken **PID Tuning**. För ornithoptrar, börja med konservativa hastigheter — flaxande dynamik förstärker kontrollingångar:
- RC Rate: 0,80–1,00
- Superhastighet: 0,60–0,70
- Expo: 0,20–0,40