
#include "config.h"
#include <string.h>

unsigned char TPReset() {
    Delay100ms(20);
    Debug("RST:");
    TPSendByte(TP_CMD_RESET); //reset
    STP.TPModule.U8LastData[0] = TPGetByte();
    STP.TPModule.U8LastData[1] = TPGetByte();
    DebugHex1(STP.TPModule.U8LastData[0]);
    Debug(" ");
    DebugHex1R(STP.TPModule.U8LastData[1]);
    if ((STP.TPModule.U8LastData[0] != 0xAA) || (STP.TPModule.U8LastData[1] != 0x00))
        return 0;
    return 1;
}

unsigned char TPGetID() {
    TPSendArg(0x00); // id touch pad
    TPSendByte(0xE9);
    STP.TPModule.U8LastData[0] = TPGetByte();
    STP.TPModule.U8LastData[1] = TPGetByte();
    STP.TPModule.U8LastData[2] = TPGetByte();

    Debug("ID:");
    DebugHex1(STP.TPModule.U8LastData[1]);
    Debug(" ");
    DebugHex1(STP.TPModule.U8LastData[2]);
    Debug(" ");
    DebugHex1R(STP.TPModule.U8LastData[3]);

    if (STP.TPModule.U8LastData[1] != 0x47)
        return 0;
    return 1;
}

void InitTP(unsigned char u8Mode) {

    TOUCH_PAD_CLK_TRIS = 1;
    TOUCH_PAD_DATA_TRIS = 1;
    TOUCH_PAD_VCC_TRIS = 0;
    TOUCH_PAD_VCC_LAT = 1;
    
    Debug("TP:INIT\r");

    STP.TPModule.u32TimeOut = 0x000FFFF;
    if (TPReset() == 0)
        Reset();
    TPGetID();

    if (u8Mode == TP_MODE_REL) {
        //  TPSendByte(TP_CMD_SET_RESOLUTION);
        //  TPSendByte(0x03); // 8mm
        //  TPSendByte(TP_CMD_STREAM_OFF); //zamiast tego clk na 0?
        TPSendByte(TP_CMD_ENABLE);
        Debug("TP:Rel\r");

        TOUCH_PAD_CLK_TRIS = 0;
        TOUCH_PAD_CLK_LAT = 0;
    } else //TP_MODE_ABS
    {
        TPSendArg(0x80);
        TPSendByte(0xF3);
        TPSendByte(0x14);
        // TPSendByte(TP_CMD_STREAM_OFF);
        TPSendByte(TP_CMD_ENABLE);
        //TOUCH_PAD_CLK_TRIS = 1;

        TOUCH_PAD_CLK_TRIS = 0;
        TOUCH_PAD_CLK_LAT = 0;
        Debug("TP:Abs\r");
    }
    STP.TPModule.u32TimeOut = 0x00FFF;
}

//void TPWaitClock(unsigned char state) {
//    unsigned long u32TimeOut = STP.TPModule.u32TimeOut;
//    if (STP.TPModule.ErrorState.b1TimeOut == 0) {
//        TOUCH_PAD_CLK_TRIS = 1;
//        while (TOUCH_PAD_CLK_PORT != state) {
//            if (!u32TimeOut--) {
//#ifdef TP_DEBUG_TOUT
//                Debug("T");
//#endif
//                STP.TPModule.ErrorState.b1TimeOut = 1;
//                return;
//            }
//        }
//    }
//} 
#define TPWaitClock(x)  TOUCH_PAD_CLK_TRIS = 1;  while (TOUCH_PAD_CLK_PORT != x)

void TPSetClk(unsigned char b1State) {
    TOUCH_PAD_CLK_TRIS = 0;
    TOUCH_PAD_CLK_LAT = b1State;
}

unsigned char TPGetClk(void) {
    TOUCH_PAD_CLK_TRIS = 1;
    return TOUCH_PAD_CLK_PORT;
}

void TPSetData(unsigned char b1State) {

    TOUCH_PAD_DATA_TRIS = 0;
    TOUCH_PAD_DATA_LAT = b1State;
}

unsigned char TPGetByte(void) {
    unsigned char i, b1Bit;
    unsigned char value = 0;
    unsigned char p = 0;

    TOUCH_PAD_DATA_TRIS = 1;
    TPSetClk(1);
    TPWaitClock(0);
    TPWaitClock(1);

    for (i = 0; i < 8; i++) {
        TPWaitClock(0);
        b1Bit = TOUCH_PAD_DATA_PORT;
        value = value + (b1Bit << i);
        p = p + b1Bit;
        TPWaitClock(1);
    }
    TPWaitClock(0);
    p = p + TOUCH_PAD_DATA_PORT;
    if ((p & 0x01) == 0) {
#ifdef TP_DEBUG_LEVEL_0
        Debug("P");
#endif
        STP.TPModule.ErrorState.b1RcvPErr = 1;
    }
    TPWaitClock(1);
    TPWaitClock(0);

    if (TOUCH_PAD_DATA_PORT == 0) {
#ifdef TP_DEBUG_LEVEL_0
        Debug("S");
#endif
        STP.TPModule.ErrorState.b1RcvSErr = 1;
    }
    TPWaitClock(0);
#ifdef TP_DEBUG_LEVEL_1
    DebugStrHex1R("TP:>", value);
#endif
    Delay50us(); // tak jest w dokumencie i chyba ma to znaczenie 
    return value;
}

