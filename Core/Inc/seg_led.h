/*
 * seg_led.h
 *
 *  Created on: Nov 13, 2023
 *      Author: MY PC
 */

#ifndef INC_SEG_LED_H_
#define INC_SEG_LED_H_

#include <stdint.h>
#include "port.h"

void initial7LED( void);
void Display7LED( int n);
void display( GPIO_PinState seg0, GPIO_PinState seg1,
		GPIO_PinState seg2, GPIO_PinState seg3, GPIO_PinState seg4,
		GPIO_PinState seg5, GPIO_PinState seg6);
void initial_traffic_light(void);
void offallLED(void);
void update7LED(int index);
void Scan7LED(void);
void control_traffic_light(int i, GPIO_PinState red, GPIO_PinState yellow, GPIO_PinState green);
void number_set(int n1, int n2);
void initial_led(void);
#endif /* INC_SEG_LED_H_ */
