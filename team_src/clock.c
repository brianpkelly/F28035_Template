/*
 * clock.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"


struct CPUTIMER_VARS Clock;
clock_struct Clock_Ticks = CLOCK_TICKS_CLEAR;

void ClockSetup()
{
	SystemClockSetup(&Clock, &Clock_Ticks);
}

// Connected to INT13 of CPU (use MINT13 mask):
// ISR can be used by the user.
__interrupt void INT13_ISR(void)     // INT13 or CPU-Timer1
{
	 //***********************************WARNING!!********************************************\\
	//BE CAREFUL YOU NEED TO ALLOW NESTING FOR ANY INTERRUPT THAT MIGHT HAPPEN IN THIS INTERRUPT\\

	 EINT;		//enable all interrupts

	//todo USER: Define Clock ISR
	ClockHeartbeat();

	Clock_Ticks.DataOut++;

	if (Clock_Ticks.DataOut >= DATAOUT_TICKS)
	{
		//send data or fill data
		SendCAN(ADC_BOX);
		SendCAN(GP_BUTTON_BOX);
		Clock_Ticks.DataOut = 0;
	}

	RestartCPUTimer1();
	DINT;
}


