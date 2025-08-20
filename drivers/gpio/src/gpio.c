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
#include "gpio1.h"

/***** Functions *****/
/**
 * @brief Sets the state of a specified GPIO pin.
 * @param port_num The port number (0 to 3).
 * @param pin_num The pin number within the port.
 * @param value The value to set the pin to (0 for low, 1 for high).
 * @return 0 if successful, 1 if an invalid port number is specified.
 */
int gpio_set(uint8_t port_num, uint8_t pin_num, uint8_t value)	// Function to set the state of a GPIO pin
{
	
    mxc_gpio_cfg_t gpio;	// GPIO configuration structure
    
    switch(port_num)	// Select the GPIO port based on port_num
    {
	case 0:
	    gpio.port = MXC_GPIO0;		// Select port 0
	    gpio.mask = 1UL << pin_num;		// Mask for the specific pin
	    gpio.pad = MXC_GPIO_PAD_NONE;	// No pad configuration	
	    gpio.func = MXC_GPIO_FUNC_OUT;	// Set function to output
	    gpio.vssel = MXC_GPIO_VSSEL_VDDIO;	// Voltage select for VDDIO
	    gpio.drvstr = MXC_GPIO_DRVSTR_0;	// Drive strength configuration
	    break;
	case 1:
	    gpio.port = MXC_GPIO1;	// Select port 1
	    gpio.mask = 1UL << pin_num;		
	    gpio.pad = MXC_GPIO_PAD_NONE;
	    gpio.func = MXC_GPIO_FUNC_OUT;
	    gpio.vssel = MXC_GPIO_VSSEL_VDDIO;
	    gpio.drvstr = MXC_GPIO_DRVSTR_0;
	    break;
	case 2:
	    gpio.port = MXC_GPIO2;	// Select port 2
	    gpio.mask = 1UL << pin_num;
	    gpio.pad = MXC_GPIO_PAD_NONE;
	    gpio.func = MXC_GPIO_FUNC_OUT;
	    gpio.vssel = MXC_GPIO_VSSEL_VDDIO;
	    gpio.drvstr = MXC_GPIO_DRVSTR_0;
	    break;
	case 3:
	    gpio.port = MXC_GPIO3;	// Select port 3
	    gpio.mask = 1UL << pin_num;
	    gpio.pad = MXC_GPIO_PAD_NONE;
	    gpio.func = MXC_GPIO_FUNC_OUT;
	    gpio.vssel = MXC_GPIO_VSSEL_VDDIO;
	    gpio.drvstr = MXC_GPIO_DRVSTR_0;
	    break;
	default:
	    printf("\nInvalid PORT");	// Print an error message for an invalid port
	    return 1;		// Return an error code
    }
    MXC_GPIO_Config(&gpio);	// Configure the GPIO with the settings specified in gpio
    if(value == 1)		// Check if the value to set is high (1)
    {
	    MXC_GPIO_OutSet(gpio.port, gpio.mask);	// Set the GPIO pin
	    return 0;		// Return success code
    }
    else if (value == 0)	// Check if the value to set is high (0)
    {
	    MXC_GPIO_OutClr(gpio.port, gpio.mask);	// Clear the GPIO pin
	    return 0;		// Return success code
    }
	return 1;		// Return error code if value is not 0 or 1 
}
/**********************************************************************************/
uint32_t gpio_get(uint8_t port_num, uint8_t pin_num)	// Function to get the state of a GPIO pin
{
	mxc_gpio_cfg_t gpio;	// GPIO configuration structure

	switch(port_num)	// Select the GPIO port based on port_num
	{
		case 0:
		    gpio.port = MXC_GPIO0;		// Select port 0
		    gpio.mask = 1UL << pin_num;		// Mask for the specific pin
		    gpio.pad = MXC_GPIO_PAD_PULL_UP;	// Enable pull-up resistor
		    gpio.func = MXC_GPIO_FUNC_IN;	//Set Function to input
		    gpio.vssel = MXC_GPIO_VSSEL_VDDIO;	// Voltage select for VDDIO
		    gpio.drvstr = MXC_GPIO_DRVSTR_0;	// Drive strength configuration
		    break;
		case 1:
		    gpio.port = MXC_GPIO1;	// Select port 1
		    gpio.mask = 1UL << pin_num;
		    gpio.pad = MXC_GPIO_PAD_PULL_UP;
		    gpio.func = MXC_GPIO_FUNC_IN;
		    gpio.vssel = MXC_GPIO_VSSEL_VDDIO;
		    gpio.drvstr = MXC_GPIO_DRVSTR_0;
		    break;
		case 2:
		    gpio.port = MXC_GPIO2;	// Select port 2
		    gpio.mask = 1UL << pin_num;
		    gpio.pad = MXC_GPIO_PAD_PULL_UP;
		    gpio.func = MXC_GPIO_FUNC_IN;
		    gpio.vssel = MXC_GPIO_VSSEL_VDDIO;
		    gpio.drvstr = MXC_GPIO_DRVSTR_0;
		    break;
		case 3:
		    gpio.port = MXC_GPIO3;	// Select port 3
		    gpio.mask = 1UL << pin_num;
		    gpio.pad = MXC_GPIO_PAD_PULL_UP;
		    gpio.func = MXC_GPIO_FUNC_IN;
		    gpio.vssel = MXC_GPIO_VSSEL_VDDIO;
		    gpio.drvstr = MXC_GPIO_DRVSTR_0;
		    break;
		default:
		    printf("\nInvalid PORT");	// Print an error message for an invalid port
		    break;    
	}
	MXC_GPIO_Config(&gpio);	// Configure the GPIO with the settings specified in gpio
	return (MXC_GPIO_InGet(gpio.port, gpio.mask) >> pin_num);	// Read and return the state of the pin

}
