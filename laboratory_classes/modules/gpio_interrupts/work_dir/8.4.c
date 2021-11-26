
#include "timer_interrupts.h"
#include "led.h"

int main (){
	unsigned int iMainLoopCtr;
	led_init();
	timer_12_interrupts_init(100,&led_step_right);

	while(1){
	 	iMainLoopCtr++;
	}
}
