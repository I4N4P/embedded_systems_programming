#include "main.h"
#include "led.h"


#define BUTTON_1_SET   (1 << 2)
#define BUTTON_1_DIR   (1 << 4) | (1 << 5)
#define BUTTON_1_PUL   (1 << 4)
#define BUTTON_2_SET   (1 << 3)
#define BUTTON_2_DIR   (1 << 6) | (1 << 7)
#define BUTTON_2_PUL   (1 << 6)

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

int main (){
	led_init();
	uart_init_with_irq();
	while(1){
		if(get() == 's');
	}
}
