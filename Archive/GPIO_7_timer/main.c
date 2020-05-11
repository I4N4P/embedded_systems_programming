#include <LPC21xx.H>
#include "Led.h"
#include "keyboard.h"
#include "timer.h" 
 
#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

enum LedState{RUN_RIGHT,STOP,RUN_LEFT};
enum LedState eLedState = STOP;


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


void Delay(float fTime){
	
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}


int main(){
	LedInit();
	//InitTimer0();
	InitTimer0Match0(1000);
	while(1){
		LedStepLeft();
		//WaitOnTimer0(250);
		WaitOnTimer0Match0();
	}
}