unsigned char TPSendByte(unsigned char u8Data) {
    unsigned char i, ack;
    unsigned char u8p = 1;
#ifdef TP_DEBUG_LEVEL_1
    DebugStrHex1R("TP:<", u8Data);
#endif

    TPSetClk(0);
    Delay100us();
    TPSetData(0);
    TPSetClk(1);

    for (i = 0; i < 8; i++) {
        TPWaitClock(0);
        TPSetData(u8Data & 0x01);
        u8p += u8Data;
        TPWaitClock(1);
        u8Data >>= 1;
    }
    TPWaitClock(0);
    TPSetData(u8p & 0x01);
    TPWaitClock(1);
    TPWaitClock(0);
    TPSetData(1);
    TPWaitClock(1);
    TOUCH_PAD_DATA_TRIS = 1;
    TPWaitClock(0);

    if (TOUCH_PAD_DATA_PORT == 1) {
#ifdef TP_DEBUG_LEVEL_0
        Debug("L");
#endif
        STP.TPModule.ErrorState.b1TxLErr = 1;
        return 0;
    }
    TPWaitClock(1);
    ack = TPGetByte();
    if (ack != 0xFA) {
        STP.TPModule.ErrorState.b1TxAErr = 1;
        return 0;
    }
    return 1;
}

void TPSendArg(unsigned char u8Arg) {
    unsigned char i;
    for (i = 0; i < 4; i++) {
        TPSendByte(0xE8);
        TPSendByte((u8Arg >> (6 - 2 * i)) & 3);
    }
}

void TPGetAbsPositon() {
    TOUCH_PAD_CLK_TRIS = 1;
    STP.TPModule.u8LastDataCnt = 0;
    //TPSendByte(TP_CMD_READ_DATA);
    while (!STP.TPModule.ErrorState.b1TimeOut) // tu trzeba chyba while 1 bo jak przerwie sie przed zassaniem wszystkich pakietów to potem sie biedzi
    {
        TPWaitClock(0) ClrWdt(); //tak tu nie ma byc srednika 
        STP.TPModule.AbsolutePosition.Raw.U8Data[STP.TPModule.u8LastDataCnt] = TPGetByte();
        STP.TPModule.u8LastDataCnt++;
        TPWaitClock(1);
        if (STP.TPModule.u8LastDataCnt == sizeof (STP.TPModule.AbsolutePosition.Raw.U8Data)) break;
    }
    if (STP.TPModule.ErrorState.u8Error)
        STP.TPModule.b1DataValid = 0;
    TOUCH_PAD_CLK_TRIS = 0;
    TOUCH_PAD_CLK_LAT = 0;
}

void TPGetRelativePosition(void) {
    TOUCH_PAD_CLK_TRIS = 1;
    STP.TPModule.u8LastDataCnt = 0;
    // TPSendByte(TP_CMD_READ_DATA);
    while (!STP.TPModule.ErrorState.u8Error) //do poprawy !
    {
        TPWaitClock(0) ClrWdt();
        STP.TPModule.RelativePosition.Raw.U8Data[STP.TPModule.u8LastDataCnt] = TPGetByte();
        STP.TPModule.u8LastDataCnt++;
        TPWaitClock(1);
        if (STP.TPModule.u8LastDataCnt == sizeof (STP.TPModule.RelativePosition.Raw.U8Data)) break;
    }
    if (STP.TPModule.ErrorState.u8Error)
        STP.TPModule.b1DataValid = 0;
    TOUCH_PAD_CLK_TRIS = 0;
    TOUCH_PAD_CLK_LAT = 0;
}

void TPCalculateRelativePosition(void) {
    STP.TPModule.RelativePosition.Raw.Fields.u8Byte1.bits.b1Middle = 0;
    //  STP.TPModule.RelativePosition.Raw.Fields.u8Byte1.bits.b1Right = 0;
    STP.TPModule.RelativePosition.Raw.Fields.u8XDelta *= 2;
    STP.TPModule.RelativePosition.Raw.Fields.u8YDelta *= 2;
}

unsigned int abs16(signed int val) {
    return (val < 0 ? (-val) : val);
}

unsigned char abs8(signed char val) {
    return (val < 0 ? (-val) : val);
}

