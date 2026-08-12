#RSSI

RSSI (Indikator Kekuatan Sinyal yang Diterima) menunjukkan kualitas tautan radio Anda. OrniFlight dapat mengambil sumber RSSI dari input analog, data penerima serial, atau protokol RSSI.

## RSSI Sumber

| Sumber | Koneksi | Konfigurasi |
|--------|-----------|---------------|
| **Protokol Serial** | Tidak ada (melalui kabel serial RX) | CRSF, GHST — otomatis |
| **AUX Saluran** | Tidak ada (TX mengirimkan RSSI sebagai saluran) | `set rssi_channel = 8` |
| **Analog ADC** | RSSI pad on FC → Penerima RSSI keluar | `set rssi_adc_channel = 1` |

## Konfigurasi

### Serial RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI ditransmisikan secara otomatis melalui protokol serial — tidak memerlukan kabel tambahan.

### Analog RSSI

Hubungkan receiver RSSI output → RSSI pad pada pengontrol penerbangan:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Saluran RSSI

Konfigurasikan pemancar Anda untuk mengirim RSSI pada saluran tertentu, lalu:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Tampilan

RSSI ditampilkan di OSD dan dapat ditransmisikan melalui telemetri ke radio Anda. Konfigurasikan ambang peringatan:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Jangkauan Ornithopter

Untuk ornithopter, RSSI sangat penting — mengepakkan sayap menciptakan pola interferensi RF yang dinamis. Pantau RSSI selama uji penerbangan awal untuk memverifikasi kinerja tautan yang andal di semua posisi sayap.