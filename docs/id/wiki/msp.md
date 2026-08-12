# MSP Protokol

> *MultiWii Serial Protocol — bagaimana Configurator berbicara dengan OrniFlight.*

## Ikhtisar

OrniFlight memperluas Betaflight MSP dengan pesan khusus ornithopter. Spesifikasi resmi ada di repositori firmware di `src/main/msp/`.

**Versi saat ini:** apiVersion 1.46 (OrniFlight v0.4.6)

## Pesan Utama

### MSP_PID_ADVANCED (112 / 0x70)

Pesan penyetelan ONDAS utama. Berkembang dari 48 byte (warisan) menjadi 87 byte (1,46).

| API Versi | Ukuran | Konten Baru |
|-------------|------|-------------|
| 1.33 | 48 | Zzz18zzz lawas tingkat lanjut |
| 1.42 | 59 | + itermRelaxCutoff, keuntungan 10 ONDAS v2 |
| 1.43 | 71 | + servo_mount_angle[4], fase_shift[4], prescience, espelho, saudade, ssff |
| 1.44 | 75 | + servo_speed, max_amplitude, flap_magnitude, wing_origin_offset[4] |
| 1.45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1.46 | 87 | + profile_index, ferocity_downstroke, ferocity_upstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

Konfigurasi servo dengan 4 byte tambahan ONDAS: glide_deg + ONDAS v1 triplet.

## Kompatibilitas Mundur

Semua versi API kompatibel dengan versi sebelumnya. Pengirim 48-byte berkomunikasi dengan penerima 1,46 — bidang tambahan default ke nilai yang masuk akal.

## Format Kawat

Semua nilai multi-byte adalah little-endian. Nilai yang ditandatangani disimpan sebagai `value + 128` di kabel. Nilai penguatan yang tidak ditandatangani (0–100) bersifat langsung. Panjang array diawali dengan hitungan u8.

---

*Lihat `docs/MSP_FIRMWARE_INTERFACE.md` di repositori firmware untuk spesifikasi lengkapnya.*