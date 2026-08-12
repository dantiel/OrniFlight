# ONDAS — Stabilisasi Adaptif Dinamis Normalisasi Berosilasi

## Prinsip Inti

Pesawat sayap tetap atau konvensional menghasilkan gaya kendali **terus menerus** — defleksi permukaan kendali atau perubahan RPM menghasilkan momen keadaan tunak. Ornithopter tidak. Setiap gram daya dorong, setiap Newton torsi, **terikat fase** dalam siklus kepakan sayap. Impuls gaya yang sama yang diterapkan pada titik-titik pukulan yang berbeda menghasilkan hasil yang berbeda secara mendasar.

ONDAS mengakui kenyataan ini dan memodulasi upaya stabilisasi secara sinkron dengan siklus flapping.

---

## Cadence — Otak Waktu

Cadence adalah filter ONDAS yang paling kritis karena menentukan **kapan** koreksi terjadi dalam setiap kepakan sayap.

| Fase Stroke | Pengaruh Penerapan Kekuatan |
|---|---|
| Pusat gaya bawah | Pengangkatan maksimum, otoritas gulungan |
| Ujung downstroke (pengereman) | Tarikan terinduksi momen yaw → |
| Pusat gaya atas | Dorong ke belakang, pitch-up |
| Akhir gaya ke atas | Pembalikan sayap, efek minimal |

**Cadence menggeser jendela modulasi** agar sejajar dengan fase di mana lengan tuas aerodinamis terpanjang. Irama yang salah = melawan fisika sayap. Irama yang benar = setiap miliwatt menjadi otoritas kendali.

### Parameter

| Parameter | Nilai | Fungsi |
|-----------|-------|----------|
| `ONDAS_K0` | 1.0 | Offset fase dasar |
| `ONDAS_K2` | 10.0 | Fase Penyebaran/Ketajaman |
| `ONDAS_PHASE_SCALE` | 0,00005 | Faktor kecil, leverage besar |

---

## Ferocity P — Dorongan Asimetris Segera

Ferocity P meningkatkan **kuadrat bentuk gelombang** (bentuk trapesium: berada di ±1, tanjakan kosinus di antaranya) secara proporsional dengan kesalahan PID saat ini.

- Lebih banyak dorongan di satu sisi → momen langsung
- Sayap yang direm pada akhir langkah mengalami **tarikan terinduksi** — inilah momen tandingannya
- Efek: langsung, proporsional, langsung

---

## Ferocity D — Eksploitasi Drag Antisipatif

Ferocity D melengkapi gambarnya. Jika P memberikan gaya dorong yang asimetris, D memanfaatkan **tarikan sayap kontralateral** sebagai rem.

- Membaca tingkat kesalahan perubahan dan **mengantisipasi**
- Dapat dengan sengaja memanfaatkan gaya tarik sayap yang diperlambat untuk momen yaw/pitch
- P+D bersama-sama menciptakan **pasangan momen diferensial** — gaya dorong di sisi A, tarikan di sisi B — lebih efisien dibandingkan gaya dorong saja

---

## Tiga Cara Cadence/Ferocity D Meningkatkan Ferocity

### 1. Zzz18zzz D langsung meningkatkan P selama perubahan kesalahan cepat

Dalam hembusan angin atau manuver agresif, `error_rate` berukuran besar. D mengalikan ini dan menambah keganasan dasar. Sayap menjadi *lebih tajam* (lebih berbentuk trapesium) karena P+D bersama-sama menuntut lebih banyak persegi daripada P saja. Hasilnya: otoritas maksimum justru pada saat kritis.

### 2. Zzz19zzz Cadence tidak langsung menggeser titik leverage

Cadence memodulasi *ketika* dalam keganasan siklus bertindak. Memindahkan jendela ke fase yang lebih sensitif secara aerodinamis (misalnya, pusat gaya turun vs. ujung gaya naik) berarti **nilai keganasan yang sama** menghasilkan lebih banyak efek — amplifikasi efektif tanpa perubahan numerik.

### 3. Kombinatorial — D × Cadence selama pemulihan terhenti

Dalam keadaan terhenti: laju tenggelam yang tinggi → D mendeteksi laju → meningkatkan keganasan. Secara bersamaan, irama menggeser modulasi ke fase gaya turun di mana sayap memiliki gigitan maksimal. Interaksinya: D memberikan kekuatan, irama momen yang tepat. Tanpa irama, gaya-D mencapai fase yang salah dan menghilang dengan sia-sia.

---

## Parameter ONDAS tambahan

| Parameter | Fungsi |
|-----------|----------|
| **Balance** | Simetri dorong atas/bawah — Bias istilah I antara gaya naik dan gaya turun. Mengkompensasi asimetri sayap, toleransi produksi, dan keausan |
| **Warp** | Roll/Yaw P → L/R ferocity differential — sayap kanan dan kiri mengepak secara independen pada sumbu roll untuk manuver bank dan belokan |
| **Anchor** | Penahan fase — mengunci modulasi ke referensi fase tertentu, menahan penyimpangan |
| **Resonance** | Kompensasi resonansi badan pesawat — menghindari mode struktural badan pesawat yang menarik |

---

## Analogi

**Cadence adalah konduktornya. Ferocity P dan D adalah instrumennya.**

Tanpa konduktor, mereka bermain — tetapi tidak bersama-sama. Di satu sisi, kebisingan menjadi musik.

---

## Lihat Juga

- [ONDAS Tuning Guide](../../tutorials/ondas_tuning.html) — prosedur penyetelan praktis
- [Protokol MSP](msp.html) format kawat — untuk parameter ONDAS
- [Profil Penerbangan](profiles.html) — konfigurasi ONDAS yang sadar profil