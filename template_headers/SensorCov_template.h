/*
 * SensorCov_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#ifndef SENSORCOV_TEMPLATE_H_
#define SENSORCOV_TEMPLATE_H_

void SystemSensorInit();
void SystemSensorDeInit();
void LatchSystemStruct();
void SensorCovSystemInit();
void PerformSystemChecks();
void SaveOpStates();
void DetermineOpStates();

#endif /* SENSORCOV_TEMPLATE_H_ */
