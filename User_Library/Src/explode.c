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

/*** File Header ***/
void EXPLODEupdate(explodeparameter* par, uint32_t x);
uint32_t EXPLODEhh(explodeparameter* par);
uint32_t EXPLODEll(explodeparameter* par);
uint32_t EXPLODElh(explodeparameter* par);
uint32_t EXPLODEhl(explodeparameter* par);

/*** EXPLODE Procedure & Function Definition ***/
EXPLODE EXPLODEenable( void )
{
	// struct object
	EXPLODE explode;
	// inic VAR
	explode.par.XI = 0;
	explode.par.XF = 0;
	// function pointers
	explode.update = EXPLODEupdate;
	return explode;
}
// boot
void EXPLODEupdate(explodeparameter* par, uint32_t x)
{
	par->XI = par->XF;
	par->XF = x;
	par->HH = EXPLODEhh(par);
	par->LL = EXPLODEll(par);
	par->LH = EXPLODElh(par);
	par->HL = EXPLODEhl(par);
}
// hh
uint32_t EXPLODEhh(explodeparameter* par)
{
	return (par->XI & par->XF);
}
// ll
uint32_t EXPLODEll(explodeparameter* par)
{
	return ~(par->XI | par->XF);
}
// lh
uint32_t EXPLODElh(explodeparameter* par)
{
	uint32_t i;
	i = par->XI ^ par->XF;
	i &= par->XF;
	return i;
}
// hl
uint32_t EXPLODEhl(explodeparameter* par)
{
	uint32_t i;
	i = par->XF ^ par->XI;
	i &= par->XI;
	return i;
}

/***EOF***/


