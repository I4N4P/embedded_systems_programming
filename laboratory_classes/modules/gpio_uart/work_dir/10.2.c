#include "main.h"
#include "led.h"
#include "uart.h"

extern char recived_data;

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

int main (){
	led_init();
	uart_init_with_irq();
	while(1){
		switch (recived_data){
		case '1' :
			led_on(0);
			break;
		case '2' :
			led_on(1);
			break;
		case '3' :
			led_on(2);
			break;
		case '4' :
			led_on(3);
			break;
		case 'c' :
			led_on(4);
			break;
		default :
			break;
		}
	}
}
