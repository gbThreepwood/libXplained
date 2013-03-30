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

#include "lcd_driver.h"

#define LCD_RS PIN3_bm		/* RS på pin PA3 */
#define LCD_E  PIN1_bm		/* E on pin PA1 */
#define LCD_INTERFACE PORTA

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

void lcd_write_byte(char c) {
	/* Overfører i 8-bit mode. */

	LCD_INTERFACE.OUT = c;

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(1);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);
}

void lcd_write_byte_8bit_mode(char c) {
	/* Overfører i 8-bit mode. */

	LCD_INTERFACE.OUT = c;

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(1);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);
}

void lcd_write_byte_4bit_mode(char c) {
	/* Overfører i 4-bit mode.
	 * Data må klokkast inn i to operasjonar.
	 * */

	LCD_INTERFACE.OUT = (c & 0x0F << 4);

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(1);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);

	LCD_INTERFACE.OUT = c;

	LCD_INTERFACE.OUTSET = LCD_E;		// setter E høg
	_delay_us(1);
	LCD_INTERFACE.OUTCLR = LCD_E;		// setter E lav
	_delay_ms(10);
}

/* Tømer skjermen og flytter skrivemerket(markøren) til første teikn. */
void lcd_clear_and_home()
{
	lcd_set_instruction_registry();
	lcd_write_byte(0x01); //
	_delay_ms(50);
	lcd_write_byte(0x02); //
	_delay_ms(50);
}

/**/
void lcd_home()
{
	lcd_set_data_registry();

	lcd_write_byte(0x02);
	_delay_ms(50);
}

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

/* Skriv eit teikn til skjermen */
void lcd_write_data(char c) {
	lcd_set_data_registry();
	lcd_write_byte(c);
}


/* Skriv ein streng til skjermen (i SRAM) */
void lcd_write_string(char *x, uint8_t len ) {
	while (--len > 0)
		lcd_write_data(*x++);
}

/* Skriv ein nullterminert streng til skjermen*/
void lcd_write_string_0(char *x) {
	while (*x)
		lcd_write_data(*x++);
}

// Same as above, but the string is located in program memory,
//  so "lpm" instructions are needed to fetch it, and a \0
//  must be defined at the end of the string to terminate it.
void lcd_write_string_0_p(const char *s)
{
	char c;

	for (c = pgm_read_byte(s); c; ++s, c = pgm_read_byte(s))
		lcd_write_data(c);
}

/* Set opp nødvendige portar på mikrokontrolleren,
 * og initsialiserer skjermen. */
void lcd_init() {

	/**/
	LCD_INTERFACE.OUT = 0x00;							// initial data lines all low
	LCD_INTERFACE.DIRSET = 0xff;						// set the 8-bit data port to all outputs

	//COMM_PORT.OUTCLR = LCD_E | LCD_RS;			// all LCD control lines low
	//COMM_PORT.DIRSET = LCD_E | LCD_RS;  		// set the LCD control line pins to outputs

	/* Tidsforseinking for oppstart av LCD */
	_delay_ms(500);

	/* Kommandoar for å initsialisera skjermen */
	lcd_write_byte(0x38);			// function set
	_delay_us(50);
	lcd_write_byte(0x0c);			// display on/off control
	_delay_us(50);
	lcd_write_byte(0x01);			// display clear
	_delay_ms(5);
	lcd_write_byte(0x06);			// entry mode set
	_delay_ms(5);

	lcd_write_byte(0x14); 			// Cursor shift

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
