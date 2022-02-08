
#include "main.h"
#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

// #define BUTTON_3_SET   (1 << 0)
// #define BUTTON_3_DIR   (1 << 2) | (1 << 3)
// #define BUTTON_3_PUL   (1 << 2) | (1 << 3)
// #define BUTTON_0_PUL   (1 << 6)

#define USR_BLUE_SET   (1 << 0)
#define USR_BLUE_DIR   (1 << 0) | (1 << 1)
#define USR_BLUE_PUL   (1 << 1)



#define GPIOA_EN       (1 << 0)

enum led_state {
	RUN_RIGHT,
	STOP,
	RUN_LEFT,
	DIODE_BLINKING,
	CALLIB,
};

enum detector_state {
	ACTIVE,
	INACTIVE,
};

enum led_state led_state_var = CALLIB;
unsigned int blinking_counter = 0;

void detector_init(void)
{
	RCCAHB1 |= GPIOA_EN;
	// configure pins as inputs
	GPIOAMODE &= ~USR_BLUE_DIR;
	GPIOAPULL |= USR_BLUE_PUL;
}

enum detector_state read_detector(void)
{
	if (!(GPIOADATA & USR_BLUE_SET) == 0)
		return ACTIVE;
	else
		return INACTIVE;
}

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
	case CALLIB :
		led_step_left();
		if (read_detector() == ACTIVE)
			led_state_var = STOP;
		break;
	default:
		break;
	}
}



int main (){
	unsigned int main_loop_ctr;
	keyboard_init();
	led_init();
	detector_init();
	timer_12_interrupts_init(100,&Automat);

	while(1){
	 	main_loop_ctr++;
	}
}
