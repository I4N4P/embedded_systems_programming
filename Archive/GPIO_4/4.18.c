
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

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

enum ButtonState {RELASED, PRESSED};

enum ButtonState eReadButton1()
{
	if (!(GPIOADATA & BUTTON_3_SET))
		return PRESSED;
	else
		return RELASED;
}

int main()
{
	led_init();
	keyboard_init();
	while (1) {
		switch (eReadButton1()) {
		case RELASED :
			led_on(0);
			break;
		case PRESSED :
			led_on(1);
			break;
		default:
			delay(10);
			break;
		}
	}
}
