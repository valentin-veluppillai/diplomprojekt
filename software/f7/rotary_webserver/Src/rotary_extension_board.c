/*
 * extension_board.c
 *
 *  Created on: 10.05.2019
 *      Author: Harald
 */

#include <rotary_extension_board.h>
#include "main.h"

#include "string.h"

int check = 0;
extern int count;
extern int pulse;
extern int period;
int steps = 20;
extern TIM_HandleTypeDef htim2;

void rotary_extension_board_init(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	HAL_GPIO_WritePin(GPIOF, LED_GND_Pin|RE_L2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, RE_L3_Pin|RE_C_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RE_L1_GPIO_Port, RE_L1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RE_VCC_GPIO_Port, RE_VCC_Pin, GPIO_PIN_SET);

	GPIO_InitStruct.Pin = LED_GND_Pin|RE_L2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = RE_L3_Pin|RE_C_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = RE_B_Pin|RE_A_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = RE_L1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RE_L1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = RE_SW_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(RE_SW_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin|RE_VCC_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	xTaskCreate(rotary_extension_board, "rexb", 100, NULL, 10, NULL);
}

void rotary_extension_board()
{
  /* Infinite loop */
  int count = 0;
  int period = 0;
  int pulse = 0;
  while (1)
  {
	  if(pulse >= period)
	  {
		  pulse = period;
	  }

	  if((count >= 0)&&(count < pulse))
	  {
		  HAL_GPIO_WritePin(RE_L1_GPIO_Port, RE_L1_Pin, GPIO_PIN_SET);
	  }
	  else if((count >= pulse)&&(count < period))
	  {
		  HAL_GPIO_WritePin(RE_L1_GPIO_Port, RE_L1_Pin, GPIO_PIN_RESET);
	  }
	  else if(count >= period)
	  {
	  	  count = 0;
	  }

	  if((HAL_GPIO_ReadPin(RE_A_GPIO_Port, RE_A_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(RE_B_GPIO_Port, RE_B_Pin) == GPIO_PIN_SET)){
		  check = 0;
	  }
	  else if((HAL_GPIO_ReadPin(RE_B_GPIO_Port, RE_B_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(RE_A_GPIO_Port, RE_A_Pin) == GPIO_PIN_SET))
	  {
		  if(check == 2)
		  {
			  HAL_GPIO_WritePin(RE_L2_GPIO_Port, RE_L2_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(RE_L3_GPIO_Port, RE_L3_Pin, GPIO_PIN_RESET);
			  if(pulse >= (period/steps))
			  {
				  pulse = pulse - (period/steps);
			  }
			  check = 3;
		  }
		  else if(check == 0)
		  {
			  check = -1;
		  }
	  }
	  else if((HAL_GPIO_ReadPin(RE_A_GPIO_Port, RE_A_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(RE_B_GPIO_Port, RE_B_Pin) == GPIO_PIN_SET))
	  {
		  if(check == -2)
		  {
			  HAL_GPIO_WritePin(RE_L2_GPIO_Port, RE_L2_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(RE_L3_GPIO_Port, RE_L3_Pin, GPIO_PIN_SET);
			  if(pulse <= (period-(period/steps)))
			  {
				  pulse = pulse + (period/steps);
			  }
			  check = 3;
		  }
		  else if (check == 0)
		  {
			  check = 1;
		  }
	  }
	  else if((HAL_GPIO_ReadPin(RE_A_GPIO_Port, RE_A_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(RE_B_GPIO_Port, RE_B_Pin) == GPIO_PIN_RESET))
	  {
		  if((check == 1)||(check == -1))
		  {
			  check = 2 * check;
		  }
	  }
  }
  vTaskDelete(NULL);
}

