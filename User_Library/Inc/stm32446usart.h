/******************************************************************************
	STM32 446 USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446USART_H_
	#define _STM32446USART_H_

/*** Library ***/
#include <inttypes.h>

/*** USART1_Common ***/
typedef struct{
	uint8_t (*cts)(void);
	void (*clear_cts)(void);
	uint8_t (*lbd)(void);
	void (*clear_lbd)(void);
	uint8_t (*txe)(void);
	uint8_t (*tc)(void);
	void (*clear_tc)(void);
	uint8_t (*rxne)(void);
	void (*clear_rxne)(void);
	uint8_t (*idle)(void);
	uint8_t (*ore)(void);
	uint8_t (*nf)(void);
	uint8_t (*fe)(void);
	uint8_t (*pe)(void);
}STM32446USART1_SR;

typedef struct{
	void (*div_mantissa)(uint16_t value);
	void (*div_fraction)(uint8_t value);
}STM32446USART1_BRR;

typedef struct{
	void (*over8)(uint8_t bool);
	void (*ue)(uint8_t bool);
	void (*m)(uint8_t bool);
	void (*wake)(uint8_t bool);
	void (*pce)(uint8_t bool);
	void (*ps)(uint8_t bool);
	void (*peie)(uint8_t bool);
	void (*txeie)(uint8_t bool);
	void (*tcie)(uint8_t bool);
	void (*rxneie)(uint8_t bool);
	void (*idleie)(uint8_t bool);
	void (*te)(uint8_t bool);
	void (*re)(uint8_t bool);
	void (*rwu)(uint8_t bool);
	void (*sbk)(uint8_t bool);
}STM32446USART1_CR1;

typedef struct{
	void (*linen)(uint8_t bool);
	void (*stop)(uint8_t value);
	void (*clken)(uint8_t bool);
	void (*cpol)(uint8_t bool);
	void (*cpha)(uint8_t bool);
	void (*lbcl)(uint8_t bool);
	void (*lbdie)(uint8_t bool);
	void (*lbdl)(uint8_t bool);
	void (*add)(uint8_t value);
}STM32446USART1_CR2;

typedef struct{
	void (*onebit)(uint8_t bool);
	void (*ctsie)(uint8_t bool);
	void (*ctse)(uint8_t bool);
	void (*rtse)(uint8_t bool);
	void (*dmat)(uint8_t bool);
	void (*dmar)(uint8_t bool);
	void (*scen)(uint8_t bool);
	void (*nack)(uint8_t bool);
	void (*hdsel)(uint8_t bool);
	void (*irlp)(uint8_t bool);
	void (*iren)(uint8_t bool);
	void (*eie)(uint8_t bool);
}STM32446USART1_CR3;

typedef struct{
	void (*gt)(uint8_t value);
	void (*psc)(uint8_t value);
}STM32446USART1_GTPR;

// USART -> USART1
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		STM32446USART1_SR sr;
		STM32446USART1_BRR brr;
		STM32446USART1_CR1 cr1;
		STM32446USART1_CR2 cr2;
		STM32446USART1_CR3 cr3;
		STM32446USART1_GTPR gtpr;
		void (*dr)(uint16_t);
		uint16_t (*get_dr)(void);
		// Other
		void (*clock)(void);
		void (*inic)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
		void (*transmit)(void);
		void (*receive)(void);
		void (*stop)(void);
	#endif
}STM32446USART1obj;

// USART -> USART2
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART2obj;

// USART -> USART3
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART3obj;

// USART -> USART4
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART4obj;

// USART -> USART5
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART5obj;

// USART -> USART6
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART6obj;

/*** USART1 ***/
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
void STM32446Usart1Clock( void );
void STM32446Usart1Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
void STM32446Usart1Inic( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
void STM32446Usart1Transmit(void);
void STM32446Usart1Receive(void);
void STM32446Usart1Stop(void);
uint32_t usart_getclocksource(void);
uint32_t usart_gethpre(void);
uint32_t usart_getpllm(void);
uint32_t usart_getplln(void);
uint32_t usart_getpllp(void);
uint32_t usart_getpllr(void);
uint32_t usart_getsysclk(void);

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


