/******************************************************************************
	STM32 446 USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446USART_H_
	#define _STM32446USART_H_
/*** Library ***/
#include <inttypes.h>
/*** USART Bit Mapping Common TypeDef ***/
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
}STM32446USART_SR;
typedef struct{
	void (*div_mantissa)(uint16_t value);
	void (*div_fraction)(uint8_t value);
}STM32446USART_BRR;
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
}STM32446USART_CR1;
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
}STM32446USART_CR2;
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
}STM32446USART_CR3;
typedef struct{
	void (*gt)(uint8_t value);
	void (*psc)(uint8_t value);
}STM32446USART_GTPR;
// USART -> USART1
typedef struct
{
	USART_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446USART_SR sr;
	STM32446USART_BRR brr;
	STM32446USART_CR1 cr1;
	STM32446USART_CR2 cr2;
	STM32446USART_CR3 cr3;
	STM32446USART_GTPR gtpr;
	void (*dr)(uint32_t data);
	uint32_t (*get_dr)(void);
	/*** Other ***/
	void (*clock)(uint8_t bool);

	void (*parameter)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
}STM32446USART1obj;
// USART -> USART2
typedef struct
{
	USART_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446USART_SR sr;
	STM32446USART_BRR brr;
	STM32446USART_CR1 cr1;
	STM32446USART_CR2 cr2;
	STM32446USART_CR3 cr3;
	STM32446USART_GTPR gtpr;
	void (*dr)(uint32_t data);
	uint32_t (*get_dr)(void);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*parameter)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
}STM32446USART2obj;
// USART -> USART3
typedef struct
{
	USART_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446USART_SR sr;
	STM32446USART_BRR brr;
	STM32446USART_CR1 cr1;
	STM32446USART_CR2 cr2;
	STM32446USART_CR3 cr3;
	STM32446USART_GTPR gtpr;
	void (*dr)(uint32_t data);
	uint32_t (*get_dr)(void);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*parameter)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
}STM32446USART3obj;
// USART -> UART4
typedef struct
{
	USART_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446USART_SR sr;
	STM32446USART_BRR brr;
	STM32446USART_CR1 cr1;
	STM32446USART_CR2 cr2;
	STM32446USART_CR3 cr3;
	STM32446USART_GTPR gtpr;
	void (*dr)(uint32_t data);
	uint32_t (*get_dr)(void);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*parameter)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
}STM32446USART4obj;
// USART -> UART5
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		/*** Bit Mapping ***/
		STM32446USART_SR sr;
		STM32446USART_BRR brr;
		STM32446USART_CR1 cr1;
		STM32446USART_CR2 cr2;
		STM32446USART_CR3 cr3;
		STM32446USART_GTPR gtpr;
		void (*dr)(uint32_t data);
		uint32_t (*get_dr)(void);
		/*** Other ***/
		void (*clock)(uint8_t bool);
		void (*parameter)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
	#endif
}STM32446USART5obj;
// USART -> USART6
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		/*** Bit Mapping ***/
		STM32446USART_SR sr;
		STM32446USART_BRR brr;
		STM32446USART_CR1 cr1;
		STM32446USART_CR2 cr2;
		STM32446USART_CR3 cr3;
		STM32446USART_GTPR gtpr;
		void (*dr)(uint32_t data);
		uint32_t (*get_dr)(void);
		/*** Other ***/
		void (*clock)(uint8_t bool);
		void (*parameter)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
	#endif
}STM32446USART6obj;
STM32446USART1obj usart1_inic(void);
STM32446USART2obj usart2_inic(void);
STM32446USART3obj usart3_inic(void);
STM32446USART4obj uart4_inic(void);
STM32446USART5obj uart5_inic(void);
STM32446USART6obj usart6_inic(void);
/*** USART1 Bit Mapping Header ***/
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
void STM32446Usart1_dr(uint32_t data);
uint32_t STM32446Usart1_get_dr(void);
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
void STM32446Usart1Clock( uint8_t bool );
void STM32446Usart1Inic( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
void STM32446Usart1Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** USART2 Bit Mapping Header ***/
// SR
uint8_t STM32446Usart2_cts(void);
void STM32446Usart2_clear_cts(void);
uint8_t STM32446Usart2_lbd(void);
void STM32446Usart2_clear_lbd(void);
uint8_t STM32446Usart2_txe(void);
uint8_t STM32446Usart2_tc(void);
void STM32446Usart2_clear_tc(void);
uint8_t STM32446Usart2_rxne(void);
void STM32446Usart2_clear_rxne(void);
uint8_t STM32446Usart2_idle(void);
uint8_t STM32446Usart2_ore(void);
uint8_t STM32446Usart2_nf(void);
uint8_t STM32446Usart2_fe(void);
uint8_t STM32446Usart2_pe(void);
// DR
void STM32446Usart2_dr(uint32_t data);
uint32_t STM32446Usart2_get_dr(void);
// BRR
void STM32446Usart2_div_mantissa(uint16_t value);
void STM32446Usart2_div_fraction(uint8_t value);
// CR1
void STM32446Usart2_over8(uint8_t bool);
void STM32446Usart2_ue(uint8_t bool);
void STM32446Usart2_m(uint8_t bool);
void STM32446Usart2_wake(uint8_t bool);
void STM32446Usart2_pce(uint8_t bool);
void STM32446Usart2_ps(uint8_t bool);
void STM32446Usart2_peie(uint8_t bool);
void STM32446Usart2_txeie(uint8_t bool);
void STM32446Usart2_tcie(uint8_t bool);
void STM32446Usart2_rxneie(uint8_t bool);
void STM32446Usart2_idleie(uint8_t bool);
void STM32446Usart2_te(uint8_t bool);
void STM32446Usart2_re(uint8_t bool);
void STM32446Usart2_rwu(uint8_t bool);
void STM32446Usart2_sbk(uint8_t bool);
// CR2
void STM32446Usart2_linen(uint8_t bool);
void STM32446Usart2_stop(uint8_t value);
void STM32446Usart2_clken(uint8_t bool);
void STM32446Usart2_cpol(uint8_t bool);
void STM32446Usart2_cpha(uint8_t bool);
void STM32446Usart2_lbcl(uint8_t bool);
void STM32446Usart2_lbdie(uint8_t bool);
void STM32446Usart2_lbdl(uint8_t bool);
void STM32446Usart2_add(uint8_t value);
// CR3
void STM32446Usart2_onebit(uint8_t bool);
void STM32446Usart2_ctsie(uint8_t bool);
void STM32446Usart2_ctse(uint8_t bool);
void STM32446Usart2_rtse(uint8_t bool);
void STM32446Usart2_dmat(uint8_t bool);
void STM32446Usart2_dmar(uint8_t bool);
void STM32446Usart2_scen(uint8_t bool);
void STM32446Usart2_nack(uint8_t bool);
void STM32446Usart2_hdsel(uint8_t bool);
void STM32446Usart2_irlp(uint8_t bool);
void STM32446Usart2_iren(uint8_t bool);
void STM32446Usart2_eie(uint8_t bool);
// GTPR
void STM32446Usart2_gt(uint8_t value);
void STM32446Usart2_psc(uint8_t value);
// Other
void STM32446Usart2Clock( uint8_t bool );
void STM32446Usart2Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** USART3 Bit Mapping Header ***/
// SR
uint8_t STM32446Usart3_cts(void);
void STM32446Usart3_clear_cts(void);
uint8_t STM32446Usart3_lbd(void);
void STM32446Usart3_clear_lbd(void);
uint8_t STM32446Usart3_txe(void);
uint8_t STM32446Usart3_tc(void);
void STM32446Usart3_clear_tc(void);
uint8_t STM32446Usart3_rxne(void);
void STM32446Usart3_clear_rxne(void);
uint8_t STM32446Usart3_idle(void);
uint8_t STM32446Usart3_ore(void);
uint8_t STM32446Usart3_nf(void);
uint8_t STM32446Usart3_fe(void);
uint8_t STM32446Usart3_pe(void);
// DR
void STM32446Usart3_dr(uint32_t data);
uint32_t STM32446Usart3_get_dr(void);
// BRR
void STM32446Usart3_div_mantissa(uint16_t value);
void STM32446Usart3_div_fraction(uint8_t value);
// CR1
void STM32446Usart3_over8(uint8_t bool);
void STM32446Usart3_ue(uint8_t bool);
void STM32446Usart3_m(uint8_t bool);
void STM32446Usart3_wake(uint8_t bool);
void STM32446Usart3_pce(uint8_t bool);
void STM32446Usart3_ps(uint8_t bool);
void STM32446Usart3_peie(uint8_t bool);
void STM32446Usart3_txeie(uint8_t bool);
void STM32446Usart3_tcie(uint8_t bool);
void STM32446Usart3_rxneie(uint8_t bool);
void STM32446Usart3_idleie(uint8_t bool);
void STM32446Usart3_te(uint8_t bool);
void STM32446Usart3_re(uint8_t bool);
void STM32446Usart3_rwu(uint8_t bool);
void STM32446Usart3_sbk(uint8_t bool);
// CR2
void STM32446Usart3_linen(uint8_t bool);
void STM32446Usart3_stop(uint8_t value);
void STM32446Usart3_clken(uint8_t bool);
void STM32446Usart3_cpol(uint8_t bool);
void STM32446Usart3_cpha(uint8_t bool);
void STM32446Usart3_lbcl(uint8_t bool);
void STM32446Usart3_lbdie(uint8_t bool);
void STM32446Usart3_lbdl(uint8_t bool);
void STM32446Usart3_add(uint8_t value);
// CR3
void STM32446Usart3_onebit(uint8_t bool);
void STM32446Usart3_ctsie(uint8_t bool);
void STM32446Usart3_ctse(uint8_t bool);
void STM32446Usart3_rtse(uint8_t bool);
void STM32446Usart3_dmat(uint8_t bool);
void STM32446Usart3_dmar(uint8_t bool);
void STM32446Usart3_scen(uint8_t bool);
void STM32446Usart3_nack(uint8_t bool);
void STM32446Usart3_hdsel(uint8_t bool);
void STM32446Usart3_irlp(uint8_t bool);
void STM32446Usart3_iren(uint8_t bool);
void STM32446Usart3_eie(uint8_t bool);
// GTPR
void STM32446Usart3_gt(uint8_t value);
void STM32446Usart3_psc(uint8_t value);
// Other
void STM32446Usart3Clock( uint8_t bool );
void STM32446Usart3Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** UART4 Bit Mapping Header ***/
// SR
uint8_t STM32446Uart4_cts(void);
void STM32446Uart4_clear_cts(void);
uint8_t STM32446Uart4_lbd(void);
void STM32446Uart4_clear_lbd(void);
uint8_t STM32446Uart4_txe(void);
uint8_t STM32446Uart4_tc(void);
void STM32446Uart4_clear_tc(void);
uint8_t STM32446Uart4_rxne(void);
void STM32446Uart4_clear_rxne(void);
uint8_t STM32446Uart4_idle(void);
uint8_t STM32446Uart4_ore(void);
uint8_t STM32446Uart4_nf(void);
uint8_t STM32446Uart4_fe(void);
uint8_t STM32446Uart4_pe(void);
// DR
void STM32446Uart4_dr(uint32_t data);
uint32_t STM32446Uart4_get_dr(void);
// BRR
void STM32446Uart4_div_mantissa(uint16_t value);
void STM32446Uart4_div_fraction(uint8_t value);
// CR1
void STM32446Uart4_over8(uint8_t bool);
void STM32446Uart4_ue(uint8_t bool);
void STM32446Uart4_m(uint8_t bool);
void STM32446Uart4_wake(uint8_t bool);
void STM32446Uart4_pce(uint8_t bool);
void STM32446Uart4_ps(uint8_t bool);
void STM32446Uart4_peie(uint8_t bool);
void STM32446Uart4_txeie(uint8_t bool);
void STM32446Uart4_tcie(uint8_t bool);
void STM32446Uart4_rxneie(uint8_t bool);
void STM32446Uart4_idleie(uint8_t bool);
void STM32446Uart4_te(uint8_t bool);
void STM32446Uart4_re(uint8_t bool);
void STM32446Uart4_rwu(uint8_t bool);
void STM32446Uart4_sbk(uint8_t bool);
// CR2
void STM32446Uart4_linen(uint8_t bool);
void STM32446Uart4_stop(uint8_t value);
void STM32446Uart4_clken(uint8_t bool);
void STM32446Uart4_cpol(uint8_t bool);
void STM32446Uart4_cpha(uint8_t bool);
void STM32446Uart4_lbcl(uint8_t bool);
void STM32446Uart4_lbdie(uint8_t bool);
void STM32446Uart4_lbdl(uint8_t bool);
void STM32446Uart4_add(uint8_t value);
// CR3
void STM32446Uart4_onebit(uint8_t bool);
void STM32446Uart4_ctsie(uint8_t bool);
void STM32446Uart4_ctse(uint8_t bool);
void STM32446Uart4_rtse(uint8_t bool);
void STM32446Uart4_dmat(uint8_t bool);
void STM32446Uart4_dmar(uint8_t bool);
void STM32446Uart4_scen(uint8_t bool);
void STM32446Uart4_nack(uint8_t bool);
void STM32446Uart4_hdsel(uint8_t bool);
void STM32446Uart4_irlp(uint8_t bool);
void STM32446Uart4_iren(uint8_t bool);
void STM32446Uart4_eie(uint8_t bool);
// GTPR
void STM32446Uart4_gt(uint8_t value);
void STM32446Uart4_psc(uint8_t value);
// Other
void STM32446Uart4Clock( uint8_t bool );
void STM32446Uart4Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** UART5 Bit Mapping Header ***/
// SR
uint8_t STM32446Uart5_cts(void);
void STM32446Uart5_clear_cts(void);
uint8_t STM32446Uart5_lbd(void);
void STM32446Uart5_clear_lbd(void);
uint8_t STM32446Uart5_txe(void);
uint8_t STM32446Uart5_tc(void);
void STM32446Uart5_clear_tc(void);
uint8_t STM32446Uart5_rxne(void);
void STM32446Uart5_clear_rxne(void);
uint8_t STM32446Uart5_idle(void);
uint8_t STM32446Uart5_ore(void);
uint8_t STM32446Uart5_nf(void);
uint8_t STM32446Uart5_fe(void);
uint8_t STM32446Uart5_pe(void);
// DR
void STM32446Uart5_dr(uint32_t data);
uint32_t STM32446Uart5_get_dr(void);
// BRR
void STM32446Uart5_div_mantissa(uint16_t value);
void STM32446Uart5_div_fraction(uint8_t value);
// CR1
void STM32446Uart5_over8(uint8_t bool);
void STM32446Uart5_ue(uint8_t bool);
void STM32446Uart5_m(uint8_t bool);
void STM32446Uart5_wake(uint8_t bool);
void STM32446Uart5_pce(uint8_t bool);
void STM32446Uart5_ps(uint8_t bool);
void STM32446Uart5_peie(uint8_t bool);
void STM32446Uart5_txeie(uint8_t bool);
void STM32446Uart5_tcie(uint8_t bool);
void STM32446Uart5_rxneie(uint8_t bool);
void STM32446Uart5_idleie(uint8_t bool);
void STM32446Uart5_te(uint8_t bool);
void STM32446Uart5_re(uint8_t bool);
void STM32446Uart5_rwu(uint8_t bool);
void STM32446Uart5_sbk(uint8_t bool);
// CR2
void STM32446Uart5_linen(uint8_t bool);
void STM32446Uart5_stop(uint8_t value);
void STM32446Uart5_clken(uint8_t bool);
void STM32446Uart5_cpol(uint8_t bool);
void STM32446Uart5_cpha(uint8_t bool);
void STM32446Uart5_lbcl(uint8_t bool);
void STM32446Uart5_lbdie(uint8_t bool);
void STM32446Uart5_lbdl(uint8_t bool);
void STM32446Uart5_add(uint8_t value);
// CR3
void STM32446Uart5_onebit(uint8_t bool);
void STM32446Uart5_ctsie(uint8_t bool);
void STM32446Uart5_ctse(uint8_t bool);
void STM32446Uart5_rtse(uint8_t bool);
void STM32446Uart5_dmat(uint8_t bool);
void STM32446Uart5_dmar(uint8_t bool);
void STM32446Uart5_scen(uint8_t bool);
void STM32446Uart5_nack(uint8_t bool);
void STM32446Uart5_hdsel(uint8_t bool);
void STM32446Uart5_irlp(uint8_t bool);
void STM32446Uart5_iren(uint8_t bool);
void STM32446Uart5_eie(uint8_t bool);
// GTPR
void STM32446Uart5_gt(uint8_t value);
void STM32446Uart5_psc(uint8_t value);
// Other
void STM32446Uart5Clock( uint8_t bool );
void STM32446Uart5Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** USART6 Bit Mapping Header ***/
// SR
uint8_t STM32446Usart6_cts(void);
void STM32446Usart6_clear_cts(void);
uint8_t STM32446Usart6_lbd(void);
void STM32446Usart6_clear_lbd(void);
uint8_t STM32446Usart6_txe(void);
uint8_t STM32446Usart6_tc(void);
void STM32446Usart6_clear_tc(void);
uint8_t STM32446Usart6_rxne(void);
void STM32446Usart6_clear_rxne(void);
uint8_t STM32446Usart6_idle(void);
uint8_t STM32446Usart6_ore(void);
uint8_t STM32446Usart6_nf(void);
uint8_t STM32446Usart6_fe(void);
uint8_t STM32446Usart6_pe(void);
// DR
void STM32446Usart6_dr(uint32_t data);
uint32_t STM32446Usart6_get_dr(void);
// BRR
void STM32446Usart6_div_mantissa(uint16_t value);
void STM32446Usart6_div_fraction(uint8_t value);
// CR1
void STM32446Usart6_over8(uint8_t bool);
void STM32446Usart6_ue(uint8_t bool);
void STM32446Usart6_m(uint8_t bool);
void STM32446Usart6_wake(uint8_t bool);
void STM32446Usart6_pce(uint8_t bool);
void STM32446Usart6_ps(uint8_t bool);
void STM32446Usart6_peie(uint8_t bool);
void STM32446Usart6_txeie(uint8_t bool);
void STM32446Usart6_tcie(uint8_t bool);
void STM32446Usart6_rxneie(uint8_t bool);
void STM32446Usart6_idleie(uint8_t bool);
void STM32446Usart6_te(uint8_t bool);
void STM32446Usart6_re(uint8_t bool);
void STM32446Usart6_rwu(uint8_t bool);
void STM32446Usart6_sbk(uint8_t bool);
// CR2
void STM32446Usart6_linen(uint8_t bool);
void STM32446Usart6_stop(uint8_t value);
void STM32446Usart6_clken(uint8_t bool);
void STM32446Usart6_cpol(uint8_t bool);
void STM32446Usart6_cpha(uint8_t bool);
void STM32446Usart6_lbcl(uint8_t bool);
void STM32446Usart6_lbdie(uint8_t bool);
void STM32446Usart6_lbdl(uint8_t bool);
void STM32446Usart6_add(uint8_t value);
// CR3
void STM32446Usart6_onebit(uint8_t bool);
void STM32446Usart6_ctsie(uint8_t bool);
void STM32446Usart6_ctse(uint8_t bool);
void STM32446Usart6_rtse(uint8_t bool);
void STM32446Usart6_dmat(uint8_t bool);
void STM32446Usart6_dmar(uint8_t bool);
void STM32446Usart6_scen(uint8_t bool);
void STM32446Usart6_nack(uint8_t bool);
void STM32446Usart6_hdsel(uint8_t bool);
void STM32446Usart6_irlp(uint8_t bool);
void STM32446Usart6_iren(uint8_t bool);
void STM32446Usart6_eie(uint8_t bool);
// GTPR
void STM32446Usart6_gt(uint8_t value);
void STM32446Usart6_psc(uint8_t value);
// Other
void STM32446Usart6Clock( uint8_t bool );
void STM32446Usart6Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );

/*** INTERRUPT HEADER ***/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void USART6_IRQHandler(void);

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


