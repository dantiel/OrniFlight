# Memulai

Selamat datang di OrniFlight! Panduan ini memandu Anda melalui pengaturan awal pengontrol penerbangan ornithopter Anda.

## Yang Anda Butuhkan

- **konfigurator OrniFlight** — unduh dari [orniflight.org](https://orniflight.org)
- **kabel USB** — untuk menghubungkan pengontrol penerbangan ke komputer
- **Ornithopter** dengan:
  - Pengontrol penerbangan yang didukung (OMNIBUSF4, TINYFISH)
  - Servo untuk penggerak sayap
  - Penerima terikat ke pemancar Anda
  - Baterai (2S–4S LiPo)

## Mulai Cepat

### 1. Flash Firmware

1. Buka **konfigurator OrniFlight**
2. Buka tab **Firmware Flasher**
3. Pilih target papan Anda (OMNIBUSF4 atau TINYFISH)
4. Pilih versi stabil terbaru
5. Klik **Muat Firmware** lalu **Flash Firmware**

### 2. Konfigurasi Awal

Setelah mem-flash, Configurator akan meminta Anda untuk menerapkan default khusus. **Selalu terima.**

### 3. Pengaturan Penerima

1. Buka tab **Ports** →, atur UART yang benar ke `Serial RX`
2. Buka tab **Konfigurasi** → pilih protokol penerima Anda (CRSF, SBUS, dll.)
3. Buka tab **Receiver** → verifikasi gerakan stick sesuai saluran yang diharapkan
4. Tetapkan titik akhir saluran: 1000–2000 dengan 1500 pusat

### 4. Pengaturan Servo

1. Buka tab **Servo**
2. Pastikan pemetaan servo cocok dengan konfigurasi sayap ornithopter Anda
3. Uji arah servo — terbalik jika diperlukan
4. Atur posisi tengah (sayap horizontal = 1500)

### 5. Pengaturan Mode

1. Buka tab **Mode**
2. Tetapkan ARM ke sakelar AUX
3. Tetapkan mode penerbangan (ANGLE / ACRO / HORIZON) sesuai keinginan
4. Tetapkan INDEPENDENT dan GLIDE ke sakelar cadangan
5. Konfigurasikan BEEPER untuk pencarian model yang hilang

### 6. Penerbangan Pertama

1. **Putuskan sambungan sayap untuk pengujian bangku**
2. Mempersenjatai dan memverifikasi arah gerakan servo
3. Periksa respon throttle
4. Untuk penerbangan pertama yang sebenarnya: gunakan mode ANGLE, tarif rendah
5. Arahkan kursor setinggi mata, rapikan sesuai kebutuhan

## Langkah Selanjutnya

- [Pengaturan Dasar](basic_setup.html) — panduan konfigurasi terperinci
- [ONDAS Tuning](../../tutorials/ondas_tuning.html) — tune mengepakkan dinamika
- [PID Tuning](../../tutorials/tuning.html) — menyesuaikan karakteristik penerbangan