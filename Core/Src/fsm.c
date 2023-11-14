/*
 * fsm.c
 *
 *  Created on: Nov 14, 2023
 *      Author: MY PC
 */
#include "fsm.h"
//status =0: function normally
//status =1: red light modify
//status =2: yellow light modify
//status =3: green light modify
//status =4: check value and goes back to mode 1
int status = 0;

//button_state  0: release, 1: pressed, 2: long pressed
int button_state[3]={0, 0, 0};
#define RED_INIT 11
#define YELLOW_INIT 3
#define GREEN_INIT 8
//Save sys pre change state
int temp[3]={RED_INIT, YELLOW_INIT, GREEN_INIT};


int red_buffer=RED_INIT;
int yellow_buffer=YELLOW_INIT;
int green_buffer=GREEN_INIT;
//Count down of each state
int red=RED_INIT;
int yellow =YELLOW_INIT;
int green=GREEN_INIT;

int traffic_light_time1=RED_INIT;
int traffic_light_time2=GREEN_INIT;
enum{
	RED, YELLOW, GREEN
} traffic_light[2]= {RED, GREEN};
enum{
	INCREASE_BY_1,INCREASE_BY_1_OVER_TIME, NOT_CHANGE
} prestatus=NOT_CHANGE;
void button0(void);
void button1(void);
void button2(void);
void fsm_traffic_light(void){
	number_set(traffic_light_time1, traffic_light_time2);
	if (traffic_light_time1 <= 0) {
		switch (traffic_light[0]) {
		case RED:
			traffic_light[0] = GREEN;
			traffic_light_time1 = green;
			control_traffic_light(0, 0, 0, 1);
			break;
		case GREEN:
			traffic_light[0] = YELLOW;
			traffic_light_time1 = yellow;
			control_traffic_light(0, 0, 1, 0);
			break;
		case YELLOW:
			traffic_light[0] = RED;
			traffic_light_time1 = red;
			control_traffic_light(0, 1, 0, 0);
			break;
		default:
			break;
		}
	}
	if (traffic_light_time2 <= 0) {
		switch (traffic_light[1]) {
		case RED:
			traffic_light[1] = GREEN;
			traffic_light_time2 = green;
			control_traffic_light(1, 0, 0, 1);
			break;
		case GREEN:
			traffic_light[1] = YELLOW;
			traffic_light_time2 = yellow;
			control_traffic_light(1, 0, 1, 0);
			break;
		case YELLOW:
			traffic_light[1] = RED;
			traffic_light_time2 = red;
			control_traffic_light(1, 1, 0, 0);
			break;
		default:
			break;
		}
	}

}
void traffic_light_adjustment(void){
	switch(status){
	case 1: //RED adjustment
		control_traffic_light(0, 1, 0, 0);
		control_traffic_light(1, 1, 0, 0);
		break;
	case 2: //YELLOW adjustment
		control_traffic_light(0, 0, 1, 0);
		control_traffic_light(1, 0, 1, 0);
		break;
	case 3: //GREEN adjustment
		control_traffic_light(0, 0, 0, 1);
		control_traffic_light(1, 0, 0, 1);
		break;
	default:
		break;
	}
}
void change_value(void){
	switch(status){
	case 1:
		red_buffer++;
		if(red_buffer > 99){
			red_buffer =0;
		}
		break;
	case 2:
		yellow_buffer++;
		if(yellow_buffer > 99){
			yellow_buffer =0;
		}
		break;

	case 3:
		green_buffer++;
		if(green_buffer > 99){
			green_buffer =0;
		}
		break;
	default:
		break;
	}
}
void fsm(void){
	if (is_timer_on(0)) {
		if (status != 0 || red == green + yellow) {
			Scan7LED();
		} else {
			offallLED();
		}
		set_timer(0, SCAN_7SEGLED_TIME);
	}
	switch (status) {
	case 0:
		//Number dont add up
		if (red != green + yellow) {
			red = temp[0];
			yellow = temp[1];
			green = temp[2];
		}
		if (is_timer_on(1)) {
			traffic_light_time1--;
			traffic_light_time2--;
			set_timer(1, ONE_SECOND);
		}
		fsm_traffic_light();
		button0();
		break;
	case 1:
		//RED adjustment
		if (prestatus == NOT_CHANGE) {
			red_buffer = red;
		}
		number_set(red_buffer, 2);
		traffic_light_adjustment();

		button0();
		button1();
		button2();
		break;
	case 2:
		//YELLOW adjustment
		if (prestatus == NOT_CHANGE) {
			yellow_buffer = yellow;
		}
		number_set(yellow_buffer, 3);
		traffic_light_adjustment();

		button0();
		button1();
		button2();
		break;

	case 3:
	//GREEEN adjustment
	if (prestatus == NOT_CHANGE) {
		green_buffer = green;
	}
	number_set(green_buffer, 4);
	traffic_light_adjustment();

	button0();
	button1();
	button2();
	break;
	case 4:
	//END adjustment, proceed to checking value
	if (green == 0 || red == 0 || yellow == 0 || red == green + yellow) {
		red = temp[0];
		yellow = temp[1];
		green = temp[2];
	} else {
		temp[0] = red;
		temp[1] = yellow;
		temp[2] = green;
	}
	status = 0;
}
}

void button0(void){
	switch(button_state[0]){
	case 0:
		if (is_button_pressed(0)) {
			status++;
			button_state[0] = 1;
		}
		break;
	case 1:
		if(!is_button_pressed(0)){
			button_state[0]=0;
		}
		break;
	default:
		break;
	}
}

void button2(void){
	switch(button_state[2]){
	case 0:
		if(is_button_pressed(2)){
			switch(status){
			case 1:
				red=red_buffer;
				prestatus= NOT_CHANGE;
				break;
			case 2:
				yellow=yellow_buffer;
				prestatus= NOT_CHANGE;
				break;
			case 3:
				green= green_buffer;
				prestatus= NOT_CHANGE;
				break;
			default:
				break;
			}
			button_state[2]=1;
		}
		break;
	case 1:
		if(!is_button_pressed(2)){
			button_state[2]=0;
		}
		break;
	default:
		break;
	}
}

void button1(void){
	switch(button_state[1]){
	case 0:
		if(is_button_pressed(1)){
			switch(status){
			case 1:
				red_buffer++;
				prestatus= INCREASE_BY_1;
				break;
			case 2:
				yellow_buffer++;
				prestatus= INCREASE_BY_1;
				break;
			case 3:
				green_buffer++;
				prestatus= INCREASE_BY_1;
				break;
			default:
				break;
			}
			button_state[1]=1;
		}
	case 1:
		if(!is_button_pressed(1)){
			button_state[1]=0;
		}
		else if(is_button_long_pressed(1)){
			button_state[1]=2;
		}
		break;
	case 2:
		if(!is_button_pressed(1)){
			button_state[1]=0;
		}
		else{
			if (is_timer_on(4)) {
				switch (status) {
				case 1:
					red_buffer++;
					prestatus = INCREASE_BY_1_OVER_TIME;
					break;
				case 2:
					yellow_buffer++;
					prestatus = INCREASE_BY_1_OVER_TIME;
					break;
				case 3:
					green_buffer++;
					prestatus = INCREASE_BY_1_OVER_TIME;
					break;
				default:
					break;
				}
				set_timer(4, ONE_SECOND);
			}
		}
	}
}
