/************************************************************************
	LCD
Author: Sergio Santos 
   <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 25102020
Comment:
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
************************************************************************/
#ifndef _LCD_H_
	#define _LCD_H_
/***Library***/
//#include <util/delay.h>
#include <inttypes.h>
/***Constant & Macro***/
//ASIGN PORT PINS TO LCD (can be setup in any way)
#define RS 0
#define RW 1
#define EN 2
#define NC 3
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7
/***Global Variable***/
typedef struct
{
	/******/
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
/***Header***/
LCD0 LCD0enable(volatile uint32_t *ddr, volatile uint32_t *pupdr, volatile uint32_t *pin, volatile uint32_t *port);
#endif
/***EOF***/

