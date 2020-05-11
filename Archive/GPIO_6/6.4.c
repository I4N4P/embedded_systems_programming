#include<LPC21xx.H>
#include"Led.h"
#include"keyboard.h"

enum LedState{RUN_RIGHT,STOP};
enum LedState eLedState = STOP;

void Delay(float fTime){
	
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}


int main(){
	KeyboardInit();
	LedInit();
	
	while(1){
			
		static int iLicznik=0;
		
		switch(eLedState){
				case STOP:
					if(eKeyBoardRead()==BUTTON_0){
						eLedState = RUN_RIGHT;
					}	
					break;
				case RUN_RIGHT:
					iLicznik++;
					LedStepRight();
					if(iLicznik==3){
						eLedState = STOP;
						iLicznik=0;
					}	
					Delay(500);
					break;
		}
	}
}
