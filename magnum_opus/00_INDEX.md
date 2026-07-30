# Magnum Opus: OrniFlight Exhaustive Analysis & Vision

## Reading Guide

This is the complete alchemical record — the **Magnum Opus** of the OrniFlight codebase. Seven documents, each building upon the last, from raw architecture to visionary roadmap.

| # | Document | Purpose | For Whom |
|---|----------|---------|----------|
| 01 | [ARCHITECTURE](01_ARCHITECTURE.md) | System topology, data flow, component graph | New contributors, integrators |
| 02 | [CONTROL THEORY](02_CONTROL_THEORY.md) | ONDAS, ferocity wave-shaping, wing ODE, three-channel modulation | Researchers, tuning experts |
| 03 | [PARAMETER SPACE](03_PARAMETER_SPACE.md) | Every parameter, range, default, interaction, MSP gap | Configurator developers, pilots |
| 04 | [IDENTITY](04_IDENTITY.md) | What OrniFlight IS — philosophy, design principles, community | Everyone |
| 05 | [CRITIQUE](05_CRITIQUE.md) | Strengths, weaknesses, dead code, fragilities | Maintainers, contributors |
| 06 | [IMPROVEMENT VISION](06_IMPROVEMENT_VISION.md) | Roadmap: immediate fixes through long-term vision | Project leadership |
| 07 | [SIMULATION](07_SIMULATION.md) | sim_ferocity.rb harness, tuning methodology, physics validation | Researchers, tuners |

## Quick Start

- **Pilot wanting to tune?** → [03_PARAMETER_SPACE](03_PARAMETER_SPACE.md) then [07_SIMULATION](07_SIMULATION.md)
- **Developer wanting to contribute?** → [01_ARCHITECTURE](01_ARCHITECTURE.md) then [04_IDENTITY](04_IDENTITY.md) then [05_CRITIQUE](05_CRITIQUE.md)
- **Researcher studying the algorithm?** → [02_CONTROL_THEORY](02_CONTROL_THEORY.md) then [07_SIMULATION](07_SIMULATION.md)
- **Project steward?** → Read in order: 01 → 02 → 03 → 04 → 05 → 06

## Key Findings At A Glance

### 🔴 Critical (Fix Immediately)
- **MSP buffer over-read**: `MSP_SET_PID_ADVANCED` guard checks 7 bytes but reads 9 — reads adjacent memory on malformed packets
- **Division by zero**: `flap_base_frequency` CLI range `{0, 255}` allows zero → `1.0/0.0 = Inf` → NaN cascade through entire PID loop

### 🟡 Important
- `ondas_gain2` and `ondas_gain3` have no MSP exposure — cannot be tuned via Configurator
- 99.43% flash usage on OMNIBUSF7 — critically tight budget
- `ferocityParamToFloat` saturates at CLI values 81-100 (all produce F≈6.66-8.0 clamped identically)

### 🟢 Philosophy
- **Core innovation**: PID modulates wing *trajectory*, not servo offset — a novel control paradigm
- **Elegance**: Trapezoidal wave shaping (dwell + cos ramp from GralhaAzul) is simpler, faster, and gives independent control over dwell vs ramp steepness
- **Three-channel breathing-pause**: P→phase, D→sharpness, I→asymmetry — each PID term has a distinct, physically meaningful role

## The Alchemical Record

This Magnum Opus was produced through a nine-step alchemical process:

| Step | Phase | What Was Done |
|------|-------|---------------|
| Nigredo | Decomposition | System identification — what IS OrniFlight? |
| Albedo | Purification | Solution definition — document architecture |
| Citrinitas | Illumination | Source survey — implementation paths |
| Rubedo | Completion | Technical stack selected |
| Solve | Dissolution | 18-item improvement inventory catalogued |
| Coagula | Coagulation | 6 changes applied across 4 files |
| Test | Verification | Build passes, all 6 sim modes functional |
| Purificatio | Purification | Edge case analysis — div/0, NaN-safety, dead code |
| Validatio | Validation | Security & performance audit — 8 findings |

The tenth step — **Documentatio** — is this very document set.