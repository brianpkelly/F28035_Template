/*
 * Init_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */
#include "all.h"

void SystemInit(float time)
{
	CANSetup();
	ClockSetup();
	StartPowerDownInt();			//start power down interrupt, this will change state to PowerDown if necessary
	StopWatchSetUp(time);
}

