/**
 *  vim:sw=8:ts=8:si:et
 *  To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 *  Filename: vt100_driver.c
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

/*
 * The ASCII code for ESC is 1B hex.
 */

#include "vt100_driver.h"
#include "../main.h"



/* key sequences sent by non-ASCII keys */
static const char specialKeySequences[22][6] PROGMEM = {
  "\x1BOP", 	/* F1 */
  "\x1BOQ", 	/* F2 */
  "\x1BOR", 	/* F3 */
  "\x1BOS", 	/* F4 */
  "\x1B[15~", 	/* F5 */
  "\x1B[17~", 	/* F6 */
  "\x1B[18~", 	/* F7 */
  "\x1B[19~", 	/* F8 */
  "\x1B[20~", 	/* F9 */
  "\x1B[21~", 	/* F10 */
  "\x1B[23~", 	/* F11 */
  "\x1B[24~", 	/* F12 */
  "\x1BOA", 	/* UP */
  "\x1BOD", 	/* LEFT */
  "\x1BOB", 	/* DOWN */
  "\x1BOC", 	/* RIGHT */
  "\x1B[2~", 	/* INS */
  "\x1B[3~",	/* DEL */
  "\x1B[H", 	/* HOME */
  "\x1B[F", 	/* END */
  "\x1B[5~", 	/* PGUP */
  "\x1B[6~", 	/* PGDN */
};

void vt100Init()
{

}

void vt100MoveCursor(uint8_t line, uint8_t col)
{
	/* ESC [ Pl ; Pc H */
	printf("\x1B[%d;%dH",line,col);
}

void vt100SetAttribute(uint8_t attr)
{
	/* ESC [ Ps m */
	printf("\x1B[%dm",attr);
}
