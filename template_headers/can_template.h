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
void CopyMCToShadow();
unsigned int getMailboxNR();
char FillHeartbeat(unsigned int Mbox, unsigned int userFlags);
void CheckBusOff();
void CreateMask(unsigned int Mbox);
void ReadCommand();
void CheckForFlags();
void BeginTransmission();

int CreateCANMailbox(int mailboxNum, int IDE, int AME, int AAM, int DLC, int STDMSGID, int Mode);
int InsertCANMessage(int Mbox, unsigned int MDH, unsigned int MDL);

#define COMMAND_BOX 	0
#define HEARTBEAT_BOX 	1
#define COMMAND_ID 		0x1
#define HEARTBEAT_ID 	0x0

#endif /* CAN_TEMPLATE_H_ */
