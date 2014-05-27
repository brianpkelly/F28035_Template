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
		ECanaMboxes.MBOX1.MDL.word.LOW_WORD = ops.SystemFlags.all;
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

/*
 * Creates a new CAN mailbox with the following options the user must pass:
 * 		mailboxNum: Mailbox number. 1 < mailboxNum < 32. Mailbox 1 and 2 are reserved.
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
int CreateCANMailbox(int mailboxNum, int IDE, int AME, int AAM, int DLC, int STDMSGID, int Mode)
{
	// Perform checks to make sure user doesn't set registers to an out-of-bounds number
	if(IDE > 1 || IDE < 0)
		return 0;
	if(AME > 1 || AME < 0)
		return 0;
	if(AAM > 1 || AME < 0)
		return 0;
	if(DLC > 8 || DLC < 0)
		return 0;

	switch(mailboxNum)
	{
	case 2:
		ECanaMboxes.MBOX2.MSGID.bit.IDE = IDE; 	//standard id
		ECanaMboxes.MBOX2.MSGID.bit.AME = AME; 	// all bit must match
		ECanaMboxes.MBOX2.MSGID.bit.AAM = AAM; 	//RTR AUTO TRANSMIT
		ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX2.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD2 = Mode; 			//transmit or receive
		SystemShadow->CANME.bit.ME2 = 1;			//enable
		return 1;
	case 3:
		ECanaMboxes.MBOX3.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX3.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX3.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX3.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX3.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD3 = Mode;
		SystemShadow->CANME.bit.ME3 = 1;
		return 1;
	case 4:
		ECanaMboxes.MBOX4.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX4.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX4.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX4.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX4.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD4 = Mode;
		SystemShadow->CANME.bit.ME4 = 1;
		return 1;
	case 5:
		ECanaMboxes.MBOX5.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX5.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX5.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX5.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX5.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD5 = Mode;
		SystemShadow->CANME.bit.ME5 = 1;
		return 1;
	case 6:
		ECanaMboxes.MBOX6.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX6.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX6.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX6.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX6.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD6 = Mode;
		SystemShadow->CANME.bit.ME6 = 1;
		return 1;
	case 7:
		ECanaMboxes.MBOX7.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX7.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX7.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX7.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX7.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD7 = Mode;
		SystemShadow->CANME.bit.ME7 = 1;
		return 1;
	case 8:
		ECanaMboxes.MBOX8.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX8.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX8.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX8.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX8.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD8 = Mode;
		SystemShadow->CANME.bit.ME8 = 1;
		return 1;
	case 9:
		ECanaMboxes.MBOX9.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX9.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX9.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX9.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX9.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD9 = Mode;
		SystemShadow->CANME.bit.ME9 = 1;
		return 1;
	case 10:
		ECanaMboxes.MBOX10.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX10.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX10.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX10.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX10.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD10 = Mode;
		SystemShadow->CANME.bit.ME10 = 1;
		return 1;
	case 11:
		ECanaMboxes.MBOX11.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX11.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX11.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX11.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX11.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD11 = Mode;
		SystemShadow->CANME.bit.ME11 = 1;
		return 1;
	case 12:
		ECanaMboxes.MBOX12.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX12.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX12.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX12.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX12.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD12 = Mode;
		SystemShadow->CANME.bit.ME12 = 1;
		return 1;
	case 13:
		ECanaMboxes.MBOX13.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX13.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX13.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX13.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX13.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD13 = Mode;
		SystemShadow->CANME.bit.ME13 = 1;
		return 1;
	case 14:
		ECanaMboxes.MBOX14.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX14.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX14.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX14.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX14.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD14 = Mode;
		SystemShadow->CANME.bit.ME14 = 1;
		return 1;
	case 15:
		ECanaMboxes.MBOX15.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX15.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX15.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX15.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX15.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD15 = Mode;
		SystemShadow->CANME.bit.ME15 = 1;
		return 1;
	case 16:
		ECanaMboxes.MBOX16.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX16.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX16.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX16.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX16.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD16 = Mode;
		SystemShadow->CANME.bit.ME16 = 1;
		return 1;
	case 17:
		ECanaMboxes.MBOX17.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX17.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX17.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX17.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX17.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD17 = Mode;
		SystemShadow->CANME.bit.ME17 = 1;
		return 1;
	case 18:
		ECanaMboxes.MBOX18.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX18.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX18.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX18.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX18.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD18 = Mode;
		SystemShadow->CANME.bit.ME18 = 1;
		return 1;
	case 19:
		ECanaMboxes.MBOX19.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX19.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX19.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX19.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX19.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD19 = Mode;
		SystemShadow->CANME.bit.ME19 = 1;
		return 1;
	case 20:
		ECanaMboxes.MBOX20.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX20.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX20.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX20.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX20.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD20 = Mode;
		SystemShadow->CANME.bit.ME20 = 1;
		return 1;
	case 21:
		ECanaMboxes.MBOX21.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX21.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX21.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX21.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX21.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD21 = Mode;
		SystemShadow->CANME.bit.ME21 = 1;
		return 1;
	case 22:
		ECanaMboxes.MBOX22.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX22.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX22.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX22.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX22.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD22 = Mode;
		SystemShadow->CANME.bit.ME22 = 1;
		return 1;
	case 23:
		ECanaMboxes.MBOX23.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX23.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX23.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX23.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX23.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD23 = Mode;
		SystemShadow->CANME.bit.ME23 = 1;
		return 1;
	case 24:
		ECanaMboxes.MBOX24.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX24.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX24.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX24.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX24.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD24 = Mode;
		SystemShadow->CANME.bit.ME24 = 1;
		return 1;
	case 25:
		ECanaMboxes.MBOX25.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX25.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX25.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX25.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX25.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD25 = Mode;
		SystemShadow->CANME.bit.ME25 = 1;
		return 1;
	case 26:
		ECanaMboxes.MBOX26.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX26.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX26.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX26.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX26.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD26 = Mode;
		SystemShadow->CANME.bit.ME26 = 1;
		return 1;
	case 27:
		ECanaMboxes.MBOX27.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX27.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX27.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX27.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX27.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD27 = Mode;
		SystemShadow->CANME.bit.ME27 = 1;
		return 1;
	case 28:
		ECanaMboxes.MBOX28.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX28.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX28.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX28.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX28.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD28 = Mode;
		SystemShadow->CANME.bit.ME28 = 1;
		return 1;
	case 29:
		ECanaMboxes.MBOX29.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX29.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX29.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX29.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX29.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD29 = Mode;
		SystemShadow->CANME.bit.ME29 = 1;
		return 1;
	case 30:
		ECanaMboxes.MBOX30.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX30.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX30.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX30.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX30.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD30 = Mode;
		SystemShadow->CANME.bit.ME30 = 1;
		return 1;
	case 31:
		ECanaMboxes.MBOX31.MSGID.bit.IDE = IDE;
		ECanaMboxes.MBOX31.MSGID.bit.AME = AME;
		ECanaMboxes.MBOX31.MSGID.bit.AAM = AAM;
		ECanaMboxes.MBOX31.MSGCTRL.bit.DLC = DLC;
		ECanaMboxes.MBOX31.MSGID.bit.STDMSGID = STDMSGID;
		SystemShadow->CANMD.bit.MD31 = Mode;
		SystemShadow->CANME.bit.ME31 = 1;
		return 1;
	default:
		return 0;
	}
}

/*
 *  Performs all the required registry calls to place data into a CAN message
 * 		Mbox: the mailbox to place the message into
 * 		MDH: The high 32 bit portion of the CAN message
 * 		MDL: The low 32 bit portion of the CAN message
 *
 *  Refer to the TI documentation to see how the low and high portion of a
 *  CAN message is laid out.
 *
 *  Returns 1 if message was inserted successfully and 0 if not.
 */
