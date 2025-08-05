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
#include "flash_test.h"

/******************************************************************************/
int test_flash_read(void)
{
	Flash_PageErase(ADDRESS);	// Erase the Flash Page at specified address
	Flash_Write(ADDRESS,BUFFER);	// Write the data in the BUFFER to the Flash memory
	if (Flash_Read(ADDRESS,4) == BUFFER)	// Read the data from the Flash memory and compares with BUFFER
	{
		return PASS;	// If read data matches,return PASS 
	}
	else
	{
		return FAIL;	// If read data doesn't matches,return FAIL
	}
}
/******************************************************************************/
int test_flash_pageErase(void)
{
	Flash_PageErase(ADDRESS);	// Erase the Flash page at specified address 
	Flash_Write(ADDRESS, BUFFER);	// Write the data in the BUFFER to the Flash memory
	Flash_PageErase(ADDRESS);	// Again Erase the Flash page at specified address
	if (Flash_Read(ADDRESS,4) == BUFFER)	// Read the data from the Flash memory and compares with BUFFER
	
	{
		return FAIL;	// If read data matches, return FAIL
	}
	else
	{
		return PASS;	// If read data doesn't matches, return PASS
	}
}
/******************************************************************************/
int test_flash_write(void)
{
	Flash_PageErase(ADDRESS);	// Erase the Flash page at specified address
	Flash_Write(ADDRESS,TEST);	// Write the data in the BUFFER to the FLASH memory 
	if (Flash_Read(ADDRESS,4) == TEST)	// Read the data from the FLASH memory and compares with TEST
	{
		return PASS;	// If read data matches, return PASS 
	}
	else
	{
		return FAIL;	// If read data doesn't matches,return FAIL 
	}
}
/******************************************************************************/
void test_flash(void)
{
	int a = test_flash_read();	
	int b = test_flash_pageErase();
	int c = test_flash_write();
	if (a == PASS && b == PASS && c == PASS)	// Check if all test cases (a,b and c) are passed
	{
		printf("All Test Cases of Flash PASSED!\n"); 	// Prints success message if all tests passed 
	}
	else
	{
		printf("Test cases of flash FAILED\n");		// Prints failure message if any test case is failed
	}
}
/******************************************************************************/
