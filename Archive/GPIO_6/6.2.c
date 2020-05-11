#include<LPC21xx.H>
#include"Led.h"
#include"keyboard.h"

enum LedState{STATE0,STATE1,STATE2,STATE3,STATE4,STATE5};
enum LedState eLedState = STATE0;

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
			case STATE0:
				eLedState = STATE1;
				LedStepRight();
				break;
			case STATE1:
				eLedState = STATE2;
				LedStepRight();
				break;
			case STATE2:
				eLedState = STATE3;
				LedStepRight();
				break;
			case STATE3:
				eLedState = STATE4;
				LedStepLeft();
				break;
			case STATE4:
				eLedState = STATE5;
				LedStepLeft();
				break;
			case STATE5:
				eLedState = STATE0;
				LedStepLeft();
				break;
			default:
				break;
			
		}
	Delay(500);
	}
}
