/**
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: OBL3_5.c
 *
 *  Created on: 8. apr. 2013
 *
 * Author: Eirik Haustveit
 *
 * Copyright (c) Eirik Haustveit, 2013
 *
 * Description:
 *
*/

/*
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

/*! \file
 *
 * \brief
 *      XMEGA i2c driver, source file.
 *
 *      This driver uses the Xmega built in TWI driver.
 *      Atmel refers to i2c as two wire interface(TWI).
 *
*/

#include "i2c.h"

/*! \brief Initializes the i2c master driver.
 *
 *  I2C master initialization function.
 *  Enables read and write interrupts.
 *  Remember to use sei() to enable interrupts globally.
 *
 *  The baudrate parameter is the parameter for the baudrate register,
 *  and needs to be calculated. Standard frequency is 100kHz or 400kHz.
 *
 *  #define I2C_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)
 *
 *  \param i2c                      The I2C_Master_t struct instance.
 *  \param module                   The I2C module to use.
 *  \param baudrate					The baud rate register value.
 */
void i2c_initialize_master(I2C_Master_t *i2c, TWI_t *interface_module, uint8_t baudrate)
{
	/* Sets the I2C_Master_t interface struct to the specified interface */
	i2c->interface = interface_module;

	/* ADDR – Address register */
	i2c->interface->MASTER.ADDR = i2c->address;

	/* BAUD – Baud Rate register */
	i2c->interface->MASTER.BAUD = baudrate;

	TWI_MASTER_INTLVL_t intLevel;

	/* RIEN: Read Interrupt Enable
	 * WIEN: Write Interrupt Enable
	 * ENABLE: Enable TWI Master */
	i2c->interface->MASTER.CTRLA =
			TWI_MASTER_INTLVL0_bm |
			TWI_MASTER_INTLVL1_bm |
			TWI_MASTER_RIEN_bm |
			TWI_MASTER_WIEN_bm |
			TWI_MASTER_ENABLE_bm;

	/* SMEN: Smart Mode Enable
	 * QCEN: Quick Command Enable */
	i2c->interface->MASTER.CTRLB = TWI_MASTER_QCEN_bm | TWI_MASTER_SMEN_bm;

	/* ACKACT: Acknowledge Action
	 * CMD[1:0]: Command */

	/*
	 * 00 NOACT X Reserved
	 * 01 START X Execute acknowledge action succeeded by repeated START condition
	 * 10 BYTEREC W No operation R Execute acknowledge action succeeded by a byte receive
	 * 11 STOP X Execute acknowledge action succeeded by issuing a STOP condition */
	i2c->interface->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD0_bm;

	i2c->interface->MASTER.STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
}

/*! \brief Returns the TWI bus state.
 *
 *  Returns the I2C bus state: unknown, idle, owner or busy.
 *
 *  \param *i2c Pointer to the I2C_Master_t struct instance.
 *
 *  \retval TWI_MASTER_BUSSTATE_UNKNOWN_gc Unknown bus state.
 *  \retval TWI_MASTER_BUSSTATE_IDLE_gc    Idle bus state.
 *  \retval TWI_MASTER_BUSSTATE_OWNER_gc   Bus state owned by the master.
 *  \retval TWI_MASTER_BUSSTATE_BUSY_gc    Busy bus state.
 */
TWI_MASTER_BUSSTATE_t i2c_master_state(I2C_Master_t *i2c)
{
	TWI_MASTER_BUSSTATE_t i2c_state;

	/* Sets i2c_state to the state from MASTER.STATUS register
	 * The two rightmost bits from status register. */
	i2c_state = i2c->interface->MASTER.STATUS & TWI_MASTER_BUSSTATE_gm;

	return i2c_state;
}

/*! \brief Checks if transaction is ready.
 *
 *  Checks whether the I2C Master is ready for a new transaction.
 *
 *  \param twi The I2C_Master_t struct instance.
 *
 *  \retval true  If transaction could be started.
 *  \retval false If transaction could not be started.
 */
register8_t i2c_MasterIsReady(I2C_Master_t *i2c)
{
	register8_t twi_status = (i2c->status & 0);

	return twi_status;
}





/*! \brief Transmits data on the i2c bus.
 *
 *  Transmits data on the i2c bus.
 *
 *  \param *i2c Pointer to the I2C_Master_t struct instance.
 *
 *  \retval I2C_DRIVER_STATUS_FAILURE Failed to transmit data.
 */
register8_t i2c_master_tx_data(I2C_Master_t *i2c,
								uint8_t rx_address,
								uint8_t *dataToWrite,
								uint8_t bytesToWrite)
{
	I2C_DRIVER_STATUS_t status = I2C_DRIVER_STATUS_UNKNOWN;

	/* Check if bus is ready */
	if (i2c->status == I2C_STATUS_READY)
	{
		i2c->status = I2C_STATUS_BUSY;
		i2c->result = I2CM_RESULT_UNKNOWN;

		/* Left bit shift since bit 0 is the ADDREN: Address Enable bit. */
		i2c->address = rx_address<<1;
	}

	i2c->interface->MASTER;

	return status;
}








register8_t i2c_master_rx_data()
{
	return 0;
}
/*!
  Initializes the i2c slave driver.
*/
void i2c_initialize_slave()
{
	I2C_INTERFACE.SLAVE;
}



ISR(TWIC_TWIM_vect)
{
  //i2c_MasterInterruptHandler(&i2cMaster);
}
