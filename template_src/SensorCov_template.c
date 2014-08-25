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

/**
 * Sets up the ADC, GPIO button, and LEDs. Also sets up the timer to determine if a conversion
 * took too long.
 */
void SystemSensorInit()
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
	conv_watch_in_sys = StartStopWatch(4);
}

/**
 * Turns off the LEDs and clears... 12V?
 */
void SystemSensorDeInit()
{
	StopStopWatch(conv_watch_in_sys);
	CLEARLED0();
	CLEARLED1();
	CLEAR12V();
}

/*
 * Latch System Struct
 */
void LatchSystemStruct()
{
	memcpy(&ops_temp_sys, &sys_ops, sizeof(struct SYS_OPS));
	memcpy(&data_temp_sys, &sys_data, sizeof(struct SYSTEM_DATA));
}

/**
 * Saves the current system_ops_struct data stored to later determine if a outside change
 * occurred during sensor conversion.
 *
 * It is strongly recommended to perform similar operations on all user data and ops before
 * starting a sensor conversion.
 */
void SensorCovSystemInit()
{
	memcpy(&sc_start_ops, &ops_temp_sys, sizeof(struct SYS_OPS));
	StopWatchRestart(conv_watch_in_sys);
}

/**
 * Determine if sensor conversion took too long to complete. If so, it triggers the system flag
 * cov_error and sets 12V.
 *
 * If a system flag is set, 12V is also set.
 */
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

/**
 * Saves the sensor conversion system data into a long time sys_data_struct. Should be called after
 * the sensor conversion is complete.
 */
void SaveOpStates()
{
	memcpy(&sys_data, &data_temp_sys, sizeof(struct SYSTEM_DATA));
}

/**
 * Determines the state of the MCN. If the state was changed during a sensor conversion, the MCN should
 * keep with that state change. If the state was not changed, the state determined in sensor conversion
 * should be applied.
 *
 * The check is done to system flags in this function.
 */
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
