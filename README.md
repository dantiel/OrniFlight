![OrniFlight](/orniflight_logo.png)

Welcome to **OrniFlight**, the open-source flight control software specifically designed for servo flapping ornithopters. Built on the robust Betaflight platform, OrniFlight brings advanced servo-based propulsion and cutting-edge aerodynamic optimization to the fascinating realm of flapping wing flight.

## Introduction

**OrniFlight** is an innovative flight control solution built on top of Betaflight 4.0.6, aimed at enthusiasts and researchers working with ornithopters. Unlike traditional quadcopters and fixed-wing aircraft, ornithopters mimic the natural flight mechanics of birds, requiring precise control of servo mechanisms to achieve efficient and stable flight. OrniFlight is tailored to meet these unique requirements, providing a versatile and powerful tool for anyone looking to explore this exciting field.

### Focus on Servo-Based Flapping Propulsion

OrniFlight replaces traditional motor outputs with oscillating servos that drive the flapping motion of the wings. This servo-based propulsion system enables realistic and efficient flapping wing motion, closely emulating the flight mechanics of birds and other flying creatures. The precise control offered by servos allows for fine-tuning of wing motion, resulting in improved flight stability and performance. OrniFlight supports any configuration with any number of wings, making it adaptable to various ornithopter designs and innovations.

## Key Features

- **Servo-Based Propulsion:** Tailored for precise control of servo mechanisms, enabling realistic and efficient flapping wing motion.
- **Advanced Aerodynamics:** Integrates the latest aerodynamic theories to enhance flight stability and performance.
	- **ONDAS:** Oscillating Normalized Dynamic Adaptive Stabilization. ONDAS facilitates gyroscopic PID stabilization specifically designed for optimizing flapping flight dynamics, ensuring consistent and controlled wing motion throughout flight.
- **Customizable Settings:** Offers a wide range of configurable options to fine-tune flight characteristics according to specific designs and requirements.
- **Open Source:** Developed as an open-source project, encouraging community involvement and continuous improvement.

## Oscillating Normalized Dynamic Adaptive Stabilization (ONDAS)

Oscillating Normalized Dynamic Adaptive Stabilization (ONDAS) is an innovative stabilization system specifically designed for flapping or oscillating systems. 
By focusing on the central, most powerful part of the oscillating wave, ONDAS dynamically adapts to real-time data to maintain optimal stability and control while preventing the system from being destabilized by its own oscillations. This system leverages advanced normalization and dynamic adjustment techniques to minimize the impact of extreme errors, ensuring efficient and stable performance in varying conditions.


### Key Features

* **Oscillating Focus:** Stabilizes systems with oscillating or flapping motions by adjusting to the system’s natural rhythm for smooth operation.
* **Normalized Management:** Reduces the impact of extreme deviations by focusing on the central part of the oscillation where the most thrust is generated.
* **Dynamic Adjustment:** Adjusts control parameters in real-time to maintain stability during varying conditions.
* **Adaptive Phasing:** Reacts differently to various flap phases, enabling clear control and a more steady wave by adapting to the setpoint flap by flap.
* **Central Stabilization:** Ensures precise control by focusing on the central phase of the oscillation, enhancing stability.


### How It Works

1. *Error Filtering:* ONDAS applies an alpha filter to the error term based on the oscillation phase, throttle input, and user-defined control variables. This filtering process reduces the influence of extreme errors and focuses on the most controllable, predictable but also impactful part of the wave.
2. *Adaptive PID Control:* The filtered error is used in the PID (Proportional-Integral-Derivative) control loop. The PID parameters are dynamically adjusted to adapt to changing conditions, ensuring responsive and stable control.
3. *Seamless Integration:* ONDAS integrates with the flapping control loop, ensuring that stabilization efforts complement the natural motion of the system without interfering with its power and efficiency.


### Benefits

* *Improved Stability:* Prevents destabilization caused by the system’s own oscillations, ensuring smooth and efficient operation. A more steady wave and trajectory generated by the stabilization system enhances overall efficiency and flight predictability.
* *Optimized Control:* Focuses on the central part of the oscillation to achieve precise stabilization and avoid overshooting.
* *Real-Time Adaptation:* Continuously adapts to real-time conditions, providing robust stabilization even in rapidly changing environments. This technology expands operational capabilities, enabling models that previously struggled or couldn’t fly without active stabilization to achieve sustained flight.
	
	
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
