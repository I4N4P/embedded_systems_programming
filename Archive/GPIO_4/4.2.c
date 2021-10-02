
#define LED_GREEN_SET (1 << 12)
#define LED_GREEN_DIR (1 << 24)
#define GPIOD_EN      (1 << 3)


#define RCCAHB1   (*((volatile unsigned long *) 0x40023830)) // uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;
#define GPIODMODE (*((volatile unsigned long *) 0x40020C00)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020C00;
#define GPIODDATA (*((volatile unsigned long *) 0x40020C14)) // uint32_t *pGpiodDataReg = (uint32_t*)0x40020C14;

int main()
{	// Enable clock for peripheral
	RCCAHB1 |= GPIOD_EN;
	// configure LED_GREEN output
	GPIODMODE |= LED_GREEN_DIR;
	// turn on LED_GREEN
  	GPIODDATA |= LED_GREEN_SET;
	
	while (1);
}