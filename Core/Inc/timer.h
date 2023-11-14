/*
 * timer.h
 *
 *  Created on: Nov 12, 2023
 *      Author: MY PC
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <stdint.h>
#define FREQUENCY_OF_TIM	1000 // Hz
#define READ_BUTTON_TIME	10 // 10ms
#define SCAN_7SEGLED_TIME	125 // 500ms/4=125ms
#define ONE_SECOND			1000 // 1s
#define TOGGLE_TIME			250


void set_timer(int i, int count);
void run_timer(void);
int is_timer_on(int i);

#endif /* INC_TIMER_H_ */
