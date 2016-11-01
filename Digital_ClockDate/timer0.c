/*
 * timer0.c
 *
 * Created: 10/31/2016 4:08:47 PM
 *  Author: AhmedShaarawy
 */ 

#include "timer0.h"


void (*pF_OVF)(void);


void timer0Init(void)
{
	TIMSK|= 0x01; // overflow interrupt only is enabled.
	TCCR0= 0x02;  // no wave generation, OC0 disabled and clock pre-scale is 8
}


ISR(TIMER0_OVF_vect)
{
	pF_OVF();
}