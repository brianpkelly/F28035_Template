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
	SetupSystemOperations();
}

void DataSetup()
{
	//todo USER: DataSetup()
	//add here and data.h
	SetupDataOperations();
}

