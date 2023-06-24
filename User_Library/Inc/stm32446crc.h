/******************************************************************************
	STM32 446 CRC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446CRC_H_
	#define _STM32446CRC_H_
/*** Library ***/
#include <inttypes.h>
/*** CRC TypeDef ***/
typedef struct
{
	CRC_TypeDef* reg;
	/*** Bit Mapping ***/
	void (*dr)(uint32_t value);
	uint32_t (*get_dr)(void);
	void (*idr)(uint8_t value);
	uint8_t (*get_idr)(void);
	void (*reset)(void);
	/*** Other ***/
	void (*clock)(uint8_t bool);
}STM32446CRCobj;

STM32446CRCobj crc_inic(void);

/***** CRC Procedure & Function Header ******/

/*** CRC Bit Mapping Header ***/
void STM32446CRC_dr(uint32_t value);
uint32_t STM32446CRC_get_dr(void);
void STM32446CRC_idr(uint8_t value);
uint8_t STM32446CRC_get_idr(void);
void STM32446CRC_reset(void);
/*** Other ***/
void STM32446CRC_clock(uint8_t bool);

#endif

/*** EOF ***/

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


