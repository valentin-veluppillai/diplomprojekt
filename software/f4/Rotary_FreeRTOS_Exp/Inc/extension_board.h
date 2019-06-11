/*
 * extension_board.h
 *
 *  Created on: 10.05.2019
 *      Author: Harald
 */

#ifndef EXTENSION_BOARD_H_
#define EXTENSION_BOARD_H_

#include "stm32f4xx_hal.h"

#define LED_GND_Pin GPIO_PIN_12
#define LED_GND_GPIO_Port GPIOF
#define RE_L2_Pin GPIO_PIN_13
#define RE_L2_GPIO_Port GPIOF
#define RE_L3_Pin GPIO_PIN_10
#define RE_L3_GPIO_Port GPIOE
#define RE_B_Pin GPIO_PIN_12
#define RE_B_GPIO_Port GPIOE
#define RE_C_Pin GPIO_PIN_14
#define RE_C_GPIO_Port GPIOE
#define RE_A_Pin GPIO_PIN_15
#define RE_A_GPIO_Port GPIOE
#define RE_L1_Pin GPIO_PIN_11
#define RE_L1_GPIO_Port GPIOD
#define RE_SW_Pin GPIO_PIN_12
#define RE_SW_GPIO_Port GPIOD
#define RE_VCC_Pin GPIO_PIN_14
#define RE_VCC_GPIO_Port GPIOG

#endif /* EXTENSION_BOARD_H_ */
