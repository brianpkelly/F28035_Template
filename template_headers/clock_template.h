/*
 * clock_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#ifndef CLOCK_TEMPLATE_H_
#define CLOCK_TEMPLATE_H_

#define SYSTEM_CLOCK_PERIOD 500000 //uS //so half second
#define HEARTBEAT_TICKS		2	//1hz

typedef struct SYSTEM_CLOCK_TICKS
{
	int HeartBeat;
}system_clock_struct;

/**
 * Setups a clock with system clock settings.
 */
void SystemClockSetup();

/**
 * Initializes CPU timer 2 and enables the timer to trigger interrupt 14.
 * In order to start the timer, the user must call the function StartCpuTimer2()
 * or RestartCpuTimer2()
 *
 * Parameters:
 * 		clock_period - period of timer in us
 */
void InitializeCpuTimer2(float clock_period);

/**
 * Checks to see if the heartbeat has elapsed the set time to send.
 * If so, HeartBeat is called
 * 		userFlags - user flags to insert into the CAN heartbeat message
 */
void ClockHeartbeat();

/**
 * Restarts CPU Timer 1
 */
void RestartCPUTimer1();

/**
 * Restarts CPU Timer 2
 */
void RestartCpuTimer2();

/**
 * Simply calls the FillHeartbeat function located in can_template
 */
void HeartBeat();


#endif /* CLOCK_TEMPLATE_H_ */
