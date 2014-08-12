/*
 * PowerDown_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#ifndef POWERDOWN_TEMPLATE_H_
#define POWERDOWN_TEMPLATE_H_

void SystemPowerDown();
void NodePowerDown();
char isPowerOn();
void PowerDownISRSetup();
void StartPowerDownInt();

#define COMPVOLTAGE 	1.9
#define VDDA			3.0
#define VSSA			0.0

#endif /* POWERDOWN_TEMPLATE_H_ */
