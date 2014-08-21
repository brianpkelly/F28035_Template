/*
 * sys_op.h
 *
 *  Created on: May 23, 2014
 *      Author: Sean
 */

#ifndef SYS_OP_H_
#define SYS_OP_H_

//State defines
#define STATE_INIT 			0
#define STATE_SENSOR_COV 	1
#define STATE_BOOT			2
#define STATE_POWER_DOWN	3

#define OPS_ID_STATE 			0
#define OPS_ID_STOPWATCHERROR 	1

typedef struct SYS_FLAGS
{
	unsigned char cov_error : 1;
	unsigned char can_error : 1;
}sys_flags_struct;

typedef struct SYS_OPS
{
	unsigned long State;
	union SystemFlags
	{
	  int 						all;
	  sys_flags_struct			bit;
	}								SystemFlags;
} sys_ops_struct;

#endif /* SYS_OP_H_ */
