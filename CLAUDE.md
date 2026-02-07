# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a ZMK keyboard firmware configuration repository (forked from urob/zmk-config). It builds firmware for split keyboards (Corneish Zen, Corne) using a shared 34-key base layout with platform-specific layers for Windows and macOS. The config uses Devicetree syntax (`.keymap`, `.dtsi` files) and relies on several custom ZMK modules.

## Build Commands

Requires Nix with flakes enabled. The Nix dev shell (activated automatically via `direnv`) provides all tooling.

```bash
# First-time setup
just init              # Initialize west workspace and fetch dependencies

# Building firmware
just build zen         # Build for Corneish Zen
just build corne       # Build for Corne
just build all         # Build all targets from build.yaml
just list              # List available build targets

# Keymap visualization
just draw              # Parse base.keymap and render SVG to draw/base.svg

# Testing
just test <path>       # Run a test case (e.g., just test tests/my-test)
just test <path> --verbose      # Show keycode event log
just test <path> --auto-accept  # Accept current output as new snapshot

# Maintenance
just update            # Update ZMK and modules via west
just upgrade-sdk       # Update Nix flake inputs (Zephyr SDK, Python deps)
just clean             # Remove .build/ and firmware/
just clean-all         # Also remove .west/ and zmk/
```

Build artifacts go to `firmware/`. The build directory is `.build/`.

## Architecture

### Workspace Layout

The repository doubles as a west workspace. After `just init`, the top-level structure is:

```
├── config/          # User configuration (this is the west manifest directory)
│   ├── base.keymap  # Main keymap shared across all boards
│   ├── west.yml     # Dependency manifest (ZMK, Zephyr, modules)
│   ├── sv.dtsi      # Swedish character macros (å, ä, ö)
│   ├── mouse.dtsi   # Mouse/pointing device config
│   ├── corne.keymap / corneish_zen.keymap  # Board-specific keymaps
│   └── corne.conf / corneish_zen.conf      # Board-specific settings
├── zmk/             # ZMK firmware source (fetched by west)
├── zephyr/          # Zephyr RTOS (fetched by west)
└── modules/zmk/     # Custom ZMK modules (fetched by west)
```

### Keymap Structure

`config/base.keymap` is the central file. It defines all behaviors, macros, and layers, then board-specific keymaps (`corne.keymap`, `corneish_zen.keymap`) include it and set key position labels for their physical layout.

**11 layers** with platform-paired variants:
- `DEF_WIN`/`DEF_OSX` (0/1) - Colemak-DH base with homerow mods
- `GAME` (2) - No homerow mods
- `NAV_WIN`/`NAV_OSX` (3/4) - Navigation, window management
- `FN` (5) - Function keys
- `NUM` (6) - Numpad (auto-toggled via numword)
- `SYS` (7) - Bluetooth, media, window tiling
- `UC_WIN`/`UC_OSX` (8/9) - Symbols and Swedish unicode characters
- `MOUSE` (10) - Mouse movement/scroll/click

### Custom ZMK Modules (in `config/west.yml`)

- **zmk-helpers** - Macros like `ZMK_HOLD_TAP`, `ZMK_MOD_MORPH`, `ZMK_LAYER`, `ZMK_COMBO_*` that simplify Devicetree syntax
- **zmk-auto-layer** - Numword: auto-deactivating number layer
- **zmk-tri-state** - Used for Alt-Tab swapper and smart-mouse
- **zmk-adaptive-key** - Context-aware key behavior (used in magic-shift)
- **zmk-leader-key** - Leader key sequences
- **zmk-unicode** - Unicode character input

### Key Design Patterns

**Homerow Mods ("timeless"):** Defined via `MAKE_HRM` macro. Uses `balanced` flavor, 280ms tapping-term, `require-prior-idle-ms = 150`, positional hold-tap (only opposite-hand keys trigger hold), and `hold-trigger-on-release`. Left HRMs (`hml`) trigger on right-side keys and vice versa (`hmr`).

**Mod-morphs:** Keys change behavior with modifiers (e.g., comma → semicolon with shift → `<` with ctrl+shift). Defined via `SIMPLE_MORPH` macro wrapping `ZMK_MOD_MORPH`.

**Smart layers:** `smart_num` uses tap-dance + hold-tap + auto-layer. `smart_mouse` uses tri-state with ignored key positions.

**Platform abstraction:** Windows and macOS each get their own base/nav/unicode layers with OS-specific shortcuts. Switching between platforms uses `&to DEF_WIN` / `&to DEF_OSX`.

### Key Position Labels

Board-specific keymaps define position labels (e.g., `LT0`, `LM3`, `RB2`, `LH0`) used by homerow mods and combos for positional logic. The naming convention: `L`/`R` (left/right), `T`/`M`/`B`/`H` (top/middle/bottom/thumb), `0-4` (column index from inside out).

## File Conventions

- `.keymap` and `.dtsi` files use C/Devicetree syntax (treated as C++ for syntax highlighting via `.gitattributes`)
- Macros from zmk-helpers reduce boilerplate — prefer using `ZMK_HOLD_TAP`, `ZMK_MOD_MORPH`, `ZMK_LAYER`, etc. over raw Devicetree nodes
- `#define XXX &none` and `#define ___ &trans` are shorthand for transparent/none keys in layer definitions
- Build targets are defined in `build.yaml` and parsed by the Justfile
