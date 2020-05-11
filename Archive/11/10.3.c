#include "uart.h"
#include "Led.h"
#include "servo.h"

extern char cOdebranyZnak;
extern struct Servo sServo;

int main(){
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(5);
	
	while(1){
	
		if(cOdebranyZnak=='1'){
			sServo.uiDesiredPosition=50;
		}
		else if(cOdebranyZnak=='2'){
			sServo.uiDesiredPosition=100;
		}
		else if(cOdebranyZnak=='3'){
			sServo.uiDesiredPosition=150;
		}
		else if(cOdebranyZnak=='c'){
			sServo.eState=CALLIB;
		}
		
	}

}

