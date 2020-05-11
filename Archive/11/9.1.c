
#include "timer_interrupts.h"
#include "led.h"
#include "Keyboard.h"
	
#define DETECTOR_bm (1<<10)

enum DetectorState {ACTIVE,INACTIVE};

void DetectorInit(){
	IO0DIR=IO0DIR&(~DETECTOR_bm);
}

enum DetectorState eReadDetector(){
	if((IO0PIN&DETECTOR_bm)==0){
		
		return ACTIVE;
	}
	else {
		return INACTIVE;
	}
}

void Automat(){
			
	enum LedState{RUN_RIGHT,STOP,RUN_LEFT,CALLIB};
	enum LedState eLedState=CALLIB;

		if(eKeyBoardRead()==BUTTON_1){
					eLedState = STOP;
		}	
		else if(eKeyBoardRead()==BUTTON_2){
						eLedState = RUN_RIGHT;
		}	
		else if(eKeyBoardRead()==BUTTON_0){
						eLedState = RUN_LEFT;
		}	
		else if(eReadDetector()==ACTIVE){
						eLedState = STOP;
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
				case CALLIB:
					Led_StepLeft();
				break;
				default:
				break;
					
		}
	}



int main (){
	unsigned int iMainLoopCtr;
	KeyboardInit();
	DetectorInit();
	Timer0Interrupts_Init(20,&Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
