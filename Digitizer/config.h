/* 
 * File:   hardware_config.h
 * Author: LLL
 *
 * Created on 16 maj 2013, 21:32
 */
#ifndef HARDWARE_CONFIG_H
#define	HARDWARE_CONFIG_H

#include <p18cxxx.h>
#include "../tp/KeyMap.h"
#include "../tp/debugRS.h"
#include "../tp/touchpad.h"
#include "../tp/delays2.h"

//pins
#define TRIS_RS_TX TRISBbits.RB7
#define LAT_RS_TX LATBbits.LATB7

#define KEY_TRIS TRISCbits.RC1
#define KEY_PORT PORTCbits.RC1

#define TOUCH_PAD_CLK_TRIS  TRISCbits.RC5
#define TOUCH_PAD_CLK_LAT   LATCbits.LATC5
#define TOUCH_PAD_CLK_PORT  PORTCbits.RC5

#define TOUCH_PAD_DATA_TRIS  TRISCbits.RC2
#define TOUCH_PAD_DATA_LAT   LATCbits.LATC2
#define TOUCH_PAD_DATA_PORT  PORTCbits.RC2

#define TOUCH_PAD_VCC_TRIS  TRISCbits.RC0
#define TOUCH_PAD_VCC_LAT   LATCbits.LATC0




//#define ABS_X_MIN 0x480
#define ABS_X_MIN 0x395
//#define ABS_X_MAX 0x16D0
#define ABS_X_MAX 0x178A
//#define ABS_Y_MIN 0x390
#define ABS_Y_MIN 0x33A
//#define ABS_Y_MAX 0x13B0
#define ABS_Y_MAX 0x1503

#define DESC_MAX 32767

#define TP_MAX_DELTA        40u

typedef struct _TSTP
{
    TTPMoudle TPModule;
}TSTP;

extern TSTP STP;



#endif	/* HARDWARE_CONFIG_H */

