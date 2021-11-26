
#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

enum led_state {
	RUN_RIGHT,
	STOP,
	RUN_LEFT,
	DIODE_BLINKING,
};
enum led_state led_state_var = STOP;
unsigned int blinking_counter = 0;

void Automat(){


	switch (led_state_var) {
	case STOP :
		if (keyboard_read() == BUTTON_0) {
			led_state_var = RUN_LEFT;
		} else if (keyboard_read() == BUTTON_2) {
			led_state_var = RUN_RIGHT;
		} else if (keyboard_read() == BUTTON_3) {
			led_state_var = DIODE_BLINKING;
			blinking_counter = 0;
		}
		break;
	case RUN_LEFT :
		led_step_left();
		if (keyboard_read() == BUTTON_1)
			led_state_var = STOP;
		break;
	case RUN_RIGHT :
		led_step_right();
		if (keyboard_read() == BUTTON_1)
			led_state_var = STOP;
		break;
	case DIODE_BLINKING :
		if (keyboard_read() == BUTTON_1) {
			led_state_var = STOP;
		} else if (blinking_counter > 20) {
			led_state_var = STOP;
		} else {
			if((blinking_counter % 2) == 0) {
				led_on(1);
			} else {
				led_on(5);
			}
			led_state_var = DIODE_BLINKING;
			blinking_counter++;
		}
		break;
	default:
		break;
	}
}



int main (){
	unsigned int iMainLoopCtr;
	keyboard_init();
	led_init();
	timer_12_interrupts_init(100,&Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
