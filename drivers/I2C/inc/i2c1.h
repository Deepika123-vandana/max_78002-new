/**
 * @file       I2C1.h
 * @brief      I2C drivers.
 * @details    This driver can be used to access the I2C pins.
 */

/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. All Rights Reserved.
 * (now owned by Analog Devices, Inc.),
 * Copyright (C) 2023 Analog Devices, Inc. All Rights Reserved. This software
 * is proprietary to Analog Devices, Inc. and its licensors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/
 
/* Define to prevent redundant inclusion */
#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/***** Includes *****/
#include <stdint.h>           // Standard integer types
#include <stddef.h>	      // Standard definitions
#include <stdio.h>            // Standard input/output functions 	
#include <string.h>           // String handling functions
#include "board.h"            // Board-specific definitions
#include "mxc_device.h"       // Device-specific definitions
#include "mxc_delay.h"        // Delay functions
#include "nvic_table.h"       // NVIC (Interrupt Controller) definitions
#include "mxc_errors.h"       // Error codes
#include "i2c.h"              // Include Maxim's I2C header

/***** Definitions *****/
#ifdef BOARD_EVKIT_V1
#define I2C_MASTER MXC_I2C2   // Define I2C2 as the master if using EVKIT_V1 board
#define I2C_SCL_PIN 30        // SCL pin number for I2C2
#define I2C_SDA_PIN 31        // SDA pin number for I2C2
#else
#define I2C_MASTER MXC_I2C1   // Define I2C1 as the master otherwise
#define I2C_SCL_PIN 16        // SCL pin number for I2C1
#define I2C_SDA_PIN 17        // SDA pin number for I2C1
#endif

#define I2C_FREQ 100000       // I2C frequency set to 100kHz

/***** Function Prototypes *****/
/**
 * @brief      Initializes the I2C master interface
 *             Prints error message if initialization fails.
*/
void i2c_init(void);
/**
 * @brief      Scan for I2C slave devices on the bus.
 *             Setup the I2C frequency.
*/
void i2c_scan(void);
/**
 * @brief      Writes data to a specific register of an I2C slave device.
 * @param      address	     Address of the slave device.
 * @param      reg_adress    Address of the register to which writing to be done.
 * @param      data	     Pointer to the address of the data to be written in the Register address.
 * @param      length	     Length of the data to be written.
 * @return     return 0, If function is successful.
*/
int i2c_write_register(uint8_t address, uint8_t reg_adress, uint8_t* data, uint8_t length);
/**
 * @brief      Reads data from the specific register of an I2C slave device.
 * @param      address	     Address of the slave device.
 * @param      reg_adress    Address of the register from which reading to be done.
 * @param      buffer	     Pointer to the address of the buffer where reading is to be done.
 * @param      length	     Length of the buffer.
 * @return     return 0, If function is successful.
*/
int i2c_read_register(uint8_t address, uint8_t reg_adress, uint8_t* buffer, uint8_t length);
#ifdef __cplusplus
}
#endif

#endif // I2C_H
