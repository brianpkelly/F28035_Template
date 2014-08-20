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

void SystemClockSetup();
void InitializeCpuTimer2(float clock_period);
void ClockHeartbeat();
void RestartCPUTimer1();
void RestartCpuTimer2();
void HeartBeat();


#endif /* CLOCK_TEMPLATE_H_ */
