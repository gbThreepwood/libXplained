/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: main.h
 *
 *  Created on: 19. mar. 2013
 *
 * Author: eirik
 *
 * Copyright:GPL V3
 * See http://www.gnu.org/licenses/gpl.html
 *
 * Description:
 *
 *********************************************/

#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>

#include <util/atomic.h>
#include <util/delay.h>

/* Funksjonsdeklarasjonar */
void heartbeat(void);
void Config32MHzClock(void);


// Events bits
#define EVENT_UPDATE_LCD		0
#define EVENT_ANALYZE_STATE		1
#define EVENT_CONVERT_TEMP		2
#define EVENT_UPDATE_EEPROM		3
#define EVENT_BUTTON_PRESSED	4
#define EVENT_ENCODER_UP		5
#define EVENT_ENCODER_DOWN		6
#define EVENT_READ_RTC			7
#define EVENT_SET_RTC			8

/* Nyttige bit operasjonar.
 *
 * number |= 1 << x; 		// Setter ein bit høg
 * number &= ~(1 << x); 	// Setter ein bit lav
 * number ^= 1 << x; 		// Toggler ein bit
 * bit = number & (1 << x); // Gir statusen til bit x
 * */

/* Nyttige definisjonar */
#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define WRITEBIT(RADDRESS,RBIT,WADDRESS,WBIT) (CHECKBIT(RADDRESS,RBIT) ? SETBIT(WADDRESS,WBIT) : CLEARBIT(WADDRESS,WBIT))

/**/
#define LED(nr,onoff) do { \
   if (onoff) { \
      PORTB &= ~(1 << (x)); \
   } else { \
      PORTB |= (1 << (x)); \
   } \
} while(0)
#define ON  1
#define OFF 0
#define LED_ALARM 0
#define LED_RUN   1
#define LED_FAIL  2



#endif /* MAIN_H_ */
