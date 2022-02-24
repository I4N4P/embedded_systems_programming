#include "command_interpreter.h"

#define NULL 0

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;

struct Keyword asKeywordList[MAX_KEYWORD_NR] = {
    {ID, "id"},
    {CALIB,"calib"},
    {GOTO, "goto" },
    {STEP, "step" }
};

unsigned char ucFindTokensInString(char *pcString)
{
    enum WorkType eTryb = DELIMITER;

    unsigned char ucTokenNr = 0;
    unsigned char ucArrayIndex;
    unsigned char ucCurrentChar;

     for(ucArrayIndex = 0;;ucArrayIndex++){
        ucCurrentChar = pcString[ucArrayIndex];
        switch(eTryb){
        case TOKEN:
            if(ucTokenNr == MAX_TOKEN_NR)
                return ucTokenNr;
            else if(ucCurrentChar == NULL)
                return ucTokenNr;
            else if(ucCurrentChar != ' ')
                eTryb = TOKEN;
            else
                eTryb = DELIMITER;
            break;

        case DELIMITER:
            if(ucCurrentChar == NULL){
                return ucTokenNr;
            }else if(ucCurrentChar == ' '){
                eTryb = DELIMITER;
            }else{
                eTryb = TOKEN;
                asToken[ucTokenNr].uValue.pcString = pcString + ucArrayIndex;
                ucTokenNr++;
            }
            break;
        }
    }
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0;(pcStr1[ucCharacterCounter] == pcStr2[ucCharacterCounter]);ucCharacterCounter++){
        if((pcStr1[ucCharacterCounter] == NULL)&&(pcStr2[ucCharacterCounter] == NULL))
            return EQUAL;
    }
    return DIFFERENT;
}

enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode)
{
    unsigned char ucArrayIndex;

    for(ucArrayIndex = 0; ucArrayIndex < MAX_KEYWORD_NR; ucArrayIndex++){

        if(EQUAL == eCompareString(asKeywordList[ucArrayIndex].cString, pcStr)){
            *peKeywordCode = asKeywordList[ucArrayIndex].eCode;
            return rOK;
       }
    }
    return rERROR;
}

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue)
{
    unsigned char ucCharacterCounter;
    unsigned char ucCurrentCharacter;

    *puiValue=0;

    if((pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == NULL))
        return rERROR;

    for(ucCharacterCounter = 2; ucCharacterCounter < 7; ucCharacterCounter++){
        ucCurrentCharacter = pcStr[ucCharacterCounter];

        if(ucCurrentCharacter == NULL)
            return rOK;
        else if(ucCharacterCounter == 6)
            return rERROR;

        *puiValue = *puiValue << 4;

        if(ucCurrentCharacter <= '9' && ucCurrentCharacter >= '0')
            ucCurrentCharacter = ucCurrentCharacter - '0';
        else if(ucCurrentCharacter <= 'F' && ucCurrentCharacter >= 'A')
            ucCurrentCharacter = ucCurrentCharacter - 'A' + 10;
        else
            return rERROR;

        *puiValue = (*puiValue) | ucCurrentCharacter;
    }
    return rERROR;
}

void DecodeTokens(void)
{
    unsigned char ucArrayIndex;
    struct Token *psCurrentToken;
    unsigned int uiTokenValue;
    enum KeywordCode eKodTokena;

    for(ucArrayIndex = 0; ucArrayIndex < ucTokenNr; ucArrayIndex++){
        psCurrentToken = &asToken[ucArrayIndex];
        if(rOK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue)){
            psCurrentToken->eType = NUMBER;
            psCurrentToken->uValue.uiNumber = uiTokenValue;
        }
        else if(rOK == eStringToKeyword(psCurrentToken->uValue.pcString, &eKodTokena)){
            psCurrentToken->eType = KEYWORD;
            psCurrentToken->uValue.eKeyword = eKodTokena;
        }
        else{
            psCurrentToken->eType = STRING;
        }
    }
}

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar)
{
    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0; pcString[ucCharacterCounter]!=NULL; ucCharacterCounter++){
        if(pcString[ucCharacterCounter] == cOldChar)
            pcString[ucCharacterCounter] = cNewChar;
    }
}

void DecodeMsg(char *pcString)
{
    ucTokenNr = ucFindTokensInString(pcString);
    ReplaceCharactersInString(pcString, ' ', NULL);
    DecodeTokens();
}
