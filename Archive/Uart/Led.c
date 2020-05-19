#include <LPC21xx.H>
#include "Led.h"


#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

void LedInit(void){
	IO1DIR=IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm;//Ustawienie wyjsc w rejestrze wpisanie 1 na odpowiednich pozycjach
	IO1CLR=LED1_bm|LED2_bm|LED3_bm;
	IO1SET=LED0_bm;	 
}

void LedStepLeft(void){
	LedStep(LEFT);
}

void LedStepRight(void){
	LedStep(RIGHT);
}

void LedStep(int StepDirection){
	
	static unsigned int uiNrDiody=0;
	
	switch(StepDirection){
		case LEFT:
			uiNrDiody++;
			break;
		case RIGHT:
			uiNrDiody--;
			break;
		default:
			break;
	}
	LedOn(uiNrDiody%4);
}

void LedOn(unsigned char ucLedindeks){
	IO1CLR=LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	switch(ucLedindeks){
		case 0:
			IO1SET=LED0_bm;
			break;
		case 1:
			IO1SET=LED1_bm;
			break;
		case 2:
			IO1SET=LED2_bm;
			break;
		case 3:
			IO1SET=LED3_bm;
			break;
		default:
			break;
	}
}

