# Building Blockamok³

This document covers how to compile Blockamok³ for every supported platform.
For a list of tested hardware and known performance characteristics, see [COMPATIBILITY.md](COMPATIBILITY.md).

---

## Table of Contents

- [Common Defines](#common-defines)
- [PC / Linux](#pc--linux)
- [PC / Windows (MSYS2)](#pc--windows-msys2)
- [PC / Windows (Visual Studio 2022)](#pc--windows-visual-studio-2022)
- [macOS](#macos)
- [Web (Emscripten / WebAssembly)](#web-emscripten--webassembly)
- [Android](#android)
- [Nintendo Switch](#nintendo-switch)
- [Nintendo Wii U](#nintendo-wii-u)
- [Nintendo Wii](#nintendo-wii)
- [Nintendo GameCube](#nintendo-gamecube)
- [Nintendo 3DS](#nintendo-3ds)
- [PlayStation Vita](#playstation-vita)
- [PlayStation Portable (PSP)](#playstation-portable-psp)
- [PlayStation 3](#playstation-3)
- [Xbox (Original)](#xbox-original)
- [Xbox 360](#xbox-360)
- [RG35XX / Handheld Linux](#rg35xx--handheld-linux)

---

## Common Defines

These preprocessor defines are available across all platforms and affect rendering behaviour:

| Define | Effect |
|---|---|
| `FORCE_DRAW_OVERLAY` | Redraws the side-bar overlay every frame. Use if it flickers or the inner black border doesn't appear. |
| `FORCE_DRAW_BG` | Redraws the background gradient every frame instead of caching it as a texture. May help or hurt performance depending on the GPU driver. |
| `LOW_SPEC_BG` | Replaces the gradient background with a flat colour. Worst visually, but fastest. Do **not** combine with `FORCE_DRAW_BG`. |

---

## PC / Linux

**Requirements:**
- GCC or Clang
- SDL2, SDL2_mixer, SDL2_ttf, libmikmod (dev packages)

```bash
# Ubuntu / Debian
sudo apt install gcc make libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libmikmod-dev

# Arch
sudo pacman -S gcc make sdl2 sdl2_mixer sdl2_ttf

make -f Makefiles/Makefile_linux
```

The output binary is `blockamokremix` in the project root.

**Low-end mode** (smaller binary, disables gradient background):
```bash
make -f Makefiles/Makefile_linux LOW_END=1
```

---

## PC / Windows (MSYS2)

**Requirements:**
- [MSYS2](https://www.msys2.org/)

Open the **MSYS2 MinGW 64-bit** shell and run:

```bash
# Install toolchain and SDL2 libraries
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 \
          mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_ttf \
          mingw-w64-x86_64-pkgconf make

# Build 64-bit
make -f Makefiles/Makefile_pc

# Build 64-bit, size-optimised (good for older PCs)
make -f Makefiles/Makefile_pc LOW_END=1
```

For a **32-bit (x86)** build, use the **MSYS2 MinGW 32-bit** shell:

```bash
pacman -S mingw-w64-i686-gcc mingw-w64-i686-SDL2 \
          mingw-w64-i686-SDL2_mixer mingw-w64-i686-SDL2_ttf \
          mingw-w64-i686-pkgconf make

make -f Makefiles/Makefile_pc_x86
```

Output: `BlockamokRemix.exe` in the project root.

---

## PC / Windows (Visual Studio 2022)

**Requirements:**
- Visual Studio 2022 (Desktop C++ workload)
- SDL2, SDL2_mixer, SDL2_ttf **VC development libraries**

**Step 1 — Download SDL2 VC libraries**

Download the **VC** (not MinGW) zip files from the SDL releases pages:

| Library | Release page |
|---|---|
| SDL2 | https://github.com/libsdl-org/SDL/releases |
| SDL2_mixer | https://github.com/libsdl-org/SDL_mixer/releases |
| SDL2_ttf | https://github.com/libsdl-org/SDL_ttf/releases |

**Step 2 — Extract into the required folder structure**

Create a folder called `SDL2` **inside the project root** (`Blockamok3/SDL2/`).
Extract each zip so the layout matches exactly:

```
Blockamok3/
└── SDL2/
    ├── SDL2/
    │   ├── include/    ← SDL.h, SDL_version.h, …
    │   └── lib/
    │       ├── x64/    ← SDL2.lib, SDL2main.lib, SDL2.dll
    │       └── x86/
    ├── SDL2_mixer/
    │   ├── include/    ← SDL_mixer.h
    │   └── lib/
    │       ├── x64/    ← SDL2_mixer.lib, SDL2_mixer.dll
    │       └── x86/
    └── SDL2_ttf/
        ├── include/    ← SDL_ttf.h
        └── lib/
            ├── x64/    ← SDL2_ttf.lib, SDL2_ttf.dll
            └── x86/
```

> **Tip:** Each SDL2 VC zip extracts as e.g. `SDL2-2.30.10/`. Just rename that folder to `SDL2`, `SDL2_mixer`, or `SDL2_ttf` respectively before moving it into the `SDL2/` parent.

**Step 3 — Build**

Open `blockamok.sln` in Visual Studio 2022 and build the **Release | x64** configuration,
or from a Developer Command Prompt:

```bat
MSBuild blockamok.sln /p:Configuration=Release /p:Platform=x64
```

The EXE is placed in `x64\Release\BlockamokRemix.exe`.
Copy the SDL2 DLLs from `SDL2\SDL2\lib\x64\`, `SDL2\SDL2_mixer\lib\x64\`, and `SDL2\SDL2_ttf\lib\x64\` next to the EXE before distributing.

---

## macOS

**Requirements:**
- Xcode command-line tools (`xcode-select --install`)
- SDL2, SDL2_mixer, SDL2_ttf via Homebrew

```bash
brew install sdl2 sdl2_mixer sdl2_ttf

make -f Makefiles/Makefile_mac
```

Output: `BlockamokRemix` in the project root.

---

## Web (Emscripten / WebAssembly)

**Requirements:**
- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html) ≥ 3.1.59

```bash
# Activate emsdk (adjust path as needed)
source ~/emsdk/emsdk_env.sh

make -f Makefiles/Makefile_wasm -j$(nproc)
```

Output is written to the `web/` directory:
- `web/index.html` — launcher page (open this in a browser)
- `web/index.js` — Emscripten JS glue
- `web/index.wasm` — compiled game
- `web/index.data` — preloaded asset bundle (font)

To run locally (browsers block `file://` WASM loading):
```bash
cd web && python3 -m http.server 8080
# Open http://localhost:8080 in your browser
```

The CI automatically deploys `web/` to **GitHub Pages** on every push to `main`.

---

## Android

**Requirements:**
- Android Studio **or** the Android command-line tools
- Android NDK r26 (`ndk;26.3.11579264`)
- Android SDK with platform `android-36`
- JDK 17
- SDL2, SDL2_mixer, SDL2_ttf Android sources (downloaded automatically by the build)

**Step 1 — Get SDL2 Android sources**

Download and extract the following source archives into `android/app/src/main/jni/`:

| Library | Version | URL |
|---|---|---|
| SDL2 | 2.30.10 | https://github.com/libsdl-org/SDL/releases |
| SDL2_mixer | 2.8.0 | https://github.com/libsdl-org/SDL_mixer/releases |
| SDL2_ttf | 2.22.0 | https://github.com/libsdl-org/SDL_ttf/releases |

The resulting layout should be:
```
android/app/src/main/jni/
├── SDL2/
├── SDL2_mixer/
└── SDL2_ttf/
```

**Step 2 — Copy game source**

```bash
cp src/*.{c,h}        android/app/src/main/c/
cp src/audio/*.{c,h}  android/app/src/main/c/audio/
cp src/fonts/*.{c,h}  android/app/src/main/c/fonts/
```

**Step 3 — Build**

```bash
cd android
./gradlew assembleDebug     # debug APK
./gradlew assembleRelease   # release APK (requires signing config)
```

APK output: `android/app/build/outputs/apk/`

**SDK versions:**
- `minSdk`: **19** (Android 4.4 KitKat and above)
- `targetSdk`: **36** (Android 16)
- All four ABI targets are built: `armeabi-v7a`, `arm64-v8a`, `x86`, `x86_64`

**Orientation:** The app is locked to **landscape** via `android:screenOrientation="landscape"` in the manifest. If you ever see portrait mode on first launch, this is caused by a missing or wrong `screenOrientation` attribute — the current manifest is correct.

---

## Nintendo Switch

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitA64`
- `switch-portlibs` package group (includes SDL2 for Switch)

```bash
# Install via dkp-pacman
dkp-pacman -S switch-portlibs switch-sdl2 switch-sdl2_mixer switch-sdl2_ttf

make -f Makefiles/Makefile_switch
```

Output: `BlockamokRemix.nro` (sideloadable via homebrew menu).

> **Emulator note:** When running under **Eden** (yuzu-android fork), set the CPU backend to **Dynarmic (JIT)** instead of NCE. Eden's NCE patcher crashes on this NRO due to a bug in Eden itself. The NRO works correctly on hardware and in Ryujinx.

---

## Nintendo Wii U

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitPPC`
- `wut` (Wii U Toolkit), `wiiu-sdl2`, `wiiu-sdl2_mixer`, `wiiu-sdl2_ttf`

```bash
dkp-pacman -S wut wiiu-sdl2 wiiu-sdl2_mixer wiiu-sdl2_ttf wiiu-cmake

mkdir build_wiiu && cd build_wiiu
cmake .. -DCMAKE_TOOLCHAIN_FILE="$DEVKITPRO/cmake/WiiU.cmake" -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

A convenience script `Makefiles/make_wii_u.sh` is included that runs these steps automatically once the prerequisites are installed.

---

## Nintendo Wii

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitPPC`
- `wii-sdl2`, `wii-sdl2_mixer`, `wii-sdl2_ttf`, `libfat-ogc`

```bash
dkp-pacman -S wii-sdl2 wii-sdl2_mixer wii-sdl2_ttf libfat-ogc

make -f Makefiles/Makefile_wii
```

Place the output `.dol` in `sd:/apps/BlockamokRemix/boot.dol` on your SD card.

---

## Nintendo GameCube

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitPPC`
- `gamecube-sdl2`, `gamecube-sdl2_mixer`, `gamecube-sdl2_ttf`, `libfat-ogc`

```bash
dkp-pacman -S gamecube-sdl2 gamecube-sdl2_mixer gamecube-sdl2_ttf libfat-ogc

make -f Makefiles/Makefile_gc
```

The game auto-detects SD cards on slots A, B, and C for save data.

---

## Nintendo 3DS

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitARM`
- `3ds-dev`, `3ds-sdl2`, `3ds-sdl2_mixer`, `3ds-sdl2_ttf`

```bash
dkp-pacman -S 3ds-dev 3ds-sdl2 3ds-sdl2_mixer 3ds-sdl2_ttf

make -f Makefiles/Makefile_3ds
```

Outputs a `.cia` (installable) and a `.3dsx` (Homebrew Launcher).

**New 3DS:** Recommended clock speed is the upgraded 804 MHz mode, toggled via the in-game debug cheat (see credits screen). The `useNew3DSClockSpeed` flag in `main.c` controls this.

---

## PlayStation Vita

**Requirements:**
- [VitaSDK](https://vitasdk.org/) installed to `/usr/local/vitasdk`
- SDL2, SDL2_mixer, SDL2_ttf installed via [vdpm](https://github.com/vitasdk/vdpm)

```bash
# Install vdpm packages (only needed once)
export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH
vdpm SDL2
vdpm SDL2_mixer
vdpm SDL2_ttf

# Build
bash Makefiles/make_vita.sh
```

Output: `BlockamokRemix.vpk` — installable via VitaShell.

Save data is stored at `ux0:data/BlockamokRemix/`.

---

## PlayStation Portable (PSP)

**Requirements:**
- [pspdev toolchain](https://pspdev.github.io/) (Linux or WSL strongly recommended)
- SDL2, SDL2_mixer, SDL2_ttf (included with pspdev or installable via `psp-pacman`)

```bash
# Install SDL2 (if not already present in your pspdev install)
psp-pacman -S psp-sdl2 psp-sdl2_mixer psp-sdl2_ttf

# Set pkg-config path so make can find the SDL2 flags
export PKG_CONFIG_PATH=/usr/local/pspdev/psp/lib/pkgconfig

make -f Makefiles/Makefile_psp
```

Output: `EBOOT.PBP`. Place it at `PSP/GAME/BlockamokRemix/EBOOT.PBP` on your Memory Stick.

> **Overclock:** The PSP build benefits significantly from running at 333 MHz. The game does not set the CPU clock itself; use a plugin (e.g. `overclock.prx`) or enable overclock in the launcher if your CFW supports it.

---

## PlayStation 3

**Requirements:**
- [ps3toolchain](https://github.com/ps3dev/ps3toolchain) + PSL1GHT, **or** the [`ps3dev/ps3dev` Docker image](https://hub.docker.com/r/ps3dev/ps3dev) (much faster)
- SDL2 for PS3 (included in ps3toolchain)

**Using Docker (recommended):**
```bash
docker run --rm -v "$PWD:/build" -w /build ps3dev/ps3dev:latest \
  make -f Makefiles/Makefile_ps3 -j$(nproc)
```

**Manual (after building ps3toolchain):**
```bash
export PS3DEV=/usr/local/ps3dev
export PSL1GHT=$PS3DEV/psl1ght
export PATH=$PS3DEV/bin:$PS3DEV/ppu/bin:$PATH

make -f Makefiles/Makefile_ps3
```

Output: `BlockamokRemix.self` — run via a CFW or HEN-enabled PS3 using webMAN or similar.

---

## Xbox (Original)

**Requirements:**
- [nxdk](https://github.com/XboxDev/nxdk) with its bundled LLVM/Clang toolchain, **or** the [`ghcr.io/xboxdev/nxdk` Docker image](https://github.com/XboxDev/nxdk/pkgs/container/nxdk) (recommended)

**Using Docker (recommended):**
```bash
docker run --rm -v "$PWD:/build" -w /build ghcr.io/xboxdev/nxdk:latest \
  make -f Makefiles/Makefile_xbox NXDK_DIR=/nxdk -j$(nproc)
```

**Manual:**
```bash
# Clone and build nxdk (takes ~20 min on first run)
git clone --recursive https://github.com/XboxDev/nxdk.git ~/nxdk
cd ~/nxdk && make toolchain -j$(nproc)

# Build the game
cd /path/to/Blockamok3
NXDK_DIR=~/nxdk make -f Makefiles/Makefile_xbox -j$(nproc)
```

Output: `BlockamokRemix.xbe` + `BlockamokRemix.iso` — run on an original Xbox with a modchip or soft-mod, or in the **xemu** emulator.

---

## Xbox 360

**Requirements:**
- [libxenon](https://github.com/Free60Project/libxenon) cross-compiler (`powerpc64-xenon-elf-gcc`)

**Build the toolchain** (one-time, ~25–35 minutes):
```bash
PREFIX=/usr/local/xenon
git clone --depth=1 https://github.com/Free60Project/libxenon.git /tmp/libxenon
cd /tmp/libxenon
CROSS_INSTALL_PREFIX=$PREFIX make -j$(nproc) toolchain
CROSS_INSTALL_PREFIX=$PREFIX make -j$(nproc) install
export PATH=$PREFIX/bin:$PATH
```

**Build the game:**
```bash
XENON_DIR=/usr/local/xenon make -f Makefiles/Makefile_xbox360 -j$(nproc)
```

Output: `BlockamokRemix.xex` — run on an RGH/JTAG Xbox 360 using Freestyle Dash or Aurora, or in the **Xenia** emulator.

---

## RG35XX / Handheld Linux

A convenience script is provided for the Anbernic RG35XX and similar Linux handhelds running GarlicOS or compatible firmware:

```bash
bash Makefiles/make_rg35xx.sh
```

The script sets the appropriate cross-compiler flags and produces a binary compatible with these devices. See `release-resources/Blockamok_rg35xx.sh` for the launcher wrapper.
