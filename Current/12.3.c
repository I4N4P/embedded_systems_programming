#include "uart.h"
#include "Led.h"
#include "servo.h"

#define TERMINATOR '0'
#define RECIEVER_SIZE 10
#define SEPARATOR ' '



unsigned char liczba[10]="test123";
unsigned char ucDane;

extern struct TransmiterBuffer sTransmiterBuffer;



int main(){
	sTransmiterBuffer.fLastCharacter=0;
	UART_InitWithInt(9600);
	
	IO0DIR=(1<<19);
	
	while(1){
		if(sTransmiterBuffer.eStatus==FREE){
			Transmiter_SendString(liczba);
		}
	}
}
