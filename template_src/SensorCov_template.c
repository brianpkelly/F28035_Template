/*
 * SensorCov_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#include "all.h"


sys_ops_struct ops_temp_sys, sc_start_ops;
sys_data_struct data_temp_sys;
stopwatch_struct* conv_watch_in_sys;

void SystemSensorInit(unsigned int time)
{
	//CONFIG ADC
	adcinit();
	//CONFIG GP_BUTTON
	ConfigGPButton();
	//CONFIG LEDS
	//led 0
	ConfigLED0();
	//led 1
	ConfigLED1();
	//CONFIG 12V SWITCH
	Config12V();
	conv_watch_in_sys = StartStopWatch(time);
}

void SystemSensorDeInit()
{
	StopStopWatch(conv_watch_in_sys);
	CLEARLED0();
	CLEARLED1();
	CLEAR12V();
}

void LatchSystemStruct()
{
	memcpy(&ops_temp_sys, &sys_ops, sizeof(struct SYS_OPS));
	memcpy(&data_temp_sys, &sys_data, sizeof(struct SYSTEM_DATA));
}

void SensorCovSystemInit()
{
	memcpy(&sc_start_ops, &ops_temp_sys, sizeof(struct SYS_OPS));
	StopWatchRestart(conv_watch_in_sys);
}

void PerformSystemChecks()
{
	//exit and stopwatch error if timeout
	if (isStopWatchComplete(conv_watch_in_sys) == 1)
	{
		ops_temp_sys.SystemFlags.bit.cov_error = 1;
	}
	else
	{
		ops_temp_sys.SystemFlags.bit.cov_error = 0;
	}

	if (ops_temp_sys.SystemFlags.all != 0)
	{
		SET12V();
	}
	else
	{
		CLEAR12V();
	}
}

void SaveOpStates()
{
	memcpy(&sys_data, &data_temp_sys, sizeof(struct SYSTEM_DATA));
}

void DetermineOpStates()
{
	if(sc_start_ops.State == sys_ops.State)
	{
		sys_ops.State = ops_temp_sys.State;
	}

	if(sc_start_ops.SystemFlags.all == sys_ops.SystemFlags.all)
	{
		//only cov error happens inside of conversion so all other changes are considered correct.
		//update accordingly to correct cov_errors
		sys_ops.SystemFlags.bit.cov_error = ops_temp_sys.SystemFlags.bit.cov_error;
	}
}
