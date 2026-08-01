# OrniFlight Website

Static site for the OrniFlight servo-flapping flight controller firmware.

## Quick Start

```bash
cd site
bundle exec rake server     # → http://localhost:8001
```

Open **http://localhost:8001** in your browser. The server auto-reloads on changes.

## Design

- **Font:** Open Sans (Google Fonts) — matches OrniFlight Configurator UI
- **Accent:** Periwinkle `#8998fe` — the OrniFlight brand color
- **Dark Mode:** `#202020` body, `#3a3a3a` cards, indigo `#3a4192` header
- **Light Mode:** Warm parchment `#f5f0e8`, sky blue `#4a7a9a`
- **Parallax Hero:** CSS-only, scrolls logo + overlay on landing page
- **Assets:** Logo SVGs, paper textures, dark/light mode icons — all from Configurator

## Architecture

```
site/
├── index.haml              # Landing page template (HAML)
├── _lang/                  # i18n JSON (en, de)
│   ├── en.json
│   └── de.json
├── assets/
│   ├── css/style.sass      # Indented syntax, dark/light themes
│   └── images/             # Logos, textures, icons (from Configurator)
├── en/                     # English subpages (Markdown)
│   ├── wiki/               # ONDAS theory, MSP, profiles
│   ├── docs/               # Hardware, CLI reference
│   └── tutorials/          # First flash, setup, tuning
├── de/                     # German subpages
├── Rakefile                # Build: HAML→HTML, SASS→CSS, MD→HTML
├── Gemfile                 # Ruby dependencies
├── watch.sh                # Auto-rebuild on changes
└── README.md
```

## Building

```bash
bundle exec rake build      # Full: landing + sass + content pages
bundle exec rake server     # Local server → http://localhost:8001
bundle exec rake watch      # Auto-rebuild on changes
```

Or use the shortcut:

```bash
./watch.sh
```

## Content Pages

Wiki, docs, and tutorials are written in **Markdown** (`.md`). The Rakefile converts them to HTML wrapped in a HAML layout template. Add a `.md` file to `en/wiki/`, `en/docs/`, or `en/tutorials/` — it auto-appears in the section index.

The first line (H1 heading) becomes the page title.

## Stack

- **Haml 6.x** — layout templates
- **Sass** (sass-embedded) — stylesheets
- **Kramdown** — Markdown → HTML
- **Rake** — build orchestration
- **WEBrick** — local dev server

## License

GPL v3 — inherits OrniFlight license.
