
#include "timer_interrupts.h"
#include "led.h"
#include "Keyboard.h"
	
#define DETECTOR_bm (1<<10)

enum DetectorState {ACTIVE,INACTIVE};

enum ServoState {CALLIB, IDLE, IN_PROGRESS};
struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};
struct Servo sServo;

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
		sServo.eState = IDLE;	
		if(sServo.eState == CALLIB){
				
		}	
		else if(sServo.uiCurrentPosition==sServo.uiDesiredPosition){
					sServo.eState = IDLE;
		}	
		else if(sServo.uiCurrentPosition!=sServo.uiDesiredPosition){
				sServo.eState=IN_PROGRESS;
		}
		
		switch(sServo.eState){
			case IDLE:
					
					break;
			case IN_PROGRESS:
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
					Led_StepRight();
					sServo.uiCurrentPosition++;
				}
				else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
					Led_StepLeft();
					sServo.uiCurrentPosition--;
				}
				else{
					sServo.eState = IDLE;
				}
				
				break;
				case CALLIB:
					if(eReadDetector()==ACTIVE){
						sServo.eState=IDLE;
						sServo.uiCurrentPosition=0;
						sServo.uiDesiredPosition=0;
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
	
	KeyboardInit();
	DetectorInit();
	Timer0Interrupts_Init(20,&Automat);

	while(1){
	 	if(eKeyBoardRead()==BUTTON_0){
					sServo.eState=CALLIB;
		}	
		else if(eKeyBoardRead()==BUTTON_1){
					sServo.uiDesiredPosition=12;
		}	
		else if(eKeyBoardRead()==BUTTON_2){
					sServo.uiDesiredPosition=24;
		}	
		else if(eKeyBoardRead()==BUTTON_3){
					sServo.uiDesiredPosition=36;
		}	
	}
}