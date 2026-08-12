# Pengaturan Dasar

> *Konfigurasi ornithopter Anda untuk penerbangan pertama.*

## Daftar Periksa Pra-Penerbangan

Sebelum hal lain:

- [ ] Pengontrol penerbangan di-flash dengan OrniFlight
- [ ] Penerima terikat ke pemancar
- [ ] Servo terhubung ke output PWM yang benar
- [ ] Baterai tersambung (sayap diamankan!)

## Pengaturan Penerima

### CRSF (Disarankan)

1. **Tab port**: Setel UART (misalnya UART1) ke "Serial RX"
2. **Tab konfigurasi**: Mode Penerima = "Penerima berbasis serial", Penyedia = "CRSF"
3. Siklus daya, verifikasi perpindahan input saluran di tab Penerima

### SBUS / Lainnya

Proses yang sama — pilih protokol yang sesuai di tab Konfigurasi.

## Pemetaan Servo

Di **tab Servo**:

| Servo | Fungsi | Tingkat Default |
|-------|----------|-------------|
| Servo 0 | Sayap Kiri | 250Hz |
| Servo 1 | Sayap Kanan | 250Hz |
| Servo 2 | Puncak/Kemudi | 50Hz |

Sesuaikan min/maks/tengah agar sesuai dengan jangkauan servo Anda. Uji dengan "Override" untuk memverifikasi arah.

## Pemilihan Mode Penerbangan

Di **tab Mode**:

1. **ARM**: Tetapkan ke sakelar (keamanan!)
2. **ORNITHOPTER INDEPENDENT** atau **ORNITHOPTER GLIDE**: Pilih mode penerbangan utama Anda
3. **ORNITHOPTER PROFILE**: Penetapan — opsional untuk peralihan profil dalam penerbangan

## ONDAS Penyetelan Pertama

Buka **Sub-tab → ONDAS lanjutan**:

1. **Cadence Gain**: Mulai dari 50 (pertengahan). Ini adalah parameter terpenting.
2. **Ferocity D Gain**: Mulai pada 30. Ini adalah stabilisasi utama Anda.
3. **Ferocity P Gain**: Mulai dari 20 untuk roll/pitch, 0 untuk yaw.
4. **Balance Gain**: 0 (di tengah).

Hubungkan baterai, **kencangkan ornithopter dengan kuat**, dan ARM. Amati gerakan servo —, gerakannya harus halus dan berbentuk sinusoidal.

## Penerbangan Pertama

1. Mulailah dengan lemparan lembut ke arah angin
2. Gunakan mode GLIDE untuk sensasi melonjak alami
3. Gunakan mode INDEPENDENT bila Anda ingin kontrol frekuensi langsung
4. Mendarat, sesuaikan ONDAS, ulangi

---

*Berikutnya: [Panduan Penyetelan ONDAS](ondas_tuning.html) →*