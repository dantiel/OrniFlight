# Perangkat Keras yang Didukung

OrniFlight berjalan pada pengontrol penerbangan komoditas STM32F3/F4/F7. Garis dasarnya adalah **STM32F3** —, target F3 apa pun dengan pin pengatur waktu berkemampuan servo akan terbang.

## Pengendali Penerbangan

| Papan | MCU | IMU | Kilatan | Penerima | Status |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (terintegrasi) | ✅ Utama |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Didukung |

### TINYFISH — Target OrniFlight Paling Ringan

Didesain oleh fishpepper, TINYFISH adalah pengontrol penerbangan ornithopter yang ideal: kelas bulu, berbasis F3, dan membawa **penerima FrSky D8 terintegrasi** di dalam pesawat. Tidak ada RX eksternal, tidak ada kabel tambahan — hanya daya, servo, dan terbang.

- **MCU**: STM32F303CCT6 @ 72MHz
- **Gyro**: MPU6000 (SPI, berkemampuan 8 kHz)
- **Flash**: 256 KB pada chip
- **RAM**: 40 KB
- **Penerima**: Zzz36zzz D8 terintegrasi (SBUS dirutekan secara internal ke UART2)
- **UART**: VCP + 2 UART perangkat keras (UART1 gratis untuk add-on GPS/CRSF)
- **Input**: 2-4S LiPo (daya servo langsung)
- **Berat**: ~2,5 gram

TINYFISH membuktikan bahwa kontrol mengepakkan transenden tidak memerlukan F7. Zzz73zzz menjalankan pipa ONDAS penuh — 10 saluran modulasi, sayap trapesium ODE, 4 profil penerbangan — dalam 256 KB.

### OMNIBUSF4 — Pekerja keras yang Dapat Diakses

Target F4 klasik. Murah, ada di mana-mana, berfitur lengkap dengan OSD dan flash SPI yang cukup untuk logging Blackbox. Tujuan untuk pengembangan dan pembangunan yang lebih besar.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Gyro**: MPU6000 (SPI, berkemampuan 8 kHz)
- **Flash**: 1 MB pada chip + 16 MB SPI (Kotak Hitam)
- **RAM**: 192 KB
- **OSD**: AT7456E (kompatibel dengan MAX7456)
- **UART**: VCP + 5 UART perangkat keras
- **Barometer**: BMP280 (beberapa varian)
- **Masukan**: 2-6S LiPo

---

## Anatomi Ornitopter

### Servo Sayap

kontrol OrniFlight mengepak melalui servo PWM. Spesifikasi utama:

| Parameter | Rentang Khas |
|-----------|--------------|
| Lebar Pulsa | 500–2500 µs |
| Pusat | 1500 µs |
| Frekuensi | 50–330 Hz |
| Sudut Pukulan | ±15–45° |

Untuk ornithopter berperforma tinggi, disarankan menggunakan servo digital dengan kecepatan pembaruan 330 Hz. Servo analog bekerja pada 50 Hz tetapi memiliki presisi lebih rendah.

### Penerima

Protokol penerima serial apa pun didukung. CRSF (TBS Crossfire / ExpressLRS) direkomendasikan untuk:
- Latensi rendah (penting untuk kontrol mengepakkan)
- Telemetri bawaan
- RSSI melalui protokol (tidak ada kabel tambahan)

### Baterai

- **2S (7.4V)**: Ornithopter kecil, bertenaga servo secara langsung
- **3S (11.1V)**: Ornithopter sedang, BEC diperlukan untuk servo
- **4S (14.8V)**: Ornithopter besar, disarankan BEC eksternal

---

## Periferal yang Didukung

| Periferal | Melalui | Catatan |
|-----------|-----|-------|
| GPS | UART | UBlox M8N atau yang kompatibel |
| VTX | UART TX | Gelandangan, SmartAudio |
| Kamera | — | Kamera FPV analog apa saja |
| Bel | BUZZ pad | Bel 5V aktif |
| LED Strip | LED pad | WS2812 / SK6812 |
| OpenLog | UART TX | Pencatatan kotak hitam |
| Bluetooth | UART | MSP passthrough untuk penyetelan seluler |

---

## Target Masa Depan

OrniFlight bertujuan untuk mendukung target STM32F4/F7 tambahan di mana sumber daya UART dan timer yang memadai tersedia untuk kontrol servo yang mengepakkan. Kontribusi diterima.