#include<LPC21xx.H>
#include"Led.h"
#include"keyboard.h"

enum LedState{RUN_RIGHT,STOP};
enum LedState eLedState = RUN_RIGHT;

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
			case RUN_RIGHT:
				if(eKeyBoardRead()==BUTTON_0){
					eLedState = STOP;
				}	
				LedStepRight();
				break;
			case STOP:
				if(eKeyBoardRead()==BUTTON_1){
					eLedState = RUN_RIGHT;
				}	
				break;
		}
	Delay(500);	
	}
}
