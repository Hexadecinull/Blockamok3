#pragma once
/* SDL_ttf stub for CI compile checks — do NOT redeclare SDL_bool (SDL2 owns it) */
typedef struct { int dummy; } TTF_Font;
int  TTF_Init(void);
void TTF_Quit(void);
TTF_Font *TTF_OpenFontRW(void *src, int freesrc, int ptsize);
void TTF_CloseFont(TTF_Font *font);
