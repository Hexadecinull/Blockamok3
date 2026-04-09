#pragma once
/* SDL_mixer stub for CI compile checks */
typedef struct { int dummy; } Mix_Music;
typedef struct { int dummy; } Mix_Chunk;
#define MIX_DEFAULT_FORMAT 0x8010
int  Mix_OpenAudio(int freq, unsigned short fmt, int channels, int chunksize);
void Mix_CloseAudio(void);
int  Mix_Quit(void);
void Mix_VolumeMusic(int volume);
void Mix_Volume(int channel, int volume);
void Mix_VolumeChunk(Mix_Chunk *chunk, int volume);
Mix_Music *Mix_LoadMUS_RW(void *src, int freesrc);
Mix_Chunk *Mix_LoadWAV_RW(void *src, int freesrc);
int  Mix_PlayMusic(Mix_Music *music, int loops);
int  Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops);
void Mix_FreeMusic(Mix_Music *music);
void Mix_FreeChunk(Mix_Chunk *chunk);
int  Mix_HaltMusic(void);
