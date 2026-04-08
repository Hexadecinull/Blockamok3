#pragma once
#include <stdint.h>
#define WPAD_CHAN_0 0
typedef enum { EXP_NONE=0, EXP_NUNCHUK=1, EXP_CLASSIC=2 } exp_type_t;
typedef struct {
    struct { struct { struct { uint8_t x,y; } pos; } ljs,rjs; } classic;
    exp_type_t type;
} expansion_t;
uint32_t WPAD_ButtonsHeld(int c);
void WPAD_ScanPads(void);
int WPAD_Expansion(int c,expansion_t *e);
#define WPAD_BUTTON_LEFT            0x00000001
#define WPAD_BUTTON_RIGHT           0x00000002
#define WPAD_BUTTON_DOWN            0x00000004
#define WPAD_BUTTON_UP              0x00000008
#define WPAD_BUTTON_PLUS            0x00000010
#define WPAD_BUTTON_1               0x00000200
#define WPAD_BUTTON_2               0x00000100
#define WPAD_BUTTON_MINUS           0x00001000
#define WPAD_BUTTON_A               0x00000800
#define WPAD_BUTTON_B               0x00000400
#define WPAD_CLASSIC_BUTTON_UP      0x00010000
#define WPAD_CLASSIC_BUTTON_DOWN    0x00020000
#define WPAD_CLASSIC_BUTTON_LEFT    0x00040000
#define WPAD_CLASSIC_BUTTON_RIGHT   0x00080000
#define WPAD_CLASSIC_BUTTON_A       0x00100000
#define WPAD_CLASSIC_BUTTON_B       0x00200000
#define WPAD_CLASSIC_BUTTON_X       0x00400000
#define WPAD_CLASSIC_BUTTON_Y       0x00800000
#define WPAD_CLASSIC_BUTTON_FULL_L  0x01000000
#define WPAD_CLASSIC_BUTTON_FULL_R  0x02000000
#define WPAD_CLASSIC_BUTTON_PLUS    0x04000000
#define WPAD_CLASSIC_BUTTON_MINUS   0x08000000
