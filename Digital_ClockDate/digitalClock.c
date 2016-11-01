/*
 * digitalClock.c
 *
 * Created: 10/31/2016 4:06:23 PM
 *  Author: AhmedShaarawy
 */ 


#include "digitalClock.h"




extern void (*pF_INT0)(void);
extern void (*pF_OVF)(void);


U8 Nums7seg[10]= { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };
U8 MthLimits[12]= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
U8 AmPm, Menue= 0, Ok= 0, Edit= 0  ;
U32 count= 0, AlarmAmPm= AM;
Unit  Sec, Min, Hor, Day, Mth, alphaMth,
	 AlarmSec, AlarmMin, AlarmHor ;
sYear Yar ;

void TaskInit(void)
{
	// timer initialization
	timer0Init();
	pF_OVF= TaskIntTimer0;
	
	// shift registers
	HC595Init();
	HC595Init_2();
	
	
	// GPIO directions
	DDRA= 0xff;
	DDRB= 0xff;

	CLR_BIT(DDR(EDIT_PORT),EDIT_PIN);	/* or DDR(EDIT_PORT) &= ~(1<<EDIT_PIN); */// to make edit pin as input
	// input switches
	CLR_PIN(EDIT_PORT,EDIT_PIN);
	CLR_PIN(OK_SW_PORT,OK_SW_PIN);
	
	
	// GPIO initialization
	PORTA= 0x00;
	PORTB ^= 1<<6 ; // toggle pin 1 in port B
	
	// disable initialization
	HC595Write(0xff);
	HC595Write_2(0xff);
	
	// Time initialization
	Sec.digit0= 0;
	Sec.digit1= 5;
	Min.digit0= 9;
	Min.digit1= 5;
	Hor.digit0= 1;
	Hor.digit1= 1;
	
	// AM, PM
	AmPm= PM;
	
	// Alarm initialization
	AlarmSec.digit0= AlarmSec.digit1= 0;
	AlarmMin.digit0= AlarmMin.digit1= 0;
	AlarmHor.digit0= 2;
	AlarmHor.digit1= 1;
	AlarmAmPm= AM;
	
	// date initialization
	Day.digit0= 1;
	Day.digit1= 0;
	Mth.digit0= 1;
	Mth.digit1= 1;
	Yar.digit0= 6;
	Yar.digit1= 1;
	Yar.digit2= 0;
	Yar.digit3= 2;
	
}

void Task2Init(void)
{
	// external interrupt initialization
	EXTIntInit();
	pF_INT0= TaskInt0;
}

// display on 7-segment
void TaskLoop(void)
{	
	LOOP{
		///////////////////// DISPLAYING TIME ////////////////
		HC595Write_2(~0x00);
		
		HC595Write(~0x00);
		PORTA= Nums7seg[Sec.digit0] & 0x7f ;
		HC595Write(~0x01);	
		_delay_ms(2);
		HC595Write(~0x00);
		PORTA=  Nums7seg[Sec.digit1] & 0x7f ;
		HC595Write(~0x02);
		_delay_ms(2);
		///////////////
		HC595Write(~0x00);
		PORTA= Nums7seg[Min.digit0] & 0x7f ;
		HC595Write(~0x04);	
		_delay_ms(2);
		HC595Write(~0x00);
		PORTA= Nums7seg[Min.digit1] & 0x7f ;
		HC595Write(~0x08);
		_delay_ms(2);
		//////////////
		HC595Write(~0x00);
		PORTA= Nums7seg[Hor.digit0] & 0x7f ;
		HC595Write(~0x10);	
		_delay_ms(2);
		HC595Write(~0x00);
		PORTA= Nums7seg[Hor.digit1] & 0x7f ;
		HC595Write(~0x20);	
		_delay_ms(2);
		////////////
		HC595Write(~0x00);
		PORTA= AmPm & 0x7f ;
		HC595Write(~0x40);	
		_delay_ms(2);
		////////////////////////////////////////////////
		
		
		//////////////// DISPLAYING DATE //////////////
		HC595Write(~0x00);
		
		HC595Write_2(~0x00);
		PORTA= Nums7seg[Day.digit0] & 0x7f ;
		HC595Write_2(~0x01);	
		//_delay_ms(2);	
		HC595Write_2(~0x00);	
		PORTA=  Nums7seg[Day.digit1] & 0x7f ;
		HC595Write_2(~0x02);	
		//_delay_ms(2);
		////////////
		HC595Write_2(~0x00);
		PORTA= Nums7seg[Mth.digit0] & 0x7f ;
		HC595Write_2(~0x04);	
		//_delay_ms(2);
		HC595Write_2(~0x00);
		PORTA= Nums7seg[Mth.digit1] & 0x7f ;
		HC595Write_2(~0x08);	
		//_delay_ms(2);
		/////////////
		HC595Write_2(~0x00);
		PORTA= Nums7seg[Yar.digit0] & 0x7f ;
		HC595Write_2(~0x10);	
		//_delay_ms(2);
		HC595Write_2(~0x00);
		PORTA= Nums7seg[Yar.digit1] & 0x7f ;
		HC595Write_2(~0x20);
		//_delay_ms(2);
		PORTA= Nums7seg[Yar.digit2] & 0x7f ;
		HC595Write_2(~0x40);
		//_delay_ms(2);
		HC595Write_2(~0x00);
		PORTA= Nums7seg[Yar.digit3] & 0x7f ;
		HC595Write_2(~0x80);
		//_delay_ms(2);
		///////////////
		/////// display Alphabetic day here /////////
		/////////////////////////////////////////////
	}
	 
}



