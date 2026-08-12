# GPS

GPS memungkinkan navigasi posisi ditahan, kembali ke rumah, dan berbasis telemetri untuk ornithopter Anda. Fitur GPS di OrniFlight berfungsi tetapi dianggap eksperimental — selalu terbang dalam garis pandang visual.

## Protokol yang Didukung

- **UBLOX** (disarankan) — protokol biner UBlox, efisien dan andal
- **NMEA** — Protokol standar berbasis teks

## Perangkat keras

- BN-880, BN-220, atau modul UBlox M8N GPS+Kompas serupa
- Hubungkan: TX/RX ke UART gratis, plus 5V/GND
- Pasang GPS jauh dari kabel listrik dan kabel servo untuk meminimalkan interferensi
- Kompas/magnetometer harus jauh dari sumber magnet (kabel listrik, servo)

## Konfigurasi

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Tetapkan port serial ke GPS di tab **Ports** (default 115200 baud untuk UBlox)
2. Aktifkan fitur GPS
3. Tetapkan penyedia
4. Simpan dan reboot

## OSD Elemen

Data GPS yang ditampilkan di OSD meliputi:
- Jumlah satelit dan jenis perbaikan
- koordinat GPS (lintang/bujur)
- Kecepatan gerak
- Ketinggian (GPS)
- Jarak dari rumah
- Panah arah rumah

## Pertimbangan Ornithopter

- Antena GPS harus memiliki pemandangan langit cerah — lokasi pemasangan sangat penting dengan sayap mengepak
- Hukuman berat sangat signifikan pada ornithopter kecil
- GPS berbantuan RTH (Kembali ke Beranda) memerlukan penyetelan nilai navigasi PID yang cermat untuk mengepakkan dinamika penerbangan