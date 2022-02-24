#include "main.h"
#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"
#include "command_interpreter.h"

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
	while(1){
		//send('G');
		if (receiver_get_status() == READY) {
			transmiter_send_string("msg received\n");
			receiver_get_string_copy(data);
			decode_msg(data);
			if((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)){
				switch(asToken[0].uValue.eKeyword){
				case CALIB:
					servo_calib();
					transmiter_send_string("calibration has started\n");
					break;
				case GOTO:
					servo_goto(asToken[1].uValue.uiNumber);
					break;
				}
			}else if((ucTokenNr != 0)){
				transmiter_send_string("unknown command\n");
			}
		}
	delay(1000);
	}
}
