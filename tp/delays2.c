#include "delays2.h"
#include <p18cxxx.h>

void Delay5us(void)
{
  Delay1us();
  Delay1us();
  Delay1us();
  Delay1us();
}

void Delay20us(void)
{
  Delay5us();
  Delay5us();
  Delay5us();
  Delay5us();
}

void Delay100us(void)
{
  Delay20us();
  Delay20us();
  Delay20us();
  Delay20us();
  Delay20us();
}


void Delay10us(void)
{
  Delay5us();
  Delay1us();
}


void Delay500us(void)
{
  Delay200us()
  Delay100us();
}

void Delay1ms(unsigned int iDelay1ms)
{
	unsigned int delay; 
	while (iDelay1ms--)
	{
		for(delay = 0; delay < 249u; delay++)
		{
                    Nop();
                }
        }
}


void Delay10ms(unsigned int iDelay10ms)
{
	while(iDelay10ms--)
		Delay1ms(10);
}

void Delay100ms(unsigned int iDelay100ms)
{
	while(iDelay100ms--)
		Delay1ms(100);
}
