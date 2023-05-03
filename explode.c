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
void EXPLODEupdate(EXPLODE* self, uint32_t x);
uint32_t EXPLODEhh(EXPLODE* self);
uint32_t EXPLODEll(EXPLODE* self);
uint32_t EXPLODElh(EXPLODE* self);
uint32_t EXPLODEhl(EXPLODE* self);

/*** Procedure & Function ***/
EXPLODE EXPLODEenable( void )
{
	// struct object
	struct expld explode;
	// inic VAR
	explode.par.XI = 0;
	explode.par.XF = 0;
	// function pointers
	explode.update = EXPLODEupdate;
	return explode;
}
// boot
void EXPLODEupdate(EXPLODE* self, uint32_t x)
{
	self->par.XI = self->par.XF;
	self->par.XF = x;
	self->HH = EXPLODEhh(self);
	self->LL = EXPLODEll(self);
	self->LH = EXPLODElh(self);
	self->HL = EXPLODEhl(self);
}
// hh
uint32_t EXPLODEhh(EXPLODE* self)
{
	return (self->par.XI & self->par.XF);
}
// ll
uint32_t EXPLODEll(EXPLODE* self)
{
	return ~(self->par.XI | self->par.XF);
}
// lh
uint32_t EXPLODElh(EXPLODE* self)
{
	uint32_t i;
	i = self->par.XI ^ self->par.XF;
	i &= self->par.XF;
	return i;
}
// hl
uint32_t EXPLODEhl(EXPLODE* self)
{
	uint32_t i;
	i = self->par.XF ^ self->par.XI;
	i &= self->par.XI;
	return i;
}

/*** File Interrupt ***/

/***EOF***/

