/*
 * extension_board.c
 *
 *  Created on: 10.05.2019
 *      Author: Harald
 */

#include "main.h"

#include "string.h"
#include "extension_board.h"



void extension_board(void *pvParameters)
{
  int check = 0;
  //char pulseString[20];
  extern int count;
  extern int factor;
  extern int pulse;
  extern int period;

  /* Infinite loop */
  while (1)
  {
	  if(pulse > period)
	  {
		  pulse = period;
	  }

	  /* PWM generation
	     The count variable is incremented in the ISR*/
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

	  /*if(change){
		  if(pulse == 0)
			  pulse = period;
		  else
			  pulse = 0;
		  change = 0;
	  }*/

	  /* Rotation check
	     Determines the direction of rotation and changes pulse width and directional LEDs accordingly*/
	  if((HAL_GPIO_ReadPin(RE_A_GPIO_Port, RE_A_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(RE_B_GPIO_Port, RE_B_Pin) == GPIO_PIN_SET))
	  {
		  check = 0;
	  }
	  else if((HAL_GPIO_ReadPin(RE_B_GPIO_Port, RE_B_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(RE_A_GPIO_Port, RE_A_Pin) == GPIO_PIN_SET))
	  {
		  if(check == 2)
		  {
			  HAL_GPIO_WritePin(RE_L2_GPIO_Port, RE_L2_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(RE_L3_GPIO_Port, RE_L3_Pin, GPIO_PIN_RESET);
			  if(pulse >= factor)
			  {
				  pulse = pulse/factor;
				  //sprintf(pulseString, "%i\n\r", pulse);
				  //UART_Send_String(pulseString);
			  }
			  else if(pulse >= 1)
			  {
				  pulse = 0;
				  //sprintf(pulseString, "%i\n\r", (int)pulse);
				  //UART_Send_String(pulseString);
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
			  if(pulse == 0)
			  {
				  pulse = 1;
				  //sprintf(pulseString, "%i\n\r", (int)pulse);
				  //UART_Send_String(pulseString);
			  }
			  else if(pulse <= (period/factor))
			  {
				  pulse = pulse*factor;
				  //sprintf(pulseString, "%i\n\r", (int)pulse);
				  //UART_Send_String(pulseString);
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
