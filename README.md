<h1 align="center">Blockamok³</h1>

<p align="center"><b>A CPU-only, from-scratch 3D game written in C, where you dodge blocks<br>
Available for all the platforms listed <a href="https://github.com/SSMG4/Blockamok3/blob/main/COMPATIBILITY.md" target="_blank" rel="noopener noreferrer">here</a></b></p>

<p align="center">You accidentally fly your spaceship into a wormhole. To your shock, you find yourself in an alternate dimension filled with blocks. The throttle on your spaceship is broken and keeps increasing the speed. How far can you make it?</p>

<p align="center"><img alt="Gameplay" src="gameplay.gif"/></p>

## Background

Blockamok³ is an extension to [Blockamok Remix](https://github.com/Mode8fx/blockamok), which itself is an update of the game [Blockamok](https://github.com/carltheperson/blockamok), a game originally made by Carl Riis to _"challenge [himself] to create a 3D game without any pre-made 3D engine or utilities"_.

This version adds many platforms and bugfixes to the game such as:
- The web (via WASM)
- Android TV
- Xbox 360 and PS3
- And much more!

## How can I play it?

[Check the latest release here.](https://github.com/SSMG4/Blockamok3/releases)

Keep in mind that due to hardware and library differences, this game runs better on some systems than others, and it's not necessarily determined by the power of the system. For example, the GameCube and Wii versions both run better than Wii U.

## Can I port it to other systems?

Go ahead! Just make sure you appropriately follow the MIT License.

This game is made using SDL2. Controller and keyboard input are handled through SDL_GameController and keyboard state respectively, and there aren't many system-specific defines. Depending on the system, you probably want to use the Linux Makefile as a base along with the `LINUX` define (and possibly `PC` as well).

The following additional defines exist and may be needed:
- `FORCE_DRAW_OVERLAY`: This makes the game redraw the overlay (colored side bars) on every frame. Enable this if the overlay has a visual issue such as flickering, or if the thin black bars on the inside edge of the overlay do not render.
- `FORCE_DRAW_BG`: This makes the game redraw the transparent background triangles on every frame instead of drawing them once and saving+rendering as a texture. Enabling this may increase or decrease performance depending on the device.
- `LOW_SPEC_BG` - Enable this to replace the background with a flat color. This looks the worst visually, so only use it if the other background options result in poor performance. Do not use `FORCE_DRAW_BG` and `LOW_SPEC_BG` together.

## How to Compile

Detailed build instructions for every supported platform are in **[BUILDING.md](BUILDING.md)**.

Quick reference:

| Platform | Command |
|---|---|
| Linux | `make -f Makefiles/Makefile_linux` |
| Windows (MSYS2 x64) | `make -f Makefiles/Makefile_pc` |
| Windows (MSYS2 x86) | `make -f Makefiles/Makefile_pc_x86` |
| Web (Emscripten) | `make -f Makefiles/Makefile_wasm` |
| Nintendo Switch | `make -f Makefiles/Makefile_switch` |
| Nintendo Wii U | `bash Makefiles/make_wii_u.sh` |
| Nintendo Wii | `make -f Makefiles/Makefile_wii` |
| Nintendo GameCube | `make -f Makefiles/Makefile_gc` |
| Nintendo 3DS | `make -f Makefiles/Makefile_3ds` |
| PlayStation Vita | `bash Makefiles/make_vita.sh` |
| PSP | `make -f Makefiles/Makefile_psp` |
| PS3 | `make -f Makefiles/Makefile_ps3` |
| Xbox (Original) | `make -f Makefiles/Makefile_xbox` |
| Xbox 360 | `make -f Makefiles/Makefile_xbox360` |

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
