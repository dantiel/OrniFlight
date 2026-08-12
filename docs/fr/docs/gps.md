#GPS

GPS permet le maintien de la position, le retour à la maison et la navigation basée sur la télémétrie pour votre ornithoptère. Les fonctionnalités GPS de OrniFlight sont fonctionnelles mais considérées comme expérimentales, — vole toujours à portée de vue.

## Protocoles pris en charge

- **UBLOX** (recommandé) — Protocole binaire UBlox, efficace et fiable
- **NMEA** — Protocole standard basé sur du texte

## Matériel

- BN-880, BN-220 ou modules UBlox M8N GPS+Compass similaires
- Connectez : TX/RX à un UART gratuit, plus 5V/GND
- Montez le GPS loin des fils d'alimentation et des câbles de servo pour minimiser les interférences
- La boussole/magnétomètre doit être éloignée des sources magnétiques (fils d'alimentation, servos)

##Configuration

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Attribuez le port série à GPS dans l'onglet **Ports** (115 200 bauds par défaut pour UBlox)
2. Activez la fonctionnalité GPS
3. Définir le fournisseur
4. Enregistrez et redémarrez

## OSD Éléments

Les données GPS affichées dans OSD incluent :
- Nombre de satellites et type de correctif
- coordonnées GPS (lat/lon)
- Vitesse au sol
- Altitude (GPS)
- Distance du domicile
- Flèche de direction vers la maison

## Considérations sur les ornithoptères

- L'antenne GPS doit avoir une vue dégagée sur le ciel. L'emplacement de montage du — est critique avec les ailes battantes.
- La pénalité de poids est importante sur les petits ornithoptères
- Zzz29zzz assisté par GPS (Retour à la maison) nécessite un réglage minutieux des valeurs de navigation PID pour la dynamique de vol battu