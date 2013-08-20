#ifndef H_DELAYS
#define H_DELAYS

#include <p18cxxx.h>
/*------------*/

#define   Delay1us()    {Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();}
#define   Delay2us()    {Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();}
#define   Delay200us()  {Delay100us();Delay100us();}
#define   Delay1000us() {Delay500us();Delay500us();}
#define   Delay50us()   {Delay20us();Delay20us();Delay5us();}
#define   Delay2000us() {Delay1000us();Delay1000us();}
#define   Delay5000us() {Delay2000us();Delay2000us();Delay1000us();}



void      Delay5us   (void);
void      Delay10us  (void);
void      Delay20us  (void);
void      Delay100us (void);
void      Delay500us (void);

void      Delay1ms   (unsigned int iDelay1ms);
void      Delay10ms  (unsigned int iDelay10ms);
void      Delay100ms (unsigned int iDelay100ms);


/*------------*/
#endif
