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
static STM32446USART1 usart1;

/*** USART 1 ***/
void STM32446Usart1Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );

// USART1
STM32446USART1 STM32446USART1enable(void)
{
	stm32446 = STM32446enable();
	usart1.reg = (USART_TypeDef*) USART1_BASE;

	usart1.inic = STM32446Usart1Inic;
	usart1.transmit = STM32446Usart1Transmit;
	usart1.receive = STM32446Usart1Receive;
	usart1.stop = STM32446Usart1Stop;

	STM32446Usart1Enable();

	return usart1;
}

// USART1
void STM32446Usart1Enable(void)
{
	stm32446.rcc.reg->APB2ENR |= (1 << 4); // USART1EN: USART1 clock enable
}

void STM32446Usart1Inic( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
{
	// RCC
	//STM32446Usart1Enable();
	// stm32446.rcc.reg->APB2ENR |= (1 << 4); // USART1EN: USART1 clock enable
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

	usart1.reg->CR1 |= (1 << 13); // UE: USART enable
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
	usart1.reg->CR3 &= (uint32_t) ~(1 << 7); // DMAT: DMA enable transmitter - disabled
	usart1.reg->CR1 |= (1 << 3); // TE: Transmitter enable
	// stm32446.usart1.reg->DR = 'A';
	// on real application, use fall threw method in main
	// for( ; stm32446.usart1.reg->SR & (1 << 6); ); // TC: Transmission complete
	// added this as disable after confirmed end of transmission [9]
	// usart1.reg->CR1 &= (uint32_t) ~(1 << 13); // UE: USART disable
	usart1.reg->SR &= ~(1 << 6); // TC: Transmission complete
}

void STM32446Usart1Receive(void) // RM0390 pg804
{
	//	Procedure: baud rate register USART_BRR
	// 6.	Set the RE bit USART_CR1. This enables the receiver that begins searching for a start
	//	bit.
	usart1.reg->CR3 &= (uint32_t) ~(1 << 6); // DMAR: DMA enable receiver - disabled
	usart1.reg->CR1 |= (1 << 2); // RE: Receiver enable
	usart1.reg->SR &= ~(1 << 5); // RXNE: Read data register not empty
}

void STM32446Usart1Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;

	if(wordlength == 9)
		usart1.reg->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		usart1.reg->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		usart1.reg->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.

	if(samplingmode == 8){
		sampling = 8;
		usart1.reg->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		usart1.reg->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		usart1.reg->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}

	usart1.reg->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		usart1.reg->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		usart1.reg->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		usart1.reg->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		usart1.reg->CR2 |= (1 << 13);

	value = (double) stm32446.query.SystemClock() / ( stm32446.CLOCK_prescaler.AHB * sampling * baudrate );
	fracpart = modf(value, &intpart);

	usart1.reg->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		usart1.reg->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		usart1.reg->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		usart1.reg->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}

void STM32446Usart1Stop(void){
	// added this as disable after confirmed end of transmission [9]
	usart1.reg->CR1 &= (uint32_t) ~(1 << 13); // UE: USART disable
}

/*** USART 2 ***/
// Future Implementation


/*** USART 3 ***/
// Future Implementation

/*** EOF ***/


