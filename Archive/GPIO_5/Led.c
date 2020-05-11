#include<LPC21xx.H>
#include"Led.h"

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

void LedInit(){
	IO1DIR=IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	IO1CLR=LED1_bm|LED2_bm|LED3_bm;
	IO1SET=LED0_bm;	 
}

void LedStepLeft(){
	LedStep(LEFT);
}

void LedStepRight(){
	LedStep(RIGHT);
}
