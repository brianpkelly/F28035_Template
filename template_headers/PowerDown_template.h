/*
 * PowerDown_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#ifndef POWERDOWN_TEMPLATE_H_
#define POWERDOWN_TEMPLATE_H_

/**
 * Performs system specific power down operations
 */
void SystemPowerDown();

/**
 * Returns whether there is power. A returned value of 1 corresponds to no power
 * and a returned value of 0 means there is power.
 */
char isPowerOn();

/**
 * Initializes a interrupt to trigger once the input voltage has dropped too low.
 */
void PowerDownISRSetup();

/**
 * Starts the power down interrupt
 */
void StartPowerDownInt();

#define COMPVOLTAGE 	1.9
#define VDDA			3.0
#define VSSA			0.0

#endif /* POWERDOWN_TEMPLATE_H_ */
