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

/**
 * Initializes CAN for a MCN
 *     UserShadow - A shadow register the user is using in order to modify
 *     the MCN registers.
 */
void SystemCANInit(struct ECAN_REGS *UserShadow);

/**
 * Initializes the command CAN mailbox as mailbox 0.
 *
 * IMPORTANT: DO NOT REASSIGN MAILBOX 0
 */
void CommandBoxInit();

/**
 * Initializes the heartbeat CAN mailbox as mailbox 1
 *
 * IMPORTANT: DO NOT REASSIGN MAILBOX 1
 */
void HeartbeatBoxInit();

/**
 * Finishes initializing the CAN interface. Should be called once all mailboxes
 * have been defined and initialized.
 */
void FinishCANInit();

/**
 * Clears the data in all 32 available mailboxes
 */
void ClearMailBoxes();

//void FillSendCAN(unsigned int Mbox);

/**
 * Restarts the CAN module to be BUS_ON
 */
void BUS_OFF();

/**
 * Copies the current MCN registers to shadow registers that can be modified freely.
 */
void CopyMCToShadow();

/**
 * Determines the mailbox number a received message was placed into
 *
 * Returns: The mailbox number the received message was placed into
 */
unsigned int getMailboxNR();

/**
 * If the Mbox parameter matches the mailbox number, the heartbeat mailbox is filled
 * with the system and users flags passed into the function
 *      Mbox: Current mailbox to be filled. This mailbox is checked against the heartbeat
 *      mailbox # to determine if the mailbox passed should be filled with the heartbeat message
 *      userFlags: User defined flags to send in the heartbeat
 *
 * Returns 1 if the heartbeat was placed into the mailbox and 0 if the Mbox did not match
 * the heartbeat box number.
 */
char FillHeartbeat(unsigned int Mbox, unsigned int userFlags);

/**
 * Checks to determine if the bus-off condition has been triggered
 */
void CheckBusOff();

/**
 * Keeps track of the mailboxes with data that needs to be sent. The Mbox
 * passed into the function is the mailbox number which has data ready to be sent.
 *      Mbox: mailbox to add to the current list of mailboxes to send
 */
void CreateMask(unsigned int Mbox);

/**
 * Reads an incoming command frame and changes the system state and flags
 * depending on the incoming message contents
 */
void ReadCommand();

/**
 * Checks to determine whether the sensor conversion took longer than the time passed
 * to the SystemSensorInit function. If so, a system CAN flag is set to 1.
 */
void CheckForFlags();

/**
 * Starts sending mailboxes that have been flagged in the mask
 */
void BeginTransmission();

/*
 * Creates a new CAN mailbox with the following options the user must pass:
 * 		mailboxNum: Mailbox number. 1 < mailboxNum < 32. Mailbox 0 - 1 are reserved.
 * 		IDE: Identifier extensive bit. Check TI documents for more details. Must be 1 or 0. Usually 0
 * 		AME: Acceptance mask enable bit. 0 means all identifier bits must match, 1 means use acceptance mask
 * 		AAM: Auto answer mode bit. 1 is auto-answer, 0 is normal transmit mode.
 * 		DLC: Data length code. Number of bytes to receive or send. The max is 8 bytes.
 * 		STDMSGID: Mailbox ID
 * 		Mode: 0 is send, 1 is receive
 *
 * 	If a mailbox is successfully created, 1 is returned. If there's a problem with the parameters,
 * 	a 0 is returned.
 */
int CreateCANMailbox(int mailboxNum, int IDE, int AME, int AAM, int DLC, int STDMSGID, int Mode);

/*
 *  Performs all the required registry calls to place data into a CAN message
 * 		Mbox: the mailbox to place the message into (1 < Mbox < 32)
 * 		MDH: The high 32 bit portion of the CAN message
 * 		MDL: The low 32 bit portion of the CAN message
 *
 *  Refer to the TI documentation to see how the low and high portion of a
 *  CAN message is laid out.
 *
 *  Returns 1 if message was inserted successfully and 0 if not.
 */
int InsertCANMessage(int Mbox, unsigned int MDH, unsigned int MDL);

#define COMMAND_BOX 	0
#define HEARTBEAT_BOX 	1
#define COMMAND_ID 		0x1
#define HEARTBEAT_ID 	0x0

#endif /* CAN_TEMPLATE_H_ */
