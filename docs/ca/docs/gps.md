#GPS

GPS permet el manteniment de la posició, el retorn a casa i la navegació basada en telemetria per al vostre ornitòpter. Les funcions GPS de OrniFlight són funcionals, però es consideren — experimentals que volen sempre dins de la línia de visió visual.

## Protocols compatibles

- **UBLOX** (recomanat) — Protocol binari UBlox, eficient i fiable
- **NMEA** — Protocol estàndard basat en text

## Maquinari

- Mòduls BN-880, BN-220 o similars UBlox M8N GPS+Brúixola
- Connecteu-vos: TX/RX a un UART gratuït, més 5V/GND
- Munteu GPS lluny dels cables d'alimentació i cables de servo per minimitzar les interferències
- La brúixola/magnetòmetre ha d'estar lluny de fonts magnètiques (cables d'alimentació, servos)

## Configuració

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Assigneu el port sèrie a GPS a la pestanya **Ports** (115200 bauds per defecte per a UBlox)
2. Activa la funció GPS
3. Estableix el proveïdor
4. Desa i reinicia

## OSD Elements

Les dades de GPS que es mostren a OSD inclouen:
- Recompte de satèl·lit i tipus de correcció
- Coordenades GPS (lat/lon)
- Velocitat en marxa
- Altitud (GPS)
- Distància des de casa
- Fletxa de direcció a casa

## Consideracions sobre l'ornitòpter

- L'antena GPS ha de tenir una visió del cel clar. La ubicació de muntatge — és crítica amb les ales batejants
- La penalització de pes és significativa en ornitòpters petits
- RTH assistit per GPS (Tornar a la pàgina d'inici) requereix una ajustada acurada dels valors de PID de navegació per a la dinàmica de vol aleteig