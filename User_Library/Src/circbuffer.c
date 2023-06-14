/******************************************************************************
	CIRCBUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 15062023
Comment:
    Circular Buffer
******************************************************************************/
/*** File Library***/
#include <stdio.h>
#include <string.h>
#include "circbuffer.h"

/*** File Header ***/
uint8_t CIRC_get(CIRCBUFFER_par* par);
void CIRC_put(CIRCBUFFER_par* par, char data);
void CIRC_putstr(CIRCBUFFER_par* par, const char* str);
void CIRC_getstr(CIRCBUFFER_par* par, char* str);

/*** CIRCBUFF Procedure & Function Definition ***/
circbuff CIRCBUFFenable( uint8_t size_buff, char* buff )
{
	// OBJECT STRUCT
	struct circ_buf_template circ;
	// inic VAR
	circ.par.tail = circ.par.head = buff;
	circ.par.orig = buff;
	circ.par.end = buff + size_buff; // generic
	*circ.par.tail = *circ.par.head = 0;
	// function pointers
	circ.get = CIRC_get;
	circ.put = CIRC_put;
	circ.putstr = CIRC_putstr;
	circ.getstr = CIRC_getstr;
	return circ; // return copy
}

uint8_t CIRC_get( CIRCBUFFER_par* par ){
	char* next;

	if( par->tail != par->end ){
		next = par->tail + 1;
	}else{
		next = par->orig;
	}

	if( par->tail != par->head ){
		par->tail = next;
	}else{
		*par->tail = 0;
	}

	return *par->tail;
}

void CIRC_put( CIRCBUFFER_par* par, char data ){
	char* next;

	if( par->head != par->end ){
		next = par->head + 1;
	}else{
		next = par->orig;

	}
	
	if( next != par->tail ){
		*next = data;
		par->head = next;
	}else{
		*next = 0;
	}
}

void CIRC_putstr( CIRCBUFFER_par* par, const char* str ){
	uint8_t i;
	for( i = 0; *(str + i) ; CIRC_put(par, *(str + i++)) );

}

void CIRC_getstr( CIRCBUFFER_par* par, char* str ){
	uint8_t i;
	for(i = 0; par->tail != par->head  ; *(str + i) = CIRC_get(par), *(str + ++i) = '\0');
}

/***EOF***/


