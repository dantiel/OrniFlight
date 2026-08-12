# Darba sākšana

Laipni lūdzam OrniFlight! Šajā rokasgrāmatā ir sniegta informācija par ornitoptera lidojuma kontroliera sākotnējo iestatīšanu.

## Kas jums nepieciešams

- **OrniFlight Configurator** — lejupielāde no [orniflight.org](https://orniflight.org)
- **USB kabelis** —, lai savienotu lidojuma kontrolieri ar datoru
- **Ornitopteris** ar:
  - Atbalstītais lidojuma kontrolieris (OMNIBUSF4, TINYFISH)
  - Servo spārnu iedarbināšanai
  - Uztvērējs ir saistīts ar jūsu raidītāju
  - Akumulators (2S–4S LiPo)

## Īsā sākšana

### 1. Flash programmaparatūra

1. Atveriet **OrniFlight Configurator**
2. Atveriet cilni **Firmware Flasher**
3. Atlasiet tāfeles mērķi (OMNIBUSF4 vai TINYFISH)
4. Izvēlieties jaunāko stabilo versiju
5. Noklikšķiniet uz **Ielādēt programmaparatūru** un pēc tam — uz **Flash programmaparatūru**.

### 2. Sākotnējā konfigurācija

Pēc mirgošanas konfigurators liks jums piemērot pielāgotus noklusējuma iestatījumus. **Vienmēr pieņemt.**

### 3. Uztvērēja iestatīšana

1. Atveriet cilni **Porti**. → iestatiet pareizo UART uz `Serial RX`
2. Atveriet cilni **Konfigurācija** → atlasiet uztvērēja protokolu (CRSF, SBUS utt.)
3. Atveriet cilni **Uztvērējs** → — pārbaudiet, vai nūjas kustības atbilst gaidītajiem kanāliem.
4. Iestatiet kanāla galapunktus: 1000–2000 ar 1500 centru

### 4. Servo iestatīšana

1. Atveriet cilni **Servos**
2. Pārbaudiet, vai servo kartēšana atbilst jūsu ornitoptera spārnu konfigurācijai
3. Ja nepieciešams, pārbaudiet servo virzienu — atpakaļgaitā
4. Iestatiet vidējo pozīciju (spārni horizontāli = 1500)

### 5. Režīmu iestatīšana

1. Atveriet cilni **Režīmi**
2. Piešķiriet ARM slēdzim AUX
3. Piešķiriet lidojuma režīmus (ANGLE / ACRO / HORIZON) pēc vēlēšanās
4. Piešķiriet INDEPENDENT un GLIDE rezerves slēdžiem
5. Konfigurējiet BEEPER, lai noteiktu pazaudētā modeļa atrašanās vietu

### 6. Pirmais lidojums

1. **Atvienojiet spārnu savienojumu, lai veiktu testēšanu stendā**
2. Nostipriniet un pārbaudiet servomehānisma kustības virzienu
3. Pārbaudiet droseles reakciju
4. Pirmajam faktiskajam lidojumam: izmantojiet ANGLE režīmu, zemas cenas
5. Virziet acu līmenī, sagrieziet pēc vajadzības

## Nākamie soļi

- [Pamata iestatīšana](basic_setup.html) — detalizēts konfigurācijas apraksts
- [ONDAS Tuning](../../tutorials/ondas_tuning.html) — melodijas viļņošanās dinamika
- [PID Tuning](../../tutorials/tuning.html) — pielāgot lidojuma raksturlielumus