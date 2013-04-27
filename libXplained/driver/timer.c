/**
 *  vim:sw=8:ts=8:si:et
 *  To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 *  Filename: timer.c
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
#include "timer.h"

#include <avr/wdt.h>


void timer_init(TC1_t timer)
{
	cli();

	/**/
	TCC0.CCA;
	TCD0.CCA;
	TCE0.CCA;
	TCF0.CCA;


	/* Timer clock source. */
	timer.CTRLA = TC_CLKSEL_DIV1024_gc;

	/*
	 * Compare or Capture Enable.
	 * Waveform Generation Mode.
	 */
	timer.CTRLB = TC_WGMODE_NORMAL_gc;

	timer.CTRLC;
	timer.CTRLD;
	timer.CTRLE;

	timer.PER = 125;

	/* Interrupt Enable register. */
	timer.INTCTRLA;
	timer.INTCTRLB;

	sei();
}


//ISR(TCC0_OVF_vect)
//{
//
//}

void watchdog_timer_enable(WDT_PER_t period)
{
	/*
	 * Write to CCP (Configuration Change Protection register)
	 * to gain access to protected registers.
	 */
	CCP = CCP_IOREG_gc;

	/* Timeout period */
	//WDT.CTRL = WDT_PER_8KCLK_gc | WDT_ENABLE_bm | WDT_CEN_bm;
	WDT.CTRL = period | WDT_ENABLE_bm | WDT_CEN_bm;

	/* WINCTRL – Window Mode Control register */
	//WDT.WINCTRL = WDT_WPER_8KCLK_gc | WDT_WEN_bm | WDT_WCEN_bm;

	while(!(WDT.STATUS & 0x01)); /* Wait for the WDT to syncronize. */

	RST.STATUS;

	wdt_reset();
}
