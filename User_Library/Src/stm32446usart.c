/******************************************************************************
	STM32 446 USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446usart.h"
#include <math.h>
/*** File Procedure & Function Header ***/
uint32_t usart_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void usart_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void usart_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void usart_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t usart_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
uint32_t usart_getclocksource(void);
uint32_t usart_gethpre(void);
uint32_t usart_getpllm(void);
uint32_t usart_getplln(void);
uint32_t usart_getpllp(void);
uint32_t usart_getpllr(void);
uint32_t usart_getsysclk(void);
STM32446USART_SR stm32446_usart1_sr_inic(void);
STM32446USART_BRR stm32446_usart1_brr_inic(void);
STM32446USART_CR1 stm32446_usart1_cr1_inic(void);
STM32446USART_CR2 stm32446_usart1_cr2_inic(void);
STM32446USART_CR3 stm32446_usart1_cr3_inic(void);
STM32446USART_GTPR stm32446_usart1_gtpr_inic(void);
STM32446USART_SR stm32446_usart2_sr_inic(void);
STM32446USART_BRR stm32446_usart2_brr_inic(void);
STM32446USART_CR1 stm32446_usart2_cr1_inic(void);
STM32446USART_CR2 stm32446_usart2_cr2_inic(void);
STM32446USART_CR3 stm32446_usart2_cr3_inic(void);
STM32446USART_GTPR stm32446_usart2_gtpr_inic(void);
STM32446USART_SR stm32446_usart3_sr_inic(void);
STM32446USART_BRR stm32446_usart3_brr_inic(void);
STM32446USART_CR1 stm32446_usart3_cr1_inic(void);
STM32446USART_CR2 stm32446_usart3_cr2_inic(void);
STM32446USART_CR3 stm32446_usart3_cr3_inic(void);
STM32446USART_GTPR stm32446_usart3_gtpr_inic(void);
STM32446USART_SR stm32446_uart4_sr_inic(void);
STM32446USART_BRR stm32446_uart4_brr_inic(void);
STM32446USART_CR1 stm32446_uart4_cr1_inic(void);
STM32446USART_CR2 stm32446_uart4_cr2_inic(void);
STM32446USART_CR3 stm32446_uart4_cr3_inic(void);
STM32446USART_GTPR stm32446_uart4_gtpr_inic(void);
STM32446USART_SR stm32446_uart5_sr_inic(void);
STM32446USART_BRR stm32446_uart5_brr_inic(void);
STM32446USART_CR1 stm32446_uart5_cr1_inic(void);
STM32446USART_CR2 stm32446_uart5_cr2_inic(void);
STM32446USART_CR3 stm32446_uart5_cr3_inic(void);
STM32446USART_GTPR stm32446_uart5_gtpr_inic(void);
STM32446USART_SR stm32446_usart6_sr_inic(void);
STM32446USART_BRR stm32446_usart6_brr_inic(void);
STM32446USART_CR1 stm32446_usart6_cr1_inic(void);
STM32446USART_CR2 stm32446_usart6_cr2_inic(void);
STM32446USART_CR3 stm32446_usart6_cr3_inic(void);
STM32446USART_GTPR stm32446_usart6_gtpr_inic(void);
/*** USART Procedure & Function Definition ***/
/*** USART1 ***/
void STM32446Usart1Clock( uint8_t bool )
{
	if(bool){ RCC->APB2ENR |= (1 << 4); } // USART1EN: USART1 clock enable
	else{ RCC->APB2ENR &= ~(1 << 4); } // USART1EN: USART1 clock disable
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
/*** USART 1 Bit Mapping ***/
// SR
uint8_t STM32446Usart1_cts(void)
{
	return usart_readreg(USART1->SR, 1, 9);
}
void STM32446Usart1_clear_cts(void)
{
	usart_setreg(&USART1->SR, 1, 9, 0);
}
uint8_t STM32446Usart1_lbd(void)
{
	return usart_readreg(USART1->SR, 1, 8);
}
void STM32446Usart1_clear_lbd(void)
{
	usart_setreg(&USART1->SR, 1, 8, 0);
}
uint8_t STM32446Usart1_txe(void)
{
	return usart_readreg(USART1->SR, 1, 7);
}
uint8_t STM32446Usart1_tc(void)
{
	return usart_readreg(USART1->SR, 1, 6);
}
void STM32446Usart1_clear_tc(void)
{
	usart_setreg(&USART1->SR, 1, 6, 0);
}
uint8_t STM32446Usart1_rxne(void)
{
	return usart_readreg(USART1->SR, 1, 5);
}
void STM32446Usart1_clear_rxne(void)
{
	usart_setreg(&USART1->SR, 1, 5, 0);
}
uint8_t STM32446Usart1_idle(void)
{
	return usart_readreg(USART1->SR, 1, 4);
}
uint8_t STM32446Usart1_ore(void)
{
	return usart_readreg(USART1->SR, 1, 3);
}
uint8_t STM32446Usart1_nf(void)
{
	return usart_readreg(USART1->SR, 1, 2);
}
uint8_t STM32446Usart1_fe(void)
{
	return usart_readreg(USART1->SR, 1, 1);
}
uint8_t STM32446Usart1_pe(void)
{
	return usart_readreg(USART1->SR, 1, 0);
}
// DR
void STM32446Usart1_dr(uint32_t data)
{
	usart_writereg(&USART1->DR, 9, 0, data);
}
uint32_t STM32446Usart1_get_dr(void)
{
	return usart_readreg(USART1->DR, 9, 0);
}
// BRR
void STM32446Usart1_div_mantissa(uint16_t value)
{
	usart_setreg(&USART1->BRR, 12, 4, value);
}
void STM32446Usart1_div_fraction(uint8_t value)
{
	usart_setreg(&USART1->BRR, 4, 0, value);
}
// CR1
void STM32446Usart1_over8(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 15, bool);
}
void STM32446Usart1_ue(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 13, bool);
}
void STM32446Usart1_m(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 12, bool);
}
void STM32446Usart1_wake(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 11, bool);
}
void STM32446Usart1_pce(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 10, bool);
}
void STM32446Usart1_ps(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 9, bool);
}
void STM32446Usart1_peie(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 8, bool);
}
void STM32446Usart1_txeie(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 7, bool);
}
void STM32446Usart1_tcie(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 6, bool);
}
void STM32446Usart1_rxneie(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 5, bool);
}
void STM32446Usart1_idleie(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 4, bool);
}
void STM32446Usart1_te(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 3, bool);
}
void STM32446Usart1_re(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 2, bool);
}
void STM32446Usart1_rwu(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 1, bool);
}
void STM32446Usart1_sbk(uint8_t bool)
{
	usart_setreg(&USART1->CR1, 1, 0, bool);
}
// CR2
void STM32446Usart1_linen(uint8_t bool)
{
	usart_setreg(&USART1->CR2, 1, 14, bool);
}
void STM32446Usart1_stop(uint8_t value)
{
	usart_setreg(&USART1->CR2, 2, 12, value);
}

