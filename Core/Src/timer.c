/*
 * timer.c
 *
 *  Created on: Nov 12, 2023
 *      Author: MY PC
 */
#include "main.h"
#include "timer.h"
#define NUMBER_OF_TIMERS 5


struct 	{
	int state;
	int count;
} timer[NUMBER_OF_TIMERS];

void set_timer(int i, int count){
	timer[i].count= count * FREQUENCY_OF_TIM / 1000.0;
	timer[i].state= 0;
}
void run_timer(){
	for(int i=0; i< NUMBER_OF_TIMERS;i++){
		if(!timer[i].state){
			timer[i].count--;
			if(timer[i].count <= 0){
				timer[i].state= 1;
			}
		}
	}
}
int is_timer_on(int i){
	return timer[i].state;
}



