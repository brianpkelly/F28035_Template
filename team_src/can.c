/*
 * can.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"

stopwatch_struct* can_watch;
struct ECAN_REGS ECanaShadow;
unsigned long mask;

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
	can_watch = StartStopWatch(SENDCAN_STOPWATCH);
}

/*
void ClearMailBoxes()
{
    ECanaMboxes.MBOX0.MDH.all = 0;
    ECanaMboxes.MBOX0.MDL.all = 0;
    ECanaMboxes.MBOX1.MDH.all = 0;
    ECanaMboxes.MBOX1.MDL.all = 0;
    ECanaMboxes.MBOX2.MDH.all = 0;
    ECanaMboxes.MBOX2.MDL.all = 0;
    ECanaMboxes.MBOX3.MDH.all = 0;
    ECanaMboxes.MBOX3.MDL.all = 0;
    ECanaMboxes.MBOX4.MDH.all = 0;
    ECanaMboxes.MBOX4.MDL.all = 0;
    ECanaMboxes.MBOX5.MDH.all = 0;
    ECanaMboxes.MBOX5.MDL.all = 0;
    ECanaMboxes.MBOX6.MDH.all = 0;
    ECanaMboxes.MBOX6.MDL.all = 0;
    ECanaMboxes.MBOX7.MDH.all = 0;
    ECanaMboxes.MBOX7.MDL.all = 0;
    ECanaMboxes.MBOX8.MDH.all = 0;
    ECanaMboxes.MBOX8.MDL.all = 0;
    ECanaMboxes.MBOX9.MDH.all = 0;
    ECanaMboxes.MBOX9.MDL.all = 0;
    ECanaMboxes.MBOX10.MDH.all = 0;
    ECanaMboxes.MBOX10.MDL.all = 0;
    ECanaMboxes.MBOX11.MDH.all = 0;
    ECanaMboxes.MBOX11.MDL.all = 0;
    ECanaMboxes.MBOX12.MDH.all = 0;
    ECanaMboxes.MBOX12.MDL.all = 0;
    ECanaMboxes.MBOX13.MDH.all = 0;
    ECanaMboxes.MBOX13.MDL.all = 0;
    ECanaMboxes.MBOX14.MDH.all = 0;
    ECanaMboxes.MBOX14.MDL.all = 0;
    ECanaMboxes.MBOX15.MDH.all = 0;
    ECanaMboxes.MBOX15.MDL.all = 0;
    ECanaMboxes.MBOX16.MDH.all = 0;
    ECanaMboxes.MBOX16.MDL.all = 0;
    ECanaMboxes.MBOX17.MDH.all = 0;
    ECanaMboxes.MBOX17.MDL.all = 0;
    ECanaMboxes.MBOX18.MDH.all = 0;
    ECanaMboxes.MBOX18.MDL.all = 0;
    ECanaMboxes.MBOX19.MDH.all = 0;
    ECanaMboxes.MBOX19.MDL.all = 0;
    ECanaMboxes.MBOX20.MDH.all = 0;
    ECanaMboxes.MBOX20.MDL.all = 0;
    ECanaMboxes.MBOX21.MDH.all = 0;
    ECanaMboxes.MBOX21.MDL.all = 0;
    ECanaMboxes.MBOX22.MDH.all = 0;
    ECanaMboxes.MBOX22.MDL.all = 0;
    ECanaMboxes.MBOX23.MDH.all = 0;
    ECanaMboxes.MBOX23.MDL.all = 0;
    ECanaMboxes.MBOX24.MDH.all = 0;
    ECanaMboxes.MBOX24.MDL.all = 0;
    ECanaMboxes.MBOX25.MDH.all = 0;
    ECanaMboxes.MBOX25.MDL.all = 0;
    ECanaMboxes.MBOX26.MDH.all = 0;
    ECanaMboxes.MBOX26.MDL.all = 0;
    ECanaMboxes.MBOX27.MDH.all = 0;
    ECanaMboxes.MBOX27.MDL.all = 0;
    ECanaMboxes.MBOX28.MDH.all = 0;
    ECanaMboxes.MBOX28.MDL.all = 0;
    ECanaMboxes.MBOX29.MDH.all = 0;
    ECanaMboxes.MBOX30.MDL.all = 0;
    ECanaMboxes.MBOX30.MDH.all = 0;
    ECanaMboxes.MBOX31.MDL.all = 0;
    ECanaMboxes.MBOX31.MDH.all = 0;
}
*/
char FillCAN(unsigned int Mbox)
{
	CopyMCToShadow(&ECanaShadow);
	//ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;

	//Try to fill heartbeat. If not heartbeat mailbox, see if it's a user mailbox
	if(FillHeartbeat(Mbox) != 1)
	{
		//todo USER: setup for all transmit MBOXs
		switch (Mbox)								//choose mailbox
		{
			case ADC_BOX:
				EALLOW;
				ECanaShadow.CANMC.bit.MBNR = Mbox;
				ECanaShadow.CANMC.bit.CDR = 1;
				ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
				ECanaMboxes.MBOX2.MDH.all = 0;
				ECanaMboxes.MBOX2.MDL.all = 0;
				ECanaMboxes.MBOX2.MDL.all = data.adc;
				ECanaShadow.CANMC.bit.CDR = 0;
				ECanaShadow.CANMC.bit.MBNR = 0;
				ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
				EDIS;
				return 1;
			case GP_BUTTON_BOX:
				EALLOW;
				ECanaShadow.CANMC.bit.MBNR = Mbox;
				ECanaShadow.CANMC.bit.CDR = 1;
				ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
				ECanaMboxes.MBOX3.MDH.all = 0;
				ECanaMboxes.MBOX3.MDL.all = 0;
				ECanaMboxes.MBOX3.MDL.all = data.gp_button;
				ECanaShadow.CANMC.bit.CDR = 0;
				ECanaShadow.CANMC.bit.MBNR = 0;
				ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
				EDIS;
				return 1;
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
void FillSendCAN(unsigned Mbox)
{
	if (FillCAN(Mbox) == 1)
	{
		SendCAN(Mbox);
	}
}
*/
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
	mask = CreateMask(Mbox);

	//todo Nathan: calibrate sendcan stopwatch
	StopWatchRestart(can_watch);

	do{ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;}
	while(((ECanaShadow.CANTA.all & mask) != mask) && (isStopWatchComplete(can_watch) == 0)); //wait to send or hit stop watch

	ClearFlags();

	//recommended USER: Check for stopwatch flag to determine if there's a CAN error
	if (isStopWatchComplete(can_watch) == 1)					//if stopwatch flag
	{
		ops.SystemFlags.bit.can_error = 1;
	}
	else if (ops.SystemFlags.bit.can_error == 1)		//if no stopwatch and flagged reset
	{
		ops.SystemFlags.bit.can_error = 0;
	}
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
