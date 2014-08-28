/*
 * gpio.h
 *
 *  Created on: Dec 7, 2013
 *      Author: Nathan
 */

#ifndef GPIO_H_
#define GPIO_H_

#define 	CLEARLED0()				GpioDataRegs.GPACLEAR.bit.GPIO29 = 1
#define		SETLED0()				GpioDataRegs.GPASET.bit.GPIO29 = 1
#define 	TOGGLELED0()			GpioDataRegs.GPATOGGLE.bit.GPIO29 = 1

#define 	CLEARLED1()				GpioDataRegs.GPACLEAR.bit.GPIO9 = 1
#define		SETLED1()				GpioDataRegs.GPASET.bit.GPIO9 = 1
#define 	TOGGLELED1()			GpioDataRegs.GPATOGGLE.bit.GPIO9 = 1

#define 	CLEAR12V()				GpioDataRegs.GPACLEAR.bit.GPIO20 = 1
#define		SET12V()				GpioDataRegs.GPASET.bit.GPIO20 = 1
#define 	TOGGLE12V()				GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1

#define		READGPBUTTON()			GpioDataRegs.GPADAT.bit.GPIO21


/**
 * Configures the GPIO pin 21 to the GPIO button.
 */
void ConfigGPButton();

/**
 * Configures the GPIO pin 20 to control 12V.
 */
void Config12V();

/**
 * Configures the GPIO pin 9 to control LED1.
 */
void ConfigLED1();

/**
 * Configures the GPIO pin 29 to control LED0.
 */
void ConfigLED0();


#endif /* GPIO_H_ */
