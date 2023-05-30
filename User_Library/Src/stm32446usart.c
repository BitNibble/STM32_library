/******************************************************************************
	STM32 446 USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446usart.h"
#include <math.h>

static STM32446 stm32446;

/*** USART 1 ***/
void STM32446Usart1Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
uint32_t usart_getclocksource(void);
uint32_t usart_getsysclk(void);
uint32_t usart_gethpre(void);
uint32_t usart_gethppre1(void);
uint32_t usart_gethppre2(void);
uint32_t usart_getrtcpre(void);
uint32_t usart_gethmco1pre(void);
uint32_t usart_gethmco2pre(void);
uint32_t usart_getpllm(void);
uint32_t usart_getplln(void);
uint32_t usart_getpllp(void);
uint32_t usart_getpllq(void);
uint32_t usart_getpllr(void);
uint32_t usart_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);


// USART1
STM32446USART1 STM32446USART1enable(void)
{
	STM32446USART1 usart1;

	stm32446 = STM32446enable();

	usart1.reg = (USART_TypeDef*) USART1_BASE;

	usart1.inic = STM32446Usart1Inic;
	usart1.transmit = STM32446Usart1Transmit;
	usart1.receive = STM32446Usart1Receive;
	usart1.stop = STM32446Usart1Stop;

	stm32446.query.dummy = 55;
	STM32446Usart1Enable();

	return usart1;
}

// USART1
void STM32446Usart1Enable(void)
{
	RCC->APB2ENR |= (1 << 4); // USART1EN: USART1 clock enable
}

void STM32446Usart1Inic( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
{
	// RCC
	//STM32446Usart1Enable();
	// RCC->APB2ENR |= (1 << 4); // USART1EN: USART1 clock enable
	// Choose GPIO
	// PA9 - TX		PA10 - RX
	// PA11 - CTS		PA12 - RTS
	// AF7 and AF8, activation. therefore
	stm32446.gpioa.moder(2,9);
	stm32446.gpioa.moder(2,10);
	stm32446.gpioa.afr(7,9);
	stm32446.gpioa.afr(7,10);
	//	Procedure:
	// 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	// 2. Program the M bit in USART_CR1 to define the word length.
	// 3. Program the number of stop bits in USART_CR2.
	// 4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
	//   place. Configure the DMA register as explained in multibuffer communication.
	// 5. Select the desired baud rate using the USART_BRR register.

	USART1->CR1 |= (1 << 13); // UE: USART enable
	STM32446Usart1Parameter( wordlength, samplingmode, stopbits, baudrate ); // Default
}

void STM32446Usart1Transmit(void) // RM0390 pg801
{
	//	Procedure:
	// 6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	// 7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
	//	for each data to be transmitted in case of single buffer.
	// 8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
	//	that the transmission of the last frame is complete. This is required for instance when
	//	the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	USART1->CR3 &= (uint32_t) ~(1 << 7); // DMAT: DMA enable transmitter - disabled
	USART1->CR1 |= (1 << 3); // TE: Transmitter enable
	// USART1->DR = 'A';
	// on real application, use fall threw method in main
	// for( ; USART1->SR & (1 << 6); ); // TC: Transmission complete
	// added this as disable after confirmed end of transmission [9]
	// USART1->CR1 &= (uint32_t) ~(1 << 13); // UE: USART disable
	USART1->SR &= ~(1 << 6); // TC: Transmission complete
}

void STM32446Usart1Receive(void) // RM0390 pg804
{
	//	Procedure: baud rate register USART_BRR
	// 6.	Set the RE bit USART_CR1. This enables the receiver that begins searching for a start
	//	bit.
	USART1->CR3 &= (uint32_t) ~(1 << 6); // DMAR: DMA enable receiver - disabled
	USART1->CR1 |= (1 << 2); // RE: Receiver enable
	USART1->SR &= ~(1 << 5); // RXNE: Read data register not empty
}

void STM32446Usart1Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;

	if(wordlength == 9)
		USART1->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		USART1->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		USART1->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.

	if(samplingmode == 8){
		sampling = 8;
		USART1->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		USART1->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		USART1->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}

	USART1->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		USART1->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		USART1->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		USART1->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		USART1->CR2 |= (1 << 13);

	value = (double) usart_getsysclk() / ( usart_gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);

	USART1->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		USART1->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART1->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		USART1->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		USART1->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		USART1->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART1->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}

