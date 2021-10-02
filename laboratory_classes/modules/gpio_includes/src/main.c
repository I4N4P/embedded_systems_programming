#include"main.h"
#include"led.h"
#include"keyboard.h"

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
		switch (keyboard_read()) {
			case BUTTON_1:
				led_step_right();
				break;
			case BUTTON_2:
				led_step_left();
				break;
			default:
				break;
		}
		delay(250);
	}
}
