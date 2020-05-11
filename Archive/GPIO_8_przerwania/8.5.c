
#include "timer_interrupts.h"
#include "led.h"
#include "Keyboard.h"
	

void Automat(){
			
enum LedState{RUN_RIGHT,STOP,RUN_LEFT};
enum LedState eLedState=STOP;

		if(eKeyBoardRead()==BUTTON_1){
					eLedState = STOP;
		}	
		else if(eKeyBoardRead()==BUTTON_2){
						eLedState = RUN_RIGHT;
		}	
		else if(eKeyBoardRead()==BUTTON_0){
						eLedState = RUN_LEFT;
		}	
	
		switch(eLedState){
			case STOP:
					
					break;
			case RUN_LEFT:
				
					Led_StepLeft();
				
				break;
			case RUN_RIGHT:
				
					Led_StepRight();
				
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
