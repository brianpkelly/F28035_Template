/*
 * clock_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#include "all.h"

struct CPUTIMER_VARS *ClockRef;
clock_struct *ClockTicks_Ref;

void SystemClockSetup(struct CPUTIMER_VARS *clock, clock_struct *ticks)
{
	ClockRef = clock;
	ClockTicks_Ref = ticks;
	ClockRef->RegsAddr = &CpuTimer1Regs;
	// Initialize timer period to maximum:
	CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
	CpuTimer1Regs.TPR.all  = 0;
	CpuTimer1Regs.TPRH.all = 0;
	// Make sure timer is stopped:
	CpuTimer1Regs.TCR.bit.TSS = 1;
	// Reload all counter register with period value:
	CpuTimer1Regs.TCR.bit.TRB = 1;
	// Reset interrupt counters:
	ClockRef->InterruptCount = 0;

	ConfigCpuTimer(ClockRef,CPU_FREQ_MHZ, CLOCK_PERIOD);

	//pie interrupt
	IER |= M_INT13;

	ReloadCpuTimer1();
	StartCpuTimer1();
}

void ClockHeartbeat()
{
	ClockTicks_Ref->HeartBeat++;
	if (ClockTicks_Ref->HeartBeat >= HEARTBEAT_TICKS)
	{
		HeartBeat();
		ClockTicks_Ref->HeartBeat = 0;
	}
}

void RestartCPUTimer1()
{
	ReloadCpuTimer1();
	StartCpuTimer1();
}

void HeartBeat()
{
	FillSendCAN(HEARTBEAT_BOX);
}
