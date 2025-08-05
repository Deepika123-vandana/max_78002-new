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

/***** Includes *****/
#include "flash.h"


/**********************************************************************************/
void MXC_FLC_AI87_Flash_Operation(void)
{
    /* Flush all instruction caches */
    MXC_GCR->sysctrl |= MXC_F_GCR_SYSCTRL_ICC0_FLUSH;

    /* Wait for flush to complete */
    while (MXC_GCR->sysctrl & MXC_F_GCR_SYSCTRL_ICC0_FLUSH) {}

    // Clear the line fill buffer by reading 2 pages from flash
    volatile uint32_t *line_addr;
    volatile uint32_t __unused line; // __unused attribute removes warning
    line_addr = (uint32_t *)(MXC_FLASH_MEM_BASE);
    line = *line_addr;
    line_addr = (uint32_t *)(MXC_FLASH_MEM_BASE + MXC_FLASH_PAGE_SIZE);
    line = *line_addr;
}
/**********************************************************************************/
int MXC_FLC_AI87_GetByAddress(mxc_flc_regs_t **flc, uint32_t addr)
{
    if ((addr >= MXC_FLASH_MEM_BASE) && (addr < (MXC_FLASH_MEM_BASE + MXC_FLASH_MEM_SIZE))) {
        *flc = MXC_FLC0;
    } else if ((addr >= MXC_INFO_MEM_BASE) && (addr < (MXC_INFO_MEM_BASE + MXC_INFO_MEM_SIZE))) {
        *flc = MXC_FLC0;
    } else {
        return E_BAD_PARAM;
    }

    return E_NO_ERROR;
}
/**********************************************************************************/
int MXC_FLC_AI87_GetPhysicalAddress(uint32_t addr, uint32_t *result)
{
    if ((addr >= MXC_FLASH_MEM_BASE) && (addr < (MXC_FLASH_MEM_BASE + MXC_FLASH_MEM_SIZE))) {
        *result = addr - MXC_FLASH_MEM_BASE;
    } else if ((addr >= MXC_INFO_MEM_BASE) && (addr < (MXC_INFO_MEM_BASE + MXC_INFO_MEM_SIZE))) {
        *result = (addr & (MXC_INFO_MEM_SIZE - 1)) + MXC_FLASH_MEM_SIZE;
    } else {
        return E_BAD_PARAM;
    }

    return E_NO_ERROR;

}
/**********************************************************************************/
uint8_t* Flash_Read(int address, int len) {
    uint8_t *buffer = malloc(len * sizeof(uint8_t));	// Allocate memory for the buffer to store the data read from flash
    if(buffer == NULL) {
        return NULL;
    }
    MXC_FLC_Com_Read(address, buffer, len);		// Read the data from the flash memory into the buffer

    for(int i=0; i < len / 2; i++)
    {
	    uint8_t temp =buffer[i];
	    buffer[i] = buffer[len - i - 1];
	    buffer[len - i - 1] = temp;
    }
    return buffer;	// Return the pointer to the buffer containing the data
}
/**********************************************************************************/
int Flash_TotalErase()
{
	int err, i;
	mxc_flc_regs_t *flc;	// Pointer to flash controller registers
	for(i = 0; i < MXC_FLC_INSTANCES; i++)
	{
		flc = MXC_FLC_GET_FLC(i);
		err = MXC_FLC_RevA_MassErase((mxc_flc_reva_regs_t *)flc);	// Perform a mass erase operation on the current flash controller
		if (err != E_NO_ERROR) {
			return err;
		}
		MXC_FLC_AI87_Flash_Operation();		// Performing additional flash operations to flush the cache
	}
	return 0;	// Return 0 if all operations were successful	
}
/**********************************************************************************/
int Flash_PageErase(uint32_t address)
{
	int err;
	uint32_t addr;
        mxc_flc_regs_t *flc = NULL;	// Pointer to flash controller registers, initialized to NULL	
    	// Get the flash controller instance for the given address
	if ((err = MXC_FLC_AI87_GetByAddress(&flc, address)) != E_NO_ERROR) {
        return err;
	}
	// Get the physical address for the given address
	if ((err = MXC_FLC_AI87_GetPhysicalAddress(address, &addr)) < E_NO_ERROR) {
        return err;
	}
	err = MXC_FLC_RevA_PageErase((mxc_flc_reva_regs_t *)flc, address);	// Perform a page erase operation on the flash memory
	MXC_FLC_AI87_Flash_Operation();	// Flush the cache

	return 0;	// Return 0 if all operations were successful
}
/**********************************************************************************/
int Flash_Write(uint32_t address, uint64_t *buffer)
{
	size_t size = 0;
	while(buffer[size]!=0)	// Calculate the size of the buffer
	{
		size++;
	}
	uint32_t length=(size-1) * sizeof(uint64_t);	// Calculate the length of data to be written in bytes
    	int err;
	uint32_t bytes_written;
	uint32_t current_data_32;
	uint8_t *current_data = (uint8_t *)&current_data_32;
	uint8_t *buffer8 = (uint8_t *)buffer;

	// Align the address to a word boundary and read/write if we have to
	if (address & 0x3) {
        // Figure out how many bytes we have to write to round up the address
        bytes_written = 4 - (address & 0x3);

        // Save the data currently in the flash
        memcpy(current_data, (void *)(address & (~0x3)), 4);

        // Modify current_data to insert the data from buffer
        memcpy(&current_data[4 - bytes_written], buffer8, bytes_written);

        // Write the modified data
        if ((err = MXC_FLC_Write32(address - (address % 4), current_data_32)) != E_NO_ERROR) {
            return err;
        }
	// Update address, length, and buffer pointer
        address += bytes_written;
        length -= bytes_written;
        buffer8 += bytes_written;
     	}

	// Align the address to a 4-word (128bit) boundary
	while ((length >= 4) && ((address & 0xF) != 0)) {
        	memcpy(current_data, buffer8, 4);
        	if ((err = MXC_FLC_Write32(address, current_data_32)) != E_NO_ERROR) {
         	    return err;
         	}
         	address += 4;
         	length -= 4;
         	buffer8 += 4;
     	}
	// Write 128-bit (16-byte) blocks to the flash memory
     	if (length >= 16) {
        	uint32_t buff128[4];
         	while (length >= 16) {
             	memcpy(buff128, buffer8, 16);
             	if ((err = MXC_FLC_Write128(address, buff128)) != E_NO_ERROR) {
                	 return err;
             	}
             	address += 16;
             	length -= 16;
             	buffer8 += 16;
         	}
     	}
	// Write remaining 32-bit words to the flash memory
     	while (length >= 4) {
        	memcpy(current_data, buffer8, 4);
         	if ((err = MXC_FLC_Write32(address, current_data_32)) != E_NO_ERROR) {
         	    return err;
         	}
         	address += 4;
         	length -= 4;
         	buffer8 += 4;
     	}
	// Write any remaining bytes to the flash memory
     	if (length > 0) {
        	// Save the data currently in the flash
         	memcpy(current_data, (void *)(address), 4);

         	// Modify current_data to insert the data from buffer
         	memcpy(current_data, buffer8, length);

         	if ((err = MXC_FLC_Write32(address, current_data_32)) != E_NO_ERROR) {
             		return err;
         	}
     	}

     	return E_NO_ERROR;	// Return 0 if the operation was successful
}
