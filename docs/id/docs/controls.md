# Kontrol

OrniFlight menggunakan pemetaan tongkat RC standar dengan ekstensi khusus ornithopter.

## Pemetaan Tongkat

| Tongkat | Sumbu | Efek Utama |
|-------|------|---------------|
| Throttle (Kiri, vertikal) | Throttle | Amplitudo / gaya dorong yang mengepak |
| Yaw (Kiri, horizontal) | Yaw | Dorongan sayap diferensial untuk berputar |
| Pitch (Kanan, vertikal) | Nada | Kemiringan maju/mundur |
| Gulung (Kanan, horizontal) | Gulung | Perbankan kiri/kanan |

## Mode Penerbangan

| Modus | Perilaku Tongkat |
|------|---------------|
| **ACRO** | Tongkat mengontrol kecepatan sudut — tanpa level otomatis |
| **ANGLE** | Sudut kontrol tongkat — level otomatis saat dilepaskan |
| **HORIZON** | ANGLE dekat pusat, ACRO pada defleksi penuh |

ACRO direkomendasikan untuk pilot berpengalaman. ANGLE bagus untuk penerbangan pertama dan lonjakan panas.

## Kontrol Khusus Ornithopter

### modus INDEPENDENT

Saat mode INDEPENDENT aktif, setiap servo sayap merespons secara independen:
- **Tongkat kiri** → servo sayap kiri
- **Tongkat kanan** → servo sayap kanan
- Memungkinkan kepakan asimetris untuk manuver agresif

### modus GLIDE

mode GLIDE mengunci kedua sayap dalam posisi horizontal. Ornithopter menjadi pesawat layang:
- **Throttle** tidak berpengaruh pada posisi sayap
- **Pitch/Roll/Yaw** masih mempengaruhi permukaan kontrol ekor (jika dilengkapi)

### Peralihan Profil

Peralihan profil dalam penerbangan melalui saluran AUX memungkinkan perubahan parameter PID/ONDAS di tengah penerbangan:
- **Profil 1**: Pengaturan pelayaran standar
- **Profil 2**: Pengaturan ketangkasan tinggi
- **Profil 3**: Pengaturan efisiensi/luncuran

## Tarif

Konfigurasikan tarif di tab **PID Tuning**. Untuk ornithopter, mulailah dengan laju konservatif — dinamika kepakan yang memperkuat masukan kontrol:
- RC Nilai: 0,80–1,00
- Tarif Super: 0,60–0,70
- Ekspo: 0,20–0,40