#ifndef INTERRUPT_H
#define INTERRUPT_H

extern volatile char rxData;

void __interrupt() ISR(void);

#endif