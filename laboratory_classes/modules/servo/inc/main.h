
#define DELAY_COUNT_1MS 1250U

#define RCCAHB1   (*((volatile unsigned long *) 0x40023830)) // uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;
#define GPIOAMODE (*((volatile unsigned long *) 0x40020000)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;
#define GPIODMODE (*((volatile unsigned long *) 0x40020C00)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020C00;
#define GPIOADATA (*((volatile unsigned long *) 0x40020010)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;
#define GPIODDATA (*((volatile unsigned long *) 0x40020C14)) // uint32_t *pGpiodDataReg = (uint32_t*)0x40020C14;
#define GPIOAPULL (*((volatile unsigned long *) 0x4002000C)) // uint32_t *pGpiodModeReg = (uint32_t*)0x40020000;

#define RCCAPB1ENR (*((volatile unsigned long *) 0x40023840))

#define TIM6CR1    (*((volatile unsigned long *) 0x40001000))
#define TIM6SR     (*((volatile unsigned long *) 0x40001010))
#define TIM6CNT    (*((volatile unsigned long *) 0x40001024))
#define TIM6PSC    (*((volatile unsigned long *) 0x40001028))
#define TIM6ARR    (*((volatile unsigned long *) 0x4000102C))

#define TIM12CR1   (*((volatile unsigned long *) 0x40001800))
#define TIM12DIER  (*((volatile unsigned long *) 0x4000180C))
#define TIM12SR    (*((volatile unsigned long *) 0x40001810))
#define TIM12CNT   (*((volatile unsigned long *) 0x40001824))
#define TIM12PSC   (*((volatile unsigned long *) 0x40001828))
#define TIM12ARR   (*((volatile unsigned long *) 0x4000182C))
#define TIM12CCR1  (*((volatile unsigned long *) 0x40001834))

#define NVICISER1  (*((volatile unsigned long *) 0xE000E104))

