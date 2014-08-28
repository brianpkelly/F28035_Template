/*
 * Init_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */
#include "all.h"

sys_ops_struct sys_ops;
sys_data_struct sys_data;

void SetupSystemOperations()
{
	sys_ops.SystemFlags.all = 0;
	sys_ops.State = STATE_SENSOR_COV;
}

