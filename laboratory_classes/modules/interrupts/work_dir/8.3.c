#include "main.h"
#include "led.h"
#include "timer.h"

#define TIM12_CLK_EN (1 << 6)
#define TIM12_PRESCA (16000 - 1)
#define TIM12_ENABLE (1 << 0)
#define TIM12_UPDATE (1 << 0)

#define TIM_IRQ_CLR  (0 << 1)
#define TIM_IRQ_EN   (1 << 0)

#define NVICI_CH_43  (1 << 11)

void (*ptrTimer0InterruptFunction)();

/**********************************************/
//(Interrupt Service Routine) of Timer 12 interrupt
__attribute__((interrupt)) void TIM8_BRK_TIM12_IRQHandler(void)
{
if (TIM12SR & TIM_IRQ_EN) ptrTimer0InterruptFunction();
	TIM12SR &= TIM_IRQ_CLR;
}
/**********************************************/
void timer_12_interrupts_init(unsigned int period,void (*ptrInterruptFunction)()) // microseconds
{
	ptrTimer0InterruptFunction = ptrInterruptFunction;
        // Enable Timer clock
	RCCAPB1ENR |= TIM12_CLK_EN;
	// set prescaler 16Mhz/16_000 = khz -> 1ms
	TIM12PSC = TIM12_PRESCA;
	// value
	TIM12ARR = period;
	// Enable Interrupt flag for a timer
	TIM12DIER |= TIM_IRQ_EN;
	// clear counter
	TIM12CNT = 0;
	// Enable Inetrrupt globally
	NVICISER1 |= NVICI_CH_43;
	// Enable Timer
	TIM12CR1 |= TIM12_ENABLE;

	while (!(TIM12SR & TIM12_UPDATE));
	// wait for interrupt
	while (!(TIM12SR & TIM_IRQ_EN));
	// Clear Interrupt flag
	TIM12SR &= TIM_IRQ_CLR;
}
/**********************************************/
int main ()
{
	unsigned int iMainLoopCtr;
	led_init();
	// void (*wsk_funckja)();
	// wsk_funckja=&Led_StepRight;
	timer_12_interrupts_init(250,&led_step_left);

	while (1) {
	 	iMainLoopCtr++;
	}
}
