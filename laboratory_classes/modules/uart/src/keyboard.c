#include"main.h"
#include"keyboard.h"

#define BUTTON_0_SET   (1 << 1)
#define BUTTON_0_DIR   (1 << 2) | (1 << 3)
#define BUTTON_0_PUL   (1 << 2)
#define BUTTON_1_SET   (1 << 2)
#define BUTTON_1_DIR   (1 << 4) | (1 << 5)
#define BUTTON_1_PUL   (1 << 4)
#define BUTTON_2_SET   (1 << 3)
#define BUTTON_2_DIR   (1 << 6) | (1 << 7)
#define BUTTON_2_PUL   (1 << 6)
#define BUTTON_3_SET   (1 << 4)
#define BUTTON_3_DIR   (1 << 8) | (1 << 9)
#define BUTTON_3_PUL   (1 << 8)
#define GPIOA_EN       (1 << 0)

void keyboard_init(void)
{
	// Enable clock for peripherals
	RCCAHB1 |= GPIOA_EN;
	// configure pins as inputs
	GPIOAMODE &= ~(BUTTON_0_DIR | BUTTON_1_DIR | BUTTON_2_DIR | BUTTON_3_DIR);
	// pullup input pins
	GPIOAPULL |= (BUTTON_0_PUL | BUTTON_1_PUL | BUTTON_2_PUL | BUTTON_3_PUL);
}

enum keyboard_state keyboard_read(void)
{
	if ((GPIOADATA & BUTTON_0_SET) == 0)
		return BUTTON_0;
	else if ((GPIOADATA & BUTTON_1_SET) == 0)
		return BUTTON_1;
	else if ((GPIOADATA & BUTTON_2_SET) == 0)
		return BUTTON_2;
	else if ((GPIOADATA & BUTTON_3_SET) == 0)
		return BUTTON_3;
	else
		return RELASED;
}
