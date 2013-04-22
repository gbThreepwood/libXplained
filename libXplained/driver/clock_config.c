/**
 *  vim:sw=8:ts=8:si:et
 *  To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 *  Filename: clock_config.c
 *
 *   Created on: 22. apr. 2013
 *
 *  Author: Eirik Haustveit
 *
 *  Copyright (c) Eirik Haustveit, 2013
 *
 *  
 *	This file is part of libXplained.
 *
 *   libXplained is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   libXplained is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with libXplained.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../main.h"
#include "clock_config.h"

/*!
  Configure 32MHz internal clock source for the CPU.

  Remember to update baud rate control registers for the devices you are using(USART's, etc...).
*/
void config_32mhz_clock()
{
	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 */
	CCP = CCP_IOREG_gc;

	/* Enable 32Mhz oscillator. */
	OSC.CTRL = OSC_RC32MEN_bm;

	while(!(OSC.STATUS & OSC_RC32MRDY_bm)); /* Wait until oscillator is ready. */

	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 */
	CCP = CCP_IOREG_gc;

	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;

};

/*!
  Configure 2MHz internal clock source for the CPU.

  Remember to update baud rate control registers for the devices you are using(USART's, etc...).
*/
void config_2mhz_clock()
{
	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 */
	CCP = CCP_IOREG_gc;

	/* Enable 2Mhz oscillator. */
	OSC.CTRL = OSC_RC2MEN_bm;

	while(!(OSC.STATUS & OSC_RC2MRDY_bm)); /* Wait until oscillator is ready. */

	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 */
	CCP = CCP_IOREG_gc;

	CLK.CTRL = CLK_SCLKSEL_RC2M_gc;

};

/*!
  Configure internal 32.768kHz clock.
*/
void config_32khz_clock()
{
	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 */
	CCP = CCP_IOREG_gc;

	/* Enable 32kHz oscillator */
	OSC.CTRL = OSC_RC32KEN_bm;

	while(!(OSC.STATUS & OSC_RC32KRDY_bm)); /* Wait until oscillator is ready. */

	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 */
	CCP = CCP_IOREG_gc;

	CLK.CTRL = CLK_SCLKSEL_RC32K_gc;

};

/*!
  Configure external clock.
*/
void config_external_clock()
{
	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 * This register is automatically cleared after 4 clock cycles.
	 */
	CCP = CCP_IOREG_gc;

	/**/
	OSC.XOSCCTRL;

	/* External oscillator failure detection. */
	OSC.XOSCFAIL = OSC_XOSCFDEN_bm;

	/* Enable external oscillator */
	OSC.CTRL = OSC_XOSCEN_bm;

	while(!(OSC.STATUS & OSC_XOSCRDY_bm)); /* Wait until oscillator is ready. */

	CCP = CCP_IOREG_gc;

	CLK.PSCTRL;

	CLK.CTRL = CLK_SCLKSEL_XOSC_gc;

}

/*!
  Protect the system clock from modification.
  A reset is necessary to unlock.
*/
void lock_system_clock()
{
	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 * This register is automatically cleared after 4 clock cycles.
	 */
	CCP = CCP_IOREG_gc;

	CLK.LOCK = 0x01;
}
