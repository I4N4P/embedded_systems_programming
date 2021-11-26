#include "main.h"
#include "timer.h"

#define TIM12_CLK_EN (1 << 6)
#define TIM12_PRESCA (16000 - 1)
#define TIM12_ENABLE (1 << 0)
#define TIM12_UPDATE (1 << 0)
#define TIM6_CLK_EN  (1 << 4)
#define TIM6_PRESCA  (16000 - 1)
#define TIM6_ENABLE  (1 << 0)
#define TIM6_UPDATE  (1 << 0)
#define TIM_IRQ_CLR  (0 << 1)
#define TIM_IRQ_EN   (1 << 0)

void init_timer_6(void)
{
	// Enable Timer clock
	RCCAPB1ENR |= TIM6_CLK_EN;
	// set prescaler 16Mhz/16 = 1Mhz -> 1us
	TIM6PSC = TIM6_PRESCA;
	// Max value
	TIM6ARR = 0xffff;
	// Enable Timer
	TIM6CR1 |= TIM6_ENABLE;
	// This bit is set by hardware when the registers are updated
	while (!(TIM6SR & TIM6_UPDATE));
}

void wait_on_timer_6(unsigned int cycles)
{
	// clear counter
	TIM6CNT = 0;
	// wait on timer
	while (TIM6CNT < cycles);
}


void init_timer_12_match_0(unsigned int delay_time)
{
	// Enable Timer clock
	RCCAPB1ENR |= TIM12_CLK_EN;
	// set prescaler 16Mhz/16_000 = khz -> 1ms
	TIM12PSC = TIM12_PRESCA;
	// Max value
	TIM12ARR = 500;
	// count value
	TIM12CCR1 = delay_time;
	// clear counter
	TIM12CNT = 0;
	// Enable Timer
	TIM12CR1 |= TIM12_ENABLE;

	while (!(TIM12SR & TIM12_UPDATE));
	// wait for interrupt
	while (!(TIM12SR & TIM_IRQ_EN));
	// Clear Interrupt flag
	TIM12SR &= TIM_IRQ_CLR;
}

void wait_on_timer_12_match_0(void)
{
	TIM12CNT = 0;
	// wait for interrupt
	while (!(TIM12SR & TIM_IRQ_EN));
	TIM12SR &= TIM_IRQ_CLR;
}

