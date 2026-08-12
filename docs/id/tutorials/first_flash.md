# Kilatan Pertama

> *Mendapatkan OrniFlight ke pengontrol penerbangan Anda — langkah demi langkah.*

## Yang Anda Butuhkan

- pengontrol penerbangan berbasis STM32F4 (OMNIBUSF4, TINYFISH, MATEKF405, dll.)
- kabel USB
- [dfu-util](http://dfu-util.sourceforge.net/) atau STM32CubeProgrammer
- file OrniFlight `.hex` dari [halaman rilis](https://github.com/dantiel/OrniFlight/releases)

## Langkah 1: Masuk ke Mode DFU

1. **Tahan tombol BOOT** di pengontrol penerbangan Anda
2. **Pasang USB** sambil menahan tombol
3. **Lepaskan** setelah 2 detik

Verifikasi di macOS/Linux:

```
dfu-util -l
```

Seharusnya menunjukkan `Found DFU: [0483:df11]`

## Langkah 2: Berkedip

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Langkah 3: Booting Pertama

1. Cabut USB
2. Pasang kembali USB (jangan ditahan BOOT)
3. Hubungkan melalui Konfigurator OrniFlight

## Langkah 4: Konfigurasi Dasar

Di Konfigurator:

1. **Tab port**: Konfigurasikan UART untuk receiver Anda (Serial RX)
2. **Tab konfigurasi**: Pilih protokol penerima (disarankan CRSF)
3. **Tab Mode**: Siapkan sakelar ARM, GLIDE/INDEPENDENT, dan PROFILE
4. **Tab → ONDAS lanjutan**: Tinjau default, setel Cadence terlebih dahulu

## Pemecahan masalah

| Masalah | Perbaiki |
|---------|-----|
| DFU perangkat tidak ditemukan | Coba kabel USB yang berbeda, centang tombol BOOT |
| Flash gagal | Periksa instalasi dfu-util, izin USB |
| Tidak ada boot setelah flash | Flash ulang, verifikasi hex cocok dengan target Anda |
| Konfigurator tidak dapat terhubung | Periksa port COM dan baud rate |

---

*Berikutnya: [Pengaturan Dasar](basic_setup.html) →*