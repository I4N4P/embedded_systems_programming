#include "uart.h"
#include "Led.h"
#include "servo.h"

#define TERMINATOR '0'
#define RECIEVER_SIZE 10

extern struct Servo sServo;
unsigned char tablica[10];
enum eRecieverStatus {EMPTY, READY, OVERFLOW};
struct RecieverBuffer sBuffer;
unsigned char ucCharCtr=0;

struct RecieverBuffer{
char cData[RECIEVER_SIZE];
unsigned char ucCharCtr;
enum eRecieverStatus eStatus;
};


void Reciever_PutCharacterToBuffer(char cCharacter){
	if(ucCharCtr==RECIEVER_SIZE){
			sBuffer.eStatus=OVERFLOW;
			
		}	
	
	 if(cCharacter!=TERMINATOR){
		
			sBuffer.cData[ucCharCtr]=cCharacter;
		 
			ucCharCtr++;
	}else if(cCharacter==TERMINATOR){
			sBuffer.cData[ucCharCtr]=TERMINATOR;
			sBuffer.eStatus=READY;
			ucCharCtr=0;
	}
	
		
	}

enum eRecieverStatus eReciever_GetStatus(void){
	return sBuffer.eStatus;
}

void Reciever_GetStringCopy(unsigned char * ucDestination){
	unsigned char ucArrayIndex;
	for(ucArrayIndex=0;sBuffer.cData[ucArrayIndex]!=TERMINATOR;ucArrayIndex++){
		ucDestination[ucArrayIndex]=sBuffer.cData[ucArrayIndex];
	}
	ucDestination[ucArrayIndex]=TERMINATOR;
	sBuffer.eStatus=EMPTY;
}
int iCompareString(unsigned char *pArray1,unsigned char *pArray2){
	unsigned char ucArrayIndex;
	for(ucArrayIndex=0;pArray1[ucArrayIndex]==pArray2[ucArrayIndex];ucArrayIndex++){
		if((pArray1[ucArrayIndex]==TERMINATOR)&&(pArray1[ucArrayIndex]==TERMINATOR)){
			return 1;
		}
	}
	return 0;
}


int main(){
	unsigned char callib[10]="callib0";
	unsigned char right[10]="right0";
	unsigned char left[10]="left0";
	
	
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(5);
	sServo.eState=IDLE;
	
	while(1){
	if(eReciever_GetStatus()==READY){
		Reciever_GetStringCopy(tablica);
		if(iCompareString(tablica,callib)){
			sServo.eState = CALLIB;
		}
		else if(iCompareString(tablica,right)){
			sServo.uiDesiredPosition = 50;
		}
		else if(iCompareString(tablica,left)){
			sServo.uiDesiredPosition = 150;
		}
		}
		
	}

}

