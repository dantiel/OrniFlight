# Per iniziare

Benvenuto su OrniFlight! Questa guida ti guida attraverso la configurazione iniziale del tuo controller di volo per ornitotteri.

## Cosa ti serve

- **Configuratore OrniFlight** — scaricabile da [orniflight.org](https://orniflight.org)
- **cavo USB** — per collegare il controller di volo al computer
- **Ornitottero** con:
  - Controller di volo supportato (OMNIBUSF4, TINYFISH)
  - Servi per l'azionamento delle ali
  - Ricevitore collegato al trasmettitore
  - Batteria (2S–4S LiPo)

## Avvio rapido

### 1. Firmware flash

1. Apri **OrniFlight Configuratore**
2. Vai alla scheda **Firmware Flasher**
3. Seleziona il target della tua scheda (OMNIBUSF4 o TINYFISH)
4. Scegli l'ultima versione stabile
5. Fare clic su **Carica firmware**, quindi su **Flash firmware**

### 2. Configurazione iniziale

Dopo il flashing, il Configuratore ti chiederà di applicare le impostazioni predefinite personalizzate. **Accetta sempre.**

### 3. Configurazione del ricevitore

1. Vai alla scheda **Porte** → imposta il valore UART corretto su `Serial RX`
2. Vai alla scheda **Configurazione** → seleziona il protocollo del tuo ricevitore (CRSF, SBUS, ecc.)
3. Vai alla scheda **Ricevitore** → verifica che i movimenti dello stick corrispondano ai canali previsti
4. Imposta gli endpoint del canale: 1000–2000 con 1500 centro

### 4. Configurazione dei servi

1. Vai alla scheda **Servi**
2. Verifica che la mappatura dei servi corrisponda alla configurazione delle ali del tuo ornitottero
3. Se necessario, testare la direzione del servo — inversa
4. Impostare la posizione centrale (ante orizzontali = 1500)

### 5. Impostazione delle modalità

1. Vai alla scheda **Modalità**
2. Assegna ARM a un interruttore AUX
3. Assegna le modalità di volo (ANGLE / ACRO / HORIZON) come desideri
4. Assegna INDEPENDENT e GLIDE agli interruttori di riserva
5. Configurare BEEPER per la localizzazione del modello smarrito

### 6. Primo volo

1. **Scollegare il collegamento dell'ala per testare al banco**
2. Armare e verificare la direzione del movimento del servo
3. Controllare la risposta dell'acceleratore
4. Per il primo volo effettivo: utilizza la modalità ANGLE, tariffe basse
5. Passa il mouse all'altezza degli occhi, ritaglia secondo necessità

## Passaggi successivi

- [Configurazione di base](basic_setup.html) procedura dettagliata per la configurazione di —
- [Accordatura ONDAS](../../tutorials/ondas_tuning.html) — sintonizza la dinamica del battito d'ali
- [Zzz38zzz Tuning](../../tutorials/tuning.html) — regola le caratteristiche di volo