# Mode Penerbangan

Mode dialihkan melalui sakelar AUX pada pemancar Anda. Setiap mode dapat ditetapkan ke rentang saluran AUX tertentu di tab **Modes** pada OrniFlight Configurator.

## Mode Standar

| Modus | Fungsi |
|------|----------|
| **ARM** | Aktifkan kontrol penerbangan (motor/servo aktif) |
| **ANGLE** | Kerajinan — level otomatis kembali ke level ketika tongkat berada di tengah |
| **HORIZON** | Mode sudut — hibrida dekat tengah, acro pada tongkat penuh |
| **ACRO** | Zzz2zzz default tidak ada level otomatis, kontrol laju murni |
| **AIRMODE** | Menjaga loop PID tetap aktif pada throttle nol untuk otoritas penuh |

## OrniFlight-Mode Khusus

| ID | Modus | Fungsi |
|----|------|----------|
| 50 | **INDEPENDENT** | Kontrol sayap independen — setiap sayap merespons saluran servonya sendiri |
| 51 | **GLIDE** | Mode luncur sayap — terkunci dalam posisi horizontal untuk melonjak |
| 52 | **PROFILE** | Pemilihan profil penerbangan — beralih antara 3 profil PID/ONDAS |

## Mode Utilitas

| Modus | Fungsi |
|------|----------|
| **BEEPER** | Aktifkan buzzer untuk mencari lokasi pesawat yang hilang |
| **BLACKBOX** | Mulai/hentikan pencatatan Blackbox |
| **FAILSAFE** | Memicu failsafe tahap 2 secara manual (panic switch) |
| **OSD** | Alihkan tampilan OSD |
| **TELEMETRY** | Mengaktifkan/menonaktifkan keluaran telemetri |

## Catatan Ornithopter

- Mode **INDEPENDENT** unik untuk OrniFlight — yang memungkinkan pemetaan servo per sayap untuk daya dorong asimetris dan kontrol sayap diferensial
- Mode **GLIDE** menahan sayap pada posisi netral, berguna untuk lonjakan termal dan penurunan hemat energi
- **PROFILE** peralihan memungkinkan perubahan parameter ONDAS dalam penerbangan untuk berbagai kondisi penerbangan (misalnya, manuver jelajah vs. agresif)