#include "config.h"
#include "uart.h"
#include "spi.h"
#include "patterns.h"
#include "interrupt.h"

void printMenu(void)
{
    UART_Write_Text("\r\nMain Menu\r\n");
    UART_Write_Text("f First name\r\n");
    UART_Write_Text("l Last Name\r\n");
    UART_Write_Text("4 Pattern 1\r\n");
    UART_Write_Text("5 Pattern 2\r\n");
    UART_Write_Text("6 Pattern 3\r\n");
    UART_Write_Text("i Inside flash\r\n");
    UART_Write_Text("o Outside flash\r\n");
    UART_Write_Text("m Menu\r\n");
}

void flashOutside(void)
{
    SPI_Write(0x7E);
}

void flashInside(void)
{
    SPI_Write(0x81);
}

void main(void)
{
    TRISA = 0x00;
    LATA = 0x00;

    UART_Init();
    SPI_Init();

    PEIE = 1;
    GIE = 1;

    printMenu();

    while(1)
    {
        if(rxData)
        {
            char cmd = rxData;
            rxData = 0;

            switch(cmd)
            {
                case 'f':
                    UART_Write_Text("Logan\r\n");
                    break;

                case 'l':
                    UART_Write_Text("Fitch\r\n");
                    break;

                case '4':
                    Pattern1();
                    break;

                case '5':
                    Pattern2();
                    break;

                case '6':
                    Pattern3();
                    break;

                case 'i':
                    while(!rxData)
                    {
                        flashInside();
                        __delay_ms(500);
                    }
                    break;

                case 'o':
                    while(!rxData)
                    {
                        flashOutside();
                        __delay_ms(500);
                    }
                    break;

                case 'm':
                    printMenu();
                    break;
            }
        }
    }
}