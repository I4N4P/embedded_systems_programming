#include "main.h"
#include "led.h"
#include "servo.h"
#include "timer_it.h"

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
	// configure pin as inputs
	GPIOAMODE &= ~USR_BLUE_DIR;
	// pull-down input
	GPIOAPULL |= USR_BLUE_PUL;
}

enum detector_state read_detector(void)
{
	if (!(GPIOADATA & USR_BLUE_SET) == 0)
		return ACTIVE;
	else
		return INACTIVE;
}

void servo_calib(void)
{
	servo.state = CALLIB;
}

void servo_goto(unsigned int position)
{
	servo.desired_position = position;
}

void Automat()
{
	switch (servo.state) {
	case CALLIB :
		if (read_detector() == ACTIVE) {
			servo.state = IDLE;
			servo.desired_position = 0;
			servo.current_position = 0;
		} else{
			servo.state = CALLIB;
			led_step_right();
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

void servo_init(unsigned int servo_frequency)
{
	led_init();
	detector_init();
	servo_calib();
	unsigned int servo_period = (1000/servo_frequency);
	timer_12_interrupts_init(servo_period,&Automat);
}
