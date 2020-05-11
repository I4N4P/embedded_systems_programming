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
enum eRecieverStatus {EMPTY, READY, OVERFLOW};
enum Result {OK, ERROR};
struct RecieverBuffer{
char cData[RECIEVER_SIZE];
unsigned char ucCharCtr;
enum eRecieverStatus eStatus;
};


unsigned int liczba3;
unsigned char tablica[10];
extern char cOdebranyZnak;
extern unsigned char ucCharCtr1;
unsigned char ucDane;
unsigned char liczba[20]="min ";
unsigned char liczba1[20]="sec ";
unsigned char liczba2[20]="calc ";
extern struct TransmiterBuffer sTransmiterBuffer;
struct RecieverBuffer sBuffer;
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

int iCompareString(unsigned char *pArray1,unsigned char *pArray2){
	unsigned char ucArrayIndex;
	for(ucArrayIndex=0;pArray1[ucArrayIndex]==pArray2[ucArrayIndex];ucArrayIndex++){
		if(ucArrayIndex==5){
			return 1;
		}
	
	
	}
	
	return 0;
}

void Reciever_PutCharacterToBuffer(char cCharacter){
	if(sBuffer.ucCharCtr==RECIEVER_SIZE){
			sBuffer.eStatus=OVERFLOW;
			
		}	
	
	 if(cCharacter!=TERMINATOR){
		
			sBuffer.cData[sBuffer.ucCharCtr]=cCharacter;
		 
			sBuffer.ucCharCtr++;
	}else if(cCharacter==TERMINATOR){
			sBuffer.cData[sBuffer.ucCharCtr]=TERMINATOR;
			sBuffer.eStatus=READY;
			sBuffer.ucCharCtr=0;
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
				
			
			}else if(eReciever_GetStatus()==READY){
				Reciever_GetStringCopy(tablica);
				if(iCompareString(tablica,liczba2)){
						eHexStringToUInt((tablica+5),&liczba3);
						liczba3=liczba3^2;
						UIntToHexStr(liczba3,liczba2+5);
						Transmiter_SendString(liczba2);
					
				}
			}
			
		}	
	
	}
}
