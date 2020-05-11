#include<LPC21xx.H>
#include"Led.h"
#include"keyboard.h"

enum LedState{LED_LEFT,LED_RIGHT};
enum LedState eLedState = LED_LEFT;

void Delay(float fTime){
	
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}


int main(){
	KeyboardInit();
	LedInit();
	
	while(1){
		
		static int iCounter=0;
		
		switch(eLedState){
			case LED_RIGHT:
				if(iCounter==3){
					eLedState = LED_LEFT;
					iCounter=0;
				}
				LedStepRight();				
				break;
			case LED_LEFT:
				if(iCounter==3){
					eLedState = LED_RIGHT;
					iCounter=0;
				}
				LedStepLeft();
				break;
		}
		iCounter++;
		Delay(500);
		/*if(iCounter==3){
			if(eLedState==LED_LEFT)	
				eLedState = LED_RIGHT;	
			else 
				eLedState = LED_LEFT;
			iCounter=0;
		}
		
	*/	
	}
}
