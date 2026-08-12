#failsafe

OrniFlight memiliki sistem failsafe dua tahap untuk melindungi ornithopter Anda jika sinyal penerima hilang.

## Sistem Dua Tahap

### Tahap 1 — Kehilangan Sinyal Terdeteksi

Dipicu ketika:
- Saluran penerbangan mana pun memiliki panjang pulsa yang tidak valid
- Penerima melaporkan mode failsafe
- Tidak ada sinyal dari penerima selama durasi yang dikonfigurasi

**Tindakan**: Semua saluran beralih ke nilai cadangan (dikonfigurasi melalui `rxfail`). Jendela pemulihan singkat dimulai — jika sinyal kembali, penerbangan normal dilanjutkan.

### Tahap 2 — Waktu Penjagaan Berakhir

Dimasuki ketika Tahap 1 bertahan lebih lama dari `failsafe_delay` (default: 400ms) DAN pesawat dipersenjatai.

**Prosedur** (dapat dikonfigurasi melalui `failsafe_procedure`):

| Prosedur | Perilaku |
|-----------|----------|
| **DROP** | Segera lucuti — sayap berhenti, pesawat turun |
| **LAND** | Mode luncur — sayap terkunci horizontal, penurunan terkontrol |

**LAND** adalah prosedur yang direkomendasikan untuk ornithopter — yang menahan sayap pada posisi netral untuk meluncur turun, sehingga memberikan waktu untuk pemulihan sinyal.

## CLI Pengaturan

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Penerima Gagal Aman

Konfigurasikan juga fail-safe receiver Anda untuk mengeluarkan **tidak ada pulsa** saat sinyal hilang. Hal ini memungkinkan pengontrol penerbangan mendeteksi kehilangan dan mengaktifkan Tahap 1.

## Pengujian

Uji failsafe **dengan sambungan sayap terputus** di bangku cadangan:
1. Tetapkan mode FAILSAFE ke sakelar
2. Persenjatai pesawatnya
3. Alihkan sakelar → amati prosedur failsafe
4. Pastikan perilaku servo sesuai dengan harapan