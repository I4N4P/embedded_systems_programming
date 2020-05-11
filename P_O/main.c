#include <LPC21xx.H>

#define NULL 0 
#define MASKA 0x0F 

  

enum Result {OK, ERROR};

enum CompResult {DIFFERENT, EQUAL}; 
  
void CopyString(char pcSource[], char pcDestination[]){ 

		unsigned char ucArrayIndex; 

		for(ucArrayIndex = 0; pcSource[ucArrayIndex]!=NULL; ucArrayIndex++){ 
				pcDestination[ucArrayIndex] = pcSource[ucArrayIndex]; 
		} 
		pcDestination[ucArrayIndex] = NULL; 
} 


enum CompResult eCompareString(char pcStr1[], char pcStr2[]){ 

		unsigned char ucArrayIndex; 

		for(ucArrayIndex=0;(pcStr1[ucArrayIndex]==pcStr2[ucArrayIndex]);ucArrayIndex++){
				if((pcStr1[ucArrayIndex]==NULL)&&(pcStr2[ucArrayIndex]==NULL)){
						return EQUAL;; 
				} 
		} 
		return DIFFERENT; 
} 


void AppendString(char pcSourceStr[],char pcDestinationStr[]){ 

		unsigned char ucArrayIndex; 

    for(ucArrayIndex = 0; pcDestinationStr[ucArrayIndex]!=NULL; ucArrayIndex++){}
		CopyString(pcSourceStr, pcDestinationStr + ucArrayIndex); 
} 


void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){ 

    unsigned char ucArrayIndex; 
	
    for(ucArrayIndex = 0; pcString[ucArrayIndex]!=NULL; ucArrayIndex++){ 
        if(pcString[ucArrayIndex] == cOldChar){ 
						pcString[ucArrayIndex] = cNewChar; 
				} 
    } 
} 

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

    unsigned char ucArrayIndex; 
    unsigned char ucCurrentChar; 
		
		*puiValue=0; 

		if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==NULL)){ 
				return ERROR; 
		} 
		for(ucArrayIndex=2; ucArrayIndex!=NULL; ucArrayIndex++){ 
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

  

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){ 

    unsigned char ucArrayIndex;   

    for(ucArrayIndex=0; pcDestinationStr[ucArrayIndex]!=NULL; ucArrayIndex++){} 
		UIntToHexStr(uiValue, &pcDestinationStr[ucArrayIndex]); 

} 
#define MAX_TOKEN_NR 3 
#define NULL 0 
#define MAX_KEYWORD_NR 3 
#define MAX_KEYWORD_STRING_LTH 10 
 
enum KeywordCode {LD, ST, RST}; 

union TokenValue{ 
    enum KeywordCode eKeyword; 
    unsigned int uiNumber; 
    char* pcString; 
}; 
  
enum TokenType {KEYWORD, NUMBER, STRING}; 
  
struct Token{ 
    enum  TokenType  eType; 
    union TokenValue uValue; 
};  

struct Token asToken[MAX_TOKEN_NR]; 

  

struct Keyword{ 
    enum KeywordCode eCode; 
    char cString[MAX_KEYWORD_STRING_LTH + 1]; 
}; 

  

struct Keyword asKeywordList[MAX_KEYWORD_NR]={ 
    {RST,"reset"}, 
    {LD, "load" }, 
    {ST, "store"} 
}; 
  

unsigned char ucTokenNr; 

enum WorkType{TOKEN, DELIMITER};  

unsigned char ucFindTokensInString(char *pcString){ 

    enum WorkType eTryb=DELIMITER; 

    unsigned char ucTokenNr=0; 
    unsigned char ucArrayIndex; 
    unsigned char ucCurrentChar; 
  
     for(ucArrayIndex=0;;ucArrayIndex++){ 
        ucCurrentChar=pcString[ucArrayIndex]; 
        switch(eTryb){ 
            case TOKEN: 
            { 
                if(ucTokenNr==MAX_TOKEN_NR){ 
                    return ucTokenNr; 
                } 
                else if(ucCurrentChar==NULL){ 
                    return ucTokenNr; 
                } 
                else if(ucCurrentChar!=' '){ 
                   eTryb=TOKEN; 
                } 
                else{ 
                    eTryb=DELIMITER; 
                } 
                break; 
            } 
            case DELIMITER: 
            { 
                if(ucCurrentChar==NULL){ 
                    return ucTokenNr; 
                } 

                else if(ucCurrentChar==' '){ 
                  eTryb=DELIMITER; 
                } 

                else{ 
                    eTryb=TOKEN; 
                    asToken[ucTokenNr].uValue.pcString=pcString+ucArrayIndex; 
                    ucTokenNr++; 
                } 

                break; 
            } 
        } 
    } 
} 

//enum Result {OK, ERROR}; 

  

enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode){ 
  
    unsigned char ucArrayIndex;   

    for(ucArrayIndex=0; ucArrayIndex< MAX_KEYWORD_NR; ucArrayIndex++){ 

        if(EQUAL == eCompareString(asKeywordList[ucArrayIndex].cString, pcStr)){ 
            *peKeywordCode= asKeywordList[ucArrayIndex].eCode; 
            return OK; 
       } 
    } 
    return ERROR; 
} 


void DecodeTokens(void){ 

    unsigned char ucArrayIndex; 
    struct Token *psCurrentToken; 
    unsigned int uiTokenValue; 
    enum KeywordCode eKodTokena; 

    for(ucArrayIndex = 0; ucArrayIndex < ucTokenNr; ucArrayIndex++){ 
        psCurrentToken = &asToken[ucArrayIndex]; 
        if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue)){ 
            psCurrentToken->eType = NUMBER; 
            psCurrentToken->uValue.uiNumber= uiTokenValue; 
        } 
        else if(OK== eStringToKeyword(psCurrentToken->uValue.pcString, &eKodTokena)){ 
            psCurrentToken->eType=KEYWORD; 
            psCurrentToken->uValue.eKeyword=eKodTokena; 
        } 
        else{ 
            psCurrentToken->eType=STRING; 
        } 
    } 
} 

void DecodeMsg(char *pcString){ 
    ucTokenNr= ucFindTokensInString(pcString); 
    ReplaceCharactersInString(pcString, ' ', NULL); 
    DecodeTokens(); 
} 

 

int main(){
	char tablica[20]="Ala ma Kota";
	char tablica2[20]="Beata ma Psa";
	while(1){

	
		CopyString(tablica,tablica2);

	}
}
