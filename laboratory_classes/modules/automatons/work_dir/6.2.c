#include"main.h"
#include"led.h"
#include"keyboard.h"

enum led_state{STATE0,STATE1,STATE2,STATE3,STATE4,STATE5};
enum led_state led_state_var = STATE0;

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

int main()
{
	keyboard_init();
	led_init();

	while (1) {
		switch (led_state_var) {
		case STATE0:
			led_state_var = STATE1;
			led_step_right();
			break;
		case STATE1:
			led_state_var = STATE2;
			led_step_right();
			break;
		case STATE2:
			led_state_var = STATE3;
			led_step_right();
			break;
		case STATE3:
			led_state_var = STATE4;
			led_step_left();
			break;
		case STATE4:
			led_state_var = STATE5;
			led_step_left();
			break;
		case STATE5:
			led_state_var = STATE0;
			led_step_left();
			break;
		default:
			break;

		}
	delay(500);
	}
}
