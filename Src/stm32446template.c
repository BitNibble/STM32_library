/******************************************************************************
	STM32 446 TEMPLATE
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446template.h" // move this then to stm32446mapping header file.
#include <math.h>

/*** File Constant & Macros ***/

/*** File Variable ***/
static STM32446 mapper;

/*** File Header ***/
// TEMPLATE1
void STM32446Template1Inic( uint8_t parameter );
// TEMPLATE1
void STM32446Template1Enable(void);

// TEMPLATE1
STM32446TEMPLATE1 STM32446TEMPLATE1enable(void)
{
	mapper = STM32446enable();
	STM32446TEMPLATE1 template1;

	template1.inic = STM32446Template1Inic;

	STM32446Template1Enable();

	return template1;
}

// TEMPLATE1
void STM32446Template1Enable(void)
{

}

void STM32446Template1Inic( uint8_t parameter )
{
	
}


