/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: lcd_driver.c
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

#include "lcd_driver.h"

#define LCD_RS 		PIN1_bm		/* Reg select */
#define LCD_E  		PIN0_bm		/* Enable */

//#define LCD_DATA0	PIN0_bm
//#define LCD_DATA1	PIN1_bm
//#define LCD_DATA6	PIN6_bm
//#define LCD_DATA7	PIN7_bm
#define LCD_DATA0	PIN2_bm
#define LCD_DATA1	PIN3_bm
#define LCD_DATA2	PIN4_bm
#define LCD_DATA3	PIN5_bm

#define LCD_INTERFACE PORTD

#define LCD_COMMAND_REG	0
#define LCD_DATA_REG	1

#define LCD_8BIT_MODE	0
#define LCD_4BIT_MODE	1

/* Setter RS(Registry select) til 0, for kommandoregister */
void lcd_set_instruction_registry() {
	LCD_INTERFACE.OUTCLR = LCD_RS;		// setter RS lav
	_delay_us(50);
}

/* Setter RS(Registry select) til 1, for dataregister */
void lcd_set_data_registry() {
	LCD_INTERFACE.OUTSET = LCD_RS;		// seter RS høg
	_delay_us(50);
}

//void lcd_write_byte(char c, char registry_select) {
//	/* Overfører i 8-bit mode. */
//
//	if(registry_select == 1) // Data
//	LCD_INTERFACE.OUT = c;
//
//	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
//	_delay_us(1);
//	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
//	_delay_ms(10);
//}
//
//void lcd_write_byte_8bit_mode(char c) {
//	/* Overfører i 8-bit mode. */
//
//	LCD_INTERFACE.OUT = c;
//
//	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
//	_delay_us(1);
//	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
//	_delay_ms(10);
//}

void lcd_write_byte(char c) {
	/* Overfører i 4-bit mode.
	 * Data må klokkast inn i to operasjonar.
	 * */
	// high-nibble, delay, low-nibble, delay.
	// GPIO 2, 3, 4 og 5.
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav

	//lcd_port = ((cmd >> 4) & 0x0F)|LCD_EN;
	//LCD_INTERFACE.OUT = ((c & 0xF0) << 2);

	//0b abcd efgh
	LCD_INTERFACE.OUT = (((c >> 4) & 0x0F) << 2); //0b00xxxx00

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(400);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);

	LCD_INTERFACE.OUT = ((c & 0x0F) << 2); //0b00xxxx00

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(400);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);
}

void lcd_write_byte_data(char c) {
	/* Overfører i 4-bit mode.
	 * Data må klokkast inn i to operasjonar.
	 * */
	// high-nibble, delay, low-nibble, delay.
	// GPIO 2, 3, 4 og 5.
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav

	//lcd_port = ((cmd >> 4) & 0x0F)|LCD_EN;
	//LCD_INTERFACE.OUT = ((c & 0xF0) << 2);

	//0b abcd efgh
	LCD_INTERFACE.OUT = (((c >> 4) & 0x0F) << 2) | 0b00000010; //0b00xxxx00

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(400);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);

	LCD_INTERFACE.OUT = ((c & 0x0F) << 2) | 0b00000010; //0b00xxxx00

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(400);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);
}

/*!
  Clear the LCD and move the cursor to home position.
*/
void lcd_clear_and_home()
{
	lcd_set_instruction_registry();
	lcd_write_byte(0x01); //
	_delay_ms(50);
	lcd_write_byte(0x02); //
	_delay_ms(50);
}

/*!
  Move the cursor to home position.
*/
void lcd_home()
{
	lcd_set_data_registry();

	lcd_write_byte(0x02);
	_delay_ms(50);
}

/*!
  Move the cursor on the LCD.
  @param[in] line what line to put the cursor on
  @param[in] pos the new position of the cursor
*/
void lcd_move_cursor(uint8_t line, uint8_t pos)
{
	uint8_t position = 0;

	lcd_set_instruction_registry();
	switch(line)
	{
		case 0: position = 0;
		break;
		case 1: position = 0x40;
		break;
	}
	lcd_write_byte(0x80 | (position + pos));
}

/*!
  Writes a single char to the LCD.
  @param[in] c the char to be written.
*/
void lcd_write_data(char c) {
	lcd_set_data_registry();
	lcd_write_byte_data(c);
}

/*!
  Writes a string to the LCD(from SRAM).
  @param[in] *x the string to be written.
  @param[in] len the length of the string.
*/
void lcd_write_string(char *x, uint8_t len ) {
	while (--len > 0)
		lcd_write_data(*x++);
}

/*!
  Writes a '\0' terminated string to the LCD.
  @param[in] *x the string to be written.
*/
void lcd_write_string_0(char *x) {
	while (*x)
		lcd_write_data(*x++);
}

/*!
  Writes a '\0' terminated string to the LCD.
  Using LPM(Load Program Memory) instructions to load the string from program memory.
  Remember to terminate the string using a '\0' char.
  @param[in] *s the string to be written.
*/
void lcd_write_string_0_p(const char *s)
{
	char c;

	for (c = pgm_read_byte(s); c; ++s, c = pgm_read_byte(s))
		lcd_write_data(c);
}

/*!
  Sets up the interface and initializes the LCD.
*/
void lcd_init() {

	LCD_INTERFACE.OUT = 0x00;					// initial data lines all low
	LCD_INTERFACE.DIRSET = 0xff;				// set the 8-bit data port to all outputs

	/* Time delay to allow the LCD to power up */
	_delay_ms(500);

	LCD_INTERFACE.OUT = 0x03 << 2;

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_ms(5);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(200);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(200);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);

	LCD_INTERFACE.OUT = 0x02 << 2;
	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(200);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);

	lcd_set_instruction_registry();

	/* Kommandoar for å initsialisera skjermen */
	lcd_write_byte(0x28);			// function set
	_delay_us(50);
	lcd_write_byte(0x0c);			// display on/off control
	_delay_us(50);
	//lcd_write_byte(0x01);			// display clear
	_delay_ms(5);
	lcd_write_byte(0x06);			// entry mode set
	_delay_ms(5);

	lcd_write_byte(0x14); 			// Cursor shift
	lcd_write_byte(0x80);
	lcd_clear_and_home();
}

/* Eigendefinerte teikn til LCD.
 *
 * Smilefjes
 * 0x0,0xa,0x0,0x4,0x0,0xe,0x0
 *
 * Smilefjes inv:
 * 0x1f,0x15,0x1f,0x1b,0x1f,0x11,0x1f
 *
 * Smilefjes2 inv:
 * 0x1f,0x15,0x1f,0x1b,0xe,0x11,0x1f
 * */
