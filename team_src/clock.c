/*
 * clock.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"


clock_struct Clock_Ticks = CLOCK_TICKS_CLEAR;

void ClockSetup()
{
	SystemClockSetup(&Clock_Ticks);
	InitializeCpuTimer2(1000000);
	StartCpuTimer2();
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

__interrupt void INT14_ISR(void)     // INT14 or CPU-Timer2
{
  // Insert ISR Code here

	RestartCpuTimer2();
}

