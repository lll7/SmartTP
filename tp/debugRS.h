#ifndef H_DEBUG
#define H_DEBUG
/*-----------*/

//#define DEBUG_ON
//#define TP_DEBUG_LEVEL_0
//#define TP_DEBUG_LEVEL_1
//#define TP_DEBUG_TOUT //d to jest bardzo ciekawe dlaczego timeouty nie wystepują ?!

#ifdef DEBUG_ON

void DebugHexR(unsigned long u32Number);
void DebugHex1R(unsigned char aiNumber);
void DebugHex2R(unsigned int aiNumber);
void Debug(const rom char *apString);
void DebugStr(char* apString);
void DebugHex(unsigned long aiNumber);
void DebugInit(void);
void DebugChar(unsigned char aiChar);
void DebugHex1(unsigned char aiNumber);
void DebugHex2(unsigned int aiNumber);
void DebugBlob(unsigned char *apBuffer, unsigned int aiLen);
void DebugBlobR(unsigned char *apBuffer, unsigned int aiLen);
void DebugStrHex1R(const rom char *apString, unsigned char aiNumber);
void DebugStrHex2R(const rom char *apString, unsigned int aiNumber);
void DebugStrHexR(const rom char *apString, unsigned long aiNumber);

unsigned char HEX(unsigned char a);


#else //#ifdef DEBUG_ON

#define DebugHexR(x) ;
#define DebugHex1R(x)    ;
#define DebugHex2R(x)       ;
#define Debug(x)            ;
#define DebugStr(x)         ;
#define DebugHex(x)         ;
#define DebugInit(x)        ;
#define DebugChar(x)        ;
#define DebugHex1(x)        ;
#define DebugHex2(x)        ;
#define DebugBlob(x)        ;
#define DebugBlobR(x)       ;
#define DebugStrHex1R(x,v)    ;
#define DebugStrHex2R(x,v)    ;
#define DebugStrHexR(x,v)


#endif
#endif
