/*
 * clock_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#include "all.h"

struct CPUTIMER_VARS *ClockRef;
struct CPUTIMER_VARS CPUTimer2;
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

/*
 * Initializes CPU timer 2 and enables the timer to trigger interrupt 14.
 * In order to start the timer, the user must call the function StartCpuTimer2()
 * or RestartCpuTimer2()
 *
 * Parameters:
 * 		clock_period - period of timer in us
 */
void StartCPUTimer2(float clock_period)
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

void RestartCpuTimer2()
{
	ReloadCpuTimer2();
	StartCpuTimer2();
}

void HeartBeat()
{
	FillSendCAN(HEARTBEAT_BOX);
}
