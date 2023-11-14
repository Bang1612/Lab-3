/*
 * port.h
 *
 *  Created on: Nov 14, 2023
 *      Author: MY PC
 */

#ifndef INC_PORT_H_
#define INC_PORT_H_
#include "stm32f1xx_hal.h"

// define input
#define EN0       GPIO_PIN_3
#define EN0_Port  GPIOA
#define EN1       GPIO_PIN_4
#define EN1_Port  GPIOA
#define EN2       GPIO_PIN_5
#define EN2_Port  GPIOA

//7 SEGMENT LED DEFINE
#define SEG7_GPIO_Port GPIOA
#define SEG7_0_Pin GPIO_PIN_12
#define SEG7_1_Pin GPIO_PIN_13
#define SEG7_2_Pin GPIO_PIN_14
#define SEG7_3_Pin GPIO_PIN_15

#define SEG_GPIO_Port GPIOB
#define SEG0_Pin GPIO_PIN_0
#define SEG1_Pin GPIO_PIN_1
#define SEG2_Pin GPIO_PIN_2
#define SEG3_Pin GPIO_PIN_3
#define SEG4_Pin GPIO_PIN_4
#define SEG5_Pin GPIO_PIN_5
#define SEG6_Pin GPIO_PIN_6

//TRAFFIC LIGHT DEFINE
#define TRAFFIC1_GPIO_Port GPIOA
#define TRAFFIC2_GPIO_Port GPIOA

#define RED1_Pin GPIO_PIN_6
#define YELLOW1_Pin GPIO_PIN_7
#define GREEN1_Pin GPIO_PIN_8
#define RED2_Pin GPIO_PIN_9
#define YELLOW2_Pin GPIO_PIN_10
#define GREEN2_Pin GPIO_PIN_11

#endif /* INC_PORT_H_ */
