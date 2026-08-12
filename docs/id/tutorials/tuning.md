# PID Penyetelan

OrniFlight menggunakan pengontrol PID (Proportional-Integral-Derivative) yang disesuaikan untuk penerbangan sayap mengepak. Tuning berbeda secara signifikan dari pesawat konvensional karena sifat dorong mengepakkan yang periodik.

## Dasar-dasar Ornithopter PID

Tidak seperti pesawat konvensional yang daya dorongnya hampir terus menerus, daya dorong ornithopter berosilasi dengan setiap gerakan sayap. Hal ini menciptakan:

- **Dorongan riak** pada frekuensi kepakan (biasanya 5–15 Hz)
- **Otoritas kontrol yang bergantung pada fase** — keluaran PID yang sama memiliki efek yang berbeda tergantung di mana dalam siklus kayuhan itu diterapkan
- **Dinamika roll-yaw yang digabungkan** — daya dorong sayap asimetris memengaruhi kedua sumbu secara bersamaan

## PID Ketentuan

| Istilah | Efek | Catatan Ornitopter |
|------|--------|-----------------|
| **P** | Koreksi segera — proporsional | Gunakan nilai-nilai konservatif; osilasi mengepak-sinkron |
| **Saya** | Koreksi kesalahan persisten — integral | Penting untuk menjaga sikap selama meluncur |
| **D** | Turunan — meredam osilasi | Disetel berdasarkan kecepatan kayuhan sayap, bukan osilasi bingkai |
| **Sial** | Umpan maju — langsung menempel ke keluaran | Berguna untuk respon tajam pada sumbu roll |

## Nilai Awal

Untuk ornithopter berukuran sedang (lebar sayap 1–1,5m):

| Sumbu | P | saya | D | F |
|------|---|---|---|---|
| Gulung | 25 | 30 | 15 | 30 |
| Nada | 30 | 35 | 20 | 35 |
| Yaw | 40 | 35 | 10 | 20 |

## Prosedur Penyetelan

### 1. Nilai Tuning Terlebih Dahulu

Sebelum penyetelan PID, tetapkan tarif yang terasa nyaman:
- Mulai dengan RC Tarif 0,90, Tarif Super 0,65, Expo 0,30
- Sesuaikan dengan gaya terbang dan ukuran ornithopter Anda

### 2. P Keuntungan

Tingkatkan P hingga Anda melihat osilasi pada frekuensi mengepak, lalu turunkan 20%:
- Osilasi gulungan: goyangan sayap sesuai kecepatan pukulan
- Osilasi nada: terayun-ayun dari depan ke belakang
- Osilasi yaw: kibasan ekor disinkronkan dengan guratan

### 3. D Keuntungan

Tingkatkan D untuk meredam pantulan kembali setelah input tongkat tajam:
- Terlalu banyak: servo jitter, panas berlebih
- Terlalu sedikit: berdering setelah roll/pitch stop

### 4. Saya Mendapatkan

Saya mendapatkan counter drift yang persisten:
- Tingkatkan hingga penyimpangan dihilangkan
- Terlalu banyak: osilasi lambat pada 1–2 Hz (di bawah tingkat kepakan)

## ONDAS Integrasi

ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) memodulasi output PID dalam setiap langkah sayap. Setelah penyetelan PID dasar:

1. Atur **Cadence Gain** — menggeser jendela modulasi ke fase aerodinamis optimal
2. Atur **Ferocity P** — dorongan asimetris langsung
3. Atur **Ferocity D** — eksploitasi drag antisipatif
4. Sempurnakan **Balance** — simetri sayap kiri/kanan

Lihat [ONDAS Tuning Guide](ondas_tuning.html) untuk prosedur detailnya.

## Analisis Kotak Hitam

Aktifkan Blackbox logging untuk memvisualisasikan kinerja PID. Carilah:
- **Osilasi suku-P** pada frekuensi flapping → mengurangi P
- **penghentian jangka I** selama belokan berkelanjutan → mengurangi I atau meningkatkan relaksasi jangka I
- **Suara jangka D** dari getaran → periksa keseimbangan mekanis terlebih dahulu, lalu kurangi D

## Profil Penerbangan

OrniFlight mendukung 3 profil penerbangan yang dapat dialihkan di tengah penerbangan:

| Profil | Kasus Penggunaan |
|---------|----------|
| 1 | Pelayaran standar |
| 2 | Kelincahan tinggi/agresif |
| 3 | Efisiensi/termal melonjak |