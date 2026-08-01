# OrniFlight Website — Magnum Opus

Static site for the OrniFlight servo-flapping flight controller firmware.
Bird-first glassmorphism design matching the Configurator palette.

## Quick Start

```bash
cd site
bundle exec rake server     # → http://localhost:8000
```

Open **http://localhost:8000** in your browser.

## Design — Glassmorphism

- **Font:** Open Sans (Google Fonts) — matches Configurator UI
- **Accent:** Periwinkle `#8998fe` / Indigo `#3a4192`
- **Glass Nav:** `backdrop-filter: blur(18px) saturate(1.5)` on semi-transparent indigo
- **Glass Main:** `blur(24px) saturate(1.35)`, rounded top, accent glow border
- **Glass Cards:** sections with `blur(10px)`, hover glow transition, subtle edge
- **Glass Footer:** `blur(16px) saturate(1.25)`
- **Fine Feathers:** 140px repeat background behind glass layers
- **Logo Breathe:** 6s glow pulse animation on cf_logo SVGs
- **Dark/Light:** CSS custom properties with RGB tuples for rgba() glass blending
- **Assets:** Logo SVGs, paper/feather textures, icons — from Configurator

## Architecture

```
site/
├── index.haml              # Landing page template (HAML)
├── _lang/                  # i18n JSON (en, de)
├── assets/
│   ├── css/style.sass      # Indented syntax, glassmorphism, dark/light
│   └── images/             # Logos, textures, icons (from Configurator)
├── en/                     # English subpages (Markdown)
│   ├── wiki/               # ONDAS theory, MSP, profiles
│   ├── docs/               # Hardware, CLI reference
│   └── tutorials/          # First flash, setup, tuning
├── de/                     # German subpages
├── Rakefile                # Build: HAML→HTML, SASS→CSS, MD→HTML
├── Gemfile                 # Ruby dependencies
└── README.md
```

## Building

```bash
bundle exec rake build      # Full: landing + sass + content pages
bundle exec rake server     # Local → http://localhost:8000
./watch.sh                  # Auto-rebuild on changes
```

## Content Pages

Add `.md` to `en/wiki/`, `en/docs/`, or `en/tutorials/` — auto-appears in section index.
First H1 line → page title.

## Stack

- **Haml 6.x** — layout templates
- **Sass** (sass-embedded) — stylesheets
- **Kramdown** — Markdown → HTML
- **Rake** — build orchestration
- **WEBrick** — local dev server

## License

GPL v3 — inherits OrniFlight license.
