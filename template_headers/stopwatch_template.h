/*
 * stopwatch.h
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

typedef struct StopWatch
{
	Uint32 StopwatchComplete;
	Uint32 Start;
	unsigned long Time;
}stopwatch_struct;

/**
 * Configures CPU0 to be used for all stopwatches.
 * 		time: period for the CPU clock in uSeconds
 */
void StopWatchSetUp(float time);

/**
 * Starts the stopwatch for x amount of seconds
 * 		time: time to run the stopwatch for in seconds.
 *
 * Returns a pointer to a new stopwatch with the corresponding end time.
 */
stopwatch_struct* StartStopWatch(unsigned int time);

/**
 * Checks whether the stopwatch has reached it's end time.
 *
 * Returns 1 if the stopwatch is complete and 0 if it isn't
 */
char isStopWatchComplete(stopwatch_struct*);

/**
 * Stops and destroys the stopwatch from memory. The stopwatch can no longer be used
 * after this function is called.
 */
void StopStopWatch(stopwatch_struct* watch);

/**
 * Restarts the stopwatch so that the time is 0.
 */
void StopWatchRestart(stopwatch_struct* watch);


#define SENDCAN_STOPWATCH 	50 //100 uS

#endif /* STOPWATCH_H_ */
