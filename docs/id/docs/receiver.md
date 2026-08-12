# Penerima (RX)

OrniFlight mendukung beberapa protokol penerima untuk kontrol radio ornithopter Anda.

## Protokol yang Didukung

| Protokol | Ketik | Catatan |
|----------|------|-------|
| **CRSF** (Baku Tembak) | Serial | Latensi rendah, telemetri, direkomendasikan |
| **SBUS** | Serial | Terbalik, membutuhkan inverter pada F4 |
| **IBUS** (FlySky) | Serial | Tidak terbalik, langsung UART |
| **PPM** | Analog kabel tunggal | 8ch, lawas, tidak direkomendasikan |
| **SPEKTRUM** | Serial | 1024/2048, ikat melalui CLI |
| **FPORT** | Serial | FrSky, menggabungkan RX+Telemetri |
| **GHST** (Hantu) | Serial | ImmersionRC, latensi rendah |

## Konfigurasi seri RX

1. Hubungkan receiver ke pin UART RX gratis
2. Di Configurator → **Ports**: atur UART ke `Serial RX`
3. Di Configurator → **Konfigurasi**: pilih protokol
4. Untuk SBUS di F4: aktifkan `set sbus_inversion = ON`

## CLI Pengaturan Cepat

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## Aman dari kegagalan

Konfigurasikan receiver failsafe sehingga receiver mengeluarkan **tidak ada pulsa** saat sinyal hilang. Pengendali penerbangan kemudian akan mendeteksi ini dan mengaktifkan prosedur failsafe-nya sendiri. Lihat [Failsafe](failsafe.html) untuk konfigurasi tingkat FC.