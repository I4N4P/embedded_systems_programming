#include "command_interpreter.h"

#define NULL 0

struct token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;

struct keyword asKeywordList[MAX_KEYWORD_NR] = {
    {ID, "id"},
    {CALIB,"calib"},
    {GOTO, "goto" },
    {STEP, "step" }
};

unsigned char find_tokens_in_string(char *pcString)
{
    enum work_type eTryb = DELIMITER;

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

enum comp_result compare_string(char pcStr1[], char pcStr2[])
{
    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0;(pcStr1[ucCharacterCounter] == pcStr2[ucCharacterCounter]);ucCharacterCounter++){
        if((pcStr1[ucCharacterCounter] == NULL)&&(pcStr2[ucCharacterCounter] == NULL))
            return EQUAL;
    }
    return DIFFERENT;
}

enum result string_to_keyword (char pcStr[],enum keyword_code *peKeywordCode)
{
    unsigned char ucArrayIndex;

    for(ucArrayIndex = 0; ucArrayIndex < MAX_KEYWORD_NR; ucArrayIndex++){

        if(EQUAL == compare_string(asKeywordList[ucArrayIndex].cString, pcStr)){
            *peKeywordCode = asKeywordList[ucArrayIndex].eCode;
            return rOK;
       }
    }
    return rERROR;
}

enum result hex_string_to_int(char pcStr[],unsigned int *puiValue)
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

void decode_tokens(void)
{
    unsigned char ucArrayIndex;
    struct token *psCurrentToken;
    unsigned int uiTokenValue;
    enum keyword_code eKodTokena;

    for(ucArrayIndex = 0; ucArrayIndex < ucTokenNr; ucArrayIndex++){
        psCurrentToken = &asToken[ucArrayIndex];
        if(rOK == hex_string_to_int(psCurrentToken->uValue.pcString, &uiTokenValue)){
            psCurrentToken->eType = NUMBER;
            psCurrentToken->uValue.uiNumber = uiTokenValue;
        }
        else if(rOK == string_to_keyword(psCurrentToken->uValue.pcString, &eKodTokena)){
            psCurrentToken->eType = KEYWORD;
            psCurrentToken->uValue.eKeyword = eKodTokena;
        }
        else{
            psCurrentToken->eType = STRING;
        }
    }
}

void replace_Char_in_string(char pcString[],char cOldChar,char cNewChar)
{
    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0; pcString[ucCharacterCounter]!=NULL; ucCharacterCounter++){
        if(pcString[ucCharacterCounter] == cOldChar)
            pcString[ucCharacterCounter] = cNewChar;
    }
}

void decode_msg(char *pcString)
{
    ucTokenNr = find_tokens_in_string(pcString);
    replace_Char_in_string(pcString, ' ', NULL);
    decode_tokens();
}
