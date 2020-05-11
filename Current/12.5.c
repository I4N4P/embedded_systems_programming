#include "uart.h"
#include "Led.h"
#include "servo.h"
#include "timer_interrupts.h"

#define TERMINATOR '0'
#define RECIEVER_SIZE 10
#define SEPARATOR ' '
#define MASKA 0x0F 
void Delay(float fTime){
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}

extern unsigned char ucCharCtr1;
unsigned char ucDane;
unsigned char liczba[20]="min ";
unsigned char liczba1[20]="sec ";
extern struct TransmiterBuffer sTransmiterBuffer;

struct Watch {
unsigned char ucMinutes, ucSecconds;
unsigned char fSeccondsValueChanged, fMinutesValueChanged;
};
struct Watch sZegarek;
void WatchUpdate(){
	
	sZegarek.ucSecconds++;
	if(sZegarek.ucSecconds==60){
		sZegarek.ucSecconds=0;
	}
	sZegarek.fSeccondsValueChanged=1;
	
	if((sZegarek.ucSecconds%60)==0){
		
		sZegarek.ucMinutes++;
		if(sZegarek.ucMinutes==60){
			sZegarek.ucMinutes=0;
		}
		sZegarek.fMinutesValueChanged=1;
		
	}

}
void UIntToHexStr(unsigned int uiValue, unsigned char pcStr[]){ 

    unsigned char ucNibbleCounter; 
    unsigned char ucCurrentNibble; 

    pcStr[0]='0'; 
    pcStr[1]='x'; 
    pcStr[10]=NULL; 

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


int main(){
	sTransmiterBuffer.fLastCharacter=0;
	UART_InitWithInt(9600);
	Timer0Interrupts_Init(100, &WatchUpdate);
	IO0DIR=(1<<19);
	
	
	
	while(1){
		if(sTransmiterBuffer.eStatus==FREE){
			if(sZegarek.fMinutesValueChanged==1){
				UIntToHexStr(sZegarek.ucMinutes,liczba+4);
				Transmiter_SendString(liczba);
				sZegarek.fMinutesValueChanged=0;
				
			}else if(sZegarek.fSeccondsValueChanged==1){
				UIntToHexStr(sZegarek.ucSecconds,liczba1+4);
				Transmiter_SendString(liczba1);
				sZegarek.fSeccondsValueChanged=0;
			
			}
			
		}	
	
	}
}
