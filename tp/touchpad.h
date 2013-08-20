
#ifndef TOUCHPAD_H
#define	TOUCHPAD_H

#define TP_MODE_REL 1
#define TP_MODE_ABS 0

#define TP_CMD_RESET              0xFF
#define TP_CMD_ENABLE             0xF4
#define TP_CMD_READ_DATA          0xEB
#define TP_CMD_STREAM_ON          0xEA
#define TP_CMD_STREAM_OFF         0xF5
#define TP_CMD_SET_RESOLUTION     0xE8

//raw min max for TM-1277

typedef struct _TTPRelativePosition {

    union {

        struct {

            union {

                struct {
                    unsigned char b1Left : 1; ///<  1 = Left button is currently pressed (or gesture in progress), 0 = released
                    unsigned char b1Right : 1; ///<  1 = Right button is currently pressed, 0 = released.
                    unsigned char b1Middle : 1; ///<  1 = Middle button is currently pressed, 0 = released.
                    unsigned char b1Unused : 1;
                    unsigned char b1XSign : 1; ///< 1 = X delta value is negative, 0 = X delta is zero or positive.
                    unsigned char b1YSign : 1; ///< 1 = Y delta value is negative, 0 = Y delta is zero or positive.
                    unsigned char b1XOvfl : 1; ///< 1 = X delta value exceeds the range –256...255, 0 = no overflow
                    unsigned char b1YOvfl : 1; ///< 1 =Y delta value exceeds the range –256...255, 0 = no overflow.
                } bits;
                unsigned char u8Byte;
            } u8Byte1;
            unsigned char u8XDelta;
            unsigned char u8YDelta;
        } Fields;
        unsigned char U8Data[3];
    } Raw;
} TTPRelativePosition;

typedef struct _TTPAbsolutePosition {

    union {

        struct {

            union {

                struct {
                    unsigned char b1Left : 1; ///<
                    unsigned char b1Right : 1; ///<
                    unsigned char b1Gesture : 1; ///<
                    unsigned char b1Zero2 : 1;
                    unsigned char b1Unsued : 1; ///<
                    unsigned char b1Finger : 1; ///<
                    unsigned char b1Zero1 : 1; ///< Always 0
                    unsigned char b1One1 : 1; ///< Always 1
                } bits;
                unsigned char u8Byte;
            } u8Byte1;

            union {

                struct {
                    unsigned char b4Xpos8_11 : 4;
                    unsigned char b4Ypos8_11 : 4;
                } bits;
                unsigned char u8Byte;
            } u8Byte2;
            unsigned char u8ZPressure;

            union {

                struct {
                    unsigned char b1Left : 1; ///<
                    unsigned char b1Right : 1; ///<
                    unsigned char b1Gesture : 1; ///<
                    unsigned char b1Zero2 : 1;
                    unsigned char b1X_12 : 1; ///<
                    unsigned char b1Y_12 : 1; ///<
                    unsigned char b1One2 : 1; ///< Always 1
                    unsigned char b1One1 : 1; ///< Always 1
                } bits;
                unsigned char u8Byte;
            } u8Byte4;
            unsigned char u8XLSB;
            unsigned char u8YLSB;
        } Fields;
        unsigned char U8Data[6];
    } Raw;
    unsigned int u16X;
    unsigned int u16Y;
    unsigned int u16LastX;
    unsigned int u16LastY;
} TTPAbsolutePosition;

typedef struct _TTPMoudle {
    TTPRelativePosition RelativePosition;
    TTPAbsolutePosition AbsolutePosition;

    unsigned long u32TimeOut; //< do inita inny do stream-a inny
    unsigned char U8LastData[6]; //< ostatnia odp touchpada
    unsigned char u8LastDataCnt; //< licznik danych
    unsigned int u16Sensivity;

    union {

        struct {
            unsigned char b1InitEr : 1;
            unsigned char b1TimeOut : 1; //< TP timeout flag
            unsigned char b1RcvPErr : 1;
            unsigned char b1RcvSErr : 1;
            unsigned char b1TxLErr : 1;
            unsigned char b1TxAErr : 1;
            unsigned char b2Unsued : 2;
        };
        unsigned char u8Error;
    } ErrorState;

    unsigned char b1DataValid : 1;
    unsigned char b1SwitchXY  : 1;
    unsigned char b1FlipX     : 1;
    unsigned char b1FlipY     : 1;

} TTPMoudle;



void InitTP(unsigned char u8Mode);
unsigned char TPSendByte(unsigned char u8Data);
unsigned char TPGetByte(void);
void TPSendArg(unsigned char u8Arg);
void TPGetRelativePosition(void);
void TPCalculateAbsPosition(void);
void TPCalculateRelativePosition(void);
void TPCalculateRelativePosition2(void);
unsigned char TPGetID();
unsigned char TPReset();
void TPRescalePosition(void);
void TPGetAbsPositon(void);

#endif	/* TOUCHPAD_H */

