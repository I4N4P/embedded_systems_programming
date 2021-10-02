
#define DELAY_COUNT_1MS 1250U

#define RCCAHB1   (*((volatile unsigned long *) 0x40023830)) // uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;
#define GPIOAMODE (*((volatile unsigned long *) 0x40020000)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;
#define GPIODMODE (*((volatile unsigned long *) 0x40020C00)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020C00;
#define GPIOADATA (*((volatile unsigned long *) 0x40020010)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;
#define GPIODDATA (*((volatile unsigned long *) 0x40020C14)) // uint32_t *pGpiodDataReg = (uint32_t*)0x40020C14;
#define GPIOAPULL (*((volatile unsigned long *) 0x4002000C)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;
