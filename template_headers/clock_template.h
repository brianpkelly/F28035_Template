/*
 * clock_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#ifndef CLOCK_TEMPLATE_H_
#define CLOCK_TEMPLATE_H_

void SystemClockSetup(struct CPUTIMER_VARS *clock, clock_struct *ticks);
void StartCPUTimer2(float clock_period);
void ClockHeartbeat();
void RestartCPUTimer1();
void RestartCpuTimer2();
void HeartBeat();


#endif /* CLOCK_TEMPLATE_H_ */
