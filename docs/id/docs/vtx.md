# Pemancar Video (VTX)

OrniFlight mendukung kontrol VTX untuk ornithopters FPV. modul VTX dapat dikonfigurasi melalui OrniFlight Configurator, MSP, atau CLI — pengaturan band, saluran, level daya, dan mode pit.

## Protokol yang Didukung

1. **IRC Tramp** — Umum pada modul VTX kecil, ideal untuk ornithopter FPV ringan
2. **TBS SmartAudio** — Protokol digital dengan dukungan mode pit
3. **RTC6705** — Kontrol SPI langsung pada board dengan VTX terintegrasi (misalnya SPRACINGF3NEO)

## Konfigurasi

Pengaturan VTX dikelola melalui tab **VTX** di OrniFlight Configurator, atau melalui CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Pelabuhan Seri

Kontrol VTX memerlukan pin UART TX khusus. Konfigurasikan port di tab **Ports** dengan periferal `IRC Tramp` atau `TBS SmartAudio`.

## FPV Pertimbangan Ornithopter

- Berat sangat penting — pilih modul VTX ringan (Tramp Nano, Eachine Nano)
- Pemasangan antena: pastikan jarak bebas dari kepakan sayap
- Pemfilteran daya: sambungkan daya VTX setelah filter LC untuk menghindari kebisingan servo dalam video
- Mode pit direkomendasikan untuk pengujian bangku untuk menghindari modul VTX kecil yang terlalu panas