int InsertCANMessage(int Mbox, unsigned int MDH, unsigned int MDL)
{
	int result = 1;
	EALLOW;
	SystemShadow->CANMC.bit.MBNR = Mbox;
	SystemShadow->CANMC.bit.CDR = 1;
	ECanaRegs.CANMC.all = SystemShadow->CANMC.all;
	switch(Mbox)
	{
	case 2:
		ECanaMboxes.MBOX2.MDH.all = 0;
		ECanaMboxes.MBOX2.MDL.all = 0;
		ECanaMboxes.MBOX2.MDH.all = MDH;
		ECanaMboxes.MBOX2.MDL.all = MDL;

	case 3:
		ECanaMboxes.MBOX3.MDH.all = 0;
		ECanaMboxes.MBOX3.MDL.all = 0;
		ECanaMboxes.MBOX3.MDH.all = MDH;
		ECanaMboxes.MBOX3.MDL.all = MDL;

	case 4:
		ECanaMboxes.MBOX4.MDH.all = 0;
		ECanaMboxes.MBOX4.MDL.all = 0;
		ECanaMboxes.MBOX4.MDH.all = MDH;
		ECanaMboxes.MBOX4.MDL.all = MDL;
	case 5:
		ECanaMboxes.MBOX5.MDH.all = 0;
		ECanaMboxes.MBOX5.MDL.all = 0;
		ECanaMboxes.MBOX5.MDH.all = MDH;
		ECanaMboxes.MBOX5.MDL.all = MDL;
	case 6:
		ECanaMboxes.MBOX6.MDH.all = 0;
		ECanaMboxes.MBOX6.MDL.all = 0;
		ECanaMboxes.MBOX6.MDH.all = MDH;
		ECanaMboxes.MBOX6.MDL.all = MDL;
	case 7:
		ECanaMboxes.MBOX7.MDH.all = 0;
		ECanaMboxes.MBOX7.MDL.all = 0;
		ECanaMboxes.MBOX7.MDH.all = MDH;
		ECanaMboxes.MBOX7.MDL.all = MDL;
	case 8:
		ECanaMboxes.MBOX8.MDH.all = 0;
		ECanaMboxes.MBOX8.MDL.all = 0;
		ECanaMboxes.MBOX8.MDH.all = MDH;
		ECanaMboxes.MBOX8.MDL.all = MDL;
	case 9:
		ECanaMboxes.MBOX9.MDH.all = 0;
		ECanaMboxes.MBOX9.MDL.all = 0;
		ECanaMboxes.MBOX9.MDH.all = MDH;
		ECanaMboxes.MBOX9.MDL.all = MDL;
	case 10:
		ECanaMboxes.MBOX10.MDH.all = 0;
		ECanaMboxes.MBOX10.MDL.all = 0;
		ECanaMboxes.MBOX10.MDH.all = MDH;
		ECanaMboxes.MBOX10.MDL.all = MDL;
	case 11:
		ECanaMboxes.MBOX11.MDH.all = 0;
		ECanaMboxes.MBOX11.MDL.all = 0;
		ECanaMboxes.MBOX11.MDH.all = MDH;
		ECanaMboxes.MBOX11.MDL.all = MDL;
	case 12:
		ECanaMboxes.MBOX12.MDH.all = 0;
		ECanaMboxes.MBOX12.MDL.all = 0;
		ECanaMboxes.MBOX12.MDH.all = MDH;
		ECanaMboxes.MBOX12.MDL.all = MDL;
	case 13:
		ECanaMboxes.MBOX13.MDH.all = 0;
		ECanaMboxes.MBOX13.MDL.all = 0;
		ECanaMboxes.MBOX13.MDH.all = MDH;
		ECanaMboxes.MBOX13.MDL.all = MDL;
	case 14:
		ECanaMboxes.MBOX14.MDH.all = 0;
		ECanaMboxes.MBOX14.MDL.all = 0;
		ECanaMboxes.MBOX14.MDH.all = MDH;
		ECanaMboxes.MBOX14.MDL.all = MDL;
	case 15:
		ECanaMboxes.MBOX15.MDH.all = 0;
		ECanaMboxes.MBOX15.MDL.all = 0;
		ECanaMboxes.MBOX15.MDH.all = MDH;
		ECanaMboxes.MBOX15.MDL.all = MDL;
	case 16:
		ECanaMboxes.MBOX16.MDH.all = 0;
		ECanaMboxes.MBOX16.MDL.all = 0;
		ECanaMboxes.MBOX16.MDH.all = MDH;
		ECanaMboxes.MBOX16.MDL.all = MDL;
	case 17:
		ECanaMboxes.MBOX17.MDH.all = 0;
		ECanaMboxes.MBOX17.MDL.all = 0;
		ECanaMboxes.MBOX17.MDH.all = MDH;
		ECanaMboxes.MBOX17.MDL.all = MDL;
	case 18:
		ECanaMboxes.MBOX18.MDH.all = 0;
		ECanaMboxes.MBOX18.MDL.all = 0;
		ECanaMboxes.MBOX18.MDH.all = MDH;
		ECanaMboxes.MBOX18.MDL.all = MDL;
	case 19:
		ECanaMboxes.MBOX19.MDH.all = 0;
		ECanaMboxes.MBOX19.MDL.all = 0;
		ECanaMboxes.MBOX19.MDH.all = MDH;
		ECanaMboxes.MBOX19.MDL.all = MDL;
	case 20:
		ECanaMboxes.MBOX20.MDH.all = 0;
		ECanaMboxes.MBOX20.MDL.all = 0;
		ECanaMboxes.MBOX20.MDH.all = MDH;
		ECanaMboxes.MBOX20.MDL.all = MDL;
	case 21:
		ECanaMboxes.MBOX21.MDH.all = 0;
		ECanaMboxes.MBOX21.MDL.all = 0;
		ECanaMboxes.MBOX21.MDH.all = MDH;
		ECanaMboxes.MBOX21.MDL.all = MDL;
	case 22:
		ECanaMboxes.MBOX22.MDH.all = 0;
		ECanaMboxes.MBOX22.MDL.all = 0;
		ECanaMboxes.MBOX22.MDH.all = MDH;
		ECanaMboxes.MBOX22.MDL.all = MDL;
	case 23:
		ECanaMboxes.MBOX23.MDH.all = 0;
		ECanaMboxes.MBOX23.MDL.all = 0;
		ECanaMboxes.MBOX23.MDH.all = MDH;
		ECanaMboxes.MBOX23.MDL.all = MDL;
	case 24:
		ECanaMboxes.MBOX24.MDH.all = 0;
		ECanaMboxes.MBOX24.MDL.all = 0;
		ECanaMboxes.MBOX24.MDH.all = MDH;
		ECanaMboxes.MBOX24.MDL.all = MDL;
	case 25:
		ECanaMboxes.MBOX25.MDH.all = 0;
		ECanaMboxes.MBOX25.MDL.all = 0;
		ECanaMboxes.MBOX25.MDH.all = MDH;
		ECanaMboxes.MBOX25.MDL.all = MDL;
	case 26:
		ECanaMboxes.MBOX26.MDH.all = 0;
		ECanaMboxes.MBOX26.MDL.all = 0;
		ECanaMboxes.MBOX26.MDH.all = MDH;
		ECanaMboxes.MBOX26.MDL.all = MDL;
	case 27:
		ECanaMboxes.MBOX27.MDH.all = 0;
		ECanaMboxes.MBOX27.MDL.all = 0;
		ECanaMboxes.MBOX27.MDH.all = MDH;
		ECanaMboxes.MBOX27.MDL.all = MDL;
	case 28:
		ECanaMboxes.MBOX28.MDH.all = 0;
		ECanaMboxes.MBOX28.MDL.all = 0;
		ECanaMboxes.MBOX28.MDH.all = MDH;
		ECanaMboxes.MBOX28.MDL.all = MDL;
	case 29:
		ECanaMboxes.MBOX29.MDH.all = 0;
		ECanaMboxes.MBOX29.MDL.all = 0;
		ECanaMboxes.MBOX29.MDH.all = MDH;
		ECanaMboxes.MBOX29.MDL.all = MDL;
	case 30:
		ECanaMboxes.MBOX30.MDH.all = 0;
		ECanaMboxes.MBOX30.MDL.all = 0;
		ECanaMboxes.MBOX30.MDH.all = MDH;
		ECanaMboxes.MBOX30.MDL.all = MDL;
	case 31:
		ECanaMboxes.MBOX31.MDH.all = 0;
		ECanaMboxes.MBOX31.MDL.all = 0;
		ECanaMboxes.MBOX31.MDH.all = MDH;
		ECanaMboxes.MBOX31.MDL.all = MDL;
	default:
		result = 0;
	}
	SystemShadow->CANMC.bit.CDR = 0;
	SystemShadow->CANMC.bit.MBNR = 0;
	ECanaRegs.CANMC.all = SystemShadow->CANMC.all;
	EDIS;
	return result;
}
