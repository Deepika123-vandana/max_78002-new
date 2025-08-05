/**
 * @file       flash.h
 * @brief      flash drivers.
 * @details    This drivers can be used to access the Flash memory.
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
#ifndef __FLASH__
#define __FLASH__

/***** Includes *****/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include "flc_regs.h"
#include "flc_reva_regs.h"
#include "max78000.h"
#include "mxc_errors.h"

/***** Function Prototypes *****/
/**
 * @brief      Reads data from the flash memory.
 * @param      address  Address in the flash memory from where the data has to be read.
 * @param      len      Length of data to be read.
 * @return     Pointer to the data read from flash memory.
 */
uint8_t* Flash_Read(int address, int len);

void MXC_FLC_Com_Read(int address,void *buffer,int len);

void MXC_FLC_AI87_Flash_Operation(void);

int MXC_FLC_AI87_GetByAddress(mxc_flc_regs_t **flc, uint32_t addr);

int MXC_FLC_AI87_GetPhysicalAddress(uint32_t addr, uint32_t *result);

int MXC_FLC_RevA_MassErase(mxc_flc_reva_regs_t *flc);

int MXC_FLC_RevA_PageErase(mxc_flc_reva_regs_t *flc, uint32_t addr);
/**
 * @brief      Performs a total erase operation on the flash memory.
 * @return     Returns 0 if successful, otherwise returns an error code.
 */
int Flash_TotalErase();
/**
 * @brief      Erases a specific page in the flash memory.
 * @param      address  Address of the page to be erased.
 * @return     Returns 0 if successful, otherwise returns an error code.
 */
int Flash_PageErase(uint32_t address);
/**
 * @brief      Writes a 32-bit word to the flash memory.
 * @param      address  Address in the flash memory where the data is to be written.
 * @param      data     32-bit data to be written.
 * @return     Returns 0 if successful, otherwise returns an error code.
 */
int MXC_FLC_Write32(uint32_t address, uint32_t data);
/**
 * @brief      Writes 128 bits (4 x 32-bit words) to the flash memory.
 * @param      address  Address in the flash memory where the data is to be written.
 * @param      data     Pointer to the data (4 x 32-bit words) to be written.
 * @return     Returns 0 if successful, otherwise returns an error code.
 */
int MXC_FLC_Write128(uint32_t address, uint32_t *data);
/**
 * @brief      Writes data to the flash memory.
 * @param      address  Address in the flash memory where the data is to be written.
 * @param      buffer   Pointer to the data to be written.
 * @return     Returns 0 if successful, otherwise returns an error code.
 */
int Flash_Write(uint32_t address, uint64_t *buffer);

#endif
