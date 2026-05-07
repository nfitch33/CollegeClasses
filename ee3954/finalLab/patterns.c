#include "config.h"
#include "patterns.h"

void Pattern1(void)
{
    for(int i=0;i<9;i++)
    {
        LATA = (i % 8) << 4; // RA4-RA6 shifting pattern
        __delay_ms(200);
    }
}

void Pattern2(void)
{
    unsigned char seq[] = {0x10,0x20,0x40,0x60,0x30,0x50,0x70,0x00,0x40};
    for(int i=0;i<9;i++)
    {
        LATA = seq[i];
        __delay_ms(200);
    }
}

void Pattern3(void)
{
    for(int i=0;i<9;i++)
    {
        LATA ^= 0x70; // toggle RA4-RA6
        __delay_ms(200);
    }
}