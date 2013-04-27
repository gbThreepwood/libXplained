/**
 *  vim:sw=8:ts=8:si:et
 *  To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 *  Filename: vt100_driver.h
 *
 *   Created on: 25. apr. 2013
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

#ifndef VT100_DRIVER_H_
#define VT100_DRIVER_H_

/* Attributes */
#define ATTR_RESET			0
#define ATTR_BRIGHT			1
#define ATTR_DIM			2
#define ATTR_UNDERSCORE		4
#define ATTR_BLINK			5
#define ATTR_REVERSE		7
#define ATTR_HIDDEN			8

/* Foreground Colours */
#define FG_COLOR_BLACK		30
#define FG_COLOR_RED		31
#define FG_COLOR_GREEN		32
#define FG_COLOR_YELLOW		33
#define FG_COLOR_BLUE		34
#define FG_COLOR_MAGENTA	35
#define FG_COLOR_CYAN		36
#define FG_COLOR_WHITE		37

/* Background Colours */
#define BG_COLOR_BLACK		40
#define BG_COLOR_RED		41
#define BG_COLOR_GREEN		42
#define BG_COLOR_YELLOW		43
#define BG_COLOR_BLUE		44
#define BG_COLOR_MAGENTA	45
#define BG_COLOR_CYAN		46
#define BG_COLOR_WHITE		47

#endif /* VT100_DRIVER_H_ */
