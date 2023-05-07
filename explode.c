/********************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com> 
License: GNU General Public License
Hardware: all
Date: 16032021
Comment:
	Pin Analysis
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
********************************************************************/
/*** File Library ***/
#include"explode.h"

/*** File Constant & Macro ***/

/*** File Variable ***/

/*** File Header ***/
void EXPLODEupdate(explodesignal* sig, uint32_t x);
uint32_t EXPLODEhh(explodesignal* sig);
uint32_t EXPLODEll(explodesignal* sig);
uint32_t EXPLODElh(explodesignal* sig);
uint32_t EXPLODEhl(explodesignal* sig);

/*** Procedure & Function ***/
EXPLODE EXPLODEenable( void )
{
	// struct object
	EXPLODE explode;
	// inic VAR
	explode.sig.XI = 0;
	explode.sig.XF = 0;
	// function pointers
	explode.update = EXPLODEupdate;
	return explode;
}
// boot
void EXPLODEupdate(explodesignal* sig, uint32_t x)
{
	sig->XI = sig->XF;
	sig->XF = x;
	sig->HH = EXPLODEhh(sig);
	sig->LL = EXPLODEll(sig);
	sig->LH = EXPLODElh(sig);
	sig->HL = EXPLODEhl(sig);
}
// hh
uint32_t EXPLODEhh(explodesignal* sig)
{
	return (sig->XI & sig->XF);
}
// ll
uint32_t EXPLODEll(explodesignal* sig)
{
	return ~(sig->XI | sig->XF);
}
// lh
uint32_t EXPLODElh(explodesignal* sig)
{
	uint32_t i;
	i = sig->XI ^ sig->XF;
	i &= sig->XF;
	return i;
}
// hl
uint32_t EXPLODEhl(explodesignal* sig)
{
	uint32_t i;
	i = sig->XF ^ sig->XI;
	i &= sig->XI;
	return i;
}

/*** File Interrupt ***/

/***EOF***/

