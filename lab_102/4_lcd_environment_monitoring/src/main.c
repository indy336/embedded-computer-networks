/*
 * main.c
 *
 * this is the skeleton for task 4
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2018
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include <stdio.h>
#include <adc.h>

// LCD DEFINES
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[2] = 
{
  "*    Ioannis Anastasiou    *",
  "*      Welcome to SHU      *"
};

// sensor pins
gpio_pin_t temp = {PF_10, GPIOF, GPIO_PIN_10};
gpio_pin_t light = {PA_0, GPIOA, GPIO_PIN_0};

// CALIBRATION VARIABLES

// limits
int sensor_max = 0;
int sensor_min = 4096;

// calibration function prototype
void calibrate_sensor(gpio_pin_t pin);

// CODE

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	//initialise temp sensor
	init_adc(temp);
	init_adc(light);
	
	// initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_RED);
  BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
  BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
  BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER); 
    
  // calibration
	calibrate_sensor(light);

	// main loop ...
	while (1)
	{
		// read sensors
		uint16_t temp_val = read_adc(temp);	
		uint16_t light_val = read_adc(light);	
			
		char str[12];		
		float light_per = ((light_val - sensor_min) / (float)(sensor_max - sensor_min)) * 100.0;
		
		// should constrain the light percentage to be 0 - 100
		// ...
		
		sprintf(str, "Light = %3.2f", light_per);
		BSP_LCD_ClearStringLine(6);
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
				
		float temp_c = ((((temp_val / 4095.0) * 3300) - 500) / 10.0);
		sprintf(str, "Temp = %3.2f", temp_c);
		BSP_LCD_ClearStringLine(7);
		BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str);
			
		HAL_Delay(100);
	}
}

// calibrate/
void calibrate_sensor(gpio_pin_t pin)
{
	// LDR Calibration procedure
	uint32_t tick = HAL_GetTick();
	while ((HAL_GetTick() - tick) < 10000)
	{
		uint16_t reading = read_adc(pin);
		
		// check against maximum sensor value
		// found so far
		if (reading > sensor_max)
		{
			sensor_max = reading;
		}
		
		// check against minimum sensor value 
		// found so far
		if (reading < sensor_min)
		{
			sensor_min = reading ;
		}
	}
}
