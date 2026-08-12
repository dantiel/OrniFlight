# Controlli

OrniFlight utilizza la mappatura stick standard RC con estensioni specifiche per gli ornitotteri.

## Mappatura degli stick

| Bastone | Asse | Effetto primario |
|-------|------|-------|
| Acceleratore (sinistra, verticale) | Acceleratore | Ampiezza/spinta del battito d'ali |
| Imbardata (sinistra, orizzontale) | Imbardata | Spinta alare differenziale per virata |
| Intonazione (destra, verticale) | Passo | Inclinazione avanti/indietro |
| Rotolare (a destra, orizzontale) | Rotolo | Sistema bancario sinistro/destro |

## Modalità di volo

| Modalità | Comportamento dello stick |
|------|---------------|
| **ACRO** | Gli stick controllano la velocità angolare — nessun livello automatico |
| **ANGLE** | L'angolo di controllo degli stick — si livella automaticamente quando viene rilasciato |
| **HORIZON** | ANGLE vicino al centro, ACRO alla massima deflessione |

ACRO è consigliato a piloti esperti. ANGLE è ottimo per i primi voli e per il volo in termica.

## Controlli specifici degli ornitotteri

### Modalità INDEPENDENT

Quando la modalità INDEPENDENT è attiva, ciascun servo dell'ala risponde in modo indipendente:
- **Levetta sinistra** → servi dell'ala sinistra
- **Levetta destra** → servi dell'ala destra
- Consente lo sbattimento asimmetrico per manovre aggressive

### Modalità GLIDE

La modalità GLIDE blocca entrambe le ali in posizione orizzontale. L'ornitottero diventa un aliante:
- **L'acceleratore** non ha alcun effetto sulla posizione dell'ala
- **Beccheggio/Roll/Imbardata** influenzano ancora le superfici di controllo della coda (se in dotazione)

### Cambio profilo

La commutazione del profilo in volo tramite il canale AUX consente di modificare i parametri PID/ONDAS durante il volo:
- **Profilo 1**: impostazioni di crociera standard
- **Profilo 2**: impostazioni ad alta agilità
- **Profilo 3**: impostazioni di efficienza/planata

## Tariffe

Configura le tariffe nella scheda **PID Tuning**. Per gli ornitotteri, iniziare con ritmi conservativi. — La dinamica del battito d'ali amplifica gli input di controllo:
- Tasso RC: 0,80–1,00
- Tasso super: 0,60–0,70
-Expo: 0,20–0,40