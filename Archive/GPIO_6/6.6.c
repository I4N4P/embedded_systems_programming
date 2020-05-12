#include"Led.h"
#include"keyboard.h"

enum LedState{RUN_RIGHT,STOP,RUN_LEFT,DIODE_BLINKING,DIODE_STATE_CHECK};
enum LedState eLedState = STOP;


void Delay(float fTime){
	
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}


int main(){
	
	unsigned int ucBlinkingCounter=0;
	
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
					else if(eKeyBoardRead()==BUTTON_3){
						eLedState = DIODE_BLINKING;
					}		
					break;
			case RUN_LEFT:
					LedStepLeft();
					if(eKeyBoardRead()==BUTTON_1){
						eLedState = STOP;
					}	
				break;
			case RUN_RIGHT:
					LedStepRight();
					if(eKeyBoardRead()==BUTTON_1){
						eLedState = STOP;
					}	
				break;
			case DIODE_BLINKING:
			{
				if( eKeyBoardRead() == BUTTON_1)
				{
					eLedState = STOP;
				}
				else if ( ucBlinkingCounter < 20 )
				{
					if( (ucBlinkingCounter%2) == 0 )
					{
						LedOn(1);
					}
					else 
					{
						LedOn(5);
					}
					ucBlinkingCounter++;
					eLedState=DIODE_BLINKING;
				}
				else 
				{
					eLedState = STOP;
				}
			break;
			}
		}
		Delay(50);	
	}
}
 
