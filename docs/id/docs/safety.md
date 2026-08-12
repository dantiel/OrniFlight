# Keamanan

## Daftar Periksa Pra-Penerbangan

1. **Sayap**: Pastikan sayap terpasang dengan aman dan sambungannya utuh
2. **Baterai**: Terisi penuh, diamankan dengan benar, jumlah sel benar
3. **Kontrol**: Verifikasi respons stick di tab penerima Configurator
4. **Failsafe**: Tes di bangku cadangan sebelum penerbangan (lihat [Failsafe](failsafe.html))
5. **Arm Switch**: Mengonfigurasi dan menguji —, jangan pernah mengandalkan stick arming saja
6. **Area Peluncuran**: Bebas dari orang, rintangan, dan penghalang di atas kepala

## Keamanan Lengan

OrniFlight menggunakan banyak pengaman sebelum mempersenjatai:

- **Throttle rendah**: Throttle harus minimum
- **Level**: Kerajinan harus cukup rata
- **RX Signal**: Diperlukan sinyal penerima yang valid
- **CPU Load**: Sistem tidak boleh kelebihan beban
- **Kalibrasi**: Akselerometer dan gyro harus dikalibrasi

## Keamanan Dalam Penerbangan

- **Terbang dalam garis pandang visual**
- Jaga jarak aman dari manusia dan hewan
- Pantau tegangan baterai — mendarat sebelum ambang peringatan
- Di FPV: selalu terbang dengan pengintai
- Angin: ornithopter bisa menjadi peka terhadap angin — ketahui batas kemampuanmu

## Prosedur Darurat

| Situasi | Aksi |
|-----------|--------|
| Kehilangan orientasi | Beralih ke mode INDEPENDENT, stik tengah |
| Kehilangan sinyal | Failsafe akan mendarat secara otomatis (jika prosedur LAND dikonfigurasi) |
| Kerusakan sayap | Segera lucuti — sayap berhenti |
| Serangan burung | Melucuti senjata, menilai kerusakan sebelum mempersenjatai kembali |
| Baterai lemah | Mendarat segera — ornithopters tidak memiliki autorotasi |

## Resiko Khusus Ornithopter

- **Bahaya terjepit**: Mengepakkan sayap dapat menyebabkan cedera — jaga tangan tetap bersih saat bersenjata
- **Kegagalan linkage**: Periksa semua pushrod dan ball joint sebelum penerbangan
- **Resonance**: Frekuensi kepakan tertentu dapat memicu resonansi badan pesawat — tune ONDAS sapuan yang harus dihindari
- **Glide lockout**: Jika servo sayap gagal pada posisi non-netral, pendaratan terkontrol tidak mungkin dilakukan — uji posisi servo failsafe