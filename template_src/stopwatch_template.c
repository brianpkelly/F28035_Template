/*
 * stopwatch.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */

#include "all.h"
#include "DSP2803x_CpuTimers.h"

struct CPUTIMER_VARS StopWatch;

/**
 * Configures CPU0 to be used for all stopwatches.
 * 		time: period for the CPU clock in uSeconds
 */
void StopWatchSetUp(float time)
{
    // CPU Timer0
	// Initialize address pointers to respective timer registers:
	StopWatch.RegsAddr = &CpuTimer0Regs;
	// Initialize timer period to maximum:
	CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
	CpuTimer0Regs.TPR.all  = 0;
	CpuTimer0Regs.TPRH.all = 0;
	// Make sure timer is stopped:
	CpuTimer0Regs.TCR.bit.TSS = 1;
	// Reload all counter register with period value:
	CpuTimer0Regs.TCR.bit.TRB = 1;
	// Reset interrupt counters:
	StopWatch.InterruptCount = 0;

	ConfigCpuTimer(&StopWatch,CPU_FREQ_MHZ , time);

	//pie interrupt
	IER |= M_INT1;
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	ReloadCpuTimer0();
	StartCpuTimer0();
}

/**
 * Starts the stopwatch for x amount of seconds
 * 		time: time to run the stopwatch for in seconds.
 *
 * Returns a pointer to a new stopwatch with the corresponding end time.
 */
stopwatch_struct* StartStopWatch(unsigned int time)
{
	stopwatch_struct* watch = (stopwatch_struct*)myMalloc(sizeof(stopwatch_struct));
	watch->Start = StopWatch.InterruptCount;
	watch->Time = time;
	watch->StopwatchComplete = 0;
	return watch;
}

/**
 * Restarts the stopwatch so that the time is 0.
 */
void StopWatchRestart(stopwatch_struct* watch)
{
	watch->Start = StopWatch.InterruptCount;
	watch->StopwatchComplete = 0;
}

/**
 * Checks whether the stopwatch has reached it's end time.
 *
 * Returns 1 if the stopwatch is complete and 0 if it isn't
 */
char isStopWatchComplete(stopwatch_struct* watch)
{
	if((StopWatch.InterruptCount - watch->Start) >= watch->Time)
	{
		watch->StopwatchComplete = 1;
	}
	return watch->StopwatchComplete;
}

/**
 * Stops and destroys the stopwatch from memory. The stopwatch can no longer be used
 * after this function is called.
 */
void StopStopWatch(stopwatch_struct* watch)
{
	myFree(watch);
}

// INT1.7
__interrupt void  TINT0_ISR(void)      // CPU-Timer 0
{
	StopWatch.InterruptCount++;
   // Acknowledge this interrupt to receive more interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
