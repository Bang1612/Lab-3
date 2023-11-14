/*
 * seg_led.c
 *
 *  Created on: Nov 13, 2023
 *      Author: MY PC
 */
#include "seg_led.h"
#define NUMBER_OF_7LEDS 4
struct {
		GPIO_TypeDef *gpio;
		uint16_t pin_0;
		uint16_t pin_1;
		uint16_t pin_2;
		uint16_t pin_3;
		uint16_t pin_4;
		uint16_t pin_5;
		uint16_t pin_6;
} LED;
uint8_t led_buffer[NUMBER_OF_7LEDS]= {1, 1, 8, 3};
int index=0;
struct {
	GPIO_TypeDef *gpio;
	uint16_t red;
	uint16_t yellow;
	uint16_t green;
} traffic_light[2];

void display( GPIO_PinState seg0, GPIO_PinState seg1,
		GPIO_PinState seg2, GPIO_PinState seg3, GPIO_PinState seg4,
		GPIO_PinState seg5, GPIO_PinState seg6) {
	HAL_GPIO_WritePin(LED.gpio, LED.pin_0, seg0);
	HAL_GPIO_WritePin(LED.gpio, LED.pin_1, seg1);
	HAL_GPIO_WritePin(LED.gpio, LED.pin_2, seg2);
	HAL_GPIO_WritePin(LED.gpio, LED.pin_3, seg3);
	HAL_GPIO_WritePin(LED.gpio, LED.pin_4, seg4);
	HAL_GPIO_WritePin(LED.gpio, LED.pin_5, seg5);
	HAL_GPIO_WritePin(LED.gpio, LED.pin_6, seg6);
}
void Display7LED( int n){
	switch (n) {
	case 0:
		display(0, 0, 0, 0, 0, 0, 1);
		break;
	case 1:
		display(1, 0, 0, 1, 1, 1, 1);
		break;
	case 2:
		display(0, 0, 1, 0, 0, 1, 0);
		break;
	case 3:
		display(0, 0, 0, 0, 1, 1, 0);
		break;
	case 4:
		display(1, 0, 0, 1, 1, 0, 0);
		break;
	case 5:
		display(0, 1, 0, 0, 1, 0, 0);
		break;
	case 6:
		display(0, 1, 0, 0, 0, 0, 0);
		break;
	case 7:
		display(0, 0, 0, 1, 1, 1, 1);
		break;
	case 8:
		display(0, 0, 0, 0, 0, 0, 0);
		break;
	case 9:
		display(0, 0, 0, 0, 1, 0, 0);
		break;
	default:
		display(1, 1, 1, 1, 1, 1, 1);
	}
}
void initial7LED(void){
	LED.gpio=SEG_GPIO_Port;
	LED.pin_0=SEG0_Pin;
	LED.pin_1=SEG1_Pin;
	LED.pin_2=SEG2_Pin;
	LED.pin_3=SEG3_Pin;
	LED.pin_4=SEG4_Pin;
	LED.pin_5=SEG5_Pin;
	LED.pin_6=SEG6_Pin;
}
void initial_traffic_light(void){
	traffic_light[0].gpio = TRAFFIC1_GPIO_Port;
	traffic_light[0].red = RED1_Pin;
	traffic_light[0].yellow = YELLOW1_Pin;
	traffic_light[0].green = GREEN1_Pin;

	traffic_light[1].gpio = TRAFFIC2_GPIO_Port;
	traffic_light[1].red = RED2_Pin;
	traffic_light[1].yellow = YELLOW2_Pin;
	traffic_light[1].green = GREEN2_Pin;
}
void offallLED(void){
	HAL_GPIO_WritePin(GPIOA, SEG7_0_Pin, 1);
	HAL_GPIO_WritePin(GPIOA, SEG7_1_Pin, 1);
	HAL_GPIO_WritePin(GPIOA, SEG7_2_Pin, 1);
	HAL_GPIO_WritePin(GPIOA, SEG7_3_Pin, 1);
}
void update7LED(int index){
	if (index >= 4 || index < 0) index = 0;
	switch (index) {
	case 0:
		offallLED();
		HAL_GPIO_WritePin(GPIOA, SEG7_0_Pin, 0);
		Display7LED(led_buffer[0]);
		break;
	case 1:
		offallLED();
		HAL_GPIO_WritePin(GPIOA, SEG7_1_Pin, 0);
		Display7LED(led_buffer[1]);
		break;
	case 2:
		offallLED();
		HAL_GPIO_WritePin(GPIOA, SEG7_2_Pin, 0);
		Display7LED(led_buffer[2]);
		break;
	case 3:
		offallLED();
		HAL_GPIO_WritePin(GPIOA, SEG7_3_Pin, 0);
		Display7LED(led_buffer[3]);
		break;
	default:
		offallLED();
	}
}
void Scan7LED(void){
	update7LED(index++);
}
// 0 is off, 1 is on
void control_traffic_light(int i, GPIO_PinState red, GPIO_PinState yellow, GPIO_PinState green){
	HAL_GPIO_WritePin(traffic_light[i].gpio, traffic_light[i].red, red);
	HAL_GPIO_WritePin(traffic_light[i].gpio, traffic_light[i].yellow, yellow);
	HAL_GPIO_WritePin(traffic_light[i].gpio, traffic_light[i].green, green);
}

void number_set(int n1, int n2){
	if(n1 > 99 || n1 < 0){
		n1 = 0;
	}
	if(n2 > 99 || n2 < 0){
		n2 = 0;
	}
	led_buffer[0]= n1/10;
	led_buffer[1]= n1%10;
	led_buffer[2]= n2/10;
	led_buffer[3]= n2%10;
}
void initial_led(void){
	initial7LED();
	initial_traffic_light();
}
