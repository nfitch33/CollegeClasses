#include "config.h"
#include "spi.h"
// 1 MHZ SPI
void SPI_Init(void)
{
    SSP1STAT = 0x40; // SMP middle
    SSP1CON1 = 0x21; // SPI master, Fosc/16 (~1MHz @ 32MHz)

    TRISC3 = 0; // SCK
    TRISC5 = 0; // SDO
}

void SPI_Write(unsigned char data)
{
    SSP1BUF = data;
    while(!SSP1IF);
    SSP1IF = 0;
}