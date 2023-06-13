/******************************************************************************
	CIRCBUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 07092022
Comment:
    Circular Buffer
******************************************************************************/
/*** File Library***/
#include <stdio.h>
#include <string.h>
#include "circbuffer.h"

/*** File Header ***/
uint8_t CIRC_get(struct circ_buf_template* circ);
void CIRC_put(struct circ_buf_template* circ, uint8_t data);
void CIRC_putstr(struct circ_buf_template* circ, const char* str);
void CIRC_getstr(struct circ_buf_template* circ, uint8_t* str);

/*** CIRCBUFF Procedure & Function Definition ***/
circbuff CIRCBUFFenable( uint8_t size_buff, uint8_t* buff )
{
	// OBJECT STRUCT
	struct circ_buf_template circ;
	// inic VAR
	circ.tail = circ.head = circ.buff = buff;
	circ.orig = buff;
	circ.end = buff + size_buff; // generic
	// function pointers
	circ.get = CIRC_get;
	circ.put = CIRC_put;
	circ.putstr = CIRC_putstr;
	circ.getstr = CIRC_getstr;
	return circ; // return copy
}

uint8_t CIRC_get( struct circ_buf_template* circ ){
	uint8_t* next;
	if( circ->tail == circ->end ){
		next = circ->orig;
	}else{
		next = circ->tail + 1;
	}
	if( circ->tail == circ->head ){
		*circ->tail = 0;
	}else{
		circ->tail = next;
	}
	return *circ->tail;
}

void CIRC_put( struct circ_buf_template* circ, uint8_t data ){
	uint8_t* next;
	if( circ->head == circ->end ){
		next = circ->orig;
	}else{
		next = circ->head + 1;
	}
	
	if( next == circ->tail ){
		*next = 0;
	}else{
		*next = data;
		circ->head = next;
	}
}

void CIRC_putstr(struct circ_buf_template* circ, const char* str){
	uint8_t i;
	for(i = 0; circ->tail != circ->head ; CIRC_put(circ, str[i++]));
}

void CIRC_getstr(struct circ_buf_template* circ, uint8_t* str){
	uint8_t i;
	for(i = 0; circ->tail != circ->head  ; str[i++] = CIRC_get(circ), str[i] = '\0');
}

/***EOF***/


