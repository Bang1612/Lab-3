/*
 * input_reading.c
 *
 *  Created on: Nov 12, 2023
 *      Author: MY PC
 */
# include "main.h"

// we aim to work with more than one buttons
# define NO_OF_BUTTONS 3
// timer interrupt duration is 10ms , so to pass 1 second ,
// we need to jump to the interrupt service routine 100 time
# define DURATION_FOR_LONG_PRESSED 100 // 1s
# define PRESSED 0
# define RELEASED 1


struct{
	int reg[3];
	int is_pressed;
	int is_long_pressed;
	int timer;

	GPIO_TypeDef *gpio;
	uint16_t pin;
} button[NO_OF_BUTTONS];

void initial_button(void){
	for(int i=0;i < NO_OF_BUTTONS;i++){
		button[i].reg[0]= button[i].reg[1]=button[i].reg[2]= RELEASED;
		button[i].is_pressed= 0;
		button[i].is_long_pressed= 0;
		button[i].timer= DURATION_FOR_LONG_PRESSED;
	}
	button[0].gpio= EN0_GPIO_Port;
	button[0].pin= EN0_Pin;
	button[1].gpio= EN1_GPIO_Port;
	button[1].pin= EN1_Pin;
	button[2].gpio= EN2_GPIO_Port;
	button[2].pin= EN2_Pin;
}
void button_reading(void){
	for(int i=0; i< NO_OF_BUTTONS; i++){
		button[i].reg[0]= button[i].reg[1];
		button[i].reg[1]= button[i].reg[2];
		button[i].reg[2]= HAL_GPIO_ReadPin(button[i].gpio, button[i].pin);
		if(button[i].reg[0] == button[i].reg[1] && button[i].reg[1] == button[i].reg[2]){
			if(button[i].reg[2] == PRESSED){
				button[i].is_pressed=1;
				if(button[i].timer > 0){
					button[i].timer--;
				}
				else{
					button[i].is_long_pressed=1;
				}
			}
			else{
				button[i].is_long_pressed= button[i].is_pressed=0;
				button[i].timer= DURATION_FOR_LONG_PRESSED;
			}
		}
	}
}
int is_button_pressed(int index){
	if(index >= NO_OF_BUTTONS) return 0;
	return button[index].is_pressed;
}
int is_button_long_pressed(int index){
	if(index >= NO_OF_BUTTONS) return 0;
		return button[index].is_long_pressed;
}


