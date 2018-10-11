/*
 * a_traffic_lights.c
 *
 * this is the main application skeleton for the student exercises in task 3
 *
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the led to GPIO PI
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t led3 = {PB_15, GPIOB, GPIO_PIN_15};

// this is the main method
int main()
{
	// we need to initialise the hal library and set up the SystemCoreClock
	// properly
	HAL_Init();
  init_sysclk_216MHz();
	
	// initialise the jpio pins
	init_gpio(led1, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	
	// loop forever...
	while (1)
	{	
		// turn red led on
		HAL_GPIO_WritePin ( GPIOI,GPIO_PIN_1, GPIO_PIN_SET);
		HAL_Delay(1000);
		
		// turn yellow led on
		HAL_GPIO_WritePin ( GPIOB,GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(1000);
		
		// turn red led off
		HAL_GPIO_WritePin ( GPIOI,GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_Delay(1000);
		
		// turn yellow led off
		HAL_GPIO_WritePin ( GPIOB,GPIO_PIN_14, GPIO_PIN_RESET);
		
		// turn green led on
		HAL_GPIO_WritePin ( GPIOB,GPIO_PIN_15, GPIO_PIN_SET);
		HAL_Delay(2000);
		// turn green led off
		HAL_GPIO_WritePin ( GPIOB,GPIO_PIN_15, GPIO_PIN_RESET);
		HAL_Delay(1000);
		
		
		
		
		
		
//		// toggle the led on the gpio pin
//		toggle_gpio(led1);		
//		// wait for 1 second
//		HAL_Delay(1000);
//		
//		toggle_gpio(led2);
//		HAL_Delay(1000);
//			
//		toggle_gpio(led3);
//		HAL_Delay(1000);
	}
}
