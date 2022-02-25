#include "main.h"
#include "console.h"
#include "string.h"

enum work_type {TOKEN, DELIMITER};
enum comp_result {DIFFERENT, EQUAL};
enum result {rOK,rERROR};

struct keyword{
        enum keyword_code eCode;
        char cString[MAX_KEYWORD_STRING_LTH + 1];
};

struct keyword keyword_list[MAX_KEYWORD_NR] = {
        {ID, "id"},
        {CALIB,"calib"},
        {GOTO, "goto" },
        {STEP, "step" },
        {CALC, "calc" },
        {TIME, "time" },
};

struct token tokken[MAX_TOKEN_NR];

unsigned char token_number;

unsigned char find_tokens_in_string(char *str)
{
        enum work_type mode = DELIMITER;

        unsigned char token_number = 0;
        unsigned char arr_index;
        unsigned char curr_char;

        for (arr_index = 0 ;; arr_index++) {
                curr_char = str[arr_index];
                switch (mode) {
                case TOKEN:
                        if (token_number == MAX_TOKEN_NR)
                                return token_number;
                        else if (curr_char == NULL)
                                return token_number;
                        else if (curr_char != ' ')
                                mode = TOKEN;
                        else
                                mode = DELIMITER;
                        break;
                case DELIMITER:
                        if (curr_char == NULL) {
                                return token_number;
                        } else if (curr_char == ' ') {
                                mode = DELIMITER;
                        } else {
                                mode = TOKEN;
                                tokken[token_number].uValue.pcString = str + arr_index;
                                token_number++;
                        }
                        break;
                }
        }
}


enum result string_to_keyword (char *str,enum keyword_code *keyword_code)
{
        unsigned char arr_index;

        for (arr_index = 0; arr_index < MAX_KEYWORD_NR; arr_index++) {
                if (EQUAL == compare_string(keyword_list[arr_index].cString, str)) {
                        *keyword_code = keyword_list[arr_index].eCode;
                        return rOK;
                }
        }
        return rERROR;
}

void decode_tokens(void)
{
        unsigned char arr_index;
        struct token *curr_token;
        unsigned int val_token;
        enum keyword_code code_token;

        for (arr_index = 0; arr_index < token_number; arr_index++) {
                curr_token = &tokken[arr_index];
                if (rOK == hex_string_to_int(curr_token->uValue.pcString, &val_token)) {
                        curr_token->eType = NUMBER;
                        curr_token->uValue.uiNumber = val_token;
                } else if (rOK == string_to_keyword(curr_token->uValue.pcString, &code_token)) {
                        curr_token->eType = KEYWORD;
                        curr_token->uValue.eKeyword = code_token;
                } else {
                        curr_token->eType = STRING;
                }
        }
}

void decode_msg(char *str)
{
        token_number = find_tokens_in_string(str);
        replace_char_in_string(str, ' ', NULL);
        decode_tokens();
}
