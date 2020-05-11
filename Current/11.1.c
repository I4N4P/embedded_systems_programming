#include "uart.h"
#include "Led.h"
#include "servo.h"

#define TERMINATOR 0
#define RECIEVER_SIZE 4

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
			return ;
		}	
	
	if(cCharacter!=TERMINATOR){
		
			sBuffer.cData[ucCharCtr]=cCharacter;
			ucCharCtr++;
	}else{
			sBuffer.cData[ucCharCtr]=TERMINATOR;
			sBuffer.eStatus=READY;
			ucCharCtr=0;
	}
	
		
	}

enum eRecieverStatus eReciever_GetStatus(void){
	return sBuffer.eStatus;
}

void Reciever_GetStringCopy(char * ucDestination){
	unsigned char ucArrayIndex;
	for(ucArrayIndex=0;sBuffer.cData[ucArrayIndex]!=TERMINATOR;ucArrayIndex++){
		ucDestination[ucArrayIndex]=sBuffer.cData[ucArrayIndex];
	}
	sBuffer.eStatus=EMPTY;
}

int main(){
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(5);
	Reciever_PutCharacterToBuffer ('k');
	Reciever_PutCharacterToBuffer ('o');
	Reciever_PutCharacterToBuffer ('d');
	Reciever_PutCharacterToBuffer (TERMINATOR);
	sBuffer.eStatus = EMPTY;
	Reciever_PutCharacterToBuffer ('k');
	Reciever_PutCharacterToBuffer ('o');	
	Reciever_PutCharacterToBuffer ('d');
	Reciever_PutCharacterToBuffer ('1');
	Reciever_PutCharacterToBuffer (TERMINATOR);
	
	while(1){
	
		
	}

}

