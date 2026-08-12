#Telemetri

Telemetri mengirimkan data penerbangan dari OrniFlight ke pemancar radio Anda — tegangan baterai, arus, RSSI, koordinat GPS, ketinggian, dan banyak lagi.

## Protokol yang Didukung

| Protokol | Sistem Radio | Jumlah Kawat |
|----------|-------------|------------|
| **CRSF** | Baku Tembak / Pelacak / ELRS | Terintegrasi dengan RX (dua arah) |
| **SmartPort** | FrSky | 1 kawat (pin TX) |
| **HoTT** | Graupner | 1 kawat (TX+TZ) |
| **IBUS** | FlySky | 1 kawat (sensor TX) |
| **LTM** | Telemetri Cahaya (MWP) | 1 kawat (TX) |

## Konfigurasi

1. Di Configurator → **Ports**: atur pin UART TX ke protokol telemetri yang sesuai
2. Aktifkan fitur telemetri: `feature TELEMETRY`
3. Konfigurasikan inversi telemetri jika diperlukan

Untuk **CRSF**, telemetri ditangani secara otomatis — tidak memerlukan port terpisah.

## SmartPort (FrSky)

SmartPort memerlukan inversi sinyal pada prosesor F4. Baik:
- Gunakan pengontrol penerbangan dengan inverter bawaan
- Gunakan SoftSerial dengan `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Data Telemetri

OrniFlight mentransmisikan:
- tegangan VBAT (baterai utama)
- Penarikan saat ini / mAh yang dikonsumsi
- RSSI (kekuatan sinyal)
- Mode penerbangan / status lengan
- koordinat GPS (jika dilengkapi)
- Ketinggian / vario (jika barometer)
- profil penerbangan ONDAS aktif