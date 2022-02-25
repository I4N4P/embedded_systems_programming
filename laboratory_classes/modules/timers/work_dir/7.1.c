#include "main.h"
#include "led.h"
#include "timer.h"

void delay(unsigned int time)
{
	wait_on_timer_6(time);
}

int main()
{
	init_timer_6();
	led_init();
	//init_timer_12_match_0(500);
	while (1) {
		led_step_right();
		delay(1000);
		//wait_on_timer_12_match_0();
	}
}
