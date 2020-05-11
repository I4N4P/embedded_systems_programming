#include <LPC21xx.H>

//void (*ptrTimer0InterruptFunction)(void);
void Timer0Interrupts_Init(unsigned int uiPeriod,void (*ptrInterruptFunction)(void));
//__irq void Timer0IRQHandler(void);


