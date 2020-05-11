#include "strings1.h" 

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

enum Result {OK, ERROR}; 

  

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

 