void TaskIntTimer0(void)
{
	PORTB ^= 1<<6 ; // toggle pin 1 in port B
	count++;
	if( count >= DISICION )
	{
		count= 0;
		Sec.digit0++;
		if (Sec.digit0 == 10 )
		{
			Sec.digit0= 0;
			Sec.digit1++;
			if (Sec.digit1 == 6)
			{
				Sec.digit1= 0;
				Min.digit0++;
				if( Min.digit0== 10 )
				{
					Min.digit0= 0;
					Min.digit1++;
					if (Min.digit1== 6)
					{
						Min.digit1= 0;
						Hor.digit0++;
						if (Hor.digit0== 10)
						{
							Hor.digit0= 0;
							Hor.digit1++;
							if (Hor.digit1== 2)
							{
								Hor.digit0= 1;
								Hor.digit1= 0;
							}
							
						}
						
						else if (Hor.digit1== 1 && Hor.digit0== 2 )
						{
							PORTB ^= 1<<7 ; // toggle pin 1 in port B
							AmPm= (AmPm == AM) ? PM : AM ;
							if( AmPm == AM )
							{
								Day.digit0++ ;
								if( Day.digit0== 10 )
								{
									Day.digit0= 0;
									Day.digit1++;
									if( Day.digit0+(Day.digit1*10) > MthLimits[Mth.digit0+(Mth.digit1*10)-1] )
									{
										Day.digit0= 1;
										Day.digit1= 0;
										Mth.digit0++ ;
										if(Mth.digit0 == 10)
										{
											Mth.digit0= 0;
											Mth.digit1++;
											if( Mth.digit1 == 3 )
											{
												Mth.digit0= 1;
												Mth.digit1 = 0;
												Yar.digit0++;
												if(Yar.digit0 == 10)
												{
													Yar.digit0= 0;
													Yar.digit1++;
													if(Yar.digit1 == 10)
													{
														Yar.digit1= 0;
														Yar.digit2++;
														if( Yar.digit2== 10 )
														{
															Yar.digit2= 0;
															Yar.digit3++;
															if(Yar.digit3 == 10)
															Yar.digit3= 0;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}



// the function is not available yet
// responsible for editing time and date with INT0
void TaskInt0(void)
{
	// hold timer0
	HoldTimer0();
	// editing
	Menue++;
	
	while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck here while Ok is not pressed
	{
		switch(Menue)
		{
			case ALARM:
			
			break;
			///////////////////////////////////////////////////////////////////////////////////////////////////////
			case EDIT_TIME:
			while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck here while Ok is not pressed
			{
				while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck in displaying seconds while Ok is not pressed
				{
					HC595Write(~0x00);
					HC595Write_2(~0x00);
					PORTA= Nums7seg[Sec.digit0] & 0x7f ;
					HC595Write(~0x01);
					_delay_ms(5);
					HC595Write(~0x00);
					PORTA=  Nums7seg[Sec.digit1] & 0x7f ;
					HC595Write(~0x02);
					_delay_ms(5);
					if( READ_PIN(EDIT_PORT,EDIT_PIN) )
					{
						while( READ_PIN(EDIT_PORT,EDIT_PIN) ); // anti-long-press
						Sec.digit0++;
						if (Sec.digit0 == 10)
						{
							Sec.digit0= 0;
							Sec.digit1++;
							if (Sec.digit1 == 6)
								Sec.digit1= 0;
						}
					}
				}
				while( READ_PIN(OK_SW_PORT,OK_SW_PIN) ); // anti-long-press
				while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck in displaying minutes while Ok is not pressed
				{
					HC595Write(~0x00);
					HC595Write_2(~0x00);
					PORTA= Nums7seg[Min.digit0] & 0x7f ;
					HC595Write(~0x04);
					_delay_ms(5);
					HC595Write(~0x00);
					PORTA= Nums7seg[Min.digit1] & 0x7f ;
					HC595Write(~0x08);
					_delay_ms(5);
					if( READ_PIN(EDIT_PORT,EDIT_PIN) )
					{
						Min.digit0++;
						while( READ_PIN(EDIT_PORT,EDIT_PIN) ); // anti-long-press
						if(Min.digit0 == 10)
						{
							Min.digit0= 0;
							Min.digit1++;
							if (Min.digit1 == 6)
							Min.digit1= 0;
						}
					}
				}
				while( READ_PIN(OK_SW_PORT,OK_SW_PIN) ); // anti-long-press
				while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck in displaying hors while Ok is not pressed
				{
					HC595Write(~0x00);
					HC595Write_2(~0x00);
					PORTA= Nums7seg[Hor.digit0] & 0x7f ;
					HC595Write(~0x10);
					_delay_ms(5);
					HC595Write(~0x00);
					PORTA= Nums7seg[Hor.digit1] & 0x7f ;
					HC595Write(~0x20);
					_delay_ms(5);
					if( READ_PIN(EDIT_PORT,EDIT_PIN) )
					{
						while( READ_PIN(EDIT_PORT,EDIT_PIN) ); // anti-long-press
						Hor.digit0++;
						if(Hor.digit0 == 10)
						{
							Hor.digit0= 0;
							Hor.digit1++;
							if (Hor.digit1 == 2)
								Hor.digit1= 0;
						}
						
					}
				}
				while( READ_PIN(OK_SW_PORT,OK_SW_PIN) ); // anti-long-press
				while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck in displaying AM/PM while Ok is not pressed
				{
					while( READ_PIN(EDIT_PORT,EDIT_PIN) ); // anti-long-press
					AmPm= AmPm == AM ? PM : AM ;
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			case EDIT_DATE:
			while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck here while Ok is not pressed
			{
				while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck displaying day while Ok is not pressed
				{
					HC595Write(~0x00);
					HC595Write_2(~0x00);	
					PORTA= Nums7seg[Day.digit0] & 0x7f ;
					HC595Write_2(~0x01);
					_delay_ms(5);
					HC595Write_2(~0x00);
					PORTA=  Nums7seg[Day.digit1] & 0x7f ;
					HC595Write_2(~0x02);
					_delay_ms(5);
					if (READ_PIN(EDIT_PORT,EDIT_PIN))
					{
						while( READ_PIN(EDIT_PORT,EDIT_PIN) ); // anti-long-press
						Day.digit0++;
						if(Day.digit0 == 10)
						{
							Day.digit0= 0;
							Day.digit1++;
							if (Day.digit0+(Day.digit1*10) > MthLimits[Mth.digit0+(Mth.digit1*10)-1])
							{
								Day.digit0= 1;
								Day.digit1= 0;
							}
						}
					}
				}
				while( READ_PIN(OK_SW_PORT,OK_SW_PIN) );	// anti-long-press
				while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck displaying month while Ok is not pressed
				{
					HC595Write(~0x00);
					HC595Write_2(~0x00);
					PORTA= Nums7seg[Mth.digit0] & 0x7f ;
					HC595Write_2(~0x04);
					_delay_ms(5);
					HC595Write_2(~0x00);
					PORTA= Nums7seg[Mth.digit1] & 0x7f ;
					HC595Write_2(~0x08);
					_delay_ms(5);
					if (READ_PIN(EDIT_PORT,EDIT_PIN))
					{
						while( READ_PIN(EDIT_PORT,EDIT_PIN) ); // anti-long-press
						Mth.digit0++;
						if (Mth.digit0 == 10)
						{
							Mth.digit0= 0;
							Mth.digit1++;
							if (Mth.digit1 == 3)
							{
								Mth.digit0= 1;
								Mth.digit1= 0;
								
							}
						}
					}
				}
				while( READ_PIN(OK_SW_PORT,OK_SW_PIN) );	// anti-long-press
				while( !READ_PIN(OK_SW_PORT,OK_SW_PIN) )	// stuck displaying year while Ok is not pressed
				{
					HC595Write(~0x00);
					HC595Write_2(~0x00);
					PORTA= Nums7seg[Yar.digit0] & 0x7f ;
					HC595Write_2(~0x10);
					_delay_ms(5);
					HC595Write_2(~0x00);
					PORTA= Nums7seg[Yar.digit1] & 0x7f ;
					HC595Write_2(~0x20);
					_delay_ms(5);
					if (READ_PIN(EDIT_PORT,EDIT_PIN))
					{
						while( READ_PIN(EDIT_PORT,EDIT_PIN) ); // anti-long-press
						Yar.digit0++;
						if (Yar.digit0 == 10)
						{
							Yar.digit0= 0;
							Yar.digit1++;
							if(Yar.digit1 == 10)
							{
								Yar.digit1= 0;
								Yar.digit2++;
								if( Yar.digit2== 10 )
								{
									Yar.digit2= 0;
									Yar.digit3++;
									if(Yar.digit3 == 10)
									Yar.digit3= 0;
								}
							}
						}
					}
					
					/////// Alphabetic month /////////
				}
				break;
			///////////////////////////////////////////////////////////////////////////////////////////////////////
			
			
			default:
			Menue= 0;
			HC595Write(0xff);
			HC595Write_2(0xff);
			break;
		}
	}
	
	// return timer
	ReturnTimer0();
	}
}



