![OrniFlight](/orniflight_logo.png)

Welcome to **OrniFlight**, the open-source flight control software specifically designed for servo flapping ornithopters. Built on the robust Betaflight platform, OrniFlight brings advanced servo-based propulsion and cutting-edge aerodynamic optimization to the fascinating realm of flapping wing flight.

## Introduction

**OrniFlight** is an innovative flight control solution built on top of Betaflight 4.0.6, aimed at enthusiasts and researchers working with ornithopters. Unlike traditional quadcopters and fixed-wing aircraft, ornithopters mimic the natural flight mechanics of birds, requiring precise control of servo mechanisms to achieve efficient and stable flight. OrniFlight is tailored to meet these unique requirements, providing a versatile and powerful tool for anyone looking to explore this exciting field.

### Focus on Servo-Based Flapping Propulsion

OrniFlight replaces traditional motor outputs with oscillating servos that drive the flapping motion of the wings. This servo-based propulsion system enables realistic and efficient flapping wing motion, closely emulating the flight mechanics of birds and other flying creatures. The precise control offered by servos allows for fine-tuning of wing motion, resulting in improved flight stability and performance. OrniFlight supports any configuration with any number of wings, making it adaptable to various ornithopter designs and innovations.

## Key Features

- **Servo-Based Propulsion:** Tailored for precise control of servo mechanisms, enabling realistic and efficient flapping wing motion.
- **ONDAS Control Architecture:** A multi-layered flapping-wing stabilization system with 8 modulation layers + variable damping anchor. PID terms directly modulate wing trajectory parameters — phase timing, wave sharpness, and thrust symmetry — through a nonlinear ODE-driven wing model. [Full documentation →](ONDAS.md)
- **Customizable Settings:** 16 CLI-tunable parameters for fine-tuning ferocity, cadence, balance, and advanced filters.
- **Open Source:** Developed as an open-source project, encouraging community involvement and continuous improvement.

## ONDAS — The Wave

ONDAS is a flapping-wing control architecture built on a single insight: the wing is a driven nonlinear oscillator. Rather than gating PID authority by wing position (the old approach), ONDAS modulates the *wing's own parameters* — spring constant, dwell ratio, and thrust asymmetry — in real time, locked to the flapping phase θ.

### The 8 Layers

| # | Layer | Source | Modulates | Description |
|---|-------|--------|-----------|-------------|
| 1 | **Cadence** | P | k₀ (ODE spring) | Shifts thrust timing within the stroke — "push harder *now*" |
| 2 | **Ferocity** | PD + Roll P + Yaw P | Dwell ratio | Wave sharpness per axis — the inertia gate |
| 3 | **Balance** | I | Up/down bias | Persistent thrust asymmetry trim |
| 4 | **Warp** | Roll/Yaw P | L/R ferocity differential | Asymmetric wing sharpness for turning |
| 5 | **Resonance** | Phase-locked | Error amplification | Lock-in amplifier — only flap-coherent corrections pass |
| 6 | **Prescience** | ω-based prediction | Feed-forward | Stroke-ahead error prediction via wing ODE state |
| 7 | **Espelho** | Reverse lock-in | Self-noise cancel | Subtracts wing's own gyro signature from error |
| 8 | **Saudade** | Per-stroke learning | Bias accumulation | Slowly absorbs persistent SSFF bias into trim |
| ⚓ | **Anchor** | — | k₂ damping | Variable frequency-lock strength |

All layers default to off (gains = 0). Tune progressively — start with Cadence + Ferocity + Balance, then layer in Warp, Resonance, Prescience, Espelho, and Saudade as needed.

**[→ Full ONDAS documentation](ONDAS.md)** — architecture diagrams, signal flow, CLI parameter table, tuning guide.
	
## Installation

To get started with OrniFlight, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/dantiel/OrniFlight.git
   cd OrniFlight
   ```

2. **Set Up Your Development Environment:**
   - Ensure you have the required toolchain and dependencies installed. Refer to the Betaflight [development setup guide](https://github.com/betaflight/betaflight/wiki/Building-Betaflight) for detailed instructions.

3. **Compile the Firmware:**
   - Replace `YOUR_TARGET` with your specific flight controller target (e.g., `TINYFISH`):
     ```bash
     make TARGET=YOUR_TARGET
     ```

4. **Flash the Firmware:**
   - Use Betaflight Configurator or another suitable tool to flash the compiled firmware to your flight controller.

## Contributing

We welcome contributions from the community! Whether you're fixing bugs, adding new features, or improving documentation, your input is valuable. Please read our [contributing guidelines](CONTRIBUTING.md) to get started.

## License

OrniFlight is licensed under the GPL-3.0 License. See the [LICENSE](LICENSE) file for more information.

## Community

Join our community to share your experiences, ask questions, and collaborate with other enthusiasts:
- [OrniFlight Forum](#) (Link to your forum or community page)
- [Discord Channel](#) (Link to your Discord server)
- [Twitter](#) (Link to your Twitter account)