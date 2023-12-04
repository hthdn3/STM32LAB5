/*
 * software_timer.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Acer
 */

#include "software_timer.h"
int timer1_flag = 0;
int counter1 = 0;
int timer2_flag = 0;
int counter2 = 0;
int timer3_flag = 0;
int counter3 = 0;
int timer0_flag = 0;
int counter0 =0;
int counter5 = 0;
int timer5_flag = 0;
int counter4 = 0;
int timer4_flag = 0;

void setTimer1(int duration){
	counter1 = duration;
	timer1_flag = 0;
}
void setTimer2(int duration){
	counter2 = duration;
	timer2_flag = 0;
}
void setTimer3(int duration){
	counter3 = duration;
	timer3_flag = 0;
}
void setTimer0(int duration){
	counter0 = duration;
	timer0_flag = 0;
}
void setTimer5( int duration ){
	counter5 = duration;
	timer5_flag = 0;
}
void setTimer4( int duration ){
	counter4 = duration;
	timer4_flag = 0;
}

void timerRun(){
	if(counter1 > 0){
		counter1--;
		if(counter1 <= 0){
			timer1_flag = 1;
              }
	}
	 if(counter2 > 0){
			counter2 -- ;
				if(counter2 <= 0){
					timer2_flag = 1;
				}
			}
		if(counter3 > 0){
				counter3--;
				if(counter3 <= 0){
					timer3_flag = 1;
				}
			}
		if(counter0 > 0){
			counter0--;
			if (counter0 <= 0){
				timer0_flag = 1 ;
			}
		}
		if(counter4 > 0){
			counter4--;
			if (counter4 <= 0){
				timer4_flag = 1;
			}
		}
		if(counter5 > 0){
			counter5--;
			if (counter5 <= 0){
				timer5_flag = 1;
			}
		}

}
