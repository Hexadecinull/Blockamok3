#pragma once
#include <stdint.h>
typedef struct { uint32_t port_status[7]; } padInfo2;
typedef struct {
    int BTN_UP,BTN_DOWN,BTN_LEFT,BTN_RIGHT;
    int BTN_CROSS,BTN_CIRCLE,BTN_SQUARE,BTN_TRIANGLE;
    int BTN_L1,BTN_R1,BTN_L2,BTN_R2,BTN_L3,BTN_R3;
    int BTN_START,BTN_SELECT;
    unsigned char ANA_L_H,ANA_L_V,ANA_R_H,ANA_R_V;
} padData;
int ioPadInit(int max);
int ioPadGetInfo2(padInfo2 *i);
int ioPadGetData(int port,padData *d);
