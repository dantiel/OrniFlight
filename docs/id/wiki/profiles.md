# Profil Penerbangan

> *4 slot penyetelan independen, dapat dialihkan dalam penerbangan.*

## Konsep

OrniFlight menyimpan 4 struct `ornithopterProfile_t` lengkap — masing-masing berisi 19 ONDAS dan parameter dinamika sayap. Mode BOX (`BOXORNITHOPTERPROFILE`, permanentId 52) memilih profil aktif melalui sakelar RC 2 posisi yang dipetakan ke 4 slot (0–3).

## Mengapa Profil?

Mode penerbangan yang berbeda memerlukan penyetelan yang berbeda:

| Profil | Kasus Penggunaan | Cadence | Ferocity | Catatan |
|---------|----------|---------|----------|-------|
| 0 | **Pelayaran** | Pertengahan (50) | Rendah (30) | Penerbangan maju yang efisien |
| 1 | **Aerobatik** | Rendah (20) | Tinggi (80) | Otoritas maksimum |
| 2 | **Melayang/Berkeliaran** | Tinggi (70) | Pertengahan (50) | Stabilitas atas kecepatan |
| 3 | **Meluncur** | Pertengahan (50) | Rendah (10) | Intervensi minimal |

## Apa yang Ada di Profil

Semua 19 bidang `ornithopterProfile_t`:

- **Geometri luncur**: glide_angle
- **ONDAS v2 (10)**: irama, ferocity_d/p/roll/yaw, keseimbangan, warp, warp_yaw, jangkar, resonansi
- **Phase 2 (4)**: kesadaran, espelho, saudade, ssff
- **Bentuk gelombang (2)**: ferocity_downstroke, ferocity_upstroke
- **Aeroelastik (2)**: aeroelastic_glide_coefisien, aeroelastic_flap_coefisien

## Yang Global (Bukan Per Profil)

- Saluran frekuensi (satu saluran RC, berfungsi di INDEPENDENT dan GLIDE)
- Sudut pemasangan servo
- Pergeseran fase mengepak
- geometri GralhaAzul (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Ini adalah konstanta fisik badan pesawat — yang tidak berubah seiring dengan rezim penerbangan.

## Beralih Dalam Penerbangan

1. Tetapkan sakelar 2 posisi atau 3 posisi ke saluran cadangan
2. Di tab Configurator Modes, petakan rentang tersebut ke `ORNITHOPTER PROFILE`
3. Setiap posisi sakelar memilih salah satu dari 4 slot
4. Dropdown profil Configurator mengedit slot *yang saat ini dipilih* melalui MSP

---

*Lihat `src/main/flight/ornithopter_profile.h` untuk definisi struct.*