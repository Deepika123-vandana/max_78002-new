/**
 * @file       flash_test.h
 * @brief      testing flash driver.
 * @details    This header contains the definitions and function prototypes for
 *             testing Flash functionality.
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
#ifndef __FLASH_TEST__
#define __FLASH_TEST__

/***** Includes *****/
#include "flash.h"

/***** Definitions *****/
#define ADDRESS 0x10002000UL
#define BUFFER 0xDDDDDDDD
#define TEST 0xEEEEEEEE
#define PASS 1
#define FAIL 0

/***** Function Prototypes *****/
/**
 * @brief      Reads data from the flash memory and verifies it.
 * @return     Returns PASS if the operation is successful, otherwise returns FAIL.
 */
int test_flash_read(void);
/**
 * @brief      Erases a page in the flash memory and verifies it.
 * @return     Returns PASS if the operation is successful, otherwise returns FAIL.
 */
int test_flash_pageErase(void);
/**
 * @brief      Writes data to the flash memory and verifies it.
 * @return     Returns PASS if the operation is successful, otherwise returns FAIL.
 */
int test_flash_write(void);
/**
 * @brief      Main function to test flash memory functionality.
 */
void test_flash(void);

#endif
