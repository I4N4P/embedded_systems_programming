#include "main.h"
#include "keyboard.h"
#include "servo.h"
#include "uart.h"

extern char received_data;
int last_position = 0;

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

	delay(100);
	}
}
