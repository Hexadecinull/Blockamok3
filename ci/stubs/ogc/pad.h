#pragma once
#include <stdint.h>
uint32_t PAD_ButtonsHeld(int c);
int8_t PAD_StickX(int c); int8_t PAD_StickY(int c);
int8_t PAD_SubStickX(int c); int8_t PAD_SubStickY(int c);
void PAD_Init(void); void PAD_ScanPads(void);
#define PAD_BUTTON_UP    0x0001
#define PAD_BUTTON_DOWN  0x0002
#define PAD_BUTTON_LEFT  0x0004
#define PAD_BUTTON_RIGHT 0x0008
#define PAD_BUTTON_A     0x0100
#define PAD_BUTTON_B     0x0200
#define PAD_BUTTON_X     0x0400
#define PAD_BUTTON_Y     0x0800
#define PAD_BUTTON_START 0x1000
#define PAD_TRIGGER_L    0x0040
#define PAD_TRIGGER_R    0x0020
#define PAD_TRIGGER_Z    0x0010
