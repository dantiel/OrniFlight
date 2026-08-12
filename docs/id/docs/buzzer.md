#buzzer

OrniFlight mendukung bel aktif untuk indikasi status yang dapat didengar dan lokasi model yang hilang.

## Fungsi

- **Lengan/Lucuti** — nada berbeda
- **Baterai Lemah** — berbunyi bip peringatan berulang
- **Failsafe** pola — SOS
- **Model Hilang** — berbunyi bip terus menerus melalui sakelar
- **GPS Fix** nada konfirmasi — pada kunci satelit
- **Kalibrasi** pola bip — selama kalibrasi gyro/accel
- **RX Sinyal Hilang** peringatan — ketika koneksi penerima terputus

## Perangkat keras

- Hubungkan bel aktif 5V (BUKAN piezo pasif) ke bantalan **BUZZ-** dan **BUZZ+**
- Buzzer digerakkan oleh transistor pada FC — tidak diperlukan driver eksternal untuk buzzer standar

## CLI Pengaturan

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Keamanan Ornitopter

Pager sangat berguna khususnya bagi ornithopter berukuran besar yang mungkin hinggap di rerumputan tinggi atau dedaunan. Konfigurasikan mode BEEPER pada sakelar sesaat untuk aktivasi cepat bila diperlukan.