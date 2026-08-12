# Instalasi

Cara menginstal firmware OrniFlight pada pengontrol penerbangan Anda.

## Prasyarat

- **konfigurator OrniFlight** (versi terbaru)
- kabel data USB (tidak hanya untuk charge)
- Papan pengontrol penerbangan yang didukung

## Papan yang Didukung

| Papan | Sasaran | Kilatan | Catatan |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256KB | STM32F411, MPU6000 |

## Langkah Berkedip

### 1. Masuk ke mode DFU/Bootloader

**OMNIBUSF4**: Tahan tombol BOOT saat menghubungkan USB. Zzz27zzz merah tetap solid — Anda berada dalam mode DFU.

**TINYFISH**: Tahan tombol BOOT saat menghubungkan USB.

### 2. Flash melalui Konfigurator

1. Buka Konfigurator OrniFlight
2. Buka tab **Firmware Flasher**
3. Pilih target Anda dari dropdown
4. Pilih versi firmware (disarankan stabil terbaru)
5. Klik **Muat Firmware (Online)** atau pilih file hex lokal
6. Klik **Firmware Flash**
7. Tunggu “Pemrograman: SUKSES”

### 3. Koneksi Pertama

Setelah mem-flash:
1. Putuskan dan sambungkan kembali USB (tanpa tombol BOOT)
2. Konfigurator harus terhubung secara otomatis
3. Terima perintah "Terapkan Default Kustom".
4. Verifikasi info papan pada tab Pengaturan

## Pemecahan masalah

### Tanpa Port DFU

**macOS/Linux**: DFU akan muncul secara otomatis. Jika tidak:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: Instal [Zadig](https://zadig.akeo.ie/) untuk menggantikan driver STM32 DFU:
1. Jalankan Zadig
2. Opsi → Daftar Semua Perangkat
3. Pilih "STM32 BOOTLOADER"
4. Ganti driver dengan "WinUSB"

### Flash Gagal

- Coba kabel USB lain (berkemampuan data, bukan hanya untuk mengisi daya)
- Coba port USB lain (langsung, bukan hub)
- Tahan tombol BOOT selama proses flash
- **OMNIBUSF4**: Penghapusan chip penuh mungkin diperlukan — centang opsi "Hapus Chip Penuh"

### Konfigurator Tidak Dapat Terhubung

- Pastikan kabel USB berkemampuan data
- Periksa papan tidak dalam mode DFU (LED berkedip = mode normal)
- Mulai ulang Konfigurator
- Coba port USB yang berbeda

## CLI Flash (Lanjutan)

Untuk pengguna tingkat lanjut, flash melalui STM32CubeProgrammer atau st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Setelah flashing, verifikasi dengan:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```