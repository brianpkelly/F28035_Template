/*
 * clock_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#ifndef CLOCK_TEMPLATE_H_
#define CLOCK_TEMPLATE_H_

void SystemClockSetup(clock_struct *ticks);
void ClockHeartbeat();
void RestartCPUTimer1();
void HeartBeat();


#endif /* CLOCK_TEMPLATE_H_ */
