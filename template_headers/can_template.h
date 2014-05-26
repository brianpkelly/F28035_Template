/*
 * can_template.h
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */
#include "all.h"
#ifndef CAN_TEMPLATE_H_
#define CAN_TEMPLATE_H_

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
int FillHeartbeat(unsigned int Mbox);
void CheckBusOff();
unsigned long CreateMask(unsigned int Mbox);
void ClearFlags();
void ReadCommand();

int CreateCANMailbox(int mailboxNum, int IDE, int AME, int AAM, int DLC, int STDMSGID, int Mode);
int InsertCANMessage(Mbox, MDH, MDL);

#define COMMAND_BOX 	0
#define HEARTBEAT_BOX 	1

#endif /* CAN_TEMPLATE_H_ */
