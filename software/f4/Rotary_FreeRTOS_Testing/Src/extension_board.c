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
char levelString[20];
extern int count;
extern int factor;
extern int level;
extern int maxCount;
extern int steps;
extern TIM_HandleTypeDef htim2;

void extension_board(void *pvParameters)
{
  /* Infinite loop */
  while (1)
  {
	  if(level > maxCount)
	  {
		  level = maxCount;
	  }

	  if((count >= 0)&&(count < level))
	  {
		  HAL_GPIO_WritePin(RE_L1_GPIO_Port, RE_L1_Pin, GPIO_PIN_SET);
	  }
	  else if((count >= level)&&(count < maxCount))
	  {
		  HAL_GPIO_WritePin(RE_L1_GPIO_Port, RE_L1_Pin, GPIO_PIN_RESET);
	  }
	  else if(count >= maxCount)
	  {
	  	  count = 0;
	  }



	  if(change){
		  if(level == 0)
			  level = maxCount;
		  else
			  level = 0;
		  change = 0;
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
			  if(level >= factor)
			  {
				  level = level/factor;
				  sprintf(levelString, "%i\n\r", level);
				  UART_Send_String(levelString);
			  }
			  else if(level >= 1)
			  {
				  level = 0;
				  sprintf(levelString, "%i\n\r", (int)level);
				  UART_Send_String(levelString);
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
			  if(level == 0)
			  {
				  level = 1;
				  sprintf(levelString, "%i\n\r", (int)level);
				  UART_Send_String(levelString);
			  }
			  else if(level <= (maxCount/factor))
			  {
				  level = level*factor;
				  sprintf(levelString, "%i\n\r", (int)level);
				  UART_Send_String(levelString);
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

