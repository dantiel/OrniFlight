# ONDAS Panduan Penyetelan

> *Pendamping praktis untuk Teori ONDAS — cara menyetel setiap parameter berdasarkan perasaan.*

## Urutan Penyetelan

parameter ONDAS saling bergantung. Sesuaikan mereka dalam urutan ini:

```
1. Cadence    →  timing
2. Ferocity D →  primary stabilization
3. Ferocity P →  response crispness
4. Balance    →  upstroke/downstroke bias
5. Warp       →  modulation width
6. Anchor     →  dry/wet mix
7. Resonance  →  cycle-to-cycle memory
8. Phase 2    →  advanced (prescience, espelho, saudade, SSFF)
```

## Langkah demi Langkah

### 1. Cadence — Temukan Jendela Fase Anda

**Sasaran**: Tempatkan modulasi di tempat sayap Anda paling banyak digigit.

**Metode**: 
- Mulai pada usia 50
- Meningkat menjadi 70 — apakah respon roll semakin lemah?
- Turun ke 30 — apakah respon roll semakin kuat?
- Titik "terkuat" adalah tempat kekuatan pukulan sayap Anda mencapai puncaknya

**Tanda terlalu tinggi**: Respon lembek, kerajinan terasa "tertunda"
**Tanda-tanda terlalu rendah**: Respon tersentak-sentak, overshoot on roll

### 2. Ferocity D — Mantap Kerajinannya

**Sasaran**: Stabilisasi primer tanpa osilasi.

**Metode**:
- Mulai jam 20
- Melayang atau terbang ke depan dengan stabil
- Tingkatkan hingga Anda merasakan kerajinan "kaku"
- Mundur 5 poin dari tempat Anda pertama kali melihat osilasi

**Tanda-tanda terlalu tinggi**: Getaran halus, dengungan seperti motor di servo
**Tanda terlalu rendah**: Kerajinan melayang, terasa longgar

### 3. Ferocity P — Kerenyahan

**Sasaran**: Responsif tetapi tidak gugup.

**Metode**:
- Mulai jam 15
- Bump the roll stick — apakah kerajinan itu langsung menggigit?
- Tingkatkan hingga respons tongkat garing
- Mundur jika Anda melihat overshoot

**Tanda terlalu tinggi**: Berdering setelah input stick, memantul kembali
**Tanda terlalu rendah**: Respon lembek dan tertunda

### 4. Balance — Penyetelan Asimetri

**Sasaran**: Otoritas yang setara di kedua arah.

**Metode**:
- Terbang lurus dan rata
- Putar ke kiri, perhatikan kecepatan respons
- Putar ke kanan, perhatikan kecepatan respon
- Sesuaikan keseimbangan untuk menyamakannya

### 5–7. Warp, Anchor, Resonance

Parameter penyempurnaan. Hanya sesuaikan setelah 1-4 sudah solid.

| Param | Mulai | Sesuaikan Kapan |
|-------|-------|-------------|
| Warp | 50 | Modulasi terasa terlalu menyebar atau terlalu lemah |
| Anchor | 70 | Ingin lebih banyak/kurang campuran PID mentah |
| Resonance | 30 | Melayang tidak stabil, atau penerbangan ke depan terasa ringy |

### 8. Phase 2 — Lanjutan

| Param | Efek |
|-------|--------|
| Prescience | Waktu maju — lebih tinggi = modulasi memimpin fase lebih banyak |
| Espelho | Kopling diferensial — roll lebih kencang, dapat mengurangi efisiensi |
| Saudade | Stroke memory — lebih halus tapi kurang responsif |
| SSFF | Injeksi gyro→wave langsung — mulai jam 10 |

---

*Tujuannya adalah sebuah pesawat yang terbang seperti ingin berada di udara. Jika Anda melawannya, mundurlah dan setel ulang dari Cadence ke atas.*