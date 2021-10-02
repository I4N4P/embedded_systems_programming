#include"main.h"
#include"led.h"
#include"keyboard.h"

enum led_state {LED_LEFT, LED_RIGHT};
enum led_state led_state_var = LED_LEFT;

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

		static int counter = 0;

		switch (led_state_var) {
		case LED_RIGHT:
			if (counter == 3) {
				led_state_var = LED_LEFT;
				counter = 0;
			}
			led_step_right();
			break;
		case LED_LEFT:
			if (counter == 3) {
				led_state_var = LED_RIGHT;
				counter = 0;
			}
			led_step_left();
			break;
		default:
			break;
		}
		counter++;
		delay(500);
	}
}
