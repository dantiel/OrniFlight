# Tampilan Di Layar (OSD)

OrniFlight menyertakan OSD (Tampilan di Layar) bawaan menggunakan chip MAX7456 atau AT7456E. Zzz14zzz melapisi data penerbangan ke umpan video FPV Anda.

## Elemen yang Didukung

Konfigurasikan elemen di tab **OSD** pada OrniFlight Configurator. Seret dan lepas elemen untuk memposisikannya di layar.

### Data Penerbangan

| Elemen | Menampilkan |
|---------|----------|
| Tegangan Baterai | Tegangan baterai utama (misalnya 14.8V) |
| Tegangan Sel Rata-rata | Tegangan per sel (misalnya 3,7V) |
| Undian Saat Ini | Ampli sesaat |
| mAh Ditarik | Kapasitas kumulatif yang dikonsumsi |
| RSSI | Kekuatan sinyal dari penerima |
| Modus Penerbangan | Mode saat ini (INDEPENDENT, GLIDE, dll.) |
| Posisi Throttle | Persentase throttle saat ini |
| pengatur waktu | Waktu penerbangan / waktu bersenjata |
| Nama Kerajinan | OrniFlight nama kerajinan |

### Khusus Ornithopter

| Elemen | Menampilkan |
|----------|----------|
| Frekuensi Mengepakkan | Tingkat kepakan sayap saat ini dalam Hz |
| Profil ONDAS | Nomor profil penerbangan aktif (1-3) |
| Cadence Fase | Offset fase modulasi saat ini |
| Sudut Servo | Posisi servo sayap |

## Manajemen Font

Zzz18zzz menggunakan sistem tampilan berbasis karakter. Tab **OSD** di Konfigurator OrniFlight menyertakan **Pengelola Font** untuk mengunggah font dan mesin terbang khusus.

## CLI Pengaturan

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Perangkat keras

Chip OSD yang saat ini didukung: **AT7456E** (ditemukan di OMNIBUSF4 dan papan yang kompatibel). MAX7456 kompatibel dan terdeteksi otomatis.