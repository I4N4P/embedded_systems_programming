#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "servo.h"

#define DETECTOR_bm (1<<7) //button3 jako detector 10 pin od detectora

enum State {ACTIVE, INACTIVE};

enum ServoState {CALLIB, IDDLE, IN_PROGRESS,SET_OFFSET};

struct Servo{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
	unsigned int uiOffset;
};

struct Servo sServo;


void DetectorInit(void){
	IO0DIR&=(~DETECTOR_bm);
}

enum State eReadDetector (void){
	if((IO0PIN&DETECTOR_bm) == 0){
		return(ACTIVE);
	}else{
		return(INACTIVE);
	}
}

void ServoCallib(void){
	sServo.eState = CALLIB;
	while(eReadDetector()==INACTIVE){
	}
}

void ServoGoTo(unsigned int uiPosition){
	sServo.eState = IN_PROGRESS;
	sServo.uiDesiredPosition= uiPosition;
}
	


void Automat(){
		
	switch(sServo.eState){
		
		case CALLIB:
			if(eReadDetector()==INACTIVE){
				LedStepLeft();
				sServo.eState = CALLIB;
			}	
			else {
				sServo.uiDesiredPosition=0;
				sServo.uiCurrentPosition=0;
				sServo.eState=SET_OFFSET;
			}
			break;	
		
		case SET_OFFSET:			
			if(sServo.uiCurrentPosition==sServo.uiOffset){
				sServo.uiCurrentPosition=0;
				sServo.eState=IDDLE;
			}
			else{	
				LedStepLeft();
				sServo.uiCurrentPosition++;
				sServo.eState=SET_OFFSET;
				}
				break;
		
		case IDDLE: 
			if (sServo.uiCurrentPosition == sServo.uiDesiredPosition){
				sServo.eState = IDDLE;
			}
			else {
				sServo.eState=IN_PROGRESS;
			}
			break;
					
		case IN_PROGRESS: 
			if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
				sServo.eState = IN_PROGRESS;
				LedStepLeft();
				sServo.uiCurrentPosition--;
			}
			else if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
				sServo.eState = IN_PROGRESS;
				LedStepRight();
				sServo.uiCurrentPosition++;
			}
			else{
				sServo.eState = IDDLE;
			}
			break;
	}
}
void ServoInit(unsigned int uiServoFrequency){
	DetectorInit();
	LedInit();
	Timer0Interrupts_Init(1000000/uiServoFrequency ,&Automat);
	ServoCallib();
	sServo.uiOffset=12;
}



