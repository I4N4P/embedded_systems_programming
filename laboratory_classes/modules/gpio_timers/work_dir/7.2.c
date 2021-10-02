#include "main.h"
#include "timer.h"
#include "led.h"

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

int main()
{
	led_init();
	init_timer_12_match_0(1000);
	while (1) {
		led_step_left();
		wait_on_timer_12_match_0();
	}
}
