#include "config.h"
#include "interrupt.h"

volatile char rxData = 0;

void __interrupt() ISR(void)
{
    if(RC1IF)
    {
        rxData = RC1REG;
        RC1IF = 0;
    }
}