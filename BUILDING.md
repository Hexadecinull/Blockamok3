# Building Blockamok³

This document covers how to compile Blockamok³ for every supported platform.
For a list of tested hardware and known performance characteristics, see [COMPATIBILITY.md](COMPATIBILITY.md).

> **How to read the "Compiled on" field:** This is the host machine OS you need to run the compiler/toolchain on. Most cross-toolchains run on Linux; Windows-native toolchains are noted where applicable.

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

> **Compiled on:** Linux

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

> **Compiled on:** Windows (via MSYS2 shell)

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

For a **32-bit (x86)** build, open the **MSYS2 MinGW 32-bit** shell:

```bash
pacman -S mingw-w64-i686-gcc mingw-w64-i686-SDL2 \
          mingw-w64-i686-SDL2_mixer mingw-w64-i686-SDL2_ttf \
          mingw-w64-i686-pkgconf make

make -f Makefiles/Makefile_pc_x86
```

Output: `BlockamokRemix.exe` in the project root.

---

## PC / Windows (Visual Studio 2022)

> **Compiled on:** Windows (Visual Studio 2022)

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
Each zip contains a single top-level folder (e.g. `SDL2-2.30.10/`). Extract each one and rename that folder so the layout looks like:

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

**Step 3 — Build**

Open `blockamok.sln` in Visual Studio 2022 and build the **Release | x64** configuration, or from a Developer Command Prompt:

```bat
MSBuild blockamok.sln /p:Configuration=Release /p:Platform=x64
```

The EXE is at `x64\Release\BlockamokRemix.exe`.
Copy the three SDL2 DLLs from `SDL2\SDL2\lib\x64\`, `SDL2\SDL2_mixer\lib\x64\`, and `SDL2\SDL2_ttf\lib\x64\` next to the EXE before distributing.

---

## macOS

> **Compiled on:** macOS

**Requirements:**
- Xcode command-line tools (`xcode-select --install`)
- Homebrew

```bash
brew install sdl2 sdl2_mixer sdl2_ttf

make -f Makefiles/Makefile_mac
```

Output: `BlockamokRemix` in the project root.

---

## Web (Emscripten / WebAssembly)

> **Compiled on:** Linux, macOS, or Windows (with MSYS2 or WSL)

**Requirements:**
- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html) ≥ 3.1.59

```bash
# Activate emsdk (adjust path as needed)
source ~/emsdk/emsdk_env.sh

make -f Makefiles/Makefile_wasm -j$(nproc)
```

Output is written to the `web/` directory:

| File | Description |
|---|---|
| `web/index.html` | Launcher page — open this in a browser |
| `web/index.js` | Emscripten JavaScript glue |
| `web/index.wasm` | Compiled game binary |
| `web/index.data` | Preloaded asset bundle (font) |

To run locally (browsers block `file://` WASM loading):
```bash
cd web && python3 -m http.server 8080
# Open http://localhost:8080
```

The CI automatically deploys `web/` to **GitHub Pages** on every push to `main` (requires Pages to be enabled in the repository settings: Settings → Pages → Source → GitHub Actions).

---

## Android

> **Compiled on:** Linux, macOS, or Windows — anywhere the Android SDK runs

**Requirements:**
- Android Studio **or** the Android command-line tools
- Android NDK r26 (`ndk;26.3.11579264`)
- Android SDK Platform `android-36`
- JDK 17
- Gradle 8.7+

**Step 1 — Get SDL2 Android sources**

Download and extract these source archives into `android/app/src/main/jni/` (creating a subfolder for each):

| Library | Version | URL |
|---|---|---|
| SDL2 | 2.30.10 | https://github.com/libsdl-org/SDL/releases |
| SDL2_mixer | 2.8.0 | https://github.com/libsdl-org/SDL_mixer/releases |
| SDL2_ttf | 2.22.0 | https://github.com/libsdl-org/SDL_ttf/releases |

The resulting layout:
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

**Step 3 — Generate Gradle wrapper and build**

```bash
cd android
gradle wrapper --gradle-version 8.7
./gradlew assembleDebug     # debug APK
./gradlew assembleRelease   # release APK (requires signing config)
```

APK output: `android/app/build/outputs/apk/`

**SDK versions:** `minSdk 19` (Android 4.4+) · `targetSdk 36` (Android 16) · ABIs: `armeabi-v7a`, `arm64-v8a`, `x86`, `x86_64`

