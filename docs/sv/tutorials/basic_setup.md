# Grundläggande inställningar

> *Konfigurera din ornithopter för första flygningen.*

## Checklista före flygning

Före allt annat:

- [ ] Flygkontrollen blinkade med OrniFlight
- [ ] Mottagaren bunden till sändaren
- [ ] Servon anslutna till korrekta PWM-utgångar
- [ ] Batteri anslutet (vingarna säkrade!)

## Mottagareinställningar

### CRSF (rekommenderas)

1. **Fliken Portar**: Ställ in UART (t.ex. UART1) till "Serial RX"
2. **Fliken Konfiguration**: Mottagarläge = "Serial-baserad mottagare", Provider = "CRSF"
3. Slå på strömmen, kontrollera att kanalingångarna rör sig på fliken Mottagare

### SBUS / Annat

Samma process — välj lämpligt protokoll på fliken Konfiguration.

## Servomappning

På fliken **Servos**:

| Servo | Funktion | Standardpris |
|-------|--------|-------------|
| Servo 0 | Vänsterflygeln | 250 Hz |
| Servo 1 | Högervinge | 250 Hz |
| Servo 2 | Vapen/Roder | 50 Hz |

Justera min/max/mitten för att matcha din servos räckvidd. Testa med "Åsidosätt" för att verifiera riktningen.

## Val av flygläge

På fliken **Lägen**:

1. **ARM**: Tilldela en switch (säkerhet!)
2. **ORNITHOPTER INDEPENDENT** eller **ORNITHOPTER GLIDE**: Välj ditt primära flygläge
3. **ORNITHOPTER PROFILE**: Valfri —-tilldelning för byte av profil under flygning

## ONDAS Första stämningen

Gå till **Avancerat → ONDAS underfliken**:

1. **Cadence Gain**: Börja vid 50 (mitten). Detta är den viktigaste parametern.
2. **Ferocity D Gain**: Börja vid 30. Detta är din primära stabilisering.
3. **Ferocity P Gain**: Börja vid 20 för roll/pitch, 0 för yaw.
4. **Balance Vinst**: 0 (centrerad).

Anslut ett batteri, **säkra ornithoptern ordentligt** och ARM. Observera servorörelse — den ska vara jämn, sinusformad flaxande.

## Första flygningen

1. Börja med ett försiktigt kast mot vinden
2. Använd GLIDE-läget för naturlig svävande känsla
3. Använd INDEPENDENT-läget när du vill ha direkt frekvenskontroll
4. Landa, justera ONDAS, upprepa

---

*Nästa: [ONDAS Tuning Guide](ondas_tuning.html) →*