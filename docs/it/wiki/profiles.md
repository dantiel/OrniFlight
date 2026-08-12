# Profili di volo

> *4 slot di accordatura indipendenti, commutabili in volo.*

##Concetto

OrniFlight memorizza 4 strutture `ornithopterProfile_t` complete —, ciascuna contenente tutti i 19 ONDAS e i parametri di dinamica dell'ala. Una modalità BOX (`BOXORNITHOPTERPROFILE`, permanentId 52) seleziona il profilo attivo tramite un interruttore RC a 2 posizioni mappato su 4 slot (0–3).

## Perché i profili?

Regimi di volo diversi richiedono una messa a punto diversa:

| Profilo | Caso d'uso | Cadence | Ferocity | Note |
|---------|----------|---------|----------|-------|
| 0| **Crociera** | Metà (50) | Basso (30) | Volo in avanti efficiente |
| 1| **Acrobazia** | Basso (20) | Alto (80) | Massima autorità |
| 2| **Passa il mouse/tarda** | Alto (70) | Metà (50) | Stabilità rispetto alla velocità |
| 3| **Scivola** | Metà (50) | Basso (10) | Intervento minimo |

## Cosa c'è in un profilo

Tutti i 19 campi di `ornithopterProfile_t`:

- **Geometria di planata**: glide_angle
- **ONDAS v2 (10)**: cadenza, ferocia_d/p/roll/yaw, equilibrio, warp, warp_yaw, ancora, risonanza
- **Phase 2 (4)**: prescienza, espelho, saudade, ssff
- **Forma d'onda (2)**: ferocity_downstroke, ferocity_upstroke
- **Aeroelastico (2)**: aeroelastic_glide_coefficient, aeroelastic_flap_coefficient

## Che cosa è globale (non per profilo)

- Canale di frequenza (un canale RC, funziona sia in INDEPENDENT che GLIDE)
- Angoli di montaggio del servo
- Sfasamenti battenti
- geometria GralhaAzul (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Queste sono costanti fisiche della cellula — e non cambiano con il regime di volo.

## Cambio in volo

1. Assegnare un interruttore a 2 o 3 posizioni a un canale di riserva
2. Nella scheda Modalità Configuratore, mappa l'intervallo su `ORNITHOPTER PROFILE`
3. Ciascuna posizione dell'interruttore seleziona uno dei 4 slot
4. Il menu a discesa del profilo del Configuratore modifica lo slot *attualmente selezionato* tramite MSP

---

*Vedi `src/main/flight/ornithopter_profile.h` per la definizione della struttura.*