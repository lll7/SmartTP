#ifndef KEYMAP_H
#define	KEYMAP_H

#define KEYBOARD_SIZE_X 11
//#define KEYBOARD_SIZE_X 6
#define KEYBOARD_SIZE_Y 4

#define KEY_PRESED_THRESHOLD 0x30

typedef struct _TKeyModule {
    unsigned int u16Width;
    unsigned int u16Height;
    unsigned int u16Left;
    unsigned int u16Top;
    unsigned char u8CurrentKey;
    unsigned char u8LastSendKey;
    unsigned char u8KeyboardSizeX;
    unsigned char u8KeyboardSizeY;
        //tu jeszcze mapa klawiszy w ramie ! <- jedna pozostałe kajś indziej ja !
} TKeyModule;

extern const rom unsigned char U8Keyboard[KEYBOARD_SIZE_Y][KEYBOARD_SIZE_X];

void MapKey(void);
void InitKey(void);

//< USB defines for keys, , to save some flash
#define _NUL 0x00

#define _a 0x04
#define _b 0x05
#define _c 0x06
#define _d 0x07
#define _e 0x08
#define _f 0x09
#define _g 0x0A
#define _h 0x0B
#define _i 0x0C
#define _j 0x0D
#define _k 0x0E
#define _l 0x0F
#define _m 0x10
#define _n 0x11
#define _o 0x12
#define _p 0x13
#define _q 0x14
#define _r 0x15
#define _s 0x16
#define _t 0x17
#define _u 0x18
#define _v 0x19
#define _w 0x1A
#define _x 0x1B
#define _y 0x1C
#define _z 0x1D

#define _1 0x1E
#define _2 0x1F
#define _3 0x20
#define _4 0x21
#define _5 0x22
#define _6 0x23
#define _7 0x24
#define _8 0x25
#define _9 0x26
#define _0 0x27

#define _RET 0x28
#define _ESC 0x29
// backspce
#define _BCK 0x2A
// tabulature
#define _TAB 0x2B
// space bar
#define _SPC 0x2C

// -
#define _MIN 0x2D
// +
#define _PLS 0x2E
// [
#define _OBR 0x2F
// ]
#define _CBR 0x30
// back slash or slash ? -> |
#define _BSL 0x31
// #
#define _SHP 0x32
// ;
#define _SMC 0x33
// '
#define _APS 0x34
// <
#define _LES 0x36
// >
#define _MRE 0x37
// >
#define _QMK 0x38
// capslock
#define _CPS 0x39

//strzalki
#define _RA 0x4F
#define _LA 0x50
#define _DA 0x51
#define _UA 0x52

//boczna klawiaturka
#define _KNUM 0x53

#define _KDIV 0x54
#define _KMUL 0x55
#define _KMIN 0x56
#define _KPLS 0x57
#define _KRET 0x58

#define _K1 0x59
#define _K2 0x5A
#define _K3 0x5B
#define _K4 0x5C
#define _K5 0x5D
#define _K6 0x5E
#define _K7 0x5F
#define _K8 0x60
#define _K9 0x61
#define _K0 0x62

#define _KDOT 0x63

#endif	/* KEYMAP_H */



