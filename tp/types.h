#ifndef H_TYPES
#define H_TYPES
/*-----------*/
typedef union _BYTEHL
{
	unsigned char iByte;
	struct 
	{
		unsigned char iNibbleL : 4;
		unsigned char iNibbleH : 4;
	};
}
BYTEHL, *PBYTEHL;

typedef union LONGHLNB
{
  	unsigned long iLong;
  	struct
  	{
    	BYTEHL iByteLL;
    	BYTEHL iByteLH;
    	BYTEHL iByteHL;
    	BYTEHL iByteHH;
  	};
  	struct
  	{
		unsigned int  iIntL;
		unsigned int  iIntH;  
  	};
}
LONGHLNB, *PLONGHLNB;

typedef union INTHL
{
  	unsigned int iInt;
  	struct
  	{
    	unsigned char iByteL;
    	unsigned char iByteH;
  	};
}
INTHL, *PINTHL;

typedef union SLONGHL
{
  	unsigned short long iSLong;
  	struct
  	{
    	unsigned char iByteLL;
    	unsigned char iByteLH;
    	unsigned char iByteHL;
  	};
  	struct
  	{
		  unsigned int  iIntL;
		  unsigned char iByteH;  
  	};
  	struct
  	{
		  unsigned char iByteL;  
		  unsigned int  iIntH;
  	};
}
SLONGHL, *SPLONGHL;

typedef union LONGHL
{
  	unsigned long iLong;
  	struct
  	{
    	unsigned char iByteLL;
    	unsigned char iByteLH;
    	unsigned char iByteHL;
    	unsigned char iByteHH;
  	};
    struct 
    {
      SLONGHL       iSLong;
      unsigned char iSByte;
    };
  	struct
  	{
		  unsigned int  iIntL;
		  unsigned int  iIntH;  
  	};
}
LONGHL, *PLONGHL;
typedef struct _TAdvancedTimer
{
  unsigned int u16s;
  unsigned int u16ms5;
  struct
  {
    unsigned char b1sTimeout    :1;
    unsigned char b1ms5Timeout  :1;
    unsigned char b4Unused      :4;
    unsigned char b1sActive     :1;
    unsigned char b1ms5Active   :1;
  }ControlBits;
}TAdvancedTimer;

typedef struct _TSummaryControl
{
  unsigned int   u16CurrentRecordIndex;
  struct
  {
    unsigned char b1TimeToSave : 1;
    unsigned char b1Saved      : 1;
    unsigned char b1Saving     : 1;
    unsigned char b5Unused     : 5;
  }ControlBits;
}TSummaryControl;

typedef struct _TIMRDeviceCommonSummaryHeader
{
  unsigned int          u16DataValidMark;
  unsigned long         u32TimeStamp;   
} TIMRDeviceCommonSummaryHeader;  

#define SMYK_TIME_MARK_SECONDS 0
#define SMYK_TIME_MARK_MINUTES 1
#define SMYK_TIME_MARK_HOURS   2
#define SMYK_TIME_MARK_INVALID 3

typedef union _TSmykTimeMark
{
   struct
   {
      unsigned char  b6Value : 6;
      unsigned char  b2Type  : 2;
   };
   unsigned char u8Value;   
} TSmykTimeMark;   

// dla zgodnosci z MBUSem inaczej nazwany 
typedef BYTEHL                    uint8HL;

#define BYTE_LONG_HH(x)						(((x) & 0xFF000000) >> 24)
#define BYTE_LONG_HL(x)						(((x) & 0x00FF0000) >> 16)
#define BYTE_LONG_LH(x)						(((x) & 0x0000FF00) >> 8 )
#define BYTE_LONG_LL(x)						(((x) & 0x000000FF)      )

#define BYTE_INT_L(x)                       ((x)  & 0x00FF)
#define BYTE_INT_H(x)                       (((x) & 0xFF00) >> 8)

#define BYTE_LONGHL_HH(x)					(((LONGHL*)&(x))->iByteHH)
#define BYTE_LONGHL_HL(x)					(((LONGHL*)&(x))->iByteHL)
#define BYTE_LONGHL_LH(x)					(((LONGHL*)&(x))->iByteLH)
#define BYTE_LONGHL_LL(x)					(((LONGHL*)&(x))->iByteLL)

#define BYTE_INTHL_H(x)						(((INTHL*)&(x))->iByteH)
#define BYTE_INTHL_L(x)						(((INTHL*)&(x))->iByteL)

#define CONVERT_UCHAR(x)                    *((unsigned char*)		  &(x))
#define CONVERT_UINT(x)                     *((unsigned int*)		    &(x))
#define CONVERT_USHORTLONG(x)               *((unsigned short long*)&(x))
#define CONVERT_ULONG(x)                    *((unsigned long*)	    &(x))

//d to jest jakis wstyd
//d przestawic kolejnosc bitow
typedef union _TIMRDeviceStatusWord
{
  unsigned short long u24Status;
  struct
  {
    unsigned short long bRTCErr                  :1;
    unsigned short long bCounterCopyErr          :1;
    unsigned short long bMaxTempErr              :1;
    unsigned short long bMinTempErr              :1;

    unsigned short long bEECounterErr            :1;
    unsigned short long bEEConfigErr             :1;
    unsigned short long bEEDiagnosticErr         :1;
    unsigned short long bEEArchiveErr            :1;

    unsigned short long bEEMonthlongArchiveErr   :1; // zamiast bEEMonthlongArchiveFull :1; - zak³adam archiwum cykliczne, a zreszta sie nie zape³ni
    unsigned short long bSIMErr                  :1;
    unsigned short long b1ModemErr               :1;
    unsigned short long bMaxFlowErr              :1;

    unsigned short long bSabotageFlag            :1;
    unsigned short long bRemoveFlag              :1;
    unsigned short long bIrFlag                  :1;
    unsigned short long bBatteryLowFlag          :1;

    unsigned short long b1MonthDiffConfidence    :1;
    unsigned short long b1DayDiffConfidence      :1;
    unsigned short long b1OpenCaseFlag           :1;
    unsigned short long b1LoggingErr             :1;
	
    unsigned short long b1FlashLogWriteErr       :1;
    unsigned short long b1FlashMultireadWriteErr :1;
    unsigned short long b1FlashAnalogArchiveErr  :1;
    unsigned short long b1FlashCommunicationErr  :1;	
  }Bits;
}TIMRDeviceStatusWord;

typedef struct _TIMRDeviceDeviceStatus
{
  TIMRDeviceStatusWord  Current;
  TIMRDeviceStatusWord  Latch;
  unsigned char         u8RTCErrCnt;
} TIMRDeviceDeviceStatus;

/*-----------*/
#endif
