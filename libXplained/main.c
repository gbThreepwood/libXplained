/*
 * main.c
 *
 *  Created on: 30. mar. 2013
 *      Author: Eirik Haustveit
 */


//#define F_CPU 8000000UL
//#define __AVR_ATxmega128A1__

#include "main.h"
#include "xmega_init.h"
#include "lcd_driver.h"

#define PB_PORT PORTD
#define LED_PORT PORTE

volatile uint8_t Int_flag = 0;
extern uint8_t  systemEventFlags;			// system event flags

int main()
{
	//set_bit(ucEventFlags,0b00000001);
	Config32MHzClock();

	struct flags_t {
	  uint8_t flag_1_ : 1;
	  uint8_t flag_2_ : 1;
	  uint8_t flag_3_ : 1;
	  uint8_t flag_4_ : 1;
	  uint8_t flag_5_ : 1;
	  uint8_t flag_6_ : 1;
	  uint8_t flag_7_ : 1;
	  uint8_t flag_8_ : 1;
	};

	CCP = 0x00; /* CCP - Configuration Change Protection register */
	CLK.PSCTRL = 0x00; /**/
	xmega_init(); /* Set opp mikrokontrolleren. */


	/* PMIC - Programmable multilevel interrupt controller.
	 * Styrer avbruddssystemet */
	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	PMIC.INTPRI = 0x00;
	PMIC.STATUS;

	//  set_sleep_mode(SLEEP_MODE_PWR_SAVE);    // same as Powerdown but RTC on/wake source
	//  set_sleep_mode(SLEEP_MODE_STANDBY);     // same as Powerdown but System clock on
	//  set_sleep_mode(SLEEP_MODE_EXT_STANDBY); // almost idle, but cpu/peripheral clocks off
	//  set_sleep_mode(SLEEP_MODE_IDLE);        // highest setting; wake on any interrupt
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	sei(); /* Aktiver globale avbrudd */

	for(;;) /* Begin main loop */
	{
	    sleep_enable();
	    sleep_cpu();

//		sbi(PORTE_OUT,5);
//		cbi(PORTE_OUT,5);

//		if(!(PORTD.IN & (1<<4)))
//		{
//			PORTE.OUT = ~i;
//			i++;
//		}
//
//		if(!(PORTD.IN & (1<<4)))
//		{
//			//PORTE.OUT |= 1 << 5;
//			//PORTE.OUT = 0x00;
//		}
//
//		if(!(PORTD.IN & (1<<5)))
//		{
//			//PORTE.OUT &= ~(1 << 5);
//			//PORTE.OUT = 0xFF;
//		}



	} /* End main loop */

	return 0;
}


/* Funksjon for å blinka ein lysdiode som indikator på at
 * programmet ikkje har låst seg. */
void heartbeat()
{
	PORTE.OUT ^= 1 << 1; /* LED 1 */
}

void Config32MHzClock(void)
{
  CCP = CCP_IOREG_gc; //Security Signature to modify clock

  // initialize clock source to be 32MHz internal oscillator (no PLL)
  OSC.CTRL |= OSC_RC32MEN_bm; // enable 32MHz oscillators

  while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // wait for oscillator ready

  CCP = CCP_IOREG_gc; //Security Signature to modify clock
  CLK.CTRL = 0x01; //select sysclock 32MHz osc
};

ISR(PORTD_INT0_vect)
{
	PORTE.OUT ^= 1 << 4;
	PORTE.OUT ^= 1 << 3;
	PORTE.OUT ^= 1 << 2;
};

ISR(PORTD_INT1_vect)
{
	PORTE.OUT ^= 1 << 4;
	PORTE.OUT ^= 1 << 3;
	PORTE.OUT ^= 1 << 2;
};

ISR(TCC0_OVF_vect)
{
//    PORTF.OUT ^= (1<<0);   // Eval-01 64A3 RevA, Eval-USB
//    PORTF.OUT ^= (1<<2);   // Eval-01 128A3, 64A3 RevB
};

#define  MS_CNT     370
void delay_ms( uint16_t ms )
{
volatile uint16_t cnt;

   while ( ms-- != 0 )           // execute 1ms delay loop this many times
   {
      for ( cnt = MS_CNT; cnt != 0; cnt-- )  // 1ms delay loop
        ;
   }
}
