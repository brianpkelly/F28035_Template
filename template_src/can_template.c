/*
 * can_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */
#include "can_template.h"
#include "all.h"

struct ECAN_REGS *SystemShadow;

unsigned long system_mask;


void SystemCANInit(struct ECAN_REGS *UserShadow)
{
	EALLOW;
	InitECanaGpio();
	InitECana();

	ClearMailBoxes();
	//Points SystemShadow to the shadow struct in can.c
	SystemShadow = UserShadow;

	SystemShadow->CANMIM.all = 0;
	SystemShadow->CANMIL.all = 0;
	SystemShadow->CANGIM.all = 0;
	SystemShadow->CANGAM.bit.AMI = 0; //must be standard
	SystemShadow->CANGIM.bit.I1EN = 1;  // enable I1EN
	SystemShadow->CANMD.all = ECanaRegs.CANMD.all;
	SystemShadow->CANME.all = ECanaRegs.CANME.all;
	EDIS;
}

void CommandBoxInit()
{
	EALLOW;
	//Command RECEIVE
	ECanaMboxes.MBOX0.MSGID.bit.IDE = 0; 	//standard id
	ECanaMboxes.MBOX0.MSGID.bit.AME = 0;	// all bit must match
	ECanaMboxes.MBOX0.MSGID.bit.AAM = 0; 	// no RTR AUTO TRANSMIT
	ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX0.MSGID.bit.STDMSGID = COMMAND_ID;
	SystemShadow->CANMD.bit.MD0 = 1;			//receive
	SystemShadow->CANME.bit.ME0 = 1;			//enable
	SystemShadow->CANMIM.bit.MIM0  = 1; 		//int enable
	SystemShadow->CANMIL.bit.MIL0  = 1;  		// Int.-Level MB#0  -> I1EN
	EDIS;
}

void HeartbeatBoxInit()
{
	EALLOW;
	//Heart TRANSMIT
	ECanaMboxes.MBOX1.MSGID.bit.IDE = 0; 	//standard id
	ECanaMboxes.MBOX1.MSGID.bit.AME = 0; 	// all bit must match
	ECanaMboxes.MBOX1.MSGID.bit.AAM = 1; 	//RTR AUTO TRANSMIT
	ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX1.MSGID.bit.STDMSGID = HEARTBEAT_ID;
	SystemShadow->CANMD.bit.MD1 = 0; 			//transmit
	SystemShadow->CANME.bit.ME1 = 1;			//enable
	EDIS;
}

void FinishCANInit()
{
	EALLOW;
	ECanaRegs.CANGAM.all = SystemShadow->CANGAM.all;
	ECanaRegs.CANGIM.all = SystemShadow->CANGIM.all;
	ECanaRegs.CANMIM.all = SystemShadow->CANMIM.all;
	ECanaRegs.CANMIL.all = SystemShadow->CANMIL.all;
	ECanaRegs.CANMD.all = SystemShadow->CANMD.all;
	ECanaRegs.CANME.all = SystemShadow->CANME.all;
	SystemShadow->CANMC.all = ECanaRegs.CANMC.all;
	SystemShadow->CANMC.bit.STM = 0;    // No self-test mode
	ECanaRegs.CANMC.all = SystemShadow->CANMC.all;
	EDIS;

	//ENABLE PIE INTERRUPTS
	IER |= M_INT9;
	PieCtrlRegs.PIEIER9.bit.INTx6= 1;
}

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



void FillSendCAN(unsigned Mbox)
{
	if (FillCAN(Mbox) == 1)
	{
		SendCAN(Mbox);
	}
}

void BUS_OFF()
{
    EALLOW;
    SystemShadow->CANMC.all = ECanaRegs.CANMC.all;


    SystemShadow->CANMC.bit.CCR = 0;
    ECanaRegs.CANMC.all = SystemShadow->CANMC.all;

    SystemShadow->CANES.all = ECanaRegs.CANES.all;
    while (SystemShadow->CANES.bit.CCE != 0)
    {
        SystemShadow->CANES.all = ECanaRegs.CANES.all;
    }

    EDIS;
}

//todo SEAN: Test whether this is correct
void CopyMCToShadow(struct ECAN_REGS *SystemShadow)
{
	SystemShadow->CANMC.all = ECanaRegs.CANMC.all;
}

unsigned int getMailboxNR()
{
	SystemShadow->CANGIF1.bit.MIV1 =  ECanaRegs.CANGIF1.bit.MIV1;
	unsigned int mailbox_nr;
	mailbox_nr = SystemShadow->CANGIF1.bit.MIV1;
	return mailbox_nr;
}
int FillHeartbeat(unsigned int Mbox)
{
	if(Mbox == HEARTBEAT_BOX)
	{
		//todo Nathan define heartbeat
		EALLOW;
		SystemShadow->CANMC.bit.MBNR = Mbox;
		SystemShadow->CANMC.bit.CDR = 1;
		ECanaRegs.CANMC.all = SystemShadow->CANMC.all;
		ECanaMboxes.MBOX1.MDH.all = 0;
		ECanaMboxes.MBOX1.MDL.all = 0;
		ECanaMboxes.MBOX1.MDH.all = ops.UserFlags.all;
		ECanaMboxes.MBOX1.MDL.all = ops.SystemFlags.all;
		SystemShadow->CANMC.bit.MBNR = 0;
		SystemShadow->CANMC.bit.CDR = 0;
		ECanaRegs.CANMC.all = SystemShadow->CANMC.all;
		EDIS;
		return 1;
	}
	else
		return 0;
}

void CheckBusOff()
{
	if (SystemShadow->CANMC.bit.CCR == 1)
	{
		BUS_OFF();
	}
}

unsigned long CreateMask(unsigned int Mbox)
{
	// 1UL so there's a mask for at least 32 mailboxes
	system_mask = 1UL << Mbox;
	SystemShadow->CANTRS.all = system_mask;
	ECanaRegs.CANTRS.all = SystemShadow->CANTRS.all;
	return system_mask;
}
/*
 * Clears the transmission acknowledgment bit after a message has been sent.
 * This must be done before another message can be sent.
 */
void ClearFlags()
{
	ECanaRegs.CANTA.all = system_mask;						//clear flag
}

void ReadCommand()
{
	Uint32 ops_id;
	Uint32 dummy;

	//todo Nathan: Define Command frame
	//proposed:
	//HIGH 4 BYTES = Uint32 ID
	//LOW 4 BYTES = Uint32 change to
	ops_id = ECanaMboxes.MBOX0.MDH.all;
	dummy = ECanaMboxes.MBOX0.MDL.all;
	switch (ops_id)
	{
	case OPS_ID_STATE:
		memcpy(&ops.State,&dummy,sizeof ops.State);
		break;
	case OPS_ID_STOPWATCHERROR:
		memcpy(&ops.SystemFlags.all,&dummy,sizeof ops.SystemFlags.all);
		break;
	}

	ECanaRegs.CANRMP.bit.RMP0 = 1;
}
