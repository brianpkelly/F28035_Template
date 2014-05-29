/*
 * can_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */
#include "all.h"
#ifndef CAN_TEMPLATE_H_
#define CAN_TEMPLATE_H_

struct CANmsg {
   char MBox;
   union CANMSGCTRL_REG   MSGCTRL;
   union CANMDL_REG       MDL;
   union CANMDH_REG       MDH;
};

struct TRS_REG {
	union CANTRS_REG	TRS;
};

void SystemCANInit(struct ECAN_REGS *UserShadow);
void CommandBoxInit();
void HeartbeatBoxInit();
void FinishCANInit();
void ClearMailBoxes();
void FillSendCAN(unsigned int Mbox);
void SendMailBoxes(unsigned int Mbox);
void BUS_OFF();
void CopyMCToShadow(struct ECAN_REGS *ECanaShadow);
unsigned int getMailboxNR();
char FillSystemBoxes(unsigned int Mbox);
void CheckBusOff();
void CreateMask(unsigned int Mbox);
void ReadCommand();
void CheckForFlags();
void BeginTransmission();

#define COMMAND_BOX 	0
#define HEARTBEAT_BOX 	1
#define COMMAND_ID 		0x1
#define HEARTBEAT_ID 	0x0

#define ADC_ID 			0x2
#define ADC_BOX 		2
#define ADC_TRS			TRS2

#define GP_BUTTON_ID 	0x3
#define GP_BUTTON_BOX 	3
#define GP_BUTTON_TRS	TRS3

#endif /* CAN_TEMPLATE_H_ */
