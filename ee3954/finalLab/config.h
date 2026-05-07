#ifndef CONFIG_H
#define CONFIG_H

// #include <xc.h>

#define _XTAL_FREQ 32000000

// CONFIG1
#pragma config FEXTOSC = OFF
#pragma config RSTOSC = HFINT32
#pragma config CLKOUTEN = OFF

// CONFIG2
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON

// CONFIG3
#pragma config LVP = OFF

#endif