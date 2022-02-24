#include "main.h"
#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"
#include "command_interpreter.h"

extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

char data[15];

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
	while(1){
	if (receiver_get_status() == READY) {
		receiver_get_string_copy(data);
		DecodeMsg(data);
		if((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)){
			switch(asToken[0].uValue.eKeyword){
			case CALIB:
				servo_calib();
				break;
			case GOTO:
				servo_goto(asToken[1].uValue.uiNumber);
				break;
			}
		}else if((ucTokenNr != 0)){
			//ucPuts("unknowncommand\n", 16);
		}
	}
	delay(100);
	}
}