**Orientation:** Locked to **landscape** via `android:screenOrientation="landscape"` in the manifest. This is the fix for the portrait-mode bug present in earlier versions.

---

## Nintendo Switch

> **Compiled on:** Linux, macOS, or Windows (devkitPro supports all three)

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitA64`
- `switch-portlibs` package group

```bash
dkp-pacman -S switch-portlibs switch-sdl2 switch-sdl2_mixer switch-sdl2_ttf

make -f Makefiles/Makefile_switch
```

Output: `BlockamokRemix.nro` — place in `switch/BlockamokRemix/` on your SD card and launch via the homebrew menu.

> **Emulator note (Eden/yuzu-android):** Set CPU backend to **Dynarmic (JIT)** instead of NCE. Eden's NCE patcher crashes on this NRO due to a bug in Eden itself — the NRO is valid and works correctly on hardware and in Ryujinx.

---

## Nintendo Wii U

> **Compiled on:** Linux, macOS, or Windows (devkitPro supports all three)

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitPPC`
- `wut`, `wiiu-sdl2`, `wiiu-sdl2_mixer`, `wiiu-sdl2_ttf`, `wiiu-cmake`

```bash
dkp-pacman -S wut wiiu-sdl2 wiiu-sdl2_mixer wiiu-sdl2_ttf wiiu-cmake

mkdir build_wiiu && cd build_wiiu
cmake .. -DCMAKE_TOOLCHAIN_FILE="$DEVKITPRO/cmake/WiiU.cmake" -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

A convenience script `Makefiles/make_wii_u.sh` runs these steps automatically once the prerequisites are installed.

---

## Nintendo Wii

> **Compiled on:** Linux, macOS, or Windows (devkitPro supports all three)

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitPPC`
- `wii-sdl2`, `wii-sdl2_mixer`, `wii-sdl2_ttf`, `libfat-ogc`

```bash
dkp-pacman -S wii-sdl2 wii-sdl2_mixer wii-sdl2_ttf libfat-ogc

make -f Makefiles/Makefile_wii
```

Place the output `.dol` at `sd:/apps/BlockamokRemix/boot.dol` on your SD card. Save data is stored at `sd:/apps/BlockamokRemix/`.

---

## Nintendo GameCube

> **Compiled on:** Linux, macOS, or Windows (devkitPro supports all three)

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitPPC`
- `gamecube-sdl2`, `gamecube-sdl2_mixer`, `gamecube-sdl2_ttf`, `libfat-ogc`

```bash
dkp-pacman -S gamecube-sdl2 gamecube-sdl2_mixer gamecube-sdl2_ttf libfat-ogc

make -f Makefiles/Makefile_gc
```

Save data is stored on an SD card; the game tries slots A, B, and C automatically.

---

## Nintendo 3DS

> **Compiled on:** Linux, macOS, or Windows (devkitPro supports all three)

**Requirements:**
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with `devkitARM`
- `3ds-dev`, `3ds-sdl2`, `3ds-sdl2_mixer`, `3ds-sdl2_ttf`

```bash
dkp-pacman -S 3ds-dev 3ds-sdl2 3ds-sdl2_mixer 3ds-sdl2_ttf

make -f Makefiles/Makefile_3ds
```

Outputs a `.cia` (installable via FBI) and a `.3dsx` (Homebrew Launcher). The `.cia` is recommended for regular use.

**New 3DS:** The game can enable the 804 MHz clock boost via an in-game toggle in the credits screen. The Old 3DS runs at reduced speed but is still playable.

---

## PlayStation Vita

> **Compiled on:** Linux (strongly recommended; macOS works; Windows via WSL)

**Requirements:**
- [VitaSDK](https://vitasdk.org/) installed to `/usr/local/vitasdk`
- SDL2, SDL2_mixer, SDL2_ttf installed via [vdpm](https://github.com/vitasdk/vdpm)

```bash
export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH

# Install SDL2 packages (only needed once)
vdpm SDL2
vdpm SDL2_mixer
vdpm SDL2_ttf

