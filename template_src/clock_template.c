/*
 * clock_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#include "all.h"

struct CPUTIMER_VARS clock;
struct CPUTIMER_VARS CPUTimer2;
system_clock_struct Sys_ClockTicks;

void SystemClockSetup()
{
	clock.RegsAddr = &CpuTimer1Regs;
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
	clock.InterruptCount = 0;

	ConfigCpuTimer(&clock,CPU_FREQ_MHZ, SYSTEM_CLOCK_PERIOD);

	//pie interrupt
	IER |= M_INT13;

	ReloadCpuTimer1();
	StartCpuTimer1();
}

void InitializeCpuTimer2(float clock_period)
{
	CPUTimer2.RegsAddr = &CpuTimer2Regs;
	// Initialize timer period to maximum:
	CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;
	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
	CpuTimer2Regs.TPR.all  = 0;
	CpuTimer2Regs.TPRH.all = 0;
	// Make sure timers are stopped:
	CpuTimer2Regs.TCR.bit.TSS = 1;
	// Reload all counter register with period value:
	CpuTimer2Regs.TCR.bit.TRB = 1;
	// Reset interrupt counters:
	CPUTimer2.InterruptCount = 0;

	ConfigCpuTimer(&CPUTimer2, CPU_FREQ_MHZ, clock_period);

	//pie interrupt
	IER |= M_INT14;

	ReloadCpuTimer2();
	// Do not automatically start CPU Timer 2
	//StartCpuTimer2();
}

void ClockHeartbeat(int userFlags)
{
	Sys_ClockTicks.HeartBeat++;
	if (Sys_ClockTicks.HeartBeat >= HEARTBEAT_TICKS)
	{
		HeartBeat(userFlags);
		Sys_ClockTicks.HeartBeat = 0;
	}
}

void RestartCPUTimer1()
{
	ReloadCpuTimer1();
	StartCpuTimer1();
}

void RestartCpuTimer2()
{
	ReloadCpuTimer2();
	StartCpuTimer2();
}

void HeartBeat(int userFlags)
{
	FillHeartbeat(HEARTBEAT_BOX, userFlags);
}


