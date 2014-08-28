/*
 * PowerDown_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#include "all.h"

void SystemPowerDown()
{
	while(isPowerOn() == 0) {}
	EALLOW;
	SysCtrlRegs.WDCR = 0x0028;               // Enable watchdog module
	SysCtrlRegs.WDKEY = 0x00;                // wrong key should restart
	SysCtrlRegs.WDKEY = 0x00;
	EDIS;

	while(1){}
}

char isPowerOn()
{
	return !Comp3Regs.COMPSTS.bit.COMPSTS; 	// 1 means cause interrupt = no power
}

void PowerDownISRSetup()
{
	InitComp3Gpio();

	EALLOW;
	AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;

	Comp3Regs.DACVAL.bit.DACVAL = (Uint16)(COMPVOLTAGE*1023.0)/(VDDA-VSSA);
	Comp3Regs.COMPCTL.bit.CMPINV = 1; //invert comp signal
	Comp3Regs.COMPCTL.bit.COMPDACEN = 1;

	EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP3OUT;
	EPwm1Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;
	EPwm1Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;
	EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_SYNC;
	EPwm1Regs.TZCLR.all = 0xFFFF;
	EPwm1Regs.TZEINT.bit.DCAEVT2 = 1;
	EPwm1Regs.TZCTL.bit.DCAEVT2 = TZ_NO_CHANGE;


	PieCtrlRegs.PIEIER2.bit.INTx1 = 1;

	IFR &= ~M_INT2;
	IER |= M_INT2;

	EDIS;
}

void StartPowerDownInt()
{
	EALLOW;
	EPwm1Regs.TZCLR.all = 0xFFFF;
	EDIS;
}

// INT2.1
__interrupt void EPWM1_TZINT_ISR(void)    // EPWM-1
{

	// To receive more interrupts from this PIE group, acknowledge this interrupt
	sys_ops.State = STATE_POWER_DOWN;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

}
