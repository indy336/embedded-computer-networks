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

// map the led to GPIO PA8
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOI, GPIO_PIN_14};
gpio_pin_t led3 = {PB_15, GPIOI, GPIO_PIN_15};

// this is the main method
int main()
{
	HAL_Init();
  init_sysclk_216MHz();
	
	init_gpio(led1, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	
	while (1)
	{	
		toggle_gpio(led2);
		HAL_Delay(1000);
	}
}
