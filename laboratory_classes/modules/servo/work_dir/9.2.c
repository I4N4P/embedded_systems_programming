
#include "main.h"
#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

#define USR_BLUE_SET   (1 << 0)
#define USR_BLUE_DIR   (1 << 0) | (1 << 1)
#define USR_BLUE_PUL   (1 << 1)
#define GPIOA_EN       (1 << 0)

enum detector_state {
	ACTIVE,
	INACTIVE,
};

enum servo_state {
	CALLIB,
	IDLE,
	IN_PROGRESS,
};

struct servo {
	enum servo_state state;
	unsigned int desired_position;
	unsigned int current_position;
};

struct servo servo;

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
	switch (servo.state) {
	case CALLIB :
		if (read_detector() == ACTIVE) {
			servo.state = IDLE;
			servo.desired_position = 0;
			servo.current_position = 0;
		} else{
			servo.state = CALLIB;
		}
		break;
	case IDLE :
		if (servo.current_position != servo.desired_position)
			servo.state = IN_PROGRESS;
		else
			servo.state = IDLE;
		break;
	case IN_PROGRESS :
		if (servo.current_position < servo.desired_position) {
			servo.current_position++;
			led_step_right();
			servo.state = IN_PROGRESS;
		} else if (servo.current_position > servo.desired_position) {
			servo.current_position--;
			led_step_left();
			servo.state = IN_PROGRESS;
		} else {
			servo.state = IDLE;
		}
		break;
	default:
		break;
	}
}



int main (){
	servo.state = CALLIB;
	unsigned int main_loop_ctr;
	keyboard_init();
	led_init();
	detector_init();
	timer_12_interrupts_init(100,&Automat);

	while(1){
	 	switch (keyboard_read()) {
		case BUTTON_1:
			servo.desired_position = 12;
			break;
		case BUTTON_2:
			servo.desired_position = 24;
			break;
		case BUTTON_3:
			servo.desired_position = 36;
			break;
		default:
			break;
		}
	delay(50);
	}
}
