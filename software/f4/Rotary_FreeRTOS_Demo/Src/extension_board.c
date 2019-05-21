/*
 * extension_board.c
 *
 *  Created on: 10.05.2019
 *      Author: Harald
 */

#include "main.h"

#include "string.h"
#include "extension_board.h"

int check = 0;
extern int count;
extern int pulse;
extern int period;
int steps = 20;
extern TIM_HandleTypeDef htim2;
void extension_board(void *pvParameters)
{
  /* Infinite loop */
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

