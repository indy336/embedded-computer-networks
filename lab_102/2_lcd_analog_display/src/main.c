/*
 * main.c
 *
 * this is the skeleton for task 2
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
// define a message boarder (note the lcd is 28 characters wide using Font24)
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[2] = 
{
  "*    Ioannis Anastasiou    *",
  "*      Welcome to SHU      *"
};


// map the potentiometer to GPIO PA0
gpio_pin_t pot= {PA_0, GPIOA, GPIO_PIN_0};

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	// initialise the potentiometer
	init_adc(pot);
	  
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
    
  // delay a little ...
  HAL_Delay(5000);
  while (1)
	{
		
	// read the potentiometer and echo that value to the terminal
	uint16_t adc_val = read_adc(pot);	

	// format a string based around the adc value and print to lcd
	char str[12];
	sprintf(str, "ADC = %4d", adc_val);
	BSP_LCD_ClearStringLine(6);
	BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
		
	sprintf(str, "ADC = %03.2f", (adc_val/4095.0) * 100.0);
	BSP_LCD_ClearStringLine(7);
	BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(0, 200, 480, 20);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(0, 200, 480*(adc_val/4095.0), 20);
    
    HAL_Delay(1000);
}
}