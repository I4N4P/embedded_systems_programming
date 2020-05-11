#include <LPC21xx.H>
#include "servo.h"
#include "timer_interrupts.h"
#include "led.h"
#include "Keyboard.h"
	
#define DETECTOR_bm (1<<10)


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
void ServoCallib(){
	sServo.eState = CALLIB;
}
void ServoInit(unsigned int uiServoFrequency){
	
	unsigned int time;
	
	ServoCallib();
	LedInit();
	DetectorInit();
	time=1000/uiServoFrequency;
	Timer0Interrupts_Init(time,&Automat);
}

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition=uiPosition;
}
