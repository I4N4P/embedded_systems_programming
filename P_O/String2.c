#include <LPC21xx.H>
#include "String2.h"

#define NULL 0 
#define MASKA 0x0F 


void UIntToHexStr(unsigned int uiValue, char pcStr[]){ 

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


enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){ 

    unsigned char ucCharacterCounter; 
    unsigned char ucCurrentChar; 
		
		*puiValue=0; 

		if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==NULL)){ 
				return ERROR; 
		} 
		for(ucCharacterCounter=2; ucCharacterCounter!=NULL; ucCharacterCounter++){ 
				ucCurrentChar = pcStr[ucCharacterCounter]; 
				if(ucCharacterCounter==6){ 
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

  

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){ 

    unsigned char ucCharacterCounter;   

    for(ucCharacterCounter=0; pcDestinationStr[ucCharacterCounter]!=NULL; ucCharacterCounter++){} 
		UIntToHexStr(uiValue, &pcDestinationStr[ucCharacterCounter]); 

} 
