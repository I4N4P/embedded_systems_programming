#include "main.h"
#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"

extern char received_data;
int last_position = 0;

char data[6];

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

enum result {
	EQUAL,
	NOT_EQUAL,
};


enum result string_compare (char str1[],char str2[])
{
	for (int i = 0; (str1[i] != NULL) || (str2[i] != NULL); i++) {
		if (str1[i] != str2[i])
			return NOT_EQUAL;
	}
	return EQUAL;
}

int main (){
	led_init();
	servo_init(10);
	//keyboard_init();
	uart_init_with_irq();
	while(1){
	if (receiver_get_status() == READY) {
		receiver_get_string_copy(&data[0]);
		if (string_compare(data,"left") == EQUAL)
			led_step_left();
		else if (string_compare(data,"right") == EQUAL)
			led_step_right();
		else if (string_compare(data,"calib") == EQUAL)
			servo_calib();
	}
	delay(100);
	}
}
