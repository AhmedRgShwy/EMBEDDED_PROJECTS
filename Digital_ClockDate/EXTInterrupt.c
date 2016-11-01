/*
 * EXTInterrupt.c
 *
 * Created: 10/31/2016 9:34:06 PM
 *  Author: AhmedShaarawy
 */ 

#include "EXTInterrupt.h"


void (*pF_INT0)(void);

void EXTIntInit(void)
{
	MCUCR |= 0x02 ; // int0 is rising edge sense
	GICR  |= 0x40 ; // enable int0
}


ISR(INT0_vect)
{
	pF_INT0();
}
