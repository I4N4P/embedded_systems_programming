
#define LED_GREEN_SET  (1 << 12)
#define LED_GREEN_DIR  (1 << 24)
#define LED_ORANGE_SET (1 << 14)
#define LED_ORANGE_DIR (1 << 28)
#define LED_RED_SET    (1 << 13)
#define LED_RED_DIR    (1 << 26)
#define LED_BLUE_SET   (1 << 15)
#define LED_BLUE_DIR   (1 << 30)
#define GPIOD_EN       (1 << 3)

#define DELAY_COUNT_1MS 1250U


#define RCCAHB1   (*((volatile unsigned long *) 0x40023830)) // uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;
#define GPIODMODE (*((volatile unsigned long *) 0x40020C00)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020C00;
#define GPIODDATA (*((volatile unsigned long *) 0x40020C14)) // uint32_t *pGpiodDataReg = (uint32_t*)0x40020C14;

int period = 250;

void led_init()
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
	switch(led_index){
	case 0:
		GPIODDATA |= LED_GREEN_SET;
		break;
	case 1:
		GPIODDATA |= LED_RED_SET;
		break;
	case 2:
		GPIODDATA |= LED_ORANGE_SET;
		break;
	case 3:
		GPIODDATA |= LED_BLUE_SET;
		break;
	default:
		GPIODDATA &= ~(LED_GREEN_SET | LED_ORANGE_SET | LED_RED_SET | LED_BLUE_SET);
		break;
	}
}

void delay(int Time)
{
	Time = Time * DELAY_COUNT_1MS;
	for(int counter = 0;counter < Time;counter++){};
}

int main(){
	led_init();
	while(1){
		led_on(0);
		delay(period);
		led_on(1);
		delay(period);
		led_on(2);
		delay(period);
		led_on(3);
		delay(period);
	}
}
