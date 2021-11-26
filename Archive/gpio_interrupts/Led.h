#include<LPC21xx.H>

enum StepDirection {LEFT,RIGHT};

void LedInit(void);
void Led_StepLeft(void);
void Led_StepRight(void);
void LedOn(unsigned char ucLedindeks);
void LedStep(int StepDirection);
