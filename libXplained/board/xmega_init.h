/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: xmega_init.h
 *
 *  Created on: 22. mar. 2013
 *
 * Author: eirik
 *
 * Copyright:GPL V3
 * See http://www.gnu.org/licenses/gpl.html
 *
 * Description:
 *
 *********************************************/

#ifndef XMEGA_INIT_H_
#define XMEGA_INIT_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <avr/pgmspace.h>

#include <util/atomic.h>
#include <util/delay.h>

/* Function declarations */
void xmega_init();
void xmega_init_interrupt();

#endif /* XMEGA_INIT_H_ */
