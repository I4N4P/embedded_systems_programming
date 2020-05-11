#include "uart.h"
#include "Led.h"
#include "servo.h"

extern char cOdebranyZnak;
extern struct Servo sServo;

int main(){
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(5);
	sServo.eState=IDLE;
	
	while(1){
	
		if(cOdebranyZnak=='1'){
			sServo.uiDesiredPosition=50;
			
		}
		else if(cOdebranyZnak=='c'){
			sServo.eState=CALLIB;
			cOdebranyZnak='d';
		}
		if(sServo.uiCurrentPosition==50){
			cOdebranyZnak='d';
			sServo.uiDesiredPosition=0;
			sServo.uiCurrentPosition=0;
		}
	
	}

}

