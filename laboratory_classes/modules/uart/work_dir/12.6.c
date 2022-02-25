#include "main.h"
#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"
#include "console.h"
#include "string.h"

#define USART2DR (*((volatile unsigned long *) 0x40004404))

extern struct token tokken[MAX_TOKEN_NR];
extern unsigned char token_number;

char data[30];

struct watch {
	unsigned int minutes, secconds;
	unsigned char secconds_changed, minutes_changed;
};

struct watch my_watch;



void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

void watch_update(void)
{
	if(my_watch.secconds == 59) {
		my_watch.secconds = 0;
		my_watch.minutes++;
		my_watch.minutes_changed = 1;
	} else {
		my_watch.secconds++;
		my_watch.secconds_changed = 1;
	}

}

int main (){
	led_init();
	servo_init(10);
	//keyboard_init();
	uart_init_with_irq();
	char string[15] = "min: ";
	char string2[4] = "\n";
	char string3[15] = "sec: ";
	char string4[15] = "calc: ";
	char empty[15] = "";
	char temp[20] = "";
	unsigned int temp2 = 0;
	while(1){
		if (my_watch.minutes_changed == 1) {
			copy_string(empty,temp);
			append_string(string,temp);
			append_int_to_string(my_watch.minutes,temp);
			append_string(string2,temp);
			my_watch.minutes_changed = 0;
			if (transmiter_get_status() == FREE)
				transmiter_send_string(temp);
		}
		if (my_watch.secconds_changed == 1) {
			copy_string(empty,temp);
			append_string(string3,temp);
			append_int_to_string(my_watch.secconds,temp);
			append_string(string2,temp);
			my_watch.secconds_changed = 0;
			if (transmiter_get_status() == FREE)
				transmiter_send_string(temp);
		}
		if (receiver_get_status() == READY) {
			receiver_get_string_copy(data);
			decode_msg(data);
			if((token_number != 0) && (tokken[0].eType == KEYWORD)){
				switch(tokken[0].uValue.eKeyword){
				case ID :
					transmiter_send_string("I'm MrRobot <3\n");
					break;
				case CALIB:
					servo_calib();
					transmiter_send_string("calibration has started\n");
					break;
				case GOTO:
					servo_goto(tokken[1].uValue.uiNumber);
					break;
				case CALC:
					copy_string(empty,temp);
					append_string(string4,temp);
					append_int_to_string((tokken[1].uValue.uiNumber * 2),temp);
					append_string(string2,temp);
					if (transmiter_get_status() == FREE)
						transmiter_send_string(temp);
					break;
				}
			}else if((token_number != 0)){
				transmiter_send_string("unknown command\n");
			}
		}
		delay(1000);
		watch_update();

	}
}
