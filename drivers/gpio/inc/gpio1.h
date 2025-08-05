/**
 * @file       gpio1.h
 * @brief      GPIO drivers.
 * @details    This driver can be used to access the GPIO pins.
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
#ifndef __GPIO_H__
#define __GPIO_H__

/***** Includes *****/
#include <stdint.h>
#include "mxc_device.h"
#include "mxc_delay.h"
#include "nvic_table.h"
#include "pb.h"
#include "board.h"
#include "gpio.h"

/***** Definitions *****/
#ifdef BOARD_EVKIT_V1
#define MXC_GPIO_PORT_IN MXC_GPIO2
#define MXC_GPIO_PIN_IN MXC_GPIO_PIN_6

#define MXC_GPIO_PORT_OUT MXC_GPIO0
#define MXC_GPIO_PIN_OUT MXC_GPIO_PIN_2

#define MXC_GPIO_PORT_INTERRUPT_IN MXC_GPIO2
#define MXC_GPIO_PIN_INTERRUPT_IN MXC_GPIO_PIN_7

#define MXC_GPIO_PORT_INTERRUPT_STATUS MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_STATUS MXC_GPIO_PIN_3
#endif

#ifdef BOARD_FTHR_REVA
#define MXC_GPIO_PORT_IN MXC_GPIO1
#define MXC_GPIO_PIN_IN MXC_GPIO_PIN_7

#define MXC_GPIO_PORT_OUT MXC_GPIO2
#define MXC_GPIO_PIN_OUT MXC_GPIO_PIN_0

#define MXC_GPIO_PORT_INTERRUPT_IN MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_IN MXC_GPIO_PIN_2

#define MXC_GPIO_PORT_INTERRUPT_STATUS MXC_GPIO0
#define MXC_GPIO_PIN_INTERRUPT_STATUS MXC_GPIO_PIN_9
#endif

/***** Function Prototypes *****/
/**
 * @brief      Setting the gpio pin to high/Low.
 * @param      port_num	Port number of the gpio on which the data has to set.
 * @param      pin_num	Pin number of the gpio on which the data has to set.
 * @param      value	If 1 gpio set to High, If 0 gpio set to Zero.
 * @return     return 0, If function is successful.
*/
int gpio_set(uint8_t port_num, uint8_t pin_num, uint8_t value);
/**
 * @brief      Read the data from the gpio pin.
 * @param      port_num	Port number of the gpio on which the data has to read.
 * @param      pin_num	Pin number of the gpio on which the data has to read.
 * @return     returns the data read on gpio pin.
*/
uint32_t gpio_get(uint8_t port_num, uint8_t pin_num);
#endif
