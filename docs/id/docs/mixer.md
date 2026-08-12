#pencampur

Mixer menerjemahkan keluaran pengontrol penerbangan (roll, pitch, yaw, throttle) menjadi sinyal servo untuk ornithopter Anda.

## Pengaduk Ornitopter

OrniFlight memperluas sistem mixer Betaflight dengan konfigurasi khusus ornithopter. Mixer menangani:

- **Servo sayap**: Mengonversi output PID menjadi modulasi gerakan sayap
- **Servo ekor** (opsional): Mengontrol permukaan elevator/kemudi

## Jenis Pengaduk

| pengaduk | Kasus Penggunaan |
|-------|----------|
| **ORNITHOPTER** | Ornithopter sayap ganda standar dengan servo 2 sayap |
| **ORNITHOPTER_4S** | Ornithopter 4-servo (kontrol sayap kiri/kanan independen) |
| **ORNITHOPTER_TAIL** | Sayap ganda + elevator ekor + kemudi |

## Konfigurasi Servo

Dikonfigurasi di tab **Servos** atau melalui CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Integrasi

Mixer bekerja bersama dengan ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System):

- **Throttle** → menyetel amplitudo kepakan dasar
- **ONDA Cadence** → menggeser jendela modulasi dalam setiap pukulan
- **ONDA Ferocity** → memodifikasi bentuk gelombang guratan (sinusoidal ↔ trapezoidal)
- **ONDA Balance** → koreksi simetri sayap kiri/kanan

Untuk teori ONDAS selengkapnya, lihat [ONDAS Wiki](../wiki/ondas.html).

## CLI Pengaturan

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```