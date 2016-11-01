/*
 * dClock2.c
 *
 * Created: 10/31/2016 4:04:10 PM
 *  Author: AhmedShaarawy
 */ 


#include "digitalClock.h"



extern void (*pF_INT0)(void);

int main(void)
{
	TaskInit();
	Gi();	// enable global interrupt
    TaskLoop();
}

