/**
 *  vim:sw=8:ts=8:si:et
 *  To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 *  Filename: spi_driver.h
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

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void spi_init();
void spi_tx_byte(uint8_t data);
uint8_t spi_rx_byte();

#endif /* SPI_DRIVER_H_ */