unsigned char u8PacketInvalid = 0;
void TPCalculateRelativePosition2(void) {


    STP.TPModule.RelativePosition.Raw.Fields.u8Byte1.bits.b1Left = STP.TPModule.AbsolutePosition.Raw.Fields.u8Byte1.bits.b1Gesture;
    
    if (STP.TPModule.AbsolutePosition.Raw.Fields.u8ZPressure < KEY_PRESED_THRESHOLD)
    {
        u8PacketInvalid = 5;
        //STP.TPModule.RelativePosition.Raw.Fields.u8Byte1.u8Byte = 0;
    }
    if (u8PacketInvalid != 0)
    {
        u8PacketInvalid --;
        STP.TPModule.AbsolutePosition.u16LastX = STP.TPModule.AbsolutePosition.u16X;
        STP.TPModule.AbsolutePosition.u16LastY = STP.TPModule.AbsolutePosition.u16Y;
        STP.TPModule.RelativePosition.Raw.Fields.u8XDelta = 0;
        STP.TPModule.RelativePosition.Raw.Fields.u8YDelta = 0;
        
        return;
    }

    STP.TPModule.u16Sensivity = 5;

    STP.TPModule.RelativePosition.Raw.Fields.u8XDelta = (abs16(STP.TPModule.AbsolutePosition.u16X - STP.TPModule.AbsolutePosition.u16LastX)) / STP.TPModule.u16Sensivity;
    STP.TPModule.RelativePosition.Raw.Fields.u8YDelta = (abs16(STP.TPModule.AbsolutePosition.u16Y - STP.TPModule.AbsolutePosition.u16LastY)) / STP.TPModule.u16Sensivity;

   // if (abs8(STP.TPModule.RelativePosition.Raw.Fields.u8YDelta) > TP_MAX_DELTA) STP.TPModule.RelativePosition.Raw.Fields.u8YDelta = 0;
   // if (abs8(STP.TPModule.RelativePosition.Raw.Fields.u8XDelta) > TP_MAX_DELTA) STP.TPModule.RelativePosition.Raw.Fields.u8XDelta = 0;

    if (STP.TPModule.AbsolutePosition.u16LastX > STP.TPModule.AbsolutePosition.u16X) 
        STP.TPModule.RelativePosition.Raw.Fields.u8XDelta = -(signed char)STP.TPModule.RelativePosition.Raw.Fields.u8XDelta;
    if (STP.TPModule.AbsolutePosition.u16LastY > STP.TPModule.AbsolutePosition.u16Y)
        STP.TPModule.RelativePosition.Raw.Fields.u8YDelta = -(signed char)STP.TPModule.RelativePosition.Raw.Fields.u8YDelta;
    
    STP.TPModule.AbsolutePosition.u16LastX = STP.TPModule.AbsolutePosition.u16X;
    STP.TPModule.AbsolutePosition.u16LastY = STP.TPModule.AbsolutePosition.u16Y;

}

void TPCalculateAbsPosition(void) {

    STP.TPModule.AbsolutePosition.u16X = 0;
    STP.TPModule.AbsolutePosition.u16Y = 0;

    STP.TPModule.AbsolutePosition.u16X = STP.TPModule.AbsolutePosition.Raw.Fields.u8Byte4.bits.b1X_12 << 4;
    STP.TPModule.AbsolutePosition.u16X |= STP.TPModule.AbsolutePosition.Raw.Fields.u8Byte2.bits.b4Xpos8_11;
    STP.TPModule.AbsolutePosition.u16X = STP.TPModule.AbsolutePosition.u16X << 8;
    STP.TPModule.AbsolutePosition.u16X |= STP.TPModule.AbsolutePosition.Raw.Fields.u8XLSB;

    STP.TPModule.AbsolutePosition.u16Y = STP.TPModule.AbsolutePosition.Raw.Fields.u8Byte4.bits.b1Y_12 << 4;
    STP.TPModule.AbsolutePosition.u16Y |= STP.TPModule.AbsolutePosition.Raw.Fields.u8Byte2.bits.b4Ypos8_11;
    STP.TPModule.AbsolutePosition.u16Y = STP.TPModule.AbsolutePosition.u16Y << 8;
    STP.TPModule.AbsolutePosition.u16Y |= STP.TPModule.AbsolutePosition.Raw.Fields.u8YLSB;

    //if (STP.TPModule.b1FlipY)
//        STP.TPModule.AbsolutePosition.u16Y = DESC_MAX - STP.TPModule.AbsolutePosition.u16Y; //flip
      //  STP.TPModule.AbsolutePosition.u16Y = ABS_Y_MAX - (STP.TPModule.AbsolutePosition.u16Y - ABS_Y_MIN); //flip
    // if (STP.TPModule.b1FlipX)
    // {
      //
          STP.TPModule.AbsolutePosition.u16X = ABS_X_MAX - (STP.TPModule.AbsolutePosition.u16X - ABS_X_MIN); //flip
     //}


}

void TPRescalePosition(void) // lepsze było by max min ustalic w deskrytporze bo to to jest jalowka
{
    STP.TPModule.AbsolutePosition.u16X = (unsigned long) (STP.TPModule.AbsolutePosition.u16X - ABS_X_MIN) * DESC_MAX / (ABS_X_MAX - ABS_X_MIN);
    STP.TPModule.AbsolutePosition.u16Y = (unsigned long) (STP.TPModule.AbsolutePosition.u16Y - ABS_Y_MIN) * DESC_MAX / (ABS_Y_MAX - ABS_Y_MIN);
}





