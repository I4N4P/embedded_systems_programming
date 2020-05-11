#include "uart.h"
#include "Led.h"
#include "servo.h"

#define TERMINATOR '0'
#define RECIEVER_SIZE 10
#define SEPARATOR ' '

void Delay(float fTime){
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}


unsigned char ucDane;

extern struct TransmiterBuffer sTransmiterBuffer;



int main(){
	sTransmiterBuffer.fLastCharacter=0;
	UART_InitWithInt(9600);

	IO0DIR=(1<<19);
	
	
	
	while(1){
		
		Delay(1);
	
	}
}
