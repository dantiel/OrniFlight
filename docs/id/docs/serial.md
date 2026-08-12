# Port Serial

OrniFlight menggunakan port serial untuk komunikasi dengan periferal: receiver, GPS, telemetri, kontrol VTX, Blackbox logging, dan MSP (Koneksi konfigurator).

## Jenis Port Serial

| Ketik | Deskripsi | Terbaik Untuk |
|------|------------|----------|
| **VCP** | USB Virtual COM Port — koneksi langsung USB ke prosesor | Konfigurasi (MSP) |
| **UART** | Pin TX/RX perangkat keras dengan deteksi sinyal perangkat keras | RX, GPS, Telemetri, VTX, Blackbox |
| **SoftSerial** | Serial berbasis perangkat lunak pada pasangan pin apa pun | Bandwidth rendah: hanya telemetri |

VCP tidak menggunakan UART — fisik, itu selalu tersedia untuk Configurator.

## Penugasan Pelabuhan

Di OrniFlight Configurator, buka tab **Ports** untuk menetapkan fungsi:

| Fungsi | Zzz31zzz yang khas | Catatan |
|----------|-------------|-------|
| Serial RX | UART1 atau UART3 | SBUS, CRSF, IBUS, dll |
| GPS | UART3 atau UART6 | 57600 atau 115200 baud |
| Telemetri | Pin TX apa saja | SmartPort, HoTT, IBUS |
| VTX (Gelandangan/SmartAudio) | Pin TX apa saja | Kabel tunggal |
| Kotak Hitam | Pin TX apa saja | OpenLog atau flash bawaan |
| MSP | VCP (USB) | Koneksi konfigurator |

## OMNIBUSF4 Pemetaan Port

| UART | Pin | Penggunaan Khas |
|------|------|------------|
| VCP | USB | MSP (Konfigurator) |
| UART1 | TX1/RX1 | Serial RX |
| UART3 | TX3/RX3 | GPS atau Telemetri |
| UART6 | TX6/RX6 | Gratis / Blackbox / VTX |

## SoftSerial

SoftSerial tersedia tetapi memiliki bandwidth terbatas. Hanya cocok untuk telemetri kecepatan rendah (misalnya 9600 baud SmartPort). Tidak disarankan untuk Serial RX atau GPS.