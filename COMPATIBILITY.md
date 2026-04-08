# Blockamok³ - Platforms & Compatibility
This Markdown is made to list all platforms supported by Blockamok Remix² as well as their compatibility (Runs well or not)

## Compatibility Score
| Icon | Percentage | Description |
|------|------------|-------------|
| 🟪 | 100% | Runs perfectly, no known issues |
| 🟦 | 85-99% | Runs nicely, minor issue(s) |
| 🟩 | 75-84% | Runs great, small issues |
| 🟨 | 50-74% | Runs okay, lots of issues |
| 🟧 | 25-49% | Runs badly, major issues |
| 🟥 | 1-24% | Runs terribly, major issues |
| ⬛ | 0% | Nothing / No results, needs work |

## List
| Platforn | Status | Compatibility |
|----------|--------|---------------|
| 3DS | Stable Releases | Unknown, needs testing |
| Android | Stable Releases | 🟦 |
| Android TV | Coming Soon | None |
| FreeBSD | Coming Soon | None |
| GameBoy | Coming Soon | None |
| GameBoy Advance / Advance SP | Coming Soon | None |
| GameBoy Color | Coming Soon | None |
| GameCube | Stable Releases | 🟩 |
| Haiku | Coming Soon | None |
| Linux | Stable Releases | Unknown, needs testing |
| macOS (Intel) | Coming Soon | None |
| macOS (Apple Silicon) | Coming Soon | None |
| MS-DOS | Coming Soon | None |
| NetBSD | Coming Soon | None |
| NES | Coming Soon | None |
| Nintendo 64 | Coming Soon | None |
| Nintendo DS | Coming Soon | None |
| OpenBSD | Coming Soon | None |
| OpenDingux | Coming Soon | None |
| PocketStation | Coming Soon | None |
| PS1 / PSOne | Coming Soon | None |
| PS2 | Coming Soon | None |
| PS3 | Coming Soon | None |
| PS4 | Coming Soon | None |
| PSP | Stable Releases | 🟦 |
| PS Vita | Stable Releases | 🟦 |
| Raspberry Pi | Coming Soon | None |
| SNES | Coming Soon | None |
| Switch | Stable Releases | 🟦 |
| Web (WASM) | Coming Soon | None |
| Wii | Stable Releases | 🟨 |
| Wii U | Stable Releases | Unknown, needs testing |
| Windows (10 - 11) | Stable Releases | 🟪 |
| Windows (7 - 8.1) | Coming Soon | None |
| Windows (95 - Vista) | Coming Soon | None |
| Xbox (original) | Coming Soon | None |
| Xbox 360 | Coming Soon | None |

## Xbox 360
- **Toolchain:** libxenon (powerpc64-xenon-elf-gcc)
- **Makefile:** `Makefiles/Makefile_xbox360`
- **Define:** `-DXBOX360`
- **Input:** libxenon USB HID (`input/input.h`)
- **Notes:** `cubeBoundsBase = 9.0` (~60 FPS retail). Build produces a `.xex` file ready for RGH/JTAG consoles.

## PS3
- **Toolchain:** ps3toolchain / PSL1GHT (ppu-gcc)
- **Makefile:** `Makefiles/Makefile_ps3`
- **Define:** `-DPS3`
- **Input:** PSL1GHT `ioPad` API (`io/pad.h`)
- **Notes:** `cubeBoundsBase = 8.5` (~55-60 FPS). Build produces a `.self` via `make_self_npdrm`. Requires a CFW/HEN PS3.

## Web (Emscripten / WebAssembly)
- **Toolchain:** Emscripten SDK 3.1.59+
- **Makefile:** `make -f Makefiles/Makefile_wasm`
- **Define:** `-D__EMSCRIPTEN__`
- **Notes:** Uses `emscripten_set_main_loop()` for browser-friendly frame scheduling. All SDL2 subsystems pulled in via Emscripten ports. Outputs to `web/`. Keyboard + gamepad supported. Automatically deployed to GitHub Pages on push to `main`.

---

## Emulator Notes

### Nintendo Switch – Eden / yuzu-android
Eden (a yuzu fork for Android) crashes when launching the NRO with **NCE (Native Code Execution)** mode enabled. The crash originates entirely inside Eden's own NCE patcher (`core/arm/nce/patcher.cpp:PatchText` hitting an unreachable assertion) and is **not caused by Blockamok**. The NRO itself is valid and runs correctly on hardware and in other emulators.

**Workaround:** In Eden → Settings → CPU → change **CPU Backend** from *NCE* to *Dynarmic (JIT)*. The game runs fine with JIT.

Alternative emulators that work without this issue: **Ryujinx**, **Yuzu** (legacy builds).
