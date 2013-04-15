/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: serial_driver.c
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

#include "serial_driver.h"

#define SERIAL_PORT_USART	USARTC0
#define SERIAL_PORT			PORTC

/**
 * Version number of the serial driver.
 */
#define SERIAL_DRIVER_VERSION "0.0.1"

/*!
  Sets up all parameters for the serial port.
*/
void UsartInit()
{
	/*
	 * Configure the serial interface.
	 * PORTC is connected to the serial/USB interface.
	 * PC2 is RX(UARTC0_RXD) and PC3 is TX(UARTC0_TXD).
	 */

	SERIAL_PORT.OUT |= (1<<3);          // Set TX pin high
	SERIAL_PORT.DIR |= (1<<3) | (1<<0); // set TX pin as output

	/*
	 * Set up the baudrate
	 * 115.2kb
	 */
	SERIAL_PORT_USART.BAUDCTRLA = 33;
	SERIAL_PORT_USART.BAUDCTRLB = (-1<<4);

	/* Enable TX and RX on USART */
	SERIAL_PORT_USART.CTRLB = USART_TXEN_bm | USART_RXEN_bm;

	/*
	 * USART_CMODE_ASYNCHRONOUS_gc
	 * USART_CMODE_SYNCHRONOUS_gc
	 * USART_CMODE_IRDA_gc
	 * USART_CMODE_MSPI_gc
	 *
	 * USART_PMODE_DISABLED_gc
	 * USART_PMODE_EVEN_gc
	 * USART_PMODE_ODD_gc
	 */
	SERIAL_PORT_USART.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
}

/*!
  Writes a single 8-bit char to the serial port.
  @param[in]  Char to be written.
*/
void UsartWriteChar(unsigned char data)
{
	SERIAL_PORT_USART.DATA = data;

	if(!(SERIAL_PORT_USART.STATUS & USART_DREIF_bm)) // If data register is not empty.
		while(!(SERIAL_PORT_USART.STATUS & USART_TXCIF_bm)); // Loop until TX is complete

	SERIAL_PORT_USART.STATUS |= USART_TXCIF_bm;  // clear TX interrupt flag
};

/*!
  Low level function. Reads a single char from the serial port.
  @return  The received 8-bit char.
*/
unsigned char UsartReadChar(void)
{
	while(!(SERIAL_PORT_USART.STATUS & USART_RXCIF_bm));  // Loop until RX is complete.

  	return SERIAL_PORT_USART.DATA;
};


/*!
  Writes a '\0' terminated string to the serial port.
  @param[in]  *string  Pointer to the string to write.
*/
void SerialWriteString(char *string)
{
    while(*string != 0)
	  UsartWriteChar(*string++);
};

/*!
  Writes a '\0' terminated string to the serial port,
  and adds "\n\r" to the end.
  @param[in]  *string  Pointer to the string to write.
*/
void SerialWriteLine(char *string)
{
   SerialWriteString(string);
   SerialWriteString("\n\r");

};

/*!
  Writes a welcome message to be displayed at the serial console of the user.
*/
void WelcomeMessage()
{
	SerialWriteLine("\n\r\n\r");
	SerialWriteLine("Velkomen til XmegaA1 Xplained.");
}

/*!
  Writes out relevant system information to the serial console.
*/
void SystemInfo()
{
	SerialWriteLine("\n\r\n\r");
	SerialWriteLine("System information.");
}
