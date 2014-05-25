/*
 * SensorCov_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#ifndef SENSORCOV_TEMPLATE_H_
#define SENSORCOV_TEMPLATE_H_

void SensorConv();
void SystemSensorInit(sys_ops_struct *ops_pointer, sys_data_struct *data_pointer);
void SystemSensorDeInit();
void LatchStruct();
void SensorCovSystemInit();
void PerformSystemMeasurements();
unsigned int StateChangeFromInterrupt();
unsigned int FlagChangeFromInterrupt();

#endif /* SENSORCOV_TEMPLATE_H_ */
