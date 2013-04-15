/**
 *  vim:sw=8:ts=8:si:et
 *  To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 *  Filename: rtc_driver.c
 *
 *   Created on: 15. apr. 2013
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

#include "rtc_driver.h"

/*!
  Initialize the built in Real Time Counter.
*/
void rtc_init()
{
	/* Set Configuration Change Protection register to allow modification of OSC register. */
	CCP = CCP_IOREG_gc;

	/* Internal 32KHz oscillator */
	OSC.CTRL |= OSC_RC32KEN_bm;

	/* Select internal 32KHz oscillator as RTC clock source. */
	CLK.RTCCTRL = CLK_RTCSRC_TOSC32_gc;

	/* Divide clock by 1024 */
	RTC.CTRL = RTC_PRESCALER_DIV1024_gc;

	/* Wait until RTC is ready */
	while(RTC.STATUS & RTC_SYNCBUSY_bm);

	/* Set the RTC to overflow after 10 seconds */
	RTC.PER = 10;

	/* High level interrupt on RTC overflow */
	RTC.INTCTRL |= RTC_OVFINTLVL_HI_gc;

	/* Initial count is zero. */
	RTC.CNT = 0;
}

/*
 *	The following ISR is executed when the RTC overflows.

	ISR(RTC_OVF_vect)
	{
		PORTE.OUT ^= (1<<0);   // Blink led
	}
*/


// TODO: Write driver for the external RTC chip DS1307.
void ds1307_init()
{

}

int16_t ds1307_get_current_time()
{
	return 0;
}
