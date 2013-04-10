/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: xmega_init.c
 *
 *  Created on: 22. mar. 2013
 *
 * Author: Eirik Haustveit
 *
 * Copyright:GPL V3
 * See http://www.gnu.org/licenses/gpl.html
 *
 * Description:
 *
 *********************************************/

#include "xmega_init.h"

/*!
  Initializes the interrupt controller.
  Enable interrupts on PortD and PortR as these ports are
  connected to the push buttons
*/
void xmega_init_interrupt()
{
	/* PMIC - Programmable multilevel interrupt controller.
	 * Styrer avbruddssystemet */
	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	PMIC.INTPRI = 0x00;
	//PMIC.STATUS;

	/* Avbruddskontroll port D */
	PORTD.INTCTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm; /* Avbruddsnivå */
	PORTD.INT0MASK = 0xFF; /* Velger kva pinnar som skal trigga avbrudd 0. */
	//PORTD.INT1MASK = 0xFF; /* Velger kva pinnar som skal trigga avbrudd 1. */
	// PORTD.INTFLAGS; /* Indikerer om avbrudd er trigga.  */

	/* Avbruddskontroll port R */
	PORTR.INTCTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm; /* Avbruddsnivå */
	PORTR.INT0MASK = 0xFF; /* Velger kva pinnar som skal trigga avbrudd 0. */
	//PORTR.INT1MASK = 0xFF; /* Velger kva pinnar som skal trigga avbrudd 1. */
	// PORTR.INTFLAGS; /* Indikerer om avbrudd er trigga.  */

	sei(); /* Set global interrupt flag */
}

/*!
  Performs necessary initialization on the ports.
  The ports ar initialized differently depending on what kind of external hardware
  they connect to.

  By default the pin headers are initialized as outputs.
*/
void xmega_init()
{
	/*-------------------- Port A --------------------*/
	//Port A er kopla til kontakt J2

	PORTA.DIR = 0xFF;
	PORTA.PIN0CTRL = PORT_OPC_TOTEM_gc;
	PORTA.PIN1CTRL = PORT_OPC_TOTEM_gc;
	PORTA.PIN2CTRL = PORT_OPC_TOTEM_gc;
	PORTA.PIN3CTRL = PORT_OPC_TOTEM_gc;
	PORTA.PIN4CTRL = PORT_OPC_TOTEM_gc;
	PORTA.PIN5CTRL = PORT_OPC_TOTEM_gc;
	PORTA.PIN6CTRL = PORT_OPC_TOTEM_gc;
	PORTA.PIN7CTRL = PORT_OPC_TOTEM_gc;

	/*-------------------- Port B --------------------*/
	/**/

	PORTB.DIR = 0x00;

	// NTC temperatur sensor på PB0 og PB1
	PORTB.PIN0CTRL;
	PORTB.PIN1CTRL;

	// Audio forsterkar på PB2
	PORTB.PIN2CTRL;

	/*-------------------- Port C --------------------*/
	/* Port C er kopla til kontakt J4 */

	PORTC.DIR = 0x00;
	PORTC.PIN0CTRL = 0b00011001;
	PORTC.PIN1CTRL = 0b00011001;
	PORTC.PIN2CTRL = 0b00011001;
	PORTC.PIN3CTRL = 0b00011001;
	PORTC.PIN4CTRL = 0b00011001;
	PORTC.PIN5CTRL = 0b00011001;
	PORTC.PIN6CTRL = 0b00011001;
	PORTC.PIN7CTRL = 0b00011001;

	/*-------------------- Port D --------------------*/
	/* Port D er kopla til trykknappane SW0 til SW5*/

	PORTD.DIR = 0x00;
	PORTD.PIN0CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	PORTD.PIN1CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	PORTD.PIN2CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	PORTD.PIN3CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	PORTD.PIN4CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	PORTD.PIN5CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	//PORTD.PIN6CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	//PORTD.PIN7CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;

	/* Avbruddskontroll */
	PORTD.INTCTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm; /* Avbruddsnivå */
	PORTD.INT0MASK = 0x00; /* Velger kva pinnar som skal trigga avbrudd 0. */
	PORTD.INT1MASK = 0xFF; /* Velger kva pinnar som skal trigga avbrudd 1. */
	// PORTD.INTFLAGS; /* Indikerer om avbrudd er trigga.  */

	/*-------------------- Port E --------------------*/
	/* Port E er kopla til lysdiodane */

	PORTE.DIR = 0xFF;
	PORTE.PIN0CTRL = PORT_OPC_TOTEM_gc;
	PORTE.PIN1CTRL = PORT_OPC_TOTEM_gc;
	PORTE.PIN2CTRL = PORT_OPC_TOTEM_gc;
	PORTE.PIN3CTRL = PORT_OPC_TOTEM_gc;
	PORTE.PIN4CTRL = PORT_OPC_TOTEM_gc;
	PORTE.PIN5CTRL = PORT_OPC_TOTEM_gc;
	PORTE.PIN6CTRL = PORT_OPC_TOTEM_gc;
	PORTE.PIN7CTRL = PORT_OPC_TOTEM_gc;
	PORTE.OUT = 0xFF;

	/*-------------------- Port F --------------------*/
	/* Port F er kopla til kontakt J1 */
	PORTF.DIR = 0x00;
	PORTF.PIN0CTRL = 0b00011001;
	PORTF.PIN1CTRL = 0b00011001;
	PORTF.PIN2CTRL = 0b00011001;
	PORTF.PIN3CTRL = 0b00011001;
	PORTF.PIN4CTRL = 0b00011001;
	PORTF.PIN5CTRL = 0b00011001;
	PORTF.PIN6CTRL = 0b00011001;
	PORTF.PIN7CTRL = 0b00011001;

	/*-------------------- Port R --------------------*/
	/* Port R Pin 0 og 1 er kobla til trykknappane
	 * SW6 og SW7 */

	PORTR.DIR = 0x00;
	PORTR.PIN0CTRL = 0b00011001;
	PORTR.PIN1CTRL = 0b00011001;


	/* PORTH, PORTJ og PORTK */
	/* external bus interface (EBI) */
	PORTH.DIR = 0x00;
	PORTH.PIN0CTRL = 0b00011001;
	PORTH.PIN1CTRL = 0b00011001;
	PORTH.PIN2CTRL = 0b00011001;
	PORTH.PIN3CTRL = 0b00011001;
	PORTH.PIN4CTRL = 0b00011001;
	PORTH.PIN5CTRL = 0b00011001;
	PORTH.PIN6CTRL = 0b00011001;
	PORTH.PIN7CTRL = 0b00011001;
}