void STM32446Usart1_clken(uint8_t bool)
{
	usart_setreg(&USART1->CR2, 1, 11, bool);
}
void STM32446Usart1_cpol(uint8_t bool)
{
	usart_setreg(&USART1->CR2, 1, 10, bool);
}
void STM32446Usart1_cpha(uint8_t bool)
{
	usart_setreg(&USART1->CR2, 1, 9, bool);
}
void STM32446Usart1_lbcl(uint8_t bool)
{
	usart_setreg(&USART1->CR2, 1, 8, bool);
}
void STM32446Usart1_lbdie(uint8_t bool)
{
	usart_setreg(&USART1->CR2, 1, 6, bool);
}
void STM32446Usart1_lbdl(uint8_t bool)
{
	usart_setreg(&USART1->CR2, 1, 5, bool);
}
void STM32446Usart1_add(uint8_t value)
{
	usart_setreg(&USART1->CR2, 4, 0, value);
}
// CR3
void STM32446Usart1_onebit(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 11, bool);
}
void STM32446Usart1_ctsie(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 10, bool);
}
void STM32446Usart1_ctse(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 9, bool);
}
void STM32446Usart1_rtse(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 8, bool);
}
void STM32446Usart1_dmat(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 7, bool);
}
void STM32446Usart1_dmar(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 6, bool);
}
void STM32446Usart1_scen(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 5, bool);
}
void STM32446Usart1_nack(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 4, bool);
}
void STM32446Usart1_hdsel(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 3, bool);
}
void STM32446Usart1_irlp(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 2, bool);
}
void STM32446Usart1_iren(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 1, bool);
}
void STM32446Usart1_eie(uint8_t bool)
{
	usart_setreg(&USART1->CR3, 1, 0, bool);
}
// GTPR
void STM32446Usart1_gt(uint8_t value)
{
	usart_setreg(&USART1->GTPR, 8, 8, value);
}
void STM32446Usart1_psc(uint8_t value)
{
	usart_setreg(&USART1->GTPR, 8, 0, value);
}
/*** USART2 ***/
void STM32446Usart2Clock( uint8_t bool )
{
	if(bool){ RCC->APB1ENR |= (1 << 17); } // USART2EN: USART2 clock enable
	else{ RCC->APB1ENR &= ~(1 << 17); } // USART2EN: USART2 clock disable
}
void STM32446Usart2Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		USART2->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		USART2->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		USART2->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		USART2->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		USART2->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		USART2->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	USART2->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		USART2->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		USART2->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		USART2->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		USART2->CR2 |= (1 << 13);
	value = (double) usart_getsysclk() / ( usart_gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	USART2->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		USART2->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART2->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		USART2->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		USART2->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		USART2->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART2->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** USART 2 Bit Mapping ***/
// SR
uint8_t STM32446Usart2_cts(void)
{
	return usart_readreg(USART2->SR, 1, 9);
}
void STM32446Usart2_clear_cts(void)
{
	usart_setreg(&USART2->SR, 1, 9, 0);
}
uint8_t STM32446Usart2_lbd(void)
{
	return usart_readreg(USART2->SR, 1, 8);
}
void STM32446Usart2_clear_lbd(void)
{
	usart_setreg(&USART2->SR, 1, 8, 0);
}
uint8_t STM32446Usart2_txe(void)
{
	return usart_readreg(USART2->SR, 1, 7);
}
uint8_t STM32446Usart2_tc(void)
{
	return usart_readreg(USART2->SR, 1, 6);
}
void STM32446Usart2_clear_tc(void)
{
	usart_setreg(&USART2->SR, 1, 6, 0);
}
uint8_t STM32446Usart2_rxne(void)
{
	return usart_readreg(USART2->SR, 1, 5);
}
void STM32446Usart2_clear_rxne(void)
{
	usart_setreg(&USART2->SR, 1, 5, 0);
}
uint8_t STM32446Usart2_idle(void)
{
	return usart_readreg(USART2->SR, 1, 4);
}
uint8_t STM32446Usart2_ore(void)
{
	return usart_readreg(USART2->SR, 1, 3);
}
uint8_t STM32446Usart2_nf(void)
{
	return usart_readreg(USART2->SR, 1, 2);
}
uint8_t STM32446Usart2_fe(void)
{
	return usart_readreg(USART2->SR, 1, 1);
}
uint8_t STM32446Usart2_pe(void)
{
	return usart_readreg(USART2->SR, 1, 0);
}
// DR
void STM32446Usart2_dr(uint32_t data)
{
	usart_writereg(&USART2->DR, 9, 0, data);
}
uint32_t STM32446Usart2_get_dr(void)
{
	return usart_readreg(USART2->DR, 9, 0);
}
// BRR
void STM32446Usart2_div_mantissa(uint16_t value)
{
	usart_setreg(&USART2->BRR, 12, 4, value);
}
void STM32446Usart2_div_fraction(uint8_t value)
{
	usart_setreg(&USART2->BRR, 4, 0, value);
}
// CR1
void STM32446Usart2_over8(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 15, bool);
}
void STM32446Usart2_ue(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 13, bool);
}
void STM32446Usart2_m(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 12, bool);
}
void STM32446Usart2_wake(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 11, bool);
}
void STM32446Usart2_pce(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 10, bool);
}
void STM32446Usart2_ps(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 9, bool);
}
void STM32446Usart2_peie(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 8, bool);
}
void STM32446Usart2_txeie(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 7, bool);
}
void STM32446Usart2_tcie(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 6, bool);
}
void STM32446Usart2_rxneie(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 5, bool);
}
void STM32446Usart2_idleie(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 4, bool);
}
void STM32446Usart2_te(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 3, bool);
}
void STM32446Usart2_re(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 2, bool);
}
void STM32446Usart2_rwu(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 1, bool);
}
void STM32446Usart2_sbk(uint8_t bool)
{
	usart_setreg(&USART2->CR1, 1, 0, bool);
}
// CR2
void STM32446Usart2_linen(uint8_t bool)
{
	usart_setreg(&USART2->CR2, 1, 14, bool);
}
void STM32446Usart2_stop(uint8_t value)
{
	usart_setreg(&USART2->CR2, 2, 12, value);
}
void STM32446Usart2_clken(uint8_t bool)
{
	usart_setreg(&USART2->CR2, 1, 11, bool);
}
void STM32446Usart2_cpol(uint8_t bool)
{
	usart_setreg(&USART2->CR2, 1, 10, bool);
}
void STM32446Usart2_cpha(uint8_t bool)
{
	usart_setreg(&USART2->CR2, 1, 9, bool);
}
void STM32446Usart2_lbcl(uint8_t bool)
{
	usart_setreg(&USART2->CR2, 1, 8, bool);
}
void STM32446Usart2_lbdie(uint8_t bool)
{
	usart_setreg(&USART2->CR2, 1, 6, bool);
}
void STM32446Usart2_lbdl(uint8_t bool)
{
	usart_setreg(&USART2->CR2, 1, 5, bool);
}
void STM32446Usart2_add(uint8_t value)
{
	usart_setreg(&USART2->CR2, 4, 0, value);
}
// CR3
void STM32446Usart2_onebit(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 11, bool);
}
void STM32446Usart2_ctsie(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 10, bool);
}
void STM32446Usart2_ctse(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 9, bool);
}
void STM32446Usart2_rtse(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 8, bool);
}
void STM32446Usart2_dmat(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 7, bool);
}
void STM32446Usart2_dmar(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 6, bool);
}
void STM32446Usart2_scen(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 5, bool);
}
void STM32446Usart2_nack(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 4, bool);
}
void STM32446Usart2_hdsel(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 3, bool);
}
void STM32446Usart2_irlp(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 2, bool);
}
void STM32446Usart2_iren(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 1, bool);
}
void STM32446Usart2_eie(uint8_t bool)
{
	usart_setreg(&USART2->CR3, 1, 0, bool);
}
// GTPR
void STM32446Usart2_gt(uint8_t value)
{
	usart_setreg(&USART2->GTPR, 8, 8, value);
}
void STM32446Usart2_psc(uint8_t value)
{
	usart_setreg(&USART2->GTPR, 8, 0, value);
}
/*** USART3 ***/
void STM32446Usart3Clock( uint8_t bool )
{
	if(bool){ RCC->APB1ENR |= (1 << 18); } // USART3EN: USART3 clock enable
	else{ RCC->APB1ENR &= ~(1 << 18); } // USART3EN: USART3 clock disable
}
void STM32446Usart3Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		USART3->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		USART3->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		USART3->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		USART3->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		USART3->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		USART3->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	USART3->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		USART3->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		USART3->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		USART3->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		USART3->CR2 |= (1 << 13);
	value = (double) usart_getsysclk() / ( usart_gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	USART3->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		USART3->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART3->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		USART3->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		USART3->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		USART3->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART3->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** USART 3 Bit Mapping ***/
// SR
uint8_t STM32446Usart3_cts(void)
{
	return usart_readreg(USART3->SR, 1, 9);
}
void STM32446Usart3_clear_cts(void)
{
	usart_setreg(&USART3->SR, 1, 9, 0);
}
uint8_t STM32446Usart3_lbd(void)
{
	return usart_readreg(USART3->SR, 1, 8);
}
void STM32446Usart3_clear_lbd(void)
{
	usart_setreg(&USART3->SR, 1, 8, 0);
}
uint8_t STM32446Usart3_txe(void)
{
	return usart_readreg(USART3->SR, 1, 7);
}
uint8_t STM32446Usart3_tc(void)
{
	return usart_readreg(USART3->SR, 1, 6);
}
void STM32446Usart3_clear_tc(void)
{
	usart_setreg(&USART3->SR, 1, 6, 0);
}
uint8_t STM32446Usart3_rxne(void)
{
	return usart_readreg(USART3->SR, 1, 5);
}
void STM32446Usart3_clear_rxne(void)
{
	usart_setreg(&USART3->SR, 1, 5, 0);
}
uint8_t STM32446Usart3_idle(void)
{
	return usart_readreg(USART3->SR, 1, 4);
}
uint8_t STM32446Usart3_ore(void)
{
	return usart_readreg(USART3->SR, 1, 3);
}
uint8_t STM32446Usart3_nf(void)
{
	return usart_readreg(USART3->SR, 1, 2);
}
uint8_t STM32446Usart3_fe(void)
{
	return usart_readreg(USART3->SR, 1, 1);
}
uint8_t STM32446Usart3_pe(void)
{
	return usart_readreg(USART3->SR, 1, 0);
}
// DR
void STM32446Usart3_dr(uint32_t data)
{
	usart_writereg(&USART3->DR, 9, 0, data);
}
uint32_t STM32446Usart3_get_dr(void)
{
	return usart_readreg(USART3->DR, 9, 0);
}
// BRR
void STM32446Usart3_div_mantissa(uint16_t value)
{
	usart_setreg(&USART3->BRR, 12, 4, value);
}
void STM32446Usart3_div_fraction(uint8_t value)
{
	usart_setreg(&USART3->BRR, 4, 0, value);
}
// CR1
void STM32446Usart3_over8(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 15, bool);
}
void STM32446Usart3_ue(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 13, bool);
}
void STM32446Usart3_m(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 12, bool);
}
void STM32446Usart3_wake(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 11, bool);
}
void STM32446Usart3_pce(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 10, bool);
}
void STM32446Usart3_ps(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 9, bool);
}
void STM32446Usart3_peie(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 8, bool);
}
void STM32446Usart3_txeie(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 7, bool);
}
void STM32446Usart3_tcie(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 6, bool);
}
void STM32446Usart3_rxneie(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 5, bool);
}
void STM32446Usart3_idleie(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 4, bool);
}
void STM32446Usart3_te(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 3, bool);
}
void STM32446Usart3_re(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 2, bool);
}
void STM32446Usart3_rwu(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 1, bool);
}
void STM32446Usart3_sbk(uint8_t bool)
{
	usart_setreg(&USART3->CR1, 1, 0, bool);
}
// CR2
void STM32446Usart3_linen(uint8_t bool)
{
	usart_setreg(&USART3->CR2, 1, 14, bool);
}
void STM32446Usart3_stop(uint8_t value)
{
	usart_setreg(&USART3->CR2, 2, 12, value);
}
void STM32446Usart3_clken(uint8_t bool)
{
	usart_setreg(&USART3->CR2, 1, 11, bool);
}
void STM32446Usart3_cpol(uint8_t bool)
{
	usart_setreg(&USART3->CR2, 1, 10, bool);
}
void STM32446Usart3_cpha(uint8_t bool)
{
	usart_setreg(&USART3->CR2, 1, 9, bool);
}
void STM32446Usart3_lbcl(uint8_t bool)
{
	usart_setreg(&USART3->CR2, 1, 8, bool);
}
void STM32446Usart3_lbdie(uint8_t bool)
{
	usart_setreg(&USART3->CR2, 1, 6, bool);
}
void STM32446Usart3_lbdl(uint8_t bool)
{
	usart_setreg(&USART3->CR2, 1, 5, bool);
}
void STM32446Usart3_add(uint8_t value)
{
	usart_setreg(&USART3->CR2, 4, 0, value);
}
// CR3
void STM32446Usart3_onebit(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 11, bool);
}
void STM32446Usart3_ctsie(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 10, bool);
}
void STM32446Usart3_ctse(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 9, bool);
}
void STM32446Usart3_rtse(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 8, bool);
}
void STM32446Usart3_dmat(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 7, bool);
}
void STM32446Usart3_dmar(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 6, bool);
}
void STM32446Usart3_scen(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 5, bool);
}
void STM32446Usart3_nack(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 4, bool);
}
void STM32446Usart3_hdsel(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 3, bool);
}
void STM32446Usart3_irlp(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 2, bool);
}
void STM32446Usart3_iren(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 1, bool);
}
void STM32446Usart3_eie(uint8_t bool)
{
	usart_setreg(&USART3->CR3, 1, 0, bool);
}
// GTPR
void STM32446Usart3_gt(uint8_t value)
{
	usart_setreg(&USART3->GTPR, 8, 8, value);
}
void STM32446Usart3_psc(uint8_t value)
{
	usart_setreg(&USART3->GTPR, 8, 0, value);
}
/*** UART4 ***/
void STM32446Uart4Clock( uint8_t bool )
{
	if(bool){ RCC->APB1ENR |= (1 << 19); } // UART4EN: USART4 clock enable
	else{ RCC->APB1ENR &= ~(1 << 19); } // UART4EN: USART4 clock disable

}
void STM32446Uart4Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the uart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		UART4->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		UART4->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		UART4->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		UART4->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		UART4->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		UART4->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	UART4->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		UART4->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		UART4->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		UART4->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		UART4->CR2 |= (1 << 13);
	value = (double) usart_getsysclk() / ( usart_gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	UART4->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		UART4->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		UART4->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		UART4->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		UART4->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		UART4->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		UART4->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** UART 4 Bit Mapping ***/
// SR
uint8_t STM32446Uart4_cts(void)
{
	return usart_readreg(UART4->SR, 1, 9);
}
void STM32446Uart4_clear_cts(void)
{
	usart_setreg(&UART4->SR, 1, 9, 0);
}
uint8_t STM32446Uart4_lbd(void)
{
	return usart_readreg(UART4->SR, 1, 8);
}
void STM32446Uart4_clear_lbd(void)
{
	usart_setreg(&UART4->SR, 1, 8, 0);
}
uint8_t STM32446Uart4_txe(void)
{
	return usart_readreg(UART4->SR, 1, 7);
}
uint8_t STM32446Uart4_tc(void)
{
	return usart_readreg(UART4->SR, 1, 6);
}
void STM32446Uart4_clear_tc(void)
{
	usart_setreg(&UART4->SR, 1, 6, 0);
}
uint8_t STM32446Uart4_rxne(void)
{
	return usart_readreg(UART4->SR, 1, 5);
}
void STM32446Uart4_clear_rxne(void)
{
	usart_setreg(&UART4->SR, 1, 5, 0);
}
uint8_t STM32446Uart4_idle(void)
{
	return usart_readreg(UART4->SR, 1, 4);
}
uint8_t STM32446Uart4_ore(void)
{
	return usart_readreg(UART4->SR, 1, 3);
}
uint8_t STM32446Uart4_nf(void)
{
	return usart_readreg(UART4->SR, 1, 2);
}
uint8_t STM32446Uart4_fe(void)
{
	return usart_readreg(UART4->SR, 1, 1);
}
uint8_t STM32446Uart4_pe(void)
{
	return usart_readreg(UART4->SR, 1, 0);
}
// DR
void STM32446Uart4_dr(uint32_t data)
{
	usart_writereg(&UART4->DR, 9, 0, data);
}
uint32_t STM32446Uart4_get_dr(void)
{
	return usart_readreg(UART4->DR, 9, 0);
}
// BRR
void STM32446Uart4_div_mantissa(uint16_t value)
{
	usart_setreg(&UART4->BRR, 12, 4, value);
}
void STM32446Uart4_div_fraction(uint8_t value)
{
	usart_setreg(&UART4->BRR, 4, 0, value);
}
// CR1
void STM32446Uart4_over8(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 15, bool);
}
void STM32446Uart4_ue(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 13, bool);
}
void STM32446Uart4_m(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 12, bool);
}
void STM32446Uart4_wake(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 11, bool);
}
void STM32446Uart4_pce(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 10, bool);
}
void STM32446Uart4_ps(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 9, bool);
}
void STM32446Uart4_peie(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 8, bool);
}
void STM32446Uart4_txeie(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 7, bool);
}
void STM32446Uart4_tcie(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 6, bool);
}
void STM32446Uart4_rxneie(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 5, bool);
}
void STM32446Uart4_idleie(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 4, bool);
}
void STM32446Uart4_te(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 3, bool);
}
void STM32446Uart4_re(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 2, bool);
}
void STM32446Uart4_rwu(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 1, bool);
}
void STM32446Uart4_sbk(uint8_t bool)
{
	usart_setreg(&UART4->CR1, 1, 0, bool);
}
// CR2
void STM32446Uart4_linen(uint8_t bool)
{
	usart_setreg(&UART4->CR2, 1, 14, bool);
}
void STM32446Uart4_stop(uint8_t value)
{
	usart_setreg(&UART4->CR2, 2, 12, value);
}
void STM32446Uart4_clken(uint8_t bool)
{
	usart_setreg(&UART4->CR2, 1, 11, bool);
}
void STM32446Uart4_cpol(uint8_t bool)
{
	usart_setreg(&UART4->CR2, 1, 10, bool);
}
void STM32446Uart4_cpha(uint8_t bool)
{
	usart_setreg(&UART4->CR2, 1, 9, bool);
}
void STM32446Uart4_lbcl(uint8_t bool)
{
	usart_setreg(&UART4->CR2, 1, 8, bool);
}
void STM32446Uart4_lbdie(uint8_t bool)
{
	usart_setreg(&UART4->CR2, 1, 6, bool);
}
void STM32446Uart4_lbdl(uint8_t bool)
{
	usart_setreg(&UART4->CR2, 1, 5, bool);
}
void STM32446Uart4_add(uint8_t value)
{
	usart_setreg(&UART4->CR2, 4, 0, value);
}
// CR3
void STM32446Uart4_onebit(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 11, bool);
}
void STM32446Uart4_ctsie(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 10, bool);
}
void STM32446Uart4_ctse(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 9, bool);
}
void STM32446Uart4_rtse(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 8, bool);
}
void STM32446Uart4_dmat(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 7, bool);
}
void STM32446Uart4_dmar(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 6, bool);
}
void STM32446Uart4_scen(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 5, bool);
}
void STM32446Uart4_nack(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 4, bool);
}
void STM32446Uart4_hdsel(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 3, bool);
}
void STM32446Uart4_irlp(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 2, bool);
}
void STM32446Uart4_iren(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 1, bool);
}
void STM32446Uart4_eie(uint8_t bool)
{
	usart_setreg(&UART4->CR3, 1, 0, bool);
}
// GTPR
void STM32446Uart4_gt(uint8_t value)
{
	usart_setreg(&UART4->GTPR, 8, 8, value);
}
void STM32446Uart4_psc(uint8_t value)
{
	usart_setreg(&UART4->GTPR, 8, 0, value);
}
/*** UART5 ***/
void STM32446Uart5Clock( uint8_t bool )
{
	if(bool){ RCC->APB1ENR |= (1 << 20); } // UART5EN: USART5 clock enable
	else{ RCC->APB1ENR &= ~(1 << 20); } // UART5EN: USART5 clock disable
}
void STM32446Uart5Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the uart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		UART5->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		UART5->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		UART5->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		UART5->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		UART5->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		UART5->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	UART5->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		UART5->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		UART5->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		UART5->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		UART5->CR2 |= (1 << 13);
	value = (double) usart_getsysclk() / ( usart_gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	UART5->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		UART5->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		UART5->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		UART5->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		UART5->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		UART5->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		UART5->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** UART 5 Bit Mapping ***/
// SR
uint8_t STM32446Uart5_cts(void)
{
	return usart_readreg(UART5->SR, 1, 9);
}
void STM32446Uart5_clear_cts(void)
{
	usart_setreg(&UART5->SR, 1, 9, 0);
}
uint8_t STM32446Uart5_lbd(void)
{
	return usart_readreg(UART5->SR, 1, 8);
}
void STM32446Uart5_clear_lbd(void)
{
	usart_setreg(&UART5->SR, 1, 8, 0);
}
uint8_t STM32446Uart5_txe(void)
{
	return usart_readreg(UART5->SR, 1, 7);
}
uint8_t STM32446Uart5_tc(void)
{
	return usart_readreg(UART5->SR, 1, 6);
}
void STM32446Uart5_clear_tc(void)
{
	usart_setreg(&UART5->SR, 1, 6, 0);
}
uint8_t STM32446Uart5_rxne(void)
{
	return usart_readreg(UART5->SR, 1, 5);
}
void STM32446Uart5_clear_rxne(void)
{
	usart_setreg(&UART5->SR, 1, 5, 0);
}
uint8_t STM32446Uart5_idle(void)
{
	return usart_readreg(UART5->SR, 1, 4);
}
uint8_t STM32446Uart5_ore(void)
{
	return usart_readreg(UART5->SR, 1, 3);
}
uint8_t STM32446Uart5_nf(void)
{
	return usart_readreg(UART5->SR, 1, 2);
}
uint8_t STM32446Uart5_fe(void)
{
	return usart_readreg(UART5->SR, 1, 1);
}
uint8_t STM32446Uart5_pe(void)
{
	return usart_readreg(UART5->SR, 1, 0);
}
// DR
void STM32446Uart5_dr(uint32_t data)
{
	usart_writereg(&UART5->DR, 9, 0, data);
}
uint32_t STM32446Uart5_get_dr(void)
{
	return usart_readreg(UART5->DR, 9, 0);
}
// BRR
void STM32446Uart5_div_mantissa(uint16_t value)
{
	usart_setreg(&UART5->BRR, 12, 4, value);
}
void STM32446Uart5_div_fraction(uint8_t value)
{
	usart_setreg(&UART5->BRR, 4, 0, value);
}
// CR1
void STM32446Uart5_over8(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 15, bool);
}
void STM32446Uart5_ue(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 13, bool);
}
void STM32446Uart5_m(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 12, bool);
}
void STM32446Uart5_wake(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 11, bool);
}
void STM32446Uart5_pce(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 10, bool);
}
void STM32446Uart5_ps(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 9, bool);
}
void STM32446Uart5_peie(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 8, bool);
}
void STM32446Uart5_txeie(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 7, bool);
}
void STM32446Uart5_tcie(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 6, bool);
}
void STM32446Uart5_rxneie(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 5, bool);
}
void STM32446Uart5_idleie(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 4, bool);
}
void STM32446Uart5_te(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 3, bool);
}
void STM32446Uart5_re(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 2, bool);
}
void STM32446Uart5_rwu(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 1, bool);
}
void STM32446Uart5_sbk(uint8_t bool)
{
	usart_setreg(&UART5->CR1, 1, 0, bool);
}
// CR2
void STM32446Uart5_linen(uint8_t bool)
{
	usart_setreg(&UART5->CR2, 1, 14, bool);
}
void STM32446Uart5_stop(uint8_t value)
{
	usart_setreg(&UART5->CR2, 2, 12, value);
}
void STM32446Uart5_clken(uint8_t bool)
{
	usart_setreg(&UART5->CR2, 1, 11, bool);
}
void STM32446Uart5_cpol(uint8_t bool)
{
	usart_setreg(&UART5->CR2, 1, 10, bool);
}
void STM32446Uart5_cpha(uint8_t bool)
{
	usart_setreg(&UART5->CR2, 1, 9, bool);
}
void STM32446Uart5_lbcl(uint8_t bool)
{
	usart_setreg(&UART5->CR2, 1, 8, bool);
}
void STM32446Uart5_lbdie(uint8_t bool)
{
	usart_setreg(&UART5->CR2, 1, 6, bool);
}
void STM32446Uart5_lbdl(uint8_t bool)
{
	usart_setreg(&UART5->CR2, 1, 5, bool);
}
void STM32446Uart5_add(uint8_t value)
{
	usart_setreg(&UART5->CR2, 4, 0, value);
}
// CR3
void STM32446Uart5_onebit(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 11, bool);
}
void STM32446Uart5_ctsie(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 10, bool);
}
void STM32446Uart5_ctse(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 9, bool);
}
void STM32446Uart5_rtse(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 8, bool);
}
void STM32446Uart5_dmat(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 7, bool);
}
void STM32446Uart5_dmar(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 6, bool);
}
void STM32446Uart5_scen(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 5, bool);
}
void STM32446Uart5_nack(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 4, bool);
}
void STM32446Uart5_hdsel(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 3, bool);
}
void STM32446Uart5_irlp(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 2, bool);
}
void STM32446Uart5_iren(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 1, bool);
}
void STM32446Uart5_eie(uint8_t bool)
{
	usart_setreg(&UART5->CR3, 1, 0, bool);
}
// GTPR
void STM32446Uart5_gt(uint8_t value)
{
	usart_setreg(&UART5->GTPR, 8, 8, value);
}
void STM32446Uart5_psc(uint8_t value)
{
	usart_setreg(&UART5->GTPR, 8, 0, value);
}
/*** USART6 ***/
void STM32446Usart6Clock( uint8_t bool )
{
	if(bool){ RCC->APB2ENR |= (1 << 5); } // USART6EN: USART6 clock enable
	else{ RCC->APB2ENR &= ~(1 << 5); } // USART6EN: USART6 clock disable
}
void STM32446Usart6Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		USART6->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		USART6->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		USART6->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		USART6->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		USART6->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		USART6->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	USART6->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		USART6->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		USART6->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		USART6->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		USART6->CR2 |= (1 << 13);
	value = (double) usart_getsysclk() / ( usart_gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	USART6->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		USART6->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART6->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		USART6->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		USART6->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		USART6->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART6->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** USART 6 Bit Mapping ***/
// SR
uint8_t STM32446Usart6_cts(void)
{
	return usart_readreg(USART6->SR, 1, 9);
}
void STM32446Usart6_clear_cts(void)
{
	usart_setreg(&USART6->SR, 1, 9, 0);
}
uint8_t STM32446Usart6_lbd(void)
{
	return usart_readreg(USART6->SR, 1, 8);
}
void STM32446Usart6_clear_lbd(void)
{
	usart_setreg(&USART6->SR, 1, 8, 0);
}
uint8_t STM32446Usart6_txe(void)
{
	return usart_readreg(USART6->SR, 1, 7);
}
uint8_t STM32446Usart6_tc(void)
{
	return usart_readreg(USART6->SR, 1, 6);
}
void STM32446Usart6_clear_tc(void)
{
	usart_setreg(&USART6->SR, 1, 6, 0);
}
uint8_t STM32446Usart6_rxne(void)
{
	return usart_readreg(USART6->SR, 1, 5);
}
void STM32446Usart6_clear_rxne(void)
{
	usart_setreg(&USART6->SR, 1, 5, 0);
}
uint8_t STM32446Usart6_idle(void)
{
	return usart_readreg(USART6->SR, 1, 4);
}
uint8_t STM32446Usart6_ore(void)
{
	return usart_readreg(USART6->SR, 1, 3);
}
uint8_t STM32446Usart6_nf(void)
{
	return usart_readreg(USART6->SR, 1, 2);
}
uint8_t STM32446Usart6_fe(void)
{
	return usart_readreg(USART6->SR, 1, 1);
}
uint8_t STM32446Usart6_pe(void)
{
	return usart_readreg(USART6->SR, 1, 0);
}
// DR
void STM32446Usart6_dr(uint32_t data)
{
	usart_writereg(&USART6->DR, 9, 0, data);
}
uint32_t STM32446Usart6_get_dr(void)
{
	return usart_readreg(USART6->DR, 9, 0);
}
// BRR
void STM32446Usart6_div_mantissa(uint16_t value)
{
	usart_setreg(&USART6->BRR, 12, 4, value);
}
void STM32446Usart6_div_fraction(uint8_t value)
{
	usart_setreg(&USART6->BRR, 4, 0, value);
}
// CR1
void STM32446Usart6_over8(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 15, bool);
}
void STM32446Usart6_ue(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 13, bool);
}
void STM32446Usart6_m(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 12, bool);
}
void STM32446Usart6_wake(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 11, bool);
}
void STM32446Usart6_pce(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 10, bool);
}
void STM32446Usart6_ps(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 9, bool);
}
void STM32446Usart6_peie(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 8, bool);
}
void STM32446Usart6_txeie(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 7, bool);
}
void STM32446Usart6_tcie(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 6, bool);
}
void STM32446Usart6_rxneie(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 5, bool);
}
void STM32446Usart6_idleie(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 4, bool);
}
void STM32446Usart6_te(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 3, bool);
}
void STM32446Usart6_re(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 2, bool);
}
void STM32446Usart6_rwu(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 1, bool);
}
void STM32446Usart6_sbk(uint8_t bool)
{
	usart_setreg(&USART6->CR1, 1, 0, bool);
}
// CR2
void STM32446Usart6_linen(uint8_t bool)
{
	usart_setreg(&USART6->CR2, 1, 14, bool);
}
void STM32446Usart6_stop(uint8_t value)
{
	usart_setreg(&USART6->CR2, 2, 12, value);
}
void STM32446Usart6_clken(uint8_t bool)
{
	usart_setreg(&USART6->CR2, 1, 11, bool);
}
void STM32446Usart6_cpol(uint8_t bool)
{
	usart_setreg(&USART6->CR2, 1, 10, bool);
}
void STM32446Usart6_cpha(uint8_t bool)
{
	usart_setreg(&USART6->CR2, 1, 9, bool);
}
void STM32446Usart6_lbcl(uint8_t bool)
{
	usart_setreg(&USART6->CR2, 1, 8, bool);
}
void STM32446Usart6_lbdie(uint8_t bool)
{
	usart_setreg(&USART6->CR2, 1, 6, bool);
}
void STM32446Usart6_lbdl(uint8_t bool)
{
	usart_setreg(&USART6->CR2, 1, 5, bool);
}
void STM32446Usart6_add(uint8_t value)
{
	usart_setreg(&USART6->CR2, 4, 0, value);
}
// CR3
void STM32446Usart6_onebit(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 11, bool);
}
void STM32446Usart6_ctsie(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 10, bool);
}
void STM32446Usart6_ctse(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 9, bool);
}
void STM32446Usart6_rtse(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 8, bool);
}
void STM32446Usart6_dmat(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 7, bool);
}
void STM32446Usart6_dmar(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 6, bool);
}
void STM32446Usart6_scen(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 5, bool);
}
void STM32446Usart6_nack(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 4, bool);
}
void STM32446Usart6_hdsel(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 3, bool);
}
void STM32446Usart6_irlp(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 2, bool);
}
void STM32446Usart6_iren(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 1, bool);
}
void STM32446Usart6_eie(uint8_t bool)
{
	usart_setreg(&USART6->CR3, 1, 0, bool);
}
// GTPR
void STM32446Usart6_gt(uint8_t value)
{
	usart_setreg(&USART6->GTPR, 8, 8, value);
}
void STM32446Usart6_psc(uint8_t value)
{
	usart_setreg(&USART6->GTPR, 8, 0, value);
}
/*** USART1 Auxiliar ***/
STM32446USART_SR stm32446_usart1_sr_inic(void)
{
	STM32446USART_SR stm32446_usart1_sr;
	// SR
	stm32446_usart1_sr.cts = STM32446Usart1_cts;
	stm32446_usart1_sr.clear_cts = STM32446Usart1_clear_cts;
	stm32446_usart1_sr.lbd = STM32446Usart1_lbd;
	stm32446_usart1_sr.clear_lbd = STM32446Usart1_clear_lbd;
	stm32446_usart1_sr.txe = STM32446Usart1_txe;
	stm32446_usart1_sr.tc = STM32446Usart1_tc;
	stm32446_usart1_sr.clear_tc = STM32446Usart1_clear_tc;
	stm32446_usart1_sr.rxne = STM32446Usart1_rxne;
	stm32446_usart1_sr.clear_rxne = STM32446Usart1_clear_rxne;
	stm32446_usart1_sr.idle = STM32446Usart1_idle;
	stm32446_usart1_sr.ore = STM32446Usart1_ore;
	stm32446_usart1_sr.nf = STM32446Usart1_nf;
	stm32446_usart1_sr.fe = STM32446Usart1_fe;
	stm32446_usart1_sr.pe = STM32446Usart1_pe;
	return stm32446_usart1_sr;
}
STM32446USART_BRR stm32446_usart1_brr_inic(void)
{
	STM32446USART_BRR stm32446_usart1_brr;
	// BRR
	stm32446_usart1_brr.div_mantissa = STM32446Usart1_div_mantissa;
	stm32446_usart1_brr.div_fraction = STM32446Usart1_div_fraction;
	return stm32446_usart1_brr;
}
STM32446USART_CR1 stm32446_usart1_cr1_inic(void)
{
	STM32446USART_CR1 stm32446_usart1_cr1;
	// CR1
	stm32446_usart1_cr1.over8 = STM32446Usart1_over8;
	stm32446_usart1_cr1.ue = STM32446Usart1_ue;
	stm32446_usart1_cr1.m = STM32446Usart1_m;
	stm32446_usart1_cr1.wake = STM32446Usart1_wake;
	stm32446_usart1_cr1.pce = STM32446Usart1_pce;
	stm32446_usart1_cr1.ps = STM32446Usart1_ps;
	stm32446_usart1_cr1.peie = STM32446Usart1_peie;
	stm32446_usart1_cr1.txeie = STM32446Usart1_txeie;
	stm32446_usart1_cr1.tcie = STM32446Usart1_tcie;
	stm32446_usart1_cr1.rxneie = STM32446Usart1_rxneie;
	stm32446_usart1_cr1.idleie = STM32446Usart1_idleie;
	stm32446_usart1_cr1.te = STM32446Usart1_te;
	stm32446_usart1_cr1.re = STM32446Usart1_re;
	stm32446_usart1_cr1.rwu = STM32446Usart1_rwu;
	stm32446_usart1_cr1.sbk = STM32446Usart1_sbk;
	return stm32446_usart1_cr1;
}
STM32446USART_CR2 stm32446_usart1_cr2_inic(void)
{
	STM32446USART_CR2 stm32446_usart1_cr2;
	// CR2
	stm32446_usart1_cr2.linen = STM32446Usart1_linen;
	stm32446_usart1_cr2.stop = STM32446Usart1_stop;
	stm32446_usart1_cr2.clken = STM32446Usart1_clken;
	stm32446_usart1_cr2.cpol = STM32446Usart1_cpol;
	stm32446_usart1_cr2.cpha = STM32446Usart1_cpha;
	stm32446_usart1_cr2.lbcl = STM32446Usart1_lbcl;
	stm32446_usart1_cr2.lbdie = STM32446Usart1_lbdie;
	stm32446_usart1_cr2.lbdl = STM32446Usart1_lbdl;
	stm32446_usart1_cr2.add = STM32446Usart1_add;
	return stm32446_usart1_cr2;
}
STM32446USART_CR3 stm32446_usart1_cr3_inic(void)
{
	STM32446USART_CR3 stm32446_usart1_cr3;
	// CR3
	stm32446_usart1_cr3.onebit = STM32446Usart1_onebit;
	stm32446_usart1_cr3.ctsie = STM32446Usart1_ctsie;
	stm32446_usart1_cr3.ctse = STM32446Usart1_ctse;
	stm32446_usart1_cr3.rtse = STM32446Usart1_rtse;
	stm32446_usart1_cr3.dmat = STM32446Usart1_dmat;
	stm32446_usart1_cr3.dmar = STM32446Usart1_dmar;
	stm32446_usart1_cr3.scen = STM32446Usart1_scen;
	stm32446_usart1_cr3.nack = STM32446Usart1_nack;
	stm32446_usart1_cr3.hdsel = STM32446Usart1_hdsel;
	stm32446_usart1_cr3.irlp = STM32446Usart1_irlp;
	stm32446_usart1_cr3.iren = STM32446Usart1_iren;
	stm32446_usart1_cr3.eie = STM32446Usart1_eie;
	return stm32446_usart1_cr3;
}
STM32446USART_GTPR stm32446_usart1_gtpr_inic(void)
{
	STM32446USART_GTPR stm32446_usart1_gtpr;
	// GTPR
	stm32446_usart1_gtpr.gt = STM32446Usart1_gt;
	stm32446_usart1_gtpr.psc = STM32446Usart1_psc;
	return stm32446_usart1_gtpr;
}
/*** USART1 INIC Procedure & Function Definition ***/
STM32446USART1obj usart1_inic(void)
{
	STM32446USART1obj stm32446_usart1;
	stm32446_usart1.reg = USART1;
	/*** USART1 Bit Mapping Link ***/
	stm32446_usart1.sr = stm32446_usart1_sr_inic();
	stm32446_usart1.dr = STM32446Usart1_dr;
	stm32446_usart1.get_dr = STM32446Usart1_get_dr;
	stm32446_usart1.brr = stm32446_usart1_brr_inic();
	stm32446_usart1.cr1 = stm32446_usart1_cr1_inic();
	stm32446_usart1.cr2 = stm32446_usart1_cr2_inic();
	stm32446_usart1.cr3 = stm32446_usart1_cr3_inic();
	stm32446_usart1.gtpr = stm32446_usart1_gtpr_inic();
	// Other
	stm32446_usart1.clock = STM32446Usart1Clock;
	stm32446_usart1.parameter = STM32446Usart1Parameter;
	return stm32446_usart1;
}
/*** USART2 Auxiliar ***/
STM32446USART_SR stm32446_usart2_sr_inic(void)
{
	STM32446USART_SR stm32446_usart2_sr;
	// SR
	stm32446_usart2_sr.cts = STM32446Usart2_cts;
	stm32446_usart2_sr.clear_cts = STM32446Usart2_clear_cts;
	stm32446_usart2_sr.lbd = STM32446Usart2_lbd;
	stm32446_usart2_sr.clear_lbd = STM32446Usart2_clear_lbd;
	stm32446_usart2_sr.txe = STM32446Usart2_txe;
	stm32446_usart2_sr.tc = STM32446Usart2_tc;
	stm32446_usart2_sr.clear_tc = STM32446Usart2_clear_tc;
	stm32446_usart2_sr.rxne = STM32446Usart2_rxne;
	stm32446_usart2_sr.clear_rxne = STM32446Usart2_clear_rxne;
	stm32446_usart2_sr.idle = STM32446Usart2_idle;
	stm32446_usart2_sr.ore = STM32446Usart2_ore;
	stm32446_usart2_sr.nf = STM32446Usart2_nf;
	stm32446_usart2_sr.fe = STM32446Usart2_fe;
	stm32446_usart2_sr.pe = STM32446Usart2_pe;
	return stm32446_usart2_sr;
}
STM32446USART_BRR stm32446_usart2_brr_inic(void)
{
	STM32446USART_BRR stm32446_usart2_brr;
	// BRR
	stm32446_usart2_brr.div_mantissa = STM32446Usart2_div_mantissa;
	stm32446_usart2_brr.div_fraction = STM32446Usart2_div_fraction;
	return stm32446_usart2_brr;
}
STM32446USART_CR1 stm32446_usart2_cr1_inic(void)
{
	STM32446USART_CR1 stm32446_usart2_cr1;
	// CR1
	stm32446_usart2_cr1.over8 = STM32446Usart2_over8;
	stm32446_usart2_cr1.ue = STM32446Usart2_ue;
	stm32446_usart2_cr1.m = STM32446Usart2_m;
	stm32446_usart2_cr1.wake = STM32446Usart2_wake;
	stm32446_usart2_cr1.pce = STM32446Usart2_pce;
	stm32446_usart2_cr1.ps = STM32446Usart2_ps;
	stm32446_usart2_cr1.peie = STM32446Usart2_peie;
	stm32446_usart2_cr1.txeie = STM32446Usart2_txeie;
	stm32446_usart2_cr1.tcie = STM32446Usart2_tcie;
	stm32446_usart2_cr1.rxneie = STM32446Usart2_rxneie;
	stm32446_usart2_cr1.idleie = STM32446Usart2_idleie;
	stm32446_usart2_cr1.te = STM32446Usart2_te;
	stm32446_usart2_cr1.re = STM32446Usart2_re;
	stm32446_usart2_cr1.rwu = STM32446Usart2_rwu;
	stm32446_usart2_cr1.sbk = STM32446Usart2_sbk;
	return stm32446_usart2_cr1;
}
STM32446USART_CR2 stm32446_usart2_cr2_inic(void)
{
	STM32446USART_CR2 stm32446_usart2_cr2;
	// CR2
	stm32446_usart2_cr2.linen = STM32446Usart2_linen;
	stm32446_usart2_cr2.stop = STM32446Usart2_stop;
	stm32446_usart2_cr2.clken = STM32446Usart2_clken;
	stm32446_usart2_cr2.cpol = STM32446Usart2_cpol;
	stm32446_usart2_cr2.cpha = STM32446Usart2_cpha;
	stm32446_usart2_cr2.lbcl = STM32446Usart2_lbcl;
	stm32446_usart2_cr2.lbdie = STM32446Usart2_lbdie;
	stm32446_usart2_cr2.lbdl = STM32446Usart2_lbdl;
	stm32446_usart2_cr2.add = STM32446Usart2_add;
	return stm32446_usart2_cr2;
}
STM32446USART_CR3 stm32446_usart2_cr3_inic(void)
{
	STM32446USART_CR3 stm32446_usart2_cr3;
	// CR3
	stm32446_usart2_cr3.onebit = STM32446Usart2_onebit;
	stm32446_usart2_cr3.ctsie = STM32446Usart2_ctsie;
	stm32446_usart2_cr3.ctse = STM32446Usart2_ctse;
	stm32446_usart2_cr3.rtse = STM32446Usart2_rtse;
	stm32446_usart2_cr3.dmat = STM32446Usart2_dmat;
	stm32446_usart2_cr3.dmar = STM32446Usart2_dmar;
	stm32446_usart2_cr3.scen = STM32446Usart2_scen;
	stm32446_usart2_cr3.nack = STM32446Usart2_nack;
	stm32446_usart2_cr3.hdsel = STM32446Usart2_hdsel;
	stm32446_usart2_cr3.irlp = STM32446Usart2_irlp;
	stm32446_usart2_cr3.iren = STM32446Usart2_iren;
	stm32446_usart2_cr3.eie = STM32446Usart2_eie;
	return stm32446_usart2_cr3;
}
STM32446USART_GTPR stm32446_usart2_gtpr_inic(void)
{
	STM32446USART_GTPR stm32446_usart2_gtpr;
	// GTPR
	stm32446_usart2_gtpr.gt = STM32446Usart2_gt;
	stm32446_usart2_gtpr.psc = STM32446Usart2_psc;
	return stm32446_usart2_gtpr;
}
/*** USART2 INIC Procedure & Function Definition ***/
STM32446USART2obj usart2_inic(void)
{
	STM32446USART2obj stm32446_usart2;
	stm32446_usart2.reg = USART2;
	/*** USART2 Bit Mapping Link ***/
	stm32446_usart2.sr = stm32446_usart2_sr_inic();
	stm32446_usart2.dr = STM32446Usart2_dr;
	stm32446_usart2.get_dr = STM32446Usart2_get_dr;
	stm32446_usart2.brr = stm32446_usart2_brr_inic();
	stm32446_usart2.cr1 = stm32446_usart2_cr1_inic();
	stm32446_usart2.cr2 = stm32446_usart2_cr2_inic();
	stm32446_usart2.cr3 = stm32446_usart2_cr3_inic();
	stm32446_usart2.gtpr = stm32446_usart2_gtpr_inic();
	// Other
	stm32446_usart2.clock = STM32446Usart2Clock;
	stm32446_usart2.parameter = STM32446Usart2Parameter;
	return stm32446_usart2;
}
/*** USART3 Auxiliar ***/
STM32446USART_SR stm32446_usart3_sr_inic(void)
{
	STM32446USART_SR stm32446_usart3_sr;
	// SR
	stm32446_usart3_sr.cts = STM32446Usart3_cts;
	stm32446_usart3_sr.clear_cts = STM32446Usart3_clear_cts;
	stm32446_usart3_sr.lbd = STM32446Usart3_lbd;
	stm32446_usart3_sr.clear_lbd = STM32446Usart3_clear_lbd;
	stm32446_usart3_sr.txe = STM32446Usart3_txe;
	stm32446_usart3_sr.tc = STM32446Usart3_tc;
	stm32446_usart3_sr.clear_tc = STM32446Usart3_clear_tc;
	stm32446_usart3_sr.rxne = STM32446Usart3_rxne;
	stm32446_usart3_sr.clear_rxne = STM32446Usart3_clear_rxne;
	stm32446_usart3_sr.idle = STM32446Usart3_idle;
	stm32446_usart3_sr.ore = STM32446Usart3_ore;
	stm32446_usart3_sr.nf = STM32446Usart3_nf;
	stm32446_usart3_sr.fe = STM32446Usart3_fe;
	stm32446_usart3_sr.pe = STM32446Usart3_pe;
	return stm32446_usart3_sr;
}
STM32446USART_BRR stm32446_usart3_brr_inic(void)
{
	STM32446USART_BRR stm32446_usart3_brr;
	// BRR
	stm32446_usart3_brr.div_mantissa = STM32446Usart3_div_mantissa;
	stm32446_usart3_brr.div_fraction = STM32446Usart3_div_fraction;
	return stm32446_usart3_brr;
}
STM32446USART_CR1 stm32446_usart3_cr1_inic(void)
{
	STM32446USART_CR1 stm32446_usart3_cr1;
	// CR1
	stm32446_usart3_cr1.over8 = STM32446Usart3_over8;
	stm32446_usart3_cr1.ue = STM32446Usart3_ue;
	stm32446_usart3_cr1.m = STM32446Usart3_m;
	stm32446_usart3_cr1.wake = STM32446Usart3_wake;
	stm32446_usart3_cr1.pce = STM32446Usart3_pce;
	stm32446_usart3_cr1.ps = STM32446Usart3_ps;
	stm32446_usart3_cr1.peie = STM32446Usart3_peie;
	stm32446_usart3_cr1.txeie = STM32446Usart3_txeie;
	stm32446_usart3_cr1.tcie = STM32446Usart3_tcie;
	stm32446_usart3_cr1.rxneie = STM32446Usart3_rxneie;
	stm32446_usart3_cr1.idleie = STM32446Usart3_idleie;
	stm32446_usart3_cr1.te = STM32446Usart3_te;
	stm32446_usart3_cr1.re = STM32446Usart3_re;
	stm32446_usart3_cr1.rwu = STM32446Usart3_rwu;
	stm32446_usart3_cr1.sbk = STM32446Usart3_sbk;
	return stm32446_usart3_cr1;
}
STM32446USART_CR2 stm32446_usart3_cr2_inic(void)
{
	STM32446USART_CR2 stm32446_usart3_cr2;
	// CR2
	stm32446_usart3_cr2.linen = STM32446Usart3_linen;
	stm32446_usart3_cr2.stop = STM32446Usart3_stop;
	stm32446_usart3_cr2.clken = STM32446Usart3_clken;
	stm32446_usart3_cr2.cpol = STM32446Usart3_cpol;
	stm32446_usart3_cr2.cpha = STM32446Usart3_cpha;
	stm32446_usart3_cr2.lbcl = STM32446Usart3_lbcl;
	stm32446_usart3_cr2.lbdie = STM32446Usart3_lbdie;
	stm32446_usart3_cr2.lbdl = STM32446Usart3_lbdl;
	stm32446_usart3_cr2.add = STM32446Usart3_add;
	return stm32446_usart3_cr2;
}
STM32446USART_CR3 stm32446_usart3_cr3_inic(void)
{
	STM32446USART_CR3 stm32446_usart3_cr3;
	// CR3
	stm32446_usart3_cr3.onebit = STM32446Usart3_onebit;
	stm32446_usart3_cr3.ctsie = STM32446Usart3_ctsie;
	stm32446_usart3_cr3.ctse = STM32446Usart3_ctse;
	stm32446_usart3_cr3.rtse = STM32446Usart3_rtse;
	stm32446_usart3_cr3.dmat = STM32446Usart3_dmat;
	stm32446_usart3_cr3.dmar = STM32446Usart3_dmar;
	stm32446_usart3_cr3.scen = STM32446Usart3_scen;
	stm32446_usart3_cr3.nack = STM32446Usart3_nack;
	stm32446_usart3_cr3.hdsel = STM32446Usart3_hdsel;
	stm32446_usart3_cr3.irlp = STM32446Usart3_irlp;
	stm32446_usart3_cr3.iren = STM32446Usart3_iren;
	stm32446_usart3_cr3.eie = STM32446Usart3_eie;
	return stm32446_usart3_cr3;
}
STM32446USART_GTPR stm32446_usart3_gtpr_inic(void)
{
	STM32446USART_GTPR stm32446_usart3_gtpr;
	// GTPR
	stm32446_usart3_gtpr.gt = STM32446Usart3_gt;
	stm32446_usart3_gtpr.psc = STM32446Usart3_psc;
	return stm32446_usart3_gtpr;
}
/*** USART3 INIC Procedure & Function Definition ***/
STM32446USART3obj usart3_inic(void)
{
	STM32446USART3obj stm32446_usart3;
	stm32446_usart3.reg = USART3;
	/*** USART3 Bit Mapping Link ***/
	stm32446_usart3.sr = stm32446_usart3_sr_inic();
	stm32446_usart3.dr = STM32446Usart3_dr;
	stm32446_usart3.get_dr = STM32446Usart3_get_dr;
	stm32446_usart3.brr = stm32446_usart3_brr_inic();
	stm32446_usart3.cr1 = stm32446_usart3_cr1_inic();
	stm32446_usart3.cr2 = stm32446_usart3_cr2_inic();
	stm32446_usart3.cr3 = stm32446_usart3_cr3_inic();
	stm32446_usart3.gtpr = stm32446_usart3_gtpr_inic();
	// Other
	stm32446_usart3.clock = STM32446Usart3Clock;
	stm32446_usart3.parameter = STM32446Usart3Parameter;
	return stm32446_usart3;
}
/*** UART4 Auxiliar ***/
STM32446USART_SR stm32446_uart4_sr_inic(void)
{
	STM32446USART_SR stm32446_uart4_sr;
	// SR
	stm32446_uart4_sr.cts = STM32446Uart4_cts;
	stm32446_uart4_sr.clear_cts = STM32446Uart4_clear_cts;
	stm32446_uart4_sr.lbd = STM32446Uart4_lbd;
	stm32446_uart4_sr.clear_lbd = STM32446Uart4_clear_lbd;
	stm32446_uart4_sr.txe = STM32446Uart4_txe;
	stm32446_uart4_sr.tc = STM32446Uart4_tc;
	stm32446_uart4_sr.clear_tc = STM32446Uart4_clear_tc;
	stm32446_uart4_sr.rxne = STM32446Uart4_rxne;
	stm32446_uart4_sr.clear_rxne = STM32446Uart4_clear_rxne;
	stm32446_uart4_sr.idle = STM32446Uart4_idle;
	stm32446_uart4_sr.ore = STM32446Uart4_ore;
	stm32446_uart4_sr.nf = STM32446Uart4_nf;
	stm32446_uart4_sr.fe = STM32446Uart4_fe;
	stm32446_uart4_sr.pe = STM32446Uart4_pe;
	return stm32446_uart4_sr;
}
STM32446USART_BRR stm32446_uart4_brr_inic(void)
{
	STM32446USART_BRR stm32446_uart4_brr;
	// BRR
	stm32446_uart4_brr.div_mantissa = STM32446Uart4_div_mantissa;
	stm32446_uart4_brr.div_fraction = STM32446Uart4_div_fraction;
	return stm32446_uart4_brr;
}
STM32446USART_CR1 stm32446_uart4_cr1_inic(void)
{
	STM32446USART_CR1 stm32446_uart4_cr1;
	// CR1
	stm32446_uart4_cr1.over8 = STM32446Uart4_over8;
	stm32446_uart4_cr1.ue = STM32446Uart4_ue;
	stm32446_uart4_cr1.m = STM32446Uart4_m;
	stm32446_uart4_cr1.wake = STM32446Uart4_wake;
	stm32446_uart4_cr1.pce = STM32446Uart4_pce;
	stm32446_uart4_cr1.ps = STM32446Uart4_ps;
	stm32446_uart4_cr1.peie = STM32446Uart4_peie;
	stm32446_uart4_cr1.txeie = STM32446Uart4_txeie;
	stm32446_uart4_cr1.tcie = STM32446Uart4_tcie;
	stm32446_uart4_cr1.rxneie = STM32446Uart4_rxneie;
	stm32446_uart4_cr1.idleie = STM32446Uart4_idleie;
	stm32446_uart4_cr1.te = STM32446Uart4_te;
	stm32446_uart4_cr1.re = STM32446Uart4_re;
	stm32446_uart4_cr1.rwu = STM32446Uart4_rwu;
	stm32446_uart4_cr1.sbk = STM32446Uart4_sbk;
	return stm32446_uart4_cr1;
}
STM32446USART_CR2 stm32446_uart4_cr2_inic(void)
{
	STM32446USART_CR2 stm32446_uart4_cr2;
	// CR2
	stm32446_uart4_cr2.linen = STM32446Uart4_linen;
	stm32446_uart4_cr2.stop = STM32446Uart4_stop;
	stm32446_uart4_cr2.clken = STM32446Uart4_clken;
	stm32446_uart4_cr2.cpol = STM32446Uart4_cpol;
	stm32446_uart4_cr2.cpha = STM32446Uart4_cpha;
	stm32446_uart4_cr2.lbcl = STM32446Uart4_lbcl;
	stm32446_uart4_cr2.lbdie = STM32446Uart4_lbdie;
	stm32446_uart4_cr2.lbdl = STM32446Uart4_lbdl;
	stm32446_uart4_cr2.add = STM32446Uart4_add;
	return stm32446_uart4_cr2;
}
STM32446USART_CR3 stm32446_uart4_cr3_inic(void)
{
	STM32446USART_CR3 stm32446_uart4_cr3;
	// CR3
	stm32446_uart4_cr3.onebit = STM32446Uart4_onebit;
	stm32446_uart4_cr3.ctsie = STM32446Uart4_ctsie;
	stm32446_uart4_cr3.ctse = STM32446Uart4_ctse;
	stm32446_uart4_cr3.rtse = STM32446Uart4_rtse;
	stm32446_uart4_cr3.dmat = STM32446Uart4_dmat;
	stm32446_uart4_cr3.dmar = STM32446Uart4_dmar;
	stm32446_uart4_cr3.scen = STM32446Uart4_scen;
	stm32446_uart4_cr3.nack = STM32446Uart4_nack;
	stm32446_uart4_cr3.hdsel = STM32446Uart4_hdsel;
	stm32446_uart4_cr3.irlp = STM32446Uart4_irlp;
	stm32446_uart4_cr3.iren = STM32446Uart4_iren;
	stm32446_uart4_cr3.eie = STM32446Uart4_eie;
	return stm32446_uart4_cr3;
}
STM32446USART_GTPR stm32446_uart4_gtpr_inic(void)
{
	STM32446USART_GTPR stm32446_uart4_gtpr;
	// GTPR
	stm32446_uart4_gtpr.gt = STM32446Uart4_gt;
	stm32446_uart4_gtpr.psc = STM32446Uart4_psc;
	return stm32446_uart4_gtpr;
}
/*** UART4 INIC Procedure & Function Definition ***/
STM32446USART4obj uart4_inic(void)
{
	STM32446USART4obj stm32446_uart4;
	stm32446_uart4.reg = UART4;
	/*** UART4 Bit Mapping Link ***/
	stm32446_uart4.sr = stm32446_uart4_sr_inic();
	stm32446_uart4.dr = STM32446Uart4_dr;
	stm32446_uart4.get_dr = STM32446Uart4_get_dr;
	stm32446_uart4.brr = stm32446_uart4_brr_inic();
	stm32446_uart4.cr1 = stm32446_uart4_cr1_inic();
	stm32446_uart4.cr2 = stm32446_uart4_cr2_inic();
	stm32446_uart4.cr3 = stm32446_uart4_cr3_inic();
	stm32446_uart4.gtpr = stm32446_uart4_gtpr_inic();
	// Other
	stm32446_uart4.clock = STM32446Uart4Clock;
	stm32446_uart4.parameter = STM32446Uart4Parameter;
	return stm32446_uart4;
}
/*** UART5 Auxiliar ***/
STM32446USART_SR stm32446_uart5_sr_inic(void)
{
	STM32446USART_SR stm32446_uart5_sr;
	// SR
	stm32446_uart5_sr.cts = STM32446Uart5_cts;
	stm32446_uart5_sr.clear_cts = STM32446Uart5_clear_cts;
	stm32446_uart5_sr.lbd = STM32446Uart5_lbd;
	stm32446_uart5_sr.clear_lbd = STM32446Uart5_clear_lbd;
	stm32446_uart5_sr.txe = STM32446Uart5_txe;
	stm32446_uart5_sr.tc = STM32446Uart5_tc;
	stm32446_uart5_sr.clear_tc = STM32446Uart5_clear_tc;
	stm32446_uart5_sr.rxne = STM32446Uart5_rxne;
	stm32446_uart5_sr.clear_rxne = STM32446Uart5_clear_rxne;
	stm32446_uart5_sr.idle = STM32446Uart5_idle;
	stm32446_uart5_sr.ore = STM32446Uart5_ore;
	stm32446_uart5_sr.nf = STM32446Uart5_nf;
	stm32446_uart5_sr.fe = STM32446Uart5_fe;
	stm32446_uart5_sr.pe = STM32446Uart5_pe;
	return stm32446_uart5_sr;
}
STM32446USART_BRR stm32446_uart5_brr_inic(void)
{
	STM32446USART_BRR stm32446_uart5_brr;
	// BRR
	stm32446_uart5_brr.div_mantissa = STM32446Uart5_div_mantissa;
	stm32446_uart5_brr.div_fraction = STM32446Uart5_div_fraction;
	return stm32446_uart5_brr;
}
STM32446USART_CR1 stm32446_uart5_cr1_inic(void)
{
	STM32446USART_CR1 stm32446_uart5_cr1;
	// CR1
	stm32446_uart5_cr1.over8 = STM32446Uart5_over8;
	stm32446_uart5_cr1.ue = STM32446Uart5_ue;
	stm32446_uart5_cr1.m = STM32446Uart5_m;
	stm32446_uart5_cr1.wake = STM32446Uart5_wake;
	stm32446_uart5_cr1.pce = STM32446Uart5_pce;
	stm32446_uart5_cr1.ps = STM32446Uart5_ps;
	stm32446_uart5_cr1.peie = STM32446Uart5_peie;
	stm32446_uart5_cr1.txeie = STM32446Uart5_txeie;
	stm32446_uart5_cr1.tcie = STM32446Uart5_tcie;
	stm32446_uart5_cr1.rxneie = STM32446Uart5_rxneie;
	stm32446_uart5_cr1.idleie = STM32446Uart5_idleie;
	stm32446_uart5_cr1.te = STM32446Uart5_te;
	stm32446_uart5_cr1.re = STM32446Uart5_re;
	stm32446_uart5_cr1.rwu = STM32446Uart5_rwu;
	stm32446_uart5_cr1.sbk = STM32446Uart5_sbk;
	return stm32446_uart5_cr1;
}
STM32446USART_CR2 stm32446_uart5_cr2_inic(void)
{
	STM32446USART_CR2 stm32446_uart5_cr2;
	// CR2
	stm32446_uart5_cr2.linen = STM32446Uart5_linen;
	stm32446_uart5_cr2.stop = STM32446Uart5_stop;
	stm32446_uart5_cr2.clken = STM32446Uart5_clken;
	stm32446_uart5_cr2.cpol = STM32446Uart5_cpol;
	stm32446_uart5_cr2.cpha = STM32446Uart5_cpha;
	stm32446_uart5_cr2.lbcl = STM32446Uart5_lbcl;
	stm32446_uart5_cr2.lbdie = STM32446Uart5_lbdie;
	stm32446_uart5_cr2.lbdl = STM32446Uart5_lbdl;
	stm32446_uart5_cr2.add = STM32446Uart5_add;
	return stm32446_uart5_cr2;
}
STM32446USART_CR3 stm32446_uart5_cr3_inic(void)
{
	STM32446USART_CR3 stm32446_uart5_cr3;
	// CR3
	stm32446_uart5_cr3.onebit = STM32446Uart5_onebit;
	stm32446_uart5_cr3.ctsie = STM32446Uart5_ctsie;
	stm32446_uart5_cr3.ctse = STM32446Uart5_ctse;
	stm32446_uart5_cr3.rtse = STM32446Uart5_rtse;
	stm32446_uart5_cr3.dmat = STM32446Uart5_dmat;
	stm32446_uart5_cr3.dmar = STM32446Uart5_dmar;
	stm32446_uart5_cr3.scen = STM32446Uart5_scen;
	stm32446_uart5_cr3.nack = STM32446Uart5_nack;
	stm32446_uart5_cr3.hdsel = STM32446Uart5_hdsel;
	stm32446_uart5_cr3.irlp = STM32446Uart5_irlp;
	stm32446_uart5_cr3.iren = STM32446Uart5_iren;
	stm32446_uart5_cr3.eie = STM32446Uart5_eie;
	return stm32446_uart5_cr3;
}
STM32446USART_GTPR stm32446_uart5_gtpr_inic(void)
{
	STM32446USART_GTPR stm32446_uart5_gtpr;
	// GTPR
	stm32446_uart5_gtpr.gt = STM32446Uart5_gt;
	stm32446_uart5_gtpr.psc = STM32446Uart5_psc;
	return stm32446_uart5_gtpr;
}
/*** UART5 INIC Procedure & Function Definition ***/
STM32446USART5obj uart5_inic(void)
{
	STM32446USART5obj stm32446_uart5;
	stm32446_uart5.reg = UART5;
	/*** UART5 Bit Mapping Link ***/
	stm32446_uart5.sr = stm32446_uart5_sr_inic();
	stm32446_uart5.dr = STM32446Uart5_dr;
	stm32446_uart5.get_dr = STM32446Uart5_get_dr;
	stm32446_uart5.brr = stm32446_uart5_brr_inic();
	stm32446_uart5.cr1 = stm32446_uart5_cr1_inic();
	stm32446_uart5.cr2 = stm32446_uart5_cr2_inic();
	stm32446_uart5.cr3 = stm32446_uart5_cr3_inic();
	stm32446_uart5.gtpr = stm32446_uart5_gtpr_inic();
	// Other
	stm32446_uart5.clock = STM32446Uart5Clock;
	stm32446_uart5.parameter = STM32446Uart5Parameter;
	return stm32446_uart5;
}
/*** USART6 Auxiliar ***/
STM32446USART_SR stm32446_usart6_sr_inic(void)
{
	STM32446USART_SR stm32446_usart6_sr;
	// SR
	stm32446_usart6_sr.cts = STM32446Usart6_cts;
	stm32446_usart6_sr.clear_cts = STM32446Usart6_clear_cts;
	stm32446_usart6_sr.lbd = STM32446Usart6_lbd;
	stm32446_usart6_sr.clear_lbd = STM32446Usart6_clear_lbd;
	stm32446_usart6_sr.txe = STM32446Usart6_txe;
	stm32446_usart6_sr.tc = STM32446Usart6_tc;
	stm32446_usart6_sr.clear_tc = STM32446Usart6_clear_tc;
	stm32446_usart6_sr.rxne = STM32446Usart6_rxne;
	stm32446_usart6_sr.clear_rxne = STM32446Usart6_clear_rxne;
	stm32446_usart6_sr.idle = STM32446Usart6_idle;
	stm32446_usart6_sr.ore = STM32446Usart6_ore;
	stm32446_usart6_sr.nf = STM32446Usart6_nf;
	stm32446_usart6_sr.fe = STM32446Usart6_fe;
	stm32446_usart6_sr.pe = STM32446Usart6_pe;
	return stm32446_usart6_sr;
}
STM32446USART_BRR stm32446_usart6_brr_inic(void)
{
	STM32446USART_BRR stm32446_usart6_brr;
	// BRR
	stm32446_usart6_brr.div_mantissa = STM32446Usart6_div_mantissa;
	stm32446_usart6_brr.div_fraction = STM32446Usart6_div_fraction;
	return stm32446_usart6_brr;
}
STM32446USART_CR1 stm32446_usart6_cr1_inic(void)
{
	STM32446USART_CR1 stm32446_usart6_cr1;
	// CR1
	stm32446_usart6_cr1.over8 = STM32446Usart6_over8;
	stm32446_usart6_cr1.ue = STM32446Usart6_ue;
	stm32446_usart6_cr1.m = STM32446Usart6_m;
	stm32446_usart6_cr1.wake = STM32446Usart6_wake;
	stm32446_usart6_cr1.pce = STM32446Usart6_pce;
	stm32446_usart6_cr1.ps = STM32446Usart6_ps;
	stm32446_usart6_cr1.peie = STM32446Usart6_peie;
	stm32446_usart6_cr1.txeie = STM32446Usart6_txeie;
	stm32446_usart6_cr1.tcie = STM32446Usart6_tcie;
	stm32446_usart6_cr1.rxneie = STM32446Usart6_rxneie;
	stm32446_usart6_cr1.idleie = STM32446Usart6_idleie;
	stm32446_usart6_cr1.te = STM32446Usart6_te;
	stm32446_usart6_cr1.re = STM32446Usart6_re;
	stm32446_usart6_cr1.rwu = STM32446Usart6_rwu;
	stm32446_usart6_cr1.sbk = STM32446Usart6_sbk;
	return stm32446_usart6_cr1;
}
STM32446USART_CR2 stm32446_usart6_cr2_inic(void)
{
	STM32446USART_CR2 stm32446_usart6_cr2;
	// CR2
	stm32446_usart6_cr2.linen = STM32446Usart6_linen;
	stm32446_usart6_cr2.stop = STM32446Usart6_stop;
	stm32446_usart6_cr2.clken = STM32446Usart6_clken;
	stm32446_usart6_cr2.cpol = STM32446Usart6_cpol;
	stm32446_usart6_cr2.cpha = STM32446Usart6_cpha;
	stm32446_usart6_cr2.lbcl = STM32446Usart6_lbcl;
	stm32446_usart6_cr2.lbdie = STM32446Usart6_lbdie;
	stm32446_usart6_cr2.lbdl = STM32446Usart6_lbdl;
	stm32446_usart6_cr2.add = STM32446Usart6_add;
	return stm32446_usart6_cr2;
}
STM32446USART_CR3 stm32446_usart6_cr3_inic(void)
{
	STM32446USART_CR3 stm32446_usart6_cr3;
	// CR3
	stm32446_usart6_cr3.onebit = STM32446Usart6_onebit;
	stm32446_usart6_cr3.ctsie = STM32446Usart6_ctsie;
	stm32446_usart6_cr3.ctse = STM32446Usart6_ctse;
	stm32446_usart6_cr3.rtse = STM32446Usart6_rtse;
	stm32446_usart6_cr3.dmat = STM32446Usart6_dmat;
	stm32446_usart6_cr3.dmar = STM32446Usart6_dmar;
	stm32446_usart6_cr3.scen = STM32446Usart6_scen;
	stm32446_usart6_cr3.nack = STM32446Usart6_nack;
	stm32446_usart6_cr3.hdsel = STM32446Usart6_hdsel;
	stm32446_usart6_cr3.irlp = STM32446Usart6_irlp;
	stm32446_usart6_cr3.iren = STM32446Usart6_iren;
	stm32446_usart6_cr3.eie = STM32446Usart6_eie;
	return stm32446_usart6_cr3;
}
STM32446USART_GTPR stm32446_usart6_gtpr_inic(void)
{
	STM32446USART_GTPR stm32446_usart6_gtpr;
	// GTPR
	stm32446_usart6_gtpr.gt = STM32446Usart6_gt;
	stm32446_usart6_gtpr.psc = STM32446Usart6_psc;
	return stm32446_usart6_gtpr;
}
/*** USART6 INIC Procedure & Function Definition ***/
STM32446USART6obj usart6_inic(void)
{
	STM32446USART6obj stm32446_usart6;
	stm32446_usart6.reg = USART6;
	/*** USART6 Bit Mapping Link ***/
	stm32446_usart6.sr = stm32446_usart6_sr_inic();
	stm32446_usart6.dr = STM32446Usart6_dr;
	stm32446_usart6.get_dr = STM32446Usart6_get_dr;
	stm32446_usart6.brr = stm32446_usart6_brr_inic();
	stm32446_usart6.cr1 = stm32446_usart6_cr1_inic();
	stm32446_usart6.cr2 = stm32446_usart6_cr2_inic();
	stm32446_usart6.cr3 = stm32446_usart6_cr3_inic();
	stm32446_usart6.gtpr = stm32446_usart6_gtpr_inic();
	// Other
	stm32446_usart6.clock = STM32446Usart6Clock;
	stm32446_usart6.parameter = STM32446Usart6Parameter;
	return stm32446_usart6;
}
/*** File Procedure & Function Definition ***/
uint32_t usart_getclocksource(void)
{
	uint32_t reg = RCC->CR;
	uint32_t source;
	if(reg & (1 << 1)){source = HSI_RC;}else if(reg & (1 << 17)){source = HSE_OSC;}
	return source;
}
uint32_t usart_gethpre(void)
{
	uint32_t value = usart_readreg(RCC->CFGR, 4, 4);
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
	return usart_readreg(RCC->PLLCFGR, 6, 0);
}
uint32_t usart_getplln(void)
{
	return usart_readreg(RCC->PLLCFGR, 9, 6);
}
uint32_t usart_getpllp(void)
{
	uint32_t value = usart_readreg(RCC->PLLCFGR, 2, 16);
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
	return usart_readreg(RCC->PLLCFGR, 3, 28);
}
uint32_t usart_getsysclk(void)
{
	uint32_t value = usart_readreg(RCC->CFGR, 2, 2);
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
uint32_t usart_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void usart_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void usart_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void usart_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t usart_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/


