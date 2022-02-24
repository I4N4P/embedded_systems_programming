#include "main.h"
#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"
#include "command_interpreter.h"

#define USART2DR (*((volatile unsigned long *) 0x40004404))

extern struct token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

char data[30];

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

int main (){
	led_init();
	servo_init(10);
	//keyboard_init();
	uart_init_with_irq();
	char string[15] = "licznik: ";
	char string2[4] = "\n";
	char empty[15] = "";
	char temp[20] = "";
	unsigned int temp2 = 0;
	while(1){
		copy_string(empty,temp);
		append_string(string,temp);
		append_int_to_string(temp2,temp);
		append_string(string2,temp);
		if (transmiter_get_status() == FREE)
			transmiter_send_string(temp);
		delay(1000);
		temp2++;

	}
}
