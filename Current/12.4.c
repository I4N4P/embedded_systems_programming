#include "uart.h"
#include "Led.h"
#include "servo.h"

#define TERMINATOR '0'
#define RECIEVER_SIZE 10
#define SEPARATOR ' '
#define MASKA 0x0F 


unsigned char liczba[20]="licznik ";
unsigned char ucDane;

extern struct TransmiterBuffer sTransmiterBuffer;


void UIntToHexStr(unsigned int uiValue, unsigned char pcStr[]){ 

    unsigned char ucNibbleCounter; 
    unsigned char ucCurrentNibble; 

    pcStr[0]='0'; 
    pcStr[1]='x'; 
    pcStr[6]=NULL; 

    for(ucNibbleCounter=0; ucNibbleCounter<4; ucNibbleCounter++){ 
				ucCurrentNibble=(uiValue >> (ucNibbleCounter*4))&MASKA; 
				if(ucCurrentNibble<10){ 
						pcStr[5-ucNibbleCounter] = '0'+ucCurrentNibble; 
				} 
				else{ 
						pcStr[5-ucNibbleCounter] = 'A'+(ucCurrentNibble-10);
				} 
		} 
} 

void AppendUIntToString(unsigned int uiValue,unsigned char pcDestinationStr[]){ 

    unsigned char ucArrayIndex;   

    for(ucArrayIndex=0; pcDestinationStr[ucArrayIndex]!=NULL; ucArrayIndex++){} 
		UIntToHexStr(uiValue, &pcDestinationStr[ucArrayIndex]); 

} 
int main(){
	sTransmiterBuffer.fLastCharacter=0;
	UART_InitWithInt(9600);
	
	IO0DIR=(1<<19);
	
	while(1){
		if(sTransmiterBuffer.eStatus==FREE){
			UIntToHexStr(ucDane,liczba+8);
			Transmiter_SendString(liczba);
			ucDane++;
			
		}	
	}
}
