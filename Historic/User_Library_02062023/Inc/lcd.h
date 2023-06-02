/************************************************************************
	LCD
Author: Sergio Santos 
   <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32
Date: 12112022
Comment:
	STM32F446RE
	- Make sure the delay are working in the inic function.
************************************************************************/
#ifndef _LCD_H_
	#define _LCD_H_

/*** Global Library ***/
//#include <util/delay.h> // if use AVR ATMEL
#include <inttypes.h>
#include "stm32446mapping.h"

/*** Global Constant & Macro ***/
// ASIGN PORT PINS TO LCD (can be setup in any way)
#define RS 0
#define RW 1
#define EN 2
#define NC 3
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7

/*** LCD ***/
typedef struct
{
	void (*write)(char c, unsigned short D_I);
	char (*read)(unsigned short D_I);
	void (*BF)(void);
	void (*putch)(char c);
	char (*getch)(void);
	void (*string)(const char *s); // RAW
	void (*string_size)(const char* s, uint32_t size); // RAW
	void (*hspace)(uint32_t n);
	void (*clear)(void);
	void (*gotoxy)(unsigned int y, unsigned int x);
	void (*reboot)(void);
}LCD0;

LCD0 LCD0enable(GPIO_TypeDef* reg);

#endif

/***EOF***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/


