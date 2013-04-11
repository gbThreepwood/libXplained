/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 *
 * Filename: i2c.h
 *
 *  Created on: 6. apr. 2013
 *
 * Author: eirik
 *
 * Copyright:GPL V3
 * See http://www.gnu.org/licenses/gpl.html
 *
 * Description:
 *
 *********************************************/

#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <avr/pgmspace.h>

#include <util/atomic.h>
#include <util/delay.h>

/*! Buffer size defines */
#define I2C_WRITE_BUFFER_SIZE         8
#define I2C_READ_BUFFER_SIZE          8

/*! Transaction status defines. */
#define I2C_STATUS_READY              0
#define I2C_STATUS_BUSY               1

/*! Transaction result enumeration. */
typedef enum I2CM_RESULT_enum {
	I2CM_RESULT_UNKNOWN          = (0x00<<0),
	I2CM_RESULT_OK               = (0x01<<0),
	I2CM_RESULT_BUFFER_OVERFLOW  = (0x02<<0),
	I2CM_RESULT_ARBITRATION_LOST = (0x03<<0),
	I2CM_RESULT_BUS_ERROR        = (0x04<<0),
	I2CM_RESULT_NACK_RECEIVED    = (0x05<<0),
	I2CM_RESULT_FAIL             = (0x06<<0),
} I2CM_RESULT_t;

/*! Command status enumeration. */
typedef enum I2C_DRIVER_STATUS_enum {
	I2C_DRIVER_STATUS_FALSE          	= (0x00<<0),
	I2C_DRIVER_STATUS_FAILURE          	= (0x01<<0),
	I2C_DRIVER_STATUS_OK			  	= (0x02<<0),
	I2C_DRIVER_STATUS_UNKNOWN			= (0x03<<0),
	I2C_DRIVER_STATUS_RES1       		= (0x04<<0),
	I2C_DRIVER_STATUS_RES2			    = (0x05<<0),
	I2C_DRIVER_STATUS_RES3              = (0x06<<0),
} I2C_DRIVER_STATUS_t;

typedef struct I2C_Master {
	TWI_t *interface;                  /*!< TWI_t - Struct containing all TWI registers */
	register8_t address;                            /*!< Slave address */
	register8_t txData[I2C_WRITE_BUFFER_SIZE];  /*!< Data to write */
	register8_t rxData[I2C_READ_BUFFER_SIZE];    /*!< Read data */
	register8_t bytesToWrite;                       /*!< Number of bytes to write */
	register8_t bytesToRead;                        /*!< Number of bytes to read */
	register8_t bytesWritten;                       /*!< Number of bytes written */
	register8_t bytesRead;                          /*!< Number of bytes read */
	register8_t status;                             /*!< Status of transaction */
	register8_t result;                             /*!< Result of transaction */
}I2C_Master_t;

#define I2C_INTERFACE TWIC

#endif /* I2C_H_ */
