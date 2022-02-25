
#define LED_GREEN_SET  (1 << 12)
#define LED_GREEN_DIR  (1 << 24)
#define LED_ORANGE_SET (1 << 13)
#define LED_ORANGE_DIR (1 << 26)
#define LED_RED_SET    (1 << 14)
#define LED_RED_DIR    (1 << 28)
#define LED_BLUE_SET   (1 << 15)
#define LED_BLUE_DIR   (1 << 30)
#define GPIOD_EN       (1 << 3)

#define BUTTON_0_SET   (1 << 0)
#define BUTTON_0_DIR   (1 << 0) | (1 << 1)
#define BUTTON_0_PUL   (1 << 0)
#define BUTTON_1_SET   (1 << 1)
#define BUTTON_1_DIR   (1 << 2) | (1 << 3)
#define BUTTON_1_PUL   (1 << 2)
#define BUTTON_2_SET   (1 << 2)
#define BUTTON_2_DIR   (1 << 4) | (1 << 5)
#define BUTTON_2_PUL   (1 << 4)
#define BUTTON_3_SET   (1 << 3)
#define BUTTON_3_DIR   (1 << 6) | (1 << 7)
#define BUTTON_3_PUL   (1 << 6)
#define GPIOA_EN       (1 << 0)

#define DELAY_COUNT_1MS 1250U

#define RCCAHB1   (*((volatile unsigned long *) 0x40023830)) // uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;
#define GPIOAMODE (*((volatile unsigned long *) 0x40020000)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;
#define GPIODMODE (*((volatile unsigned long *) 0x40020C00)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020C00;
#define GPIOADATA (*((volatile unsigned long *) 0x40020010)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;
#define GPIODDATA (*((volatile unsigned long *) 0x40020C14)) // uint32_t *pGpiodDataReg = (uint32_t*)0x40020C14;
#define GPIOAPULL (*((volatile unsigned long *) 0x4002000C)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;

int period = 250;

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

void keyboard_init(void)
{
	// Enable clock for peripherals
	RCCAHB1 |= GPIOA_EN;
	// configure pins as inputs
	GPIOAMODE &= ~(BUTTON_0_DIR | BUTTON_1_DIR | BUTTON_2_DIR | BUTTON_3_DIR);
	// pullup input pins
	GPIOAPULL |= (BUTTON_0_PUL | BUTTON_1_PUL | BUTTON_2_PUL | BUTTON_3_PUL);
}

enum keyboard_state {RELASED, BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3};

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

enum step_direction {LEFT,RIGHT};

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

