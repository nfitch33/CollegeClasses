#ifndef UART_H
#define UART_H

void UART_Init(void);
void UART_Write(char data);
void UART_Write_Text(const char *text);

#endif