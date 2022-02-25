#include "main.h"
#include "keyboard.h"
#include "servo.h"


void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

int main (){
	servo_init(10);
	keyboard_init();
	while(1){
	 	switch (keyboard_read()) {
		case BUTTON_0:
			servo_calib();
			break;
		case BUTTON_1:
			servo_goto(12);
			break;
		case BUTTON_2:
			servo_goto(24);
			break;
		case BUTTON_3:
			servo_goto(36);
			break;
		default:
			break;
		}
	delay(50);
	}
}