# Build
bash Makefiles/make_vita.sh
```

Output: `BlockamokRemix.vpk` — install via VitaShell. Save data is stored at `ux0:data/BlockamokRemix/`.

---

## PlayStation Portable (PSP)

> **Compiled on:** Linux (strongly recommended; Windows via WSL)

**Requirements:**
- [pspdev toolchain](https://pspdev.github.io/)
- SDL2, SDL2_mixer, SDL2_ttf (included with pspdev or via `psp-pacman`)

```bash
# Install SDL2 if not already present
psp-pacman -S psp-sdl2 psp-sdl2_mixer psp-sdl2_ttf

# Set pkg-config path so make can find SDL2 flags
export PKG_CONFIG_PATH=/usr/local/pspdev/psp/lib/pkgconfig

make -f Makefiles/Makefile_psp
```

Output: `EBOOT.PBP` — place at `PSP/GAME/BlockamokRemix/EBOOT.PBP` on your Memory Stick.

> **Overclock:** The PSP benefits significantly from running at 333 MHz. The game does not set the CPU clock itself; use a plugin such as `overclock.prx` or enable it in your CFW launcher.

---

## PlayStation 3

> **Compiled on:** Linux

**Requirements:**
- [ps3toolchain](https://github.com/ps3dev/ps3toolchain) + PSL1GHT

**Build the toolchain** (one-time, ~35–45 minutes):
```bash
export PS3DEV=/usr/local/ps3dev
export PSL1GHT=$PS3DEV/psl1ght

git clone --depth=1 https://github.com/ps3dev/ps3toolchain.git /tmp/ps3toolchain
cd /tmp/ps3toolchain
INSTALL_PREFIX=$PS3DEV bash toolchain.sh
```

**Build the game:**
```bash
export PATH=$PS3DEV/bin:$PS3DEV/ppu/bin:$PATH
make -f Makefiles/Makefile_ps3
```

Output: `BlockamokRemix.self` — run on a CFW or HEN-enabled PS3 via webMAN, multiMAN, or similar homebrew launcher.

---

## Xbox (Original)

> **Compiled on:** Linux (via the nxdk Docker container or installed nxdk)

**Recommended — Docker:**
```bash
docker run --rm -v "$PWD:/build" -w /build \
  ghcr.io/xboxdev/nxdk:latest \
  make -f Makefiles/Makefile_xbox NXDK_DIR="$NXDK_DIR" -j$(nproc)
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

Output: `BlockamokRemix.xbe` — run on an original Xbox with a modchip or softmod, or in the **xemu** emulator.

---

## Xbox 360

> **Compiled on:** Linux

**Requirements:**
- [libxenon](https://github.com/Free60Project/libxenon) cross-compiler (`powerpc64-xenon-elf-gcc`)

**Build the toolchain** (one-time, ~25–35 minutes):
```bash
export PREFIX=/usr/local/xenon
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

Output: `BlockamokRemix.xex` — run on an RGH/JTAG Xbox 360 via Freestyle Dash or Aurora, or in the **Xenia** emulator.

---

## RG35XX / Handheld Linux

> **Compiled on:** Linux (cross-compiled for ARM using the GarlicOS/Buildroot SDK)

The RG35XX and compatible Anbernic handhelds (RG35XX-H, RG35XX+, etc.) run a custom ARM Linux. A Buildroot-based cross-toolchain is available from the [GarlicOS buildroot repository](https://github.com/GarlicOS/buildroot/releases).

**Step 1 — Get the SDK:**
```bash
SDK_URL="https://github.com/GarlicOS/buildroot/releases/latest/download/arm-buildroot-linux-gnueabihf_sdk-buildroot.tar.gz"
sudo mkdir -p /usr/local/rg35xx
sudo tar -xz -C /usr/local/rg35xx < <(curl -L "$SDK_URL")
# Run the relocation script
/usr/local/rg35xx/arm-buildroot-linux-gnueabihf_sdk-buildroot/relocate-sdk.sh
```

**Step 2 — Build:**
```bash
export RGTOOLCHAIN=/usr/local/rg35xx/arm-buildroot-linux-gnueabihf_sdk-buildroot
bash Makefiles/make_rg35xx.sh
```

Output: binary in `build_rg35xx/`. Use the `release-resources/Blockamok_rg35xx.sh` launcher wrapper for correct library paths on the device.

> **Note:** The RG35XX build shares the same Linux + SDL2 code path as the PC Linux build (`-DLINUX -DPC`). There is no separate "handheld Linux" CI — the compile-check CI's `PC_LINUX` matrix entry verifies this code path on every push.
