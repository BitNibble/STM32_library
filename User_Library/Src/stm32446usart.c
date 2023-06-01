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

uint32_t usart_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void usart_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);

// USART1
STM32446USART1 STM32446USART1enable(void)
{
	STM32446USART1 usart1;

	usart1.reg = (USART_TypeDef*) USART1_BASE;
	// SR
	usart1.sr.cts = STM32446Usart1_cts;
	usart1.sr.clear_cts = STM32446Usart1_clear_cts;
	usart1.sr.lbd = STM32446Usart1_lbd;
	usart1.sr.clear_lbd = STM32446Usart1_clear_lbd;
	usart1.sr.txe = STM32446Usart1_txe;
	usart1.sr.tc = STM32446Usart1_tc;
	usart1.sr.clear_tc = STM32446Usart1_clear_tc;
	usart1.sr.rxne = STM32446Usart1_rxne;
	usart1.sr.clear_rxne = STM32446Usart1_clear_rxne;
	usart1.sr.idle = STM32446Usart1_idle;
	usart1.sr.ore = STM32446Usart1_ore;
	usart1.sr.nf = STM32446Usart1_nf;
	usart1.sr.fe = STM32446Usart1_fe;
	usart1.sr.pe = STM32446Usart1_pe;
	// DR
	usart1.dr = STM32446Usart1_dr;
	usart1.get_dr = STM32446Usart1_get_dr;
	// BRR
	usart1.brr.div_mantissa = STM32446Usart1_div_mantissa;
	usart1.brr.div_fraction = STM32446Usart1_div_fraction;
	// CR1
	usart1.cr1.over8 = STM32446Usart1_over8;
	usart1.cr1.ue = STM32446Usart1_ue;
	usart1.cr1.m = STM32446Usart1_m;
	usart1.cr1.wake = STM32446Usart1_wake;
	usart1.cr1.pce = STM32446Usart1_pce;
	usart1.cr1.ps = STM32446Usart1_ps;
	usart1.cr1.peie = STM32446Usart1_peie;
	usart1.cr1.txeie = STM32446Usart1_txeie;
	usart1.cr1.tcie = STM32446Usart1_tcie;
	usart1.cr1.rxneie = STM32446Usart1_rxneie;
	usart1.cr1.idleie = STM32446Usart1_idleie;
	usart1.cr1.te = STM32446Usart1_te;
	usart1.cr1.re = STM32446Usart1_re;
	usart1.cr1.rwu = STM32446Usart1_rwu;
	usart1.cr1.sbk = STM32446Usart1_sbk;
	// CR2
	usart1.cr2.linen = STM32446Usart1_linen;
	usart1.cr2.stop = STM32446Usart1_stop;
	usart1.cr2.clken = STM32446Usart1_clken;
	usart1.cr2.cpol = STM32446Usart1_cpol;
	usart1.cr2.cpha = STM32446Usart1_cpha;
	usart1.cr2.lbcl = STM32446Usart1_lbcl;
	usart1.cr2.lbdie = STM32446Usart1_lbdie;
	usart1.cr2.lbdl = STM32446Usart1_lbdl;
	usart1.cr2.add = STM32446Usart1_add;
	// CR3
	usart1.cr3.onebit = STM32446Usart1_onebit;
	usart1.cr3.ctsie = STM32446Usart1_ctsie;
	usart1.cr3.ctse = STM32446Usart1_ctse;
	usart1.cr3.rtse = STM32446Usart1_rtse;
	usart1.cr3.dmat = STM32446Usart1_dmat;
	usart1.cr3.dmar = STM32446Usart1_dmar;
	usart1.cr3.scen = STM32446Usart1_scen;
	usart1.cr3.nack = STM32446Usart1_nack;
	usart1.cr3.hdsel = STM32446Usart1_hdsel;
	usart1.cr3.irlp = STM32446Usart1_irlp;
	usart1.cr3.iren = STM32446Usart1_iren;
	usart1.cr3.eie = STM32446Usart1_eie;
	// GTPR
	usart1.gtpr.gt = STM32446Usart1_gt;
	usart1.gtpr.psc = STM32446Usart1_psc;
	// Other
	usart1.clock = STM32446Usart1Clock;
	usart1.inic = STM32446Usart1Inic;
	usart1.transmit = STM32446Usart1Transmit;
	usart1.receive = STM32446Usart1Receive;
	usart1.stop = STM32446Usart1Stop;

	RCC->APB2ENR |= (1 << 4); // USART1EN: USART1 clock enable

	return usart1;
}

void STM32446Usart1Clock( void )
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
	//stm32446.gpioa.moder(2,9);
	//stm32446.gpioa.moder(2,10);
	//stm32446.gpioa.afr(7,9);
	//stm32446.gpioa.afr(7,10);
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

