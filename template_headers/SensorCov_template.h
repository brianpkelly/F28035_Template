/*
 * SensorCov_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#ifndef SENSORCOV_TEMPLATE_H_
#define SENSORCOV_TEMPLATE_H_

/**
 * Sets up the ADC, GPIO button, and LEDs. Also sets up the timer to determine if a conversion
 * took too long.
 */
void SystemSensorInit();

/**
 * Turns off the LEDs and 12V
 */
void SystemSensorDeInit();

/*
 * Latch System Struct
 */
void LatchSystemStruct();

/**
 * Saves the current system_ops_struct data stored to later determine if a outside change
 * occurred during sensor conversion.
 *
 * It is strongly recommended to perform similar operations on all user data and ops before
 * starting a sensor conversion.
 */
void SensorCovSystemInit();

/**
 * Determine if sensor conversion took too long to complete. If so, it triggers the system flag
 * cov_error and sets 12V.
 *
 * If a system flag is set, 12V is also set.
 */
void PerformSystemChecks();

/**
 * Saves the sensor conversion system data into a long time sys_data_struct. Should be called after
 * the sensor conversion is complete.
 */
void SaveOpStates();

/**
 * Determines the state of the MCN. If the state was changed during a sensor conversion, the MCN should
 * keep with that state change. If the state was not changed, the state determined in sensor conversion
 * should be applied.
 *
 * The check is done to system flags in this function.
 */
void DetermineOpStates();

#endif /* SENSORCOV_TEMPLATE_H_ */
