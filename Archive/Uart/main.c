
#include "timer_interrupts.h"
#include "led.h"
#include "Keyboard.h"
	enum LedState{RUN_RIGHT,STOP,RUN_LEFT};
enum LedState eLedState=STOP;

void Automat(){
			
//enum LedState eLedState=STOP;
	
	
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
					Led_StepLeft();
				
				}
				break;
				case RUN_RIGHT:
				if(eKeyBoardRead()==BUTTON_1){
					eLedState = STOP;
				}	
				else{
					Led_StepRight();
					
				}
				break;
				default:
				break;
					
		}
	}



int main (){
	unsigned int iMainLoopCtr;
	KeyboardInit();
	Timer0Interrupts_Init(20,&Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
