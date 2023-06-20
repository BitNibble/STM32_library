/************************************************************************
	FUNCTION
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 18062023
Comment:
	Tested ->  Atemga128, Atmega328, Atmega32U4, Atmega324, Atmega8535, Atmega88, STM32F446RE
	Very Stable
************************************************************************/
#ifndef _FUNCTION_H_
	#define _FUNCTION_H_

/*** Global Library ***/
#include <inttypes.h>
/*** Global Define & Macro ***/
#define FUNCSTRSIZE 95

/*** Global TypeDef ***/
// Low Byte High Byte
typedef struct
{
	uint8_t H;
	uint8_t L;
} FUNCHighLowByte;
/*** PROCEDURE & FUNCTION TypeDef ***/
typedef struct
{
	// PROTOTYPES VTABLE
	/******/
	uint16_t (*ReadHLByte)(FUNCHighLowByte reg);
	uint16_t (*ReadLHByte)(FUNCHighLowByte reg);
	FUNCHighLowByte (*WriteHLByte)(uint16_t val);
	FUNCHighLowByte (*WriteLHByte)(uint16_t val);
	uint16_t (*SwapByte)(uint16_t num);
	/******/
	int (*stringlength)(const char string[]);
	void (*reverse)(char s[]);
	unsigned int (*mayia)(unsigned int xi, unsigned int xf, uint8_t nbits);
	void (*swap)(long *px, long *py);
	void (*copy)(char to[], char from[]);
	void (*squeeze)(char s[], int c);
	void (*shellsort)(int v[], int n);
	char* (*resizestr)(char *string, int size);
	int (*trim)(char s[]);
	/******/
	uint8_t (*bcd2dec)(uint8_t num);
	uint8_t (*dec2bcd)(uint8_t num);
	char* (*dectohex)(int32_t num);
	uint8_t (*bcd2bin)(uint8_t val);
	/******/
	char* (*print_v1)( char* str, uint8_t size_str, const char* format, ... );
	char* (*print_v2)( const char *format, ... );
	char* (*print_binary)(unsigned int n_bits, unsigned int number);
	/*******/
	char* (*i16toa)(int16_t n);
	char* (*ui16toa)(uint16_t n);
	char* (*i32toa)(int32_t n);
	char* (*ftoa)(double num, char* res, uint8_t afterpoint);
	int (*strToInt)(const char string[]);
	/*******/
	long (*trimmer)(long x, long in_min, long in_max, long out_min, long out_max);
	int (*pmax)(int a1, int a2);
	int (*gcd_v1)(int u, int v);
	long (*gcd_v2)(long a, long b);
	/******/
	int (*twocomptoint8bit)(int twoscomp);
	int (*twocomptoint10bit)(int twoscomp);
	int (*twocomptointnbit)(int twoscomp, uint8_t nbits);
	/******/
	uint32_t (*readreg)(uint32_t reg, uint32_t size_block, uint32_t bit);
	void (*writereg)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
	void (*setreg)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
	void (*setbit)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
	uint32_t (*getsetbit)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
	void (*regsetbits)( unsigned int* reg, int n_bits, ... );
	void (*regresetbits)( unsigned int* reg, int n_bits, ... );
	void (*vecsetup)( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n );
	/******/
	uint32_t (*triggerA)(uint32_t hllh_io, uint8_t pin, uint32_t counter);
	uint32_t (*triggerB)(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
	uint32_t (*value)(void);

}FUNC;

FUNC FUNCenable(void);

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


