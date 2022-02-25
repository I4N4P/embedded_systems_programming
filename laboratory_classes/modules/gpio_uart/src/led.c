#include"main.h"
#include"led.h"

#define LED_GREEN_SET  (1 << 12)
#define LED_GREEN_DIR  (1 << 24)
#define LED_ORANGE_SET (1 << 13)
#define LED_ORANGE_DIR (1 << 26)
#define LED_RED_SET    (1 << 14)
#define LED_RED_DIR    (1 << 28)
#define LED_BLUE_SET   (1 << 15)
#define LED_BLUE_DIR   (1 << 30)
#define GPIOD_EN       (1 << 3)

enum step_direction {
	LEFT,
	RIGHT,
};

void led_init(void)
{
	// Enable clock for peripherals
	RCCAHB1 |= GPIOD_EN;
	// configure leds as outputs
	GPIODMODE |= (LED_GREEN_DIR | LED_ORANGE_DIR | LED_RED_DIR | LED_BLUE_DIR);
	// turn off leds
	GPIODDATA &= ~(LED_ORANGE_SET | LED_RED_SET | LED_BLUE_SET);
	// turn on green led
	GPIODDATA |= LED_GREEN_SET;
}

void led_on(unsigned char led_index)
{
	GPIODDATA &= ~(LED_GREEN_SET | LED_ORANGE_SET | LED_RED_SET | LED_BLUE_SET);
	switch (led_index) {
	case 0 :
		GPIODDATA |= LED_GREEN_SET;
		break;
	case 1 :
		GPIODDATA |= LED_ORANGE_SET;
		break;
	case 2 :
		GPIODDATA |= LED_RED_SET;
		break;
	case 3 :
		GPIODDATA |= LED_BLUE_SET;
		break;
	default:
		GPIODDATA &= ~(LED_GREEN_SET | LED_ORANGE_SET | LED_RED_SET | LED_BLUE_SET);
		break;
	}
}

void led_step(int step_direction)
{
	// remembers value between calls
	static unsigned int diode_number = 0;

	switch (step_direction) {
	case LEFT :
		diode_number++;
		break;
	case RIGHT :
		diode_number--;
		break;
	default:
		break;
	}
	led_on(diode_number % 4);
}

void led_step_left(void)
{
	led_step(LEFT);
}

void led_step_right(void)
{
	led_step(RIGHT);
}
