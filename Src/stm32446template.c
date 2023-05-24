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

/*** File Constant & Macros ***/

/*** File Variable ***/
static STM32446 template_stm32446;

/*** File Header ***/
void STM32446TemplateInic(void);

// ADC1
STM32446TEMPLATE STM32446TEMPLATEenable(void)
{
	template_stm32446 = STM32446enable();
	STM32446TEMPLATE template;

	template.inic = STM32446TemplateInic;

	return template;
}

void STM32446TemplateInic(void)
{
	// Enable TEMPLATE Clock
}

