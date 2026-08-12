# Prvi koraci

Dobrodošli u OrniFlight! Ovaj vodič vodi vas kroz početno postavljanje kontrolera leta vašeg ornitoptera.

## Što trebate

- **OrniFlight konfigurator** — preuzimanje s [orniflight.org](https://orniflight.org)
- **USB kabel** — za spajanje kontrolera leta na računalo
- **Ornithopter** sa:
  - Podržani kontroler leta (OMNIBUSF4, TINYFISH)
  - Servo za aktiviranje krila
  - Prijemnik povezan s vašim odašiljačem
  - Baterija (2S–4S LiPo)

## Brzi početak

### 1. Flash firmware

1. Otvorite **OrniFlight konfigurator**
2. Idite na karticu **Firmware Flasher**
3. Odaberite ciljnu ploču (OMNIBUSF4 ili TINYFISH)
4. Odaberite najnoviju stabilnu verziju
5. Kliknite **Load Firmware** zatim **Flash Firmware**

### 2. Početna konfiguracija

Nakon treptanja, konfigurator će od vas tražiti da primijenite prilagođene zadane postavke. **Uvijek prihvatiti.**

### 3. Postavljanje prijemnika

1. Idite na karticu **Portovi** → postavite ispravan UART na `Serial RX`
2. Idite na karticu **Konfiguracija** → odaberite svoj protokol prijemnika (CRSF, SBUS, itd.)
3. Idite na karticu **Prijemnik** → potvrdite da pokreti štapa odgovaraju očekivanim kanalima
4. Postavite krajnje točke kanala: 1000–2000 sa 1500 središtem

### 4. Servo podešavanje

1. Idite na karticu **Servos**
2. Provjerite odgovara li servo mapiranje konfiguraciji krila vašeg ornitoptera
3. Testirajte smjer servo — obrnuti ako je potrebno
4. Postavite središnji položaj (krila vodoravno = 1500)

### 5. Postavljanje načina

1. Idite na karticu **Načini**
2. Dodijelite ARM prekidaču AUX
3. Dodijelite načine letenja (ANGLE / ACRO / HORIZON) po želji
4. Dodijelite INDEPENDENT i GLIDE rezervnim prekidačima
5. Konfigurirajte BEEPER za lociranje izgubljenog modela

### 6. Prvi let

1. **Odspojite polugu krila za testiranje na stolu**
2. Aktivirajte i provjerite smjer kretanja servoagregata
3. Provjerite odziv leptira za gas
4. Za prvi stvarni let: koristite način ANGLE, niske stope
5. Lebdite u razini očiju, podrežite po potrebi

## Sljedeći koraci

- [Osnovno postavljanje](basic_setup.html) — detaljan vodič za konfiguraciju
- [ONDAS ugađanje](../../tutorials/ondas_tuning.html) — podešavanje dinamike lepršanja
- [PID podešavanje](../../tutorials/tuning.html) — prilagođava karakteristike leta