void STM32446Usart1Stop(void){
	// added this as disable after confirmed end of transmission [9]
	USART1->CR1 &= (uint32_t) ~(1 << 13); // UE: USART disable
}

/*** USART 2 ***/
// Future Implementation


/*** USART 3 ***/
// Future Implementation


uint32_t usart_getclocksource(void)
{
	uint32_t reg = RCC->CR;
	uint32_t source;
	if(reg & (1 << 1)){source = HSI_RC;}else if(reg & (1 << 17)){source = HSE_OSC;}

	return source;
}
uint32_t usart_getsysclk(void)
{
	uint32_t reg = RCC->CFGR; uint32_t size_block = 2; uint32_t bit = 2;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	switch(value) // SWS[2]: System clock switch status
	{
		case 1: // 01: HSE oscillator used as the system clock
			value = HSE_OSC;
		break;
		case 2: // 10: PLL used as the system clock
			value = ( stm32446.query.PLL_parameter.Source / stm32446.query.PLL_parameter.M ) * ( stm32446.query.PLL_parameter.N / stm32446.query.PLL_parameter.P );
		break;
		case 3: // 11: PLL_R used as the system clock
			value = ( stm32446.query.PLL_parameter.Source / stm32446.query.PLL_parameter.M ) * ( stm32446.query.PLL_parameter.N / stm32446.query.PLL_parameter.R );
		break;
		default: // 00: HSI oscillator used as the system clock
			value = HSI_RC;
		break;
	}
	return value;
}

uint32_t usart_gethpre(void)
{
	uint32_t reg = RCC->CFGR; uint32_t size_block = 4; uint32_t bit = 4;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	switch(value)
	{
		case 0b1000:
			value = 2;
		break;
		case 0b1001:
			value = 4;
		break;
		case 0b1010:
			value = 8;
		break;
		case 0b1011:
			value = 16;
		break;
		case 0b1100:
			value = 64;
		break;
		case 0b1101:
			value = 128;
		break;
		case 0b1110:
			value = 256;
		break;
		case 0b1111:
			value = 512;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}

uint32_t usart_gethppre1(void)
{
	uint32_t reg = RCC->CFGR; uint32_t size_block = 3; uint32_t bit = 10;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		default:
			value = 1;
		break;
	}
	return value;
}

uint32_t usart_gethppre2(void)
{
	uint32_t reg = RCC->CFGR; uint32_t size_block = 3; uint32_t bit = 13;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		default:
			value = 1;
		break;
	}
	return value;
}

uint32_t usart_getrtcpre(void)
{
	uint32_t reg = RCC->CFGR; uint32_t size_block = 5; uint32_t bit = 16;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	return value;
}

uint32_t usart_gethmco1pre(void)
{
	uint32_t reg = RCC->CFGR; uint32_t size_block = 3; uint32_t bit = 24;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		default:
			value = 1;
		break;
	}
	return value;
}

uint32_t usart_gethmco2pre(void)
{
	uint32_t reg = RCC->CFGR; uint32_t size_block = 3; uint32_t bit = 27;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		default:
			value = 1;
		break;
		}
	return value;
}

uint32_t usart_getpllm(void)
{
	uint32_t reg = RCC->PLLCFGR; uint32_t size_block = 6; uint32_t bit = 0;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	return value;
}

uint32_t usart_getplln(void)
{
	uint32_t reg = RCC->PLLCFGR; uint32_t size_block = 9; uint32_t bit = 6;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	return value;
}

uint32_t usart_getpllp(void)
{
	uint32_t reg = RCC->PLLCFGR; uint32_t size_block = 2; uint32_t bit = 16;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	switch(value)
	{
		case 0b00:
			value = 2;
		break;
		case 0b01:
			value = 4;
		break;
		case 0b10:
			value = 6;
		break;
		case 0b11:
			value = 8;
		break;
		default:
		break;
	}
	return value;
}

uint32_t usart_getpllq(void)
{
	uint32_t reg = RCC->PLLCFGR; uint32_t size_block = 4; uint32_t bit = 24;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	return value;
}

uint32_t usart_getpllr(void)
{
	uint32_t reg = RCC->PLLCFGR; uint32_t size_block = 3; uint32_t bit = 28;
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	return value;
}

uint32_t usart_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);

	switch(value) // Logic
		{
			case 1:
				value = 1;
			break;
			case 2:
				value = 2;
			break;
			case 3:
				value = 3;
			break;
			default:
			break;
		}
	return value;
}

/*** EOF ***/


