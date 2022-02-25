#include "main.h"
#include "keyboard.h"
#include "servo.h"
#include "uart.h"

extern char recived_data;

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

int main (){
	led_init();
	servo_init(10);
	keyboard_init();
	uart_init_with_irq();
	while(1){
		switch (recived_data){
		case '1' :
			servo_goto(12);
			break;
		case '2' :
			servo_goto(24);
			break;
		case '3' :
			servo_goto(36);
			break;
		case 'c' :
			servo_calib();
			break;
		default :
			break;
		}
		recived_data = 0;
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
