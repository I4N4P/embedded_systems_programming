#include "uart.h"
#include "Led.h"
#include "servo.h"

#define TERMINATOR '0'
#define RECIEVER_SIZE 10
#define SEPARATOR ' '


unsigned char tablica[10];
unsigned char ucCharCtr=0;

enum eRecieverStatus {EMPTY, READY, OVERFLOW};
enum Result {OK, ERROR};

struct RecieverBuffer sBuffer;
extern struct Servo sServo;

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
int iCompareString(unsigned char *pArray1,unsigned char *pArray2,unsigned char *pArray3){
	unsigned char ucArrayIndex;
	for(ucArrayIndex=0;pArray1[ucArrayIndex]==pArray2[ucArrayIndex];ucArrayIndex++){
		if(ucArrayIndex==5){
			return 1;
		}
	for(ucArrayIndex=0;pArray1[ucArrayIndex]==pArray3[ucArrayIndex];ucArrayIndex++){
		if(ucArrayIndex==5){
			return 2;
		}
	}
	}
	
	return 0;
}

enum Result eHexStringToUInt(unsigned char pcStr[],unsigned int *puiValue){ 

    unsigned char ucArrayIndex; 
    unsigned char ucCurrentChar; 
		
		*puiValue=0; 

		if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==TERMINATOR)){ 
				return ERROR; 
		} 
		for(ucArrayIndex=2; ucArrayIndex!=TERMINATOR; ucArrayIndex++){ 
				ucCurrentChar = pcStr[ucArrayIndex]; 
				if(ucArrayIndex==6){ 
						return ERROR; 
				} 
				*puiValue = *puiValue << 4;
        if((ucCurrentChar<= 'F') && (ucCurrentChar>= 'A')){ 
						ucCurrentChar=ucCurrentChar-'A'+10; 
				} 
				else if((ucCurrentChar <= '9') && (ucCurrentChar>= '0')){ 
						ucCurrentChar=ucCurrentChar-'0'; 
				} 
				else{ 
						return ERROR; 
				} 
				*puiValue = (*puiValue) | ucCurrentChar; 
		} 
		return OK; 

} 

int main(){
	unsigned char callib[10]="callib";
	unsigned char gt[10]="goto ";
	
	
	
	
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(5);
	sServo.eState=IDLE;
	
	while(1){
		if(eReciever_GetStatus()==READY){
			Reciever_GetStringCopy(tablica);
			switch(iCompareString(tablica,callib,gt)){
				case 0:
					break;
				case 1:
					sServo.eState=CALLIB;
					break;
				case 2:
					eHexStringToUInt((tablica+5),&sServo.uiDesiredPosition);
					break;
				default:
					break;
				}
		}
	}
}
