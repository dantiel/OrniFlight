# Pemantauan Baterai

OrniFlight memonitor tegangan baterai utama melalui ADC (Analog-to-Digital Converter). Hal ini mengaktifkan peringatan baterai lemah melalui bel, status LED, dan pola strip LED.

## Fitur

- Deteksi otomatis jumlah sel saat terhubung (berdasarkan tegangan sel min/maks)
- Peringatan baterai lemah dengan ambang batas yang dapat dikonfigurasi
- Penginderaan arus untuk konsumsi mAh (jika didukung oleh FC)
- Tegangan ditampilkan di OSD dan ditransmisikan melalui telemetri

## Target yang Didukung

Semua pengontrol penerbangan yang didukung (OMNIBUSF4, TINYFISH) menyertakan pemantauan VBAT melalui pembagi tegangan.

## Koneksi

**SELALU PERIKSA POLARITAS.** Ukur voltase yang diharapkan sebelum menghubungkan. Tegangan yang salah atau polaritas terbalik akan merusak pengontrol penerbangan Anda.

### OMNIBUSF4

Hubungkan baterai utama ke bantalan VBAT. Pembagi tegangan onboard menangani hingga 6S secara langsung.

### TINYFISH

VBAT disalurkan melalui input daya papan — tidak diperlukan koneksi terpisah.

## CLI Pengaturan

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Keamanan

baterai LiPo tidak boleh habis di bawah 3,5V per sel saat beban. Ambang batas OrniFlight yang dapat dikonfigurasi membantu memastikan pengoperasian yang aman dan umur baterai yang panjang.