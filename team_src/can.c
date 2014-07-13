/*
 * can.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"

struct ECAN_REGS ECanaShadow;

void CANSetup()
{
	//System specific CAN setup
	SystemCANInit(&ECanaShadow);

	EALLOW;
	//MBOX 0 and 1
	CommandBoxInit();   // Mbox 0
	HeartbeatBoxInit(); // Mbox 1


	//SOMETHING ODD ABOUT ORDER HERE AND RTR BIT...

	//todo USER: Node specifc CAN setup
	// create mailbox for all Receive and transmit IDs
	// MBOX2 - MBOX31

	//adc TRANSMIT
	ECanaMboxes.MBOX2.MSGID.bit.IDE = 0; 	//standard id
	ECanaMboxes.MBOX2.MSGID.bit.AME = 0; 	// all bit must match
	ECanaMboxes.MBOX2.MSGID.bit.AAM = 1; 	//RTR AUTO TRANSMIT
	ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX2.MSGID.bit.STDMSGID = ADC_ID;
	ECanaShadow.CANMD.bit.MD2 = 0; 			//transmit
	ECanaShadow.CANME.bit.ME2 = 1;			//enable

	//gp_button TRANSMIT
	ECanaMboxes.MBOX3.MSGID.bit.IDE = 0; 	//standard id
	ECanaMboxes.MBOX3.MSGID.bit.AME = 0; 	// all bit must match
	ECanaMboxes.MBOX3.MSGID.bit.AAM = 1; 	//RTR AUTO TRANSMIT
	ECanaMboxes.MBOX3.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX3.MSGID.bit.STDMSGID = GP_BUTTON_ID;
	ECanaShadow.CANMD.bit.MD3 = 0; 			//transmit
	ECanaShadow.CANME.bit.ME3 = 1;			//enable

    EDIS;
    FinishCANInit();
}

char FillCAN(unsigned int Mbox)
{
	CopyMCToShadow(&ECanaShadow);
	//ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;

	//Try to fill heartbeat. If not heartbeat mailbox, see if it's a user mailbox
	if(FillSystemBoxes(Mbox) != 1)
	{
		//todo USER: setup for all transmit MBOXs

		return 0;
	}
	else
	{
		return 1;
	}
}

//todo SEAN: Determine if setting the ops flag can be in a system function. What if user removes that op?
//Another issue is if you put everything up until the stopWatchComplete into a system function, can_watch
//is no longer available
void SendCAN(unsigned int Mbox)
{
	EALLOW;
	// Check for bus off
	CopyMCToShadow(&ECanaShadow);
	//ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	CheckBusOff();
	CreateMask(Mbox);

	BeginTransmission();
	CheckForFlags();
	EDIS;
}


void FillCANData()
{
	//todo USER: use FillCAN to put data into correct mailboxes
	/*
	 * Examples:
	 *	FillCAN(ADC_BOX);
	 *  FillCAN(GP_BUTTON_BOX);
	 */
}



//todo SEAN: Determine how to handle this interrupt
// INT9.6
__interrupt void ECAN1INTA_ISR(void)  // eCAN-A
{
	Uint32 ops_id;
	Uint32 dummy;
  	unsigned int mailbox_nr;
  	mailbox_nr = getMailboxNR();
  	//todo USER: Setup ops command
  	if(mailbox_nr == COMMAND_BOX)
  	{
  		ReadCommand();
  	}
  	//todo USER: Setup other reads

  	//To receive more interrupts from this PIE group, acknowledge this interrupt
  	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
