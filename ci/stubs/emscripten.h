#pragma once
void emscripten_set_main_loop(void (*func)(void), int fps, int simulate_infinite_loop);
void emscripten_cancel_main_loop(void);
