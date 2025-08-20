/**
 * @file       gpio_test.h
 * @brief      testing gpio driver.
 * @details    This header contains the definitions and function prototypes for
 *             testing GPIO functionality.
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
#ifndef __test_gpio__
#define __test_gpio_

/***** Includes *****/
#include "gpio1.h"

/***** Definitions *****/
#define PORT 2	//GPIO PORT 2
#define PIN4 4	//GPIO PIN 4 
#define PIN5 5	//GPIO PIN 5
#define VALUE0 0
#define VALUE1 1
#define PASS 1
#define FAIL 0

/***** Function Prototypes *****/
/***** Function Prototypes *****/
/**
 * @brief      Sets the GPIO pin to a specific value.
 * @return     Returns PASS if the operation is successful, otherwise returns FAIL.
 */
int test_gpio_set(void);
/**
 * @brief      Gets the current value of the GPIO pin.
 * @return     Returns the value of the GPIO pin.
 */
int test_gpio_get(void);
/**
 * @brief      Toggles the value of the GPIO pin.
 * @return     Returns PASS if the operation is successful, otherwise returns FAIL.
 */
int test_gpio_toggle(void);
/**
 * @brief      Main function to test GPIO functionality.
 */
void test_gpio(void);

#endif
