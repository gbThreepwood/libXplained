/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: lcd_driver.h
 *
 *  Created on: 21. mar. 2013
 *
 * Author: Eirik Haustveit
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

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>


void lcd_init();

/*! \brief Low level functions
 * Low level functions used by the driver. */
void lcd_write_byte(char c);
void lcd_write_byte_data(char c);

void lcd_move_cursor(uint8_t line, uint8_t pos);

void lcd_write_string_0(char *x);

/*! \brief High level functions
 * High level functions for the users. */
//void lcd_send_command(char command);
//void lcd_write_string(char *string, char address);

#endif /* LCD_DRIVER_H_ */
