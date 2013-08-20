#include "config.h"
#include <string.h>
#include "delays2.h"

void BTInit(void) {
    /* CSRC|TX9|TXEN|SYNC|?|BRGH|TRMT|TX9D      */
    TXSTA = 0b00000100;
    /* SPEN|RX9|SREN|CREN|ADDEN|FERR|OERR|RX9D  */
    RCSTA = 0b10000000;
    /* ABDOVF|RCMT|RXDTP|TXCKP|BRG16|?|WUE|ABDEN*/
    Nop();
    Nop();
    BAUDCON = 0b000000000;
    //48MHz
    SPBRG = 25;

    TRIS_RS_TX = 0;
    TRIS_RS_RX = 1;
    // ten init nie działa nie wiem dlaczego moze za duze timeouty ?
//    Delay100ms(10);
//    BTSendDataFFlash("$$$");
//    Delay100ms(10);
//    BTSendDataFFlash("$$$");
//    Delay100ms(10);
//    BTSendDataFFlash("S~,6\r");
//    Delay100ms(10);
//    BTSendDataFFlash("SH,0230\r");
//    Delay100ms(10);
//    BTSendDataFFlash("R,1\r");
//    Delay100ms(10);
    
}

void BTSendChar(char aiChar)
{
    char s8tmp2; //to zmergowac razem z debugami
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

void BTSendData(char * apString)
{
   while (*apString)
       BTSendChar(*apString++);
}

void BTSendDataFFlash(const rom char *apString)
{
    while (*apString)
        BTSendChar(*apString++);
}

void BTEmulateKeyboard(unsigned char u8Key)
{
    BTSendChar(u8Key);
    
    //BTSendData(u8Key);
}



