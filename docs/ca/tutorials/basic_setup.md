# Configuració bàsica

> *Configura el teu ornitòpter per al primer vol.*

## Llista de comprovació prèvia al vol

Abans de res:

- [ ] El controlador de vol va parpellejar amb OrniFlight
- [ ] Receptor vinculat al transmissor
- [ ] Servos connectats per corregir les sortides PWM
- [ ] Bateria connectada (ales assegurades!)

## Configuració del receptor

### CRSF (recomanat)

1. **Pestaña Ports**: defineix UART (p. ex., UART1) a "Serial RX"
2. **Pestanya de configuració**: Mode receptor = "Receptor basat en sèrie", Proveïdor = "CRSF"
3. Cicle d'engegada, comproveu que les entrades del canal es mouen a la pestanya Receptor

### SBUS / Altres

El mateix procés — seleccioneu el protocol adequat a la pestanya Configuració.

## Mapes de servo

A la pestanya **Servos**:

| Servo | Funció | Tarifa predeterminada |
|-------|-----------|--------------|
| Servo 0 | Ala esquerra | 250 Hz |
| Servo 1 | Ala dreta | 250 Hz |
| Servo 2 | Cresta/Timón | 50 Hz |

Ajusteu el mínim/màx/mig perquè coincideixi amb el rang del vostre servo. Prova amb "Anul·lació" per verificar la direcció.

## Selecció del mode de vol

A la pestanya **Modes**:

1. **ARM**: assigna a un interruptor (seguretat!)
2. **ORNITHOPTER INDEPENDENT** o **ORNITHOPTER GLIDE**: trieu el vostre mode de vol principal
3. **ORNITHOPTER PROFILE**: assignació de — opcional per al canvi de perfil durant el vol

## ONDAS Primera sintonia

Aneu a la **subpestanya → ONDAS avançada**:

1. **Zzz10zzz Guany**: Comença a 50 (mitjans). Aquest és el paràmetre més important.
2. **Guany Ferocity D**: comença a les 30. Aquesta és la teva estabilització principal.
3. **Zzz9zzz Guany**: Comenceu a les 20 per al rodet/cau, 0 per a la guiada.
4. **Balance Guany**: 0 (centrat).

Connecteu una bateria, **fixeu l'ornitòpter fermament** i ARM. Observeu el moviment del servo —, ha de ser un aleteig suau i sinusoïdal.

## Primer vol

1. Comença amb un suau llançament al vent
2. Utilitzeu el mode GLIDE per a una sensació d'elevació natural
3. Utilitzeu el mode INDEPENDENT quan vulgueu un control directe de freqüència
4. Aterrar, ajustar ONDAS, repetir

---

*Següent: [ONDAS Guia d'afinació](ondas_tuning.html) →*