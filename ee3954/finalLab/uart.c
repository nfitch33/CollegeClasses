#include "config.h"
#include "uart.h"
// 19,200 BAUD
void UART_Init(void)
{
    TX1STA = 0x24;   // BRGH = 1
    RC1STA = 0x90;   // Enable serial port
    BAUD1CON = 0x08; // BRG16 = 1

    SP1BRG = 416; // 19200 baud @ 32MHz

    RC1IE = 1; // Enable RX interrupt
}

void UART_Write(char data)
{
    while(!TX1IF);
    TX1REG = data;
}

void UART_Write_Text(const char *text)
{
    while(*text)
        UART_Write(*text++);
}