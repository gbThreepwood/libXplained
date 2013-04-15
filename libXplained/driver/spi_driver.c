/**
 *  vim:sw=8:ts=8:si:et
 *  To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 *  Filename: spi_driver.c
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


#include "spi_driver.h"

#define SPI_INTERFACE	 SPID
#define SPI_PORT		 PORTD

#define ss_low() 	SPI_PORT.OUT &= ~(1<<4);
#define ss_high()	SPI_PORT.OUT |= (1<<4);

void spi_init()
{
	/* Configure MOSI, SS and CLK as output */
	SPI_PORT.DIR = 0xFF;

	/* Enable SPI in master mode. Divide clock by 64. */
	SPI_INTERFACE.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV64_gc;
}

void spi_tx_byte(uint8_t data)
{
	/* Set slave select low to indicate start of transfer.  */
	ss_low();

	SPI_INTERFACE.DATA = data;

	/* Wait until transfer is complete. */
	while(!(SPI_INTERFACE.STATUS & (1<<7)));

	/* Set slave select high to indicate end of transfer. */
	ss_high();
}

uint8_t spi_rx_byte()
{
	spi_tx_byte(0);

	return SPI_INTERFACE.DATA;
}
