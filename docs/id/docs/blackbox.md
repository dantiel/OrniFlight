# Pencatatan Kotak Hitam

Blackbox mencatat data penerbangan untuk analisis pasca-penerbangan, penyetelan, dan debugging. OrniFlight mendukung logging ke chip flash onboard atau perangkat OpenLog eksternal.

## Apa yang Dicatat

- **Gyro** — kecepatan sudut 3 sumbu mentah dan terfilter
- **Akselerometer** — akselerasi 3 sumbu
- **PID Output** — kontribusi P, I, D, F per sumbu
- **ONDAS** — Cadence, Ferocity P/D, dan parameter khusus pengepakkan lainnya
- **Perintah RC** — tetap posisi setelah tarif/pameran
- **Output Servo** keluaran akhir — ke setiap saluran servo
- **Baterai** tegangan dan arus — per iterasi
- **GPS** — posisi, kecepatan, ketinggian (bila tersedia)

## Pengaturan

### Flash Terpasang (OMNIBUSF4)

Zzz34zzz menyertakan flash onboard 16MB untuk logging Blackbox. Aktifkan di Konfigurator:

1. **Kotak Hitam** tab → Setel `Blackbox logging device` ke `Onboard flash`
2. Tetapkan tingkat logging (direkomendasikan: `1/N` dengan N=2-4 untuk target F4)
3. Tetapkan saklar untuk memulai/menghentikan pencatatan

### Zzz36zzz eksternal

Hubungkan OpenLog ke pin UART TX gratis:

1. **Ports** tab → Setel UART ke `Blackbox logging` pada 115200 baud
2. Hubungkan OpenLog: FC TX → OpenLog RX, ditambah 5V/GND

## Alat Analisis

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — penampil log berbasis web
- `blackbox_decode` — konversikan ke CSV untuk analisis khusus

## ONDAS-Khusus

Blackbox sangat penting untuk menyetel parameter ONDAS. Data ONDAS yang dicatat meliputi:
- waktu jendela modulasi `ondas_cadence_phase` —
- komponen dorong asimetris `ondas_ferocity_p` / `ondas_ferocity_d` —
- `ondas_balance` — keseimbangan sayap kiri/kanan
- Output per-servo pada setiap iterasi

Hal ini memungkinkan analisis yang tepat terhadap mekanika kepakan dan koreksi asimetri sayap.