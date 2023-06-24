/******************************************************************************
	STM32 446 PWR
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446PWR_H_
	#define _STM32446PWR_H_
/*** Library ***/
#include <inttypes.h>
/*** PWR Bit Mapping TypeDef ***/
// CR
typedef struct
{
	void (*fissr)(uint8_t bool);
	void (*fmssr)(uint8_t bool);
	void (*uden)(uint8_t value);
	void (*odswen)(uint8_t bool);
	void (*oden)(uint8_t bool);
	void (*vos)(uint8_t value);
	void (*adcdc1)(uint8_t bool);
	void (*mruds)(uint8_t bool);
	void (*lpuds)(uint8_t bool);
	void (*fpds)(uint8_t bool);
	void (*dbp)(uint8_t bool);
	void (*pls)(uint8_t value);
	uint8_t (*get_pls)(void);
	void (*pvde)(uint8_t bool);
	void (*clear_csbf)(void);
	void (*clear_cwuf)(void);
	void (*pdds)(uint8_t bool);
	void (*lpds)(uint8_t bool);
}STM32446PWR_cr;
// CSR
typedef struct
{
	uint8_t (*udrdy)(void);
	void (*clear_udrdy)(void);
	uint8_t (*odswrdy)(void);
	uint8_t (*odrdy)(void);
	uint8_t (*vosrdy)(void);
	void (*bre)(uint8_t bool);
	void (*ewup1)(uint8_t bool);
	void (*ewup2)(uint8_t bool);
	uint8_t (*brr)(void);
	uint8_t (*pvdo)(void);
	uint8_t (*sbf)(void);
	uint8_t (*wuf)(void);
}STM32446PWR_csr;

/*** PWR TypeDef ***/
typedef struct
{
	PWR_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446PWR_cr cr;
	STM32446PWR_csr csr;
	/*** Other ***/
	void (*clock)(uint8_t bool);
}STM32446PWRobj;

STM32446PWRobj pwr_inic(void);

/*** PWR Bit Mapping Header ***/
void STM32446PWR_clock(uint8_t bool);
// CR
void STM32446PWR_cr_fissr(uint8_t bool);
void STM32446PWR_cr_fmssr(uint8_t bool);
void STM32446PWR_cr_uden(uint8_t value);
void STM32446PWR_cr_odswen(uint8_t bool);
void STM32446PWR_cr_oden(uint8_t bool);
void STM32446PWR_cr_vos(uint8_t value);
void STM32446PWR_cr_adcdc1(uint8_t bool);
void STM32446PWR_cr_mruds(uint8_t bool);
void STM32446PWR_cr_lpuds(uint8_t bool);
void STM32446PWR_cr_fpds(uint8_t bool);
void STM32446PWR_cr_dbp(uint8_t bool);
void STM32446PWR_cr_pls(uint8_t value);
uint8_t STM32446PWR_cr_get_pls(void);
void STM32446PWR_cr_pvde(uint8_t bool);
void STM32446PWR_cr_clear_csbf(void);
void STM32446PWR_cr_clear_cwuf(void);
void STM32446PWR_cr_pdds(uint8_t bool);
void STM32446PWR_cr_lpds(uint8_t bool);
// CSR
uint8_t STM32446PWR_udrdy(void);
void STM32446PWR_csr_clear_udrdy(void);
uint8_t STM32446PWR_csr_odswrdy(void);
uint8_t STM32446PWR_csr_odrdy(void);
uint8_t STM32446PWR_csr_vosrdy(void);
void STM32446PWR_csr_bre(uint8_t bool);
void STM32446PWR_csr_ewup1(uint8_t bool);
void STM32446PWR_csr_ewup2(uint8_t bool);
uint8_t STM32446PWR_csr_brr(void);
uint8_t STM32446PWR_csr_pvdo(void);
uint8_t STM32446PWR_csr_sbf(void);
uint8_t STM32446PWR_csr_wuf(void);

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


