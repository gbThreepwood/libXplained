/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: serial_driver.h
 *
 *  Created on: 4. apr. 2013
 *
 * Author: eirik
 *
 * Copyright:GPL V3
 * See http://www.gnu.org/licenses/gpl.html
 *
 * Description:
 *
 *********************************************/

/*
	This file is part of libXplained.

    libXplained is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libXplained is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libXplained.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SERIAL_DRIVER_H_
#define SERIAL_DRIVER_H_

#include <stdio.h>
#include <stddef.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//#define F_CPU 32000000UL

void UsartInit();

void UsartWriteChar(unsigned char data);
unsigned char UsartReadChar(void);

void SerialWriteString(char *string);
void SerialWriteLine(char *string);


#endif /* SERIAL_DRIVER_H_ */
