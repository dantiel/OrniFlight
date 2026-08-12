#LED Strip

OrniFlight mendukung strip WS2812/SK6812 LED yang dapat dialamatkan untuk indikasi status dan umpan balik visual.

## Konfigurasi

LED strip dikonfigurasikan di tab **LED Strip** pada OrniFlight Configurator. Setiap posisi, warna, dan fungsi LED dapat diatur secara individual.

## Fungsi

| Fungsi | Efek Visual |
|----------|--------------|
| Indikator Baterai | Gradien warna dari hijau → kuning → merah |
| RSSI | Tampilan kekuatan sinyal |
| Negara Bagian | Perubahan warna pada lengan/melucuti |
| Modus Penerbangan | Warna khusus mode |
| Peringatan | Pola kedip untuk baterai lemah, failsafe |
| Indikator Mengepak | Pulsa pada frekuensi kepakan arus |
| Arah Dorong | Pergeseran warna menunjukkan keluaran roll/pitch/yaw |
| GPS | Kunci satelit dan arah pulang |

## Perangkat keras

- LED WS2812 atau SK6812 RGB
- Hubungkan ke pad/pin **LED** pada pengontrol penerbangan Anda
- LED daya dari BEC (JANGAN daya dari 3.3V — gunakan 5V)
- Untuk strip panjang (>8 LED), sambungkan daya 5V langsung ke bantalan baterai, bukan melalui FC

## Penggunaan Ornitopter

**Flapping Indicator** unik untuk pulsa LED OrniFlight — yang sinkron dengan frekuensi gerakan sayap, memberikan representasi visual ritme kepakan dan membantu menyetel parameter irama ONDAS.