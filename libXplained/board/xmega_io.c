/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: xmega_io.c
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

#include "xmega_io.h"

void ioport_toggle_port(PORT_t PORT)
{
	PORT.OUT = ~PORT.OUT;
}

void ioport_toggle_pin(PORT_t PORT)
{
	PORT.OUT = ~PORT.OUT;
}

void ioport_set_pin_high()
{

}

void analog_comparator()
{

	/* Analog comparator A */
	ACA.CTRLA = 0;

	ACA.AC0CTRL = 0;

	/* Digital to analog converter*/
	/* Nedre og øvre resultatregister. */
	DACB.CH0DATAL;
	DACB.CH0DATAH;
	DACA.CH1DATA;

	ACA.AC1MUXCTRL;
}

void analog_input()
{
	int result = 0;
	float resultVolt = 0;


	/* Analog to digital converter. */
	//ADCA.CALL = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0) );
	//ADCA.CALH = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1) );

	PORTA.DIR = 0x00;
	ADCA.CTRLA |= 0x01;
	ADCA.CTRLB = ADC_RESOLUTION_12BIT_gc; /* 12-bit oppløysing */
	ADCA.REFCTRL = ADC_REFSEL_INT1V_gc | 0x02; /* Intern referanse på 1V */
	ADCA.PRESCALER = ADC_PRESCALER_DIV8_gc; /*  */

	ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN2_gc; /* Multiplekseren velger pin 2 */

	ADCA.CH0.CTRL |= ADC_CH_START_bm; /* Starter konverteringa */

	while(!ADCA.CH0.INTFLAGS); /* Køyrer heilt til konverteringa er fullført */

	result = ADCA.CH0RES;

	resultVolt = (float)result/4096; // 1V ref, 12bit ADC count

}

/* Funksjon for å lesa kalibreringsinformasjon frå
 * ein spesielt signaturregister i mikrokontrolleren. */
//uint8_t ReadCalibrationByte( uint8_t index )
//{
//uint8_t result;
//
///* Load the NVM Command register to read the calibration row. */
//NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
//result = pgm_read_byte(index);
//
///* Clean up NVM Command register. */
//NVM_CMD = NVM_CMD_NO_OPERATION_gc;
//
//return( result );
//}


/*
void ioport_set_pin_high();
void ioport_set_pin_low();
void ioport_toggle_pin();

void ioport_set_group_high(LEDS,0bxxxxxxxx);
void ioport_set_group_low(LEDS,0bxxxxxxxx);
void ioport_tgl_group(LEDS,0bxxxxxxxx);

int ioport_pin_is_low(PB0)
*/

void timer_init()
{
	TCC0.CTRLA = TC_CLKSEL_DIV1024_gc;   // clk/1024
	TCC0.PER   = 7812;
	TCC0.INTCTRLA = TC_OVFINTLVL_LO_gc; // set low level interrupt on overflow
	TCC0.CNT   = 0;
}

void serial_init()
{

}

char serial_rx()
{
	return 0;
}
