/*
 * Init.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "all.h"


sys_ops_struct ops;
sys_data_struct data;

void Initialize()
{
	OperationsSetup();
	DataSetup();
	SystemInit(10);
}



void OperationsSetup()
{
	//todo USER: OperationsSetup()
	//add here and ops.h
	ops.SystemFlags.all = 0;
	ops.State = STATE_SENSOR_COV;
}

void DataSetup()
{
	//todo USER: DataSetup()
	//add here and data.h
	data.adc = 0;
	data.gp_button = 0;
}

