
#define LED_GREEN_SET (1 << 12)
#define LED_GREEN_DIR (1 << 24)

#define GPIOD_EN      (1 << 3)

#define DELAY_COUNT_1MS 1250U

#define RCCAHB1   (*((volatile unsigned long *) 0x40023830)) // uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;
#define GPIODMODE (*((volatile unsigned long *) 0x40020C00)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020C00;
#define GPIODDATA (*((volatile unsigned long *) 0x40020C14)) // uint32_t *pGpiodDataReg = (uint32_t*)0x40020C14;

int period = 50;

void delay(int time)
{
	time = time * DELAY_COUNT_1MS;
	for (int counter = 0;counter < time;counter++);
}

int main()
{
	// Enable clock for peripherals
	RCCAHB1 |= GPIOD_EN;
	// configure led as an output
	GPIODMODE |= LED_GREEN_DIR;

	while (1) {
		GPIODDATA |= LED_GREEN_SET;
		delay(period);
		GPIODDATA &= ~LED_GREEN_SET;
		delay(period);
	}
}
