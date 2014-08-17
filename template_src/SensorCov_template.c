/*
 * SensorCov_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#include "all.h"

sys_ops_struct *ops_temp_sys, sc_start_ops;
sys_data_struct *data_temp_sys;
stopwatch_struct* conv_watch_in_sys;

void SystemSensorInit(sys_ops_struct *ops_pointer, sys_data_struct *data_pointer)
{
	ops_temp_sys = ops_pointer;
	data_temp_sys = data_pointer;
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
	conv_watch_in_sys = StartStopWatch(4);
}

void SystemSensorDeInit()
{
	StopStopWatch(conv_watch_in_sys);
	CLEARLED0();
	CLEARLED1();
	CLEAR12V();
}

void LatchStruct()
{
	memcpy(ops_temp_sys, &ops, sizeof(struct OPERATIONS));
	memcpy(data_temp_sys, &data, sizeof(struct SYSTEM_DATA));
}

void SensorCovSystemInit()
{
	memcpy(&sc_start_ops, ops_temp_sys, sizeof(struct OPERATIONS));
	StopWatchRestart(conv_watch_in_sys);
}

void PerformSystemMeasurements(stopwatch_struct *watch)
{
	data_temp_sys->adc = A0RESULT;

	data_temp_sys->gp_button = READGPBUTTON();

	if (data_temp_sys->gp_button == 0) 			//if pushed cause stopwatch
	{
		SETLED0();
		int i = 0;
		while (i < 100)
		{
			i++;
		}
	}
	else
	{
		CLEARLED0();
	}
	if (data_temp_sys->adc > 2000)
	{
		SETLED1();
	}
	else
	{
		CLEARLED1();
	}
	//exit and stopwatch error if timeout
	if (isStopWatchComplete(watch) == 1)
	{
		ops_temp_sys->SystemFlags.bit.cov_error = 1;
	}
	else
	{
		ops_temp_sys->SystemFlags.bit.cov_error = 0;
	}


	if (ops_temp_sys->SystemFlags.all != 0)
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
	memcpy(&data, data_temp_sys, sizeof(struct SYSTEM_DATA));
}

void DetermineOpStates()
{
	if(sc_start_ops.State == ops.State)
	{
		ops.State = ops_temp_sys->State;
	}

	if(sc_start_ops.SystemFlags.all == ops.SystemFlags.all)
	{
		//only cov error happens inside of conversion so all other changes are considered correct.
		//update accordingly to correct cov_errors
		ops.SystemFlags.bit.cov_error = ops_temp_sys->SystemFlags.bit.cov_error;
	}
}
