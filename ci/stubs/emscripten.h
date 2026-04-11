#pragma once
/* Emscripten stub for CI compile checks (host gcc, not emcc) */
void emscripten_set_main_loop(void (*func)(void), int fps, int simulate_infinite_loop);
void emscripten_cancel_main_loop(void);
void emscripten_set_main_loop_timing(int mode, int value);
void emscripten_run_script(const char *script);
int  emscripten_run_script_int(const char *script);
