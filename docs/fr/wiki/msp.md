# Protocole MSP

> *MultiWii Serial Protocol — comment le configurateur communique avec OrniFlight.*

## Aperçu

OrniFlight étend le Betaflight MSP avec des messages spécifiques aux ornithoptères. La spécification faisant autorité se trouve dans le référentiel du micrologiciel à l'adresse `src/main/msp/`.

**Version actuelle :** apiVersion 1.46 (OrniFlight v0.4.6)

## Messages clés

### MSP_PID_ADVANCED (112 / 0x70)

Le message principal de réglage de ONDAS. Passé de 48 octets (hérité) à 87 octets (1,46).

| Version API | Taille | Nouveau contenu |
|-------------|------|-------------|
| 1.33 | 48 | Héritage PID avancé |
| 1.42 | 59 | + itermRelaxCutoff, 10 gains ONDAS v2 |
| 1.43 | 71 | + servo_mount_angle[4], phase_shift[4], prescience, espelho, saudade, ssff |
| 1,44 | 75 | + servo_speed, max_amplitude, flap_magnitude, wing_origin_offset[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1,46 | 87 | + profile_index, ferocity_downStroke, ferocity_upStroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

Configuration du servo avec 4 octets de fin ONDAS : glide_deg + triplet ONDAS v1.

## Compatibilité descendante

Toutes les versions de API sont rétrocompatibles. Un expéditeur de 48 octets communique avec un destinataire de 1,46 —, les champs supplémentaires sont par défaut des valeurs raisonnables.

## Format de fil

Toutes les valeurs multi-octets sont en petit-boutiste. Valeurs signées stockées sous `value + 128` sur le fil. Les valeurs de gain non signées (0–100) sont directes. Longueurs de tableau précédées du nombre u8.

---

*Voir `docs/MSP_FIRMWARE_INTERFACE.md` dans le référentiel du micrologiciel pour les spécifications complètes.*