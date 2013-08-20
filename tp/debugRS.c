#include "debugRS.h"
#include "types.h"
#include <p18cxxx.h>

#include "config.h"

#define HEX2(a)	if (a > 9u) a = a + 0x37; else a = a + 0x30;
/* -------------------------------------------------------------------------------- */
unsigned char HEX(unsigned char a)
{
    if (a > 9u)
        return (a + 0x37);
    else
        return (a + 0x30);
}

#ifdef DEBUG_ON

/* -------------------------------------------------------------------------------- */
void DebugInit  (void)
{

    /* CSRC|TX9|TXEN|SYNC|?|BRGH|TRMT|TX9D      */
    TXSTA = 0b00000100;
    /* SPEN|RX9|SREN|CREN|ADDEN|FERR|OERR|RX9D  */
    RCSTA = 0b10000000;
    /* ABDOVF|RCMT|RXDTP|TXCKP|BRG16|?|WUE|ABDEN*/
    Nop();
    Nop(); // errata
    BAUDCON = 0b000000000;
    //48MHz
    SPBRG             = 25; 

    TRIS_RS_TX = 0;
}

/* -------------------------------------------------------------------------------- */
void DebugChar  (unsigned char aiChar)
{
    char s8tmp2;
    if (RCSTAbits.OERR || RCSTAbits.FERR)
    {
        s8tmp2 = RCREG;
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    TXSTAbits.TXEN    = 1;
    while (!TXSTAbits.TRMT);
    TXREG = aiChar;
    TXSTAbits.TXEN    = 0;
}

/* -------------------------------------------------------------------------------- */
void DebugStr   (char* apString)
{
    while (*apString)
        DebugChar(*apString++);
}

/* -------------------------------------------------------------------------------- */
void Debug      (const rom char *apString)
{
    while (*apString)
        DebugChar(*apString++);
}

/* -------------------------------------------------------------------------------- */
void DebugHex1  (unsigned char aiNumber)
{
    DebugChar(HEX(((PBYTEHL) & aiNumber)->iNibbleH));
    DebugChar(HEX(((PBYTEHL) & aiNumber)->iNibbleL));
}

/* -------------------------------------------------------------------------------- */
void DebugHex2  (unsigned int aiNumber)
{
    DebugChar(HEX(((PBYTEHL)&((PINTHL) & aiNumber)->iByteH)->iNibbleH));
    DebugChar(HEX(((PBYTEHL)&((PINTHL) & aiNumber)->iByteH)->iNibbleL));
    DebugChar(HEX(((PBYTEHL)&((PINTHL) & aiNumber)->iByteL)->iNibbleH));
    DebugChar(HEX(((PBYTEHL)&((PINTHL) & aiNumber)->iByteL)->iNibbleL));
}

/* -------------------------------------------------------------------------------- */
void DebugHex   (unsigned long aiNumber)
{
    DebugChar(HEX(((PBYTEHL)&((PLONGHL) & aiNumber)->iByteHH)->iNibbleH));
    DebugChar(HEX(((PBYTEHL)&((PLONGHL) & aiNumber)->iByteHH)->iNibbleL));
    DebugChar(HEX(((PBYTEHL)&((PLONGHL) & aiNumber)->iByteHL)->iNibbleH));
    DebugChar(HEX(((PBYTEHL)&((PLONGHL) & aiNumber)->iByteHL)->iNibbleL));
    DebugChar(HEX(((PBYTEHL)&((PLONGHL) & aiNumber)->iByteLH)->iNibbleH));
    DebugChar(HEX(((PBYTEHL)&((PLONGHL) & aiNumber)->iByteLH)->iNibbleL));
    DebugChar(HEX(((PBYTEHL)&((PLONGHL) & aiNumber)->iByteLL)->iNibbleH));
    DebugChar(HEX(((PBYTEHL)&((PLONGHL) & aiNumber)->iByteLL)->iNibbleL));
}

/* -------------------------------------------------------------------------------- */
void DebugHex1R        (unsigned char   aiNumber)
{
    DebugHex1(aiNumber);
    DebugChar('\r');
}

/* -------------------------------------------------------------------------------- */
void DebugHex2R        (unsigned int   aiNumber)
{
    DebugHex2(aiNumber);
    DebugChar('\r');
}

/* -------------------------------------------------------------------------------- */
void DebugHexR   (unsigned long u32Number)
{
    DebugHex(u32Number);
    DebugChar('\r');
}

/* -------------------------------------------------------------------------------- */
void DebugStrHex1R(const rom char *apString, unsigned char aiNumber)
{
    Debug(apString);
    DebugHex1R(aiNumber);
}

/* -------------------------------------------------------------------------------- */
void DebugStrHex2R(const rom char *apString, unsigned int aiNumber)
{
    Debug(apString);
    DebugHex2R(aiNumber);
}

/* -------------------------------------------------------------------------------- */
void DebugStrHexR(const rom char *apString, unsigned long aiNumber)
{
    Debug(apString);
    DebugHexR(aiNumber);
}

/* -------------------------------------------------------------------------------- */
void DebugBlob(unsigned char *apBuffer, unsigned int aiLen)
{
    unsigned char iChar;
    while (aiLen--)
    {
        iChar = *apBuffer++;
        DebugChar(HEX(((PBYTEHL)&((PLONGHL) & iChar)->iByteLL)->iNibbleH));
        DebugChar(HEX(((PBYTEHL)&((PLONGHL) & iChar)->iByteLL)->iNibbleL));
    }
}

/* -------------------------------------------------------------------------------- */
void DebugBlobR(unsigned char  *apBuffer, unsigned int aiLen)
{
    DebugBlob(apBuffer, aiLen);
    DebugChar('\r');
}
/* -------------------------------------------------------------------------------- */

#endif //DEBUG_ON
