#include<LPC21xx.H>

enum StepDirection {LEFT,RIGHT};

void LedInit(void);
void LedStepLeft(void);
void LedStepRight(void);
void LedOn(unsigned char ucLedindeks);
