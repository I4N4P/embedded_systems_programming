#include<LPC21xx.H>
#include"Led.h"
#include"keyboard.h"

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
	KeyboardInit();
	LedInit();
	
	while(1){
			
		switch(eLedState){
			case STOP:
					if(eKeyBoardRead()==BUTTON_0){
						eLedState = RUN_LEFT;
					}	
					else if(eKeyBoardRead()==BUTTON_2){
						eLedState = RUN_RIGHT;
					}		
					break;
			case RUN_LEFT:
				if(eKeyBoardRead()==BUTTON_1){
					eLedState = STOP;
				}	
				else{
					LedStepLeft();
					Delay(500);
				}
				break;
				case RUN_RIGHT:
				if(eKeyBoardRead()==BUTTON_1){
					eLedState = STOP;
				}	
				else{
					LedStepRight();
					Delay(500);
				}
				break;
		}
	Delay(50);	
	}
}
