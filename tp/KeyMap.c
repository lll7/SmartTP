#ifndef KEYMAP_C
#define KEYMAP_C

#include "config.h"




//const rom unsigned char U8Keyboard [KEYBOARD_SIZE_Y][KEYBOARD_SIZE_X] = {
//    {_SHP, _1  , _2  , _3, _4, _5, _6, _7, _8, _9, _0  , _MIN, _PLS, _BCK, _BCK, _BCK},
//    {_TAB, _TAB, _q  , _w, _e, _r, _t, _y, _u, _i, _o  , _p  , _OBR, _CBR, _BSL, _RET},
//    {_CPS, _CPS, _CPS, _a, _s, _d, _f, _g, _h, _j, _k  , _l  , _SMC, _APS, _RET, _RET},
//    {_SPC, _SPC, _SPC, _z, _x, _c, _v, _b, _n, _m, _LES, _MRE, _QMK, _RET, _RET, _RET}
//};

//const rom unsigned char U8Keyboard [KEYBOARD_SIZE_Y][KEYBOARD_SIZE_X] = {
//    {_1, _2, _3, _4, _5, _6, _7, _8, _9, _0, _BCK},
//    {_TAB, _q, _w, _e, _r, _t, _y, _u, _i, _o, _p},
//    {_a, _s, _d, _f, _g, _h, _j, _k, _l, _RET, _RET},
//    {_SPC, _SPC, _z, _x, _c, _v, _b, _n, _m, _LES, _MRE}
//};

//const rom unsigned char U8Keyboard [KEYBOARD_SIZE_Y][KEYBOARD_SIZE_X] = {
//    {_7, _8  , _9  , _KDIV, _KMIN,_UA},
//    {_4, _5  , _6  , _KMUL, _KPLS,_DA},
//    {_1, _2  , _3  , _a   , _b   ,_LA},
//    {_0,_MRE, _PLS , _BCK , _c   ,_RA}
//};

//ta jest user friendly do debugów i do BT !!
const rom unsigned char U8Keyboard [KEYBOARD_SIZE_Y][KEYBOARD_SIZE_X] = {
    {'1', '2', '3', '4','5', '6', '7', '8', '9', '0', 0x08},
    {'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
    {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\r', '\r'},
    {' ', ' ', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.'}
};

//const rom unsigned char U8Keyboard [KEYBOARD_SIZE_Y][KEYBOARD_SIZE_X] = {
//    {'~', '~', '~', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '+', '\b'},
//    {'q', 'q', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n', '\n'},
//    {'a', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '"', '\n', '\n', '\n', '\n'},
//    {'z', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '<', '>', '/', '/', '\n', '\n', '\n', '\n'}
//};

void InitKey(void) {


        STP.KeyModule.u16Left = ABS_X_MIN;
        STP.KeyModule.u16Top = ABS_Y_MIN;
        STP.KeyModule.u16Width = ABS_X_MAX - ABS_X_MIN;
        STP.KeyModule.u16Height = ABS_X_MAX - ABS_X_MIN;

//    STP.KeyModule.u16Left = STP.MouseConfig.u16Left + STP.MouseConfig.u16Width;
//    STP.KeyModule.u16Width = (ABS_X_MAX - ABS_X_MIN) / 3 * 2;
//    STP.KeyModule.u16Top = ABS_Y_MIN;
//    STP.KeyModule.u16Height = ABS_Y_MAX;

    Debug("I:K ");
    DebugHex2(STP.KeyModule.u16Left);
    Debug(" ");
    DebugHex2(STP.KeyModule.u16Width);
    Debug(" ");
    DebugHex2(STP.KeyModule.u16Top);
    Debug(" ");
    DebugHex2R(STP.KeyModule.u16Height);


    STP.KeyModule.u8KeyboardSizeX = KEYBOARD_SIZE_X;
    STP.KeyModule.u8KeyboardSizeY = KEYBOARD_SIZE_Y;
}

void MapKey(void) {
    unsigned char u8IX, u8IY;
    u8IX = ((STP.KeyModule.u8KeyboardSizeX) * (unsigned long) (STP.TPModule.AbsolutePosition.u16X - STP.KeyModule.u16Left)) / (STP.KeyModule.u16Width);
    u8IY = ((STP.KeyModule.u8KeyboardSizeY) * (unsigned long) (STP.TPModule.AbsolutePosition.u16Y - STP.KeyModule.u16Top)) / (STP.KeyModule.u16Height);

    if (u8IX >= STP.KeyModule.u8KeyboardSizeX) u8IX = STP.KeyModule.u8KeyboardSizeX - 1;
    if (u8IY >= STP.KeyModule.u8KeyboardSizeY) u8IY = STP.KeyModule.u8KeyboardSizeY - 1;

    STP.KeyModule.u8CurrentKey = U8Keyboard[u8IY][u8IX];

//        Debug("\r ");
//        DebugHex1(TPModule.AbsolutePosition.Raw.Fields.u8ZPressure);Debug(" ");
//        DebugHex2(STP.TPModule.AbsolutePosition.u16X);Debug(",");
//        DebugHex2(STP.TPModule.AbsolutePosition.u16Y);
//        Debug(" I ");
//        DebugHex1(u8IX);
//        Debug(",");
//        DebugHex1(u8IY);
//        Debug(" K ");
//        DebugChar(STP.KeyModule.u8CurrentKey);



}
#endif //KEYMAP_C