// SR
uint8_t STM32446Usart1_cts(void)
{
	return usart_getbit(USART1->SR, 1, 9);
}
void STM32446Usart1_clear_cts(void)
{
	usart_setbit(&USART1->SR, 1, 9, 0);
}
uint8_t STM32446Usart1_lbd(void)
{
	return usart_getbit(USART1->SR, 1, 8);
}
void STM32446Usart1_clear_lbd(void)
{
	usart_setbit(&USART1->SR, 1, 8, 0);
}
uint8_t STM32446Usart1_txe(void)
{
	return usart_getbit(USART1->SR, 1, 7);
}
uint8_t STM32446Usart1_tc(void)
{
	return usart_getbit(USART1->SR, 1, 6);
}
void STM32446Usart1_clear_tc(void)
{
	usart_setbit(&USART1->SR, 1, 6, 0);
}
uint8_t STM32446Usart1_rxne(void)
{
	return usart_getbit(USART1->SR, 1, 5);
}
void STM32446Usart1_clear_rxne(void)
{
	usart_setbit(&USART1->SR, 1, 5, 0);
}
uint8_t STM32446Usart1_idle(void)
{
	return usart_getbit(USART1->SR, 1, 4);
}
uint8_t STM32446Usart1_ore(void)
{
	return usart_getbit(USART1->SR, 1, 3);
}
uint8_t STM32446Usart1_nf(void)
{
	return usart_getbit(USART1->SR, 1, 2);
}
uint8_t STM32446Usart1_fe(void)
{
	return usart_getbit(USART1->SR, 1, 1);
}
uint8_t STM32446Usart1_pe(void)
{
	return usart_getbit(USART1->SR, 1, 0);
}

// DR
void STM32446Usart1_dr(uint16_t value)
{
	usart_setbit(&USART1->DR, 9, 0, value);
}
uint16_t STM32446Usart1_get_dr(void)
{
	return usart_getbit(USART1->DR, 9, 0);
}

// BRR
void STM32446Usart1_div_mantissa(uint16_t value)
{
	usart_setbit(&USART1->BRR, 12, 4, value);
}
void STM32446Usart1_div_fraction(uint8_t value)
{
	usart_setbit(&USART1->BRR, 4, 0, value);
}

// CR1
void STM32446Usart1_over8(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 15, bool);
}
void STM32446Usart1_ue(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 13, bool);
}
void STM32446Usart1_m(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 12, bool);
}
void STM32446Usart1_wake(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 11, bool);
}
void STM32446Usart1_pce(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 10, bool);
}
void STM32446Usart1_ps(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 9, bool);
}
void STM32446Usart1_peie(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 8, bool);
}
void STM32446Usart1_txeie(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 7, bool);
}
void STM32446Usart1_tcie(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 6, bool);
}
void STM32446Usart1_rxneie(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 5, bool);
}
void STM32446Usart1_idleie(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 4, bool);
}
void STM32446Usart1_te(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 3, bool);
}
void STM32446Usart1_re(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 2, bool);
}
void STM32446Usart1_rwu(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 1, bool);
}
void STM32446Usart1_sbk(uint8_t bool)
{
	usart_setbit(&USART1->CR1, 1, 0, bool);
}

// CR2
void STM32446Usart1_linen(uint8_t bool)
{
	usart_setbit(&USART1->CR2, 1, 14, bool);
}
void STM32446Usart1_stop(uint8_t value)
{
	usart_setbit(&USART1->CR2, 2, 12, value);
}
void STM32446Usart1_clken(uint8_t bool)
{
	usart_setbit(&USART1->CR2, 1, 11, bool);
}
void STM32446Usart1_cpol(uint8_t bool)
{
	usart_setbit(&USART1->CR2, 1, 10, bool);
}
void STM32446Usart1_cpha(uint8_t bool)
{
	usart_setbit(&USART1->CR2, 1, 9, bool);
}
void STM32446Usart1_lbcl(uint8_t bool)
{
	usart_setbit(&USART1->CR2, 1, 8, bool);
}
void STM32446Usart1_lbdie(uint8_t bool)
{
	usart_setbit(&USART1->CR2, 1, 6, bool);
}
void STM32446Usart1_lbdl(uint8_t bool)
{
	usart_setbit(&USART1->CR2, 1, 5, bool);
}
void STM32446Usart1_add(uint8_t value)
{
	usart_setbit(&USART1->CR2, 4, 0, value);
}

// CR3
void STM32446Usart1_onebit(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 11, bool);
}
void STM32446Usart1_ctsie(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 10, bool);
}
void STM32446Usart1_ctse(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 9, bool);
}
void STM32446Usart1_rtse(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 8, bool);
}
void STM32446Usart1_dmat(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 7, bool);
}
void STM32446Usart1_dmar(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 6, bool);
}
void STM32446Usart1_scen(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 5, bool);
}
void STM32446Usart1_nack(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 4, bool);
}
void STM32446Usart1_hdsel(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 3, bool);
}
void STM32446Usart1_irlp(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 2, bool);
}
void STM32446Usart1_iren(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 1, bool);
}
void STM32446Usart1_eie(uint8_t bool)
{
	usart_setbit(&USART1->CR3, 1, 0, bool);
}

// GTPR
void STM32446Usart1_gt(uint8_t value)
{
	usart_setbit(&USART1->GTPR, 8, 8, value);
}
void STM32446Usart1_psc(uint8_t value)
{
	usart_setbit(&USART1->GTPR, 8, 0, value);
}

uint32_t usart_getclocksource(void)
{
	uint32_t reg = RCC->CR;
	uint32_t source;
	if(reg & (1 << 1)){source = HSI_RC;}else if(reg & (1 << 17)){source = HSE_OSC;}

	return source;
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
			value = ( usart_getclocksource() / usart_getpllm() ) * ( usart_getplln() / usart_getpllp() );
		break;
		case 3: // 11: PLL_R used as the system clock
			value = ( usart_getclocksource() / usart_getpllm() ) * ( usart_getplln() / usart_getpllr() );
		break;
		default: // 00: HSI oscillator used as the system clock
			value = HSI_RC;
		break;
	}
	return value;
}

/*** File Procedure & Function Definition ***/
uint32_t usart_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void usart_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

/*** EOF ***/


