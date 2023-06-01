/******************************************************************************
	STM32 446 USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446USART_H_
	#define _STM32446USART_H_

/*** Library ***/
#include <inttypes.h>

/*** USART 1 ***/
typedef struct{
	USART_TypeDef* reg;
	STM32446USART1_SR sr;
	STM32446USART1_BRR brr;
	STM32446USART1_CR1 cr1;
	STM32446USART1_CR2 cr2;
	STM32446USART1_CR3 cr3;
	STM32446USART1_GTPR gtpr;
	void (*dr)(uint16_t);
	uint16_t (*get_dr)(void);
	// Other
	void (*inic)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
	void (*transmit)(void);
	void (*receive)(void);
	void (*stop)(void);
}STM32446USART1;

STM32446USART1 STM32446USART1enable(void);
// SR
uint8_t STM32446Usart1_cts(void);
void STM32446Usart1_clear_cts(void);
uint8_t STM32446Usart1_lbd(void);
void STM32446Usart1_clear_lbd(void);
uint8_t STM32446Usart1_txe(void);
uint8_t STM32446Usart1_tc(void);
void STM32446Usart1_clear_tc(void);
uint8_t STM32446Usart1_rxne(void);
void STM32446Usart1_clear_rxne(void);
uint8_t STM32446Usart1_idle(void);
uint8_t STM32446Usart1_ore(void);
uint8_t STM32446Usart1_nf(void);
uint8_t STM32446Usart1_fe(void);
uint8_t STM32446Usart1_pe(void);
// DR
void STM32446Usart1_dr(uint16_t);
uint16_t STM32446Usart1_get_dr(void);
// BRR
void STM32446Usart1_div_mantissa(uint16_t value);
void STM32446Usart1_div_fraction(uint8_t value);
// CR1
void STM32446Usart1_over8(uint8_t bool);
void STM32446Usart1_ue(uint8_t bool);
void STM32446Usart1_m(uint8_t bool);
void STM32446Usart1_wake(uint8_t bool);
void STM32446Usart1_pce(uint8_t bool);
void STM32446Usart1_ps(uint8_t bool);
void STM32446Usart1_peie(uint8_t bool);
void STM32446Usart1_txeie(uint8_t bool);
void STM32446Usart1_tcie(uint8_t bool);
void STM32446Usart1_rxneie(uint8_t bool);
void STM32446Usart1_idleie(uint8_t bool);
void STM32446Usart1_te(uint8_t bool);
void STM32446Usart1_re(uint8_t bool);
void STM32446Usart1_rwu(uint8_t bool);
void STM32446Usart1_sbk(uint8_t bool);
// CR2
void STM32446Usart1_linen(uint8_t bool);
void STM32446Usart1_stop(uint8_t value);
void STM32446Usart1_clken(uint8_t bool);
void STM32446Usart1_cpol(uint8_t bool);
void STM32446Usart1_cpha(uint8_t bool);
void STM32446Usart1_lbcl(uint8_t bool);
void STM32446Usart1_lbdie(uint8_t bool);
void STM32446Usart1_lbdl(uint8_t bool);
void STM32446Usart1_add(uint8_t value);
// CR3
void STM32446Usart1_onebit(uint8_t bool);
void STM32446Usart1_ctsie(uint8_t bool);
void STM32446Usart1_ctse(uint8_t bool);
void STM32446Usart1_rtse(uint8_t bool);
void STM32446Usart1_dmat(uint8_t bool);
void STM32446Usart1_dmar(uint8_t bool);
void STM32446Usart1_scen(uint8_t bool);
void STM32446Usart1_nack(uint8_t bool);
void STM32446Usart1_hdsel(uint8_t bool);
void STM32446Usart1_irlp(uint8_t bool);
void STM32446Usart1_iren(uint8_t bool);
void STM32446Usart1_eie(uint8_t bool);
// GTPR
void STM32446Usart1_gt(uint8_t value);
void STM32446Usart1_psc(uint8_t value);
// Other
void STM32446Usart1Inic( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
void STM32446Usart1Transmit(void);
void STM32446Usart1Receive(void);
void STM32446Usart1Stop(void);

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


