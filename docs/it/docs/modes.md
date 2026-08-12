# Modalità di volo

Le modalità vengono attivate tramite gli interruttori AUX sul trasmettitore. Ciascuna modalità può essere assegnata a uno specifico intervallo di canali AUX nella scheda **Modalità** del Configuratore OrniFlight.

## Modalità standard

| Modalità | Funzione |
|------|----------|
| **ARM** | Abilita il controllo di volo (motori/servi attivi) |
| **ANGLE** | L'imbarcazione — con livellamento automatico ritorna al livello quando i bastoncini sono centrati |
| **HORIZON** | Modalità angolare — ibrida vicino al centro, acro con la levetta massima |
| **ACRO** | Predefinito — nessun livello automatico, controllo puro della velocità |
| **AIRMODE** | Mantiene attivo il loop PID a zero accelerazione per la massima autorità |

## Modalità specifiche di OrniFlight

| ID | Modalità | Funzione |
|----|------|----------|
| 50| **INDEPENDENT** | Controllo indipendente delle ali — ciascuna ala risponde al proprio canale servo |
| 51| **GLIDE** | Modalità planata — ali bloccate in posizione orizzontale per il volo in volo |
| 52| **PROFILE** | Selezione del profilo di volo — cambia tra 3 profili PID/ONDAS |

## Modalità di utilità

| Modalità | Funzione |
|------|----------|
| **BEEPER** | Attiva il cicalino per la localizzazione dell'aereo smarrito |
| **BLACKBOX** | Avvia/arresta la registrazione Blackbox |
| **FAILSAFE** | Attivare manualmente lo stadio 2 del failsafe (interruttore antipanico) |
| **OSD** | Attiva/disattiva la visualizzazione OSD |
| **TELEMETRY** | Abilita/disabilita l'uscita telemetrica |

## Note sugli ornitotteri

- La modalità **INDEPENDENT** è unica per OrniFlight — e consente la mappatura servo per ala per la spinta asimmetrica e il controllo differenziale dell'ala
- La modalità **GLIDE** mantiene le ali in posizione neutra, utile per il volo in termica e la discesa ad alta efficienza energetica
- La commutazione **PROFILE** consente la modifica dei parametri ONDAS in volo per condizioni di volo variabili (ad esempio, crociera o manovra aggressiva)