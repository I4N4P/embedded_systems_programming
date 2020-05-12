#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "servo.h"

#define DETECTOR_bm (1<<7)

enum State {ACTIVE, INACTIVE};

enum ServoState {CALLIB, IDDLE, IN_PROGRESS,SET_OFFSET};

struct Servo{
	enum ServoState eState;
	int iCurrentPosition;
	int iDesiredPosition;
	int iOffset;
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
	sServo.iDesiredPosition= uiPosition;
}
	

void Automat(){
		
	switch(sServo.eState){
		
		case CALLIB:
			if(eReadDetector()==INACTIVE){
				LedStepLeft();
			}	
			else {
				sServo.iDesiredPosition=0;
				sServo.iCurrentPosition=0;
				sServo.eState=SET_OFFSET;
			}
			break;	
		
		case SET_OFFSET:	
			sServo.iOffset=12;
			if(sServo.iCurrentPosition<sServo.iOffset){
				LedStepLeft();
				sServo.iCurrentPosition++;
			}
			else if(sServo.iCurrentPosition>sServo.iOffset){
				LedStepRight();
				sServo.iCurrentPosition--;
			}
			else{
				sServo.eState=IDDLE;
				sServo.iCurrentPosition=0;
				}
				break;
		
		case IDDLE: 
			if (sServo.iCurrentPosition == sServo.iDesiredPosition){
				sServo.eState = IDDLE;
			}
			else {
				sServo.eState=IN_PROGRESS;
			}
			break;
					
		case IN_PROGRESS: 
			if(sServo.iCurrentPosition > sServo.iDesiredPosition){
				sServo.eState = IN_PROGRESS;
				LedStepLeft();
				sServo.iCurrentPosition--;
			}
			else if(sServo.iCurrentPosition < sServo.iDesiredPosition){
				sServo.eState = IN_PROGRESS;
				LedStepRight();
				sServo.iCurrentPosition++;
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
}



