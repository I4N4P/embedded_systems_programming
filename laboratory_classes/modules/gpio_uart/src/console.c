#include "main.h"
#include "console.h"

enum comp_result {DIFFERENT, EQUAL};
enum work_type {TOKEN, DELIMITER};
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

enum comp_result compare_string(char *str1, char *str2)
{
        for (str1; (*str1 == *str2); str1++) {
                if ((*str1 == NULL) && (*str2 == NULL))
                        return EQUAL;
                str2++;
        }
        return DIFFERENT;
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

enum result hex_string_to_int(char str[],unsigned int *val)
{
        unsigned char char_ctr;
        unsigned char curr_char;

        *val = 0;

        if ((str[0] != '0') || (str[1] != 'x') || (str[2] == NULL))
                return rERROR;

        for (char_ctr = 2; char_ctr < 7; char_ctr++) {
                curr_char = str[char_ctr];
                if (curr_char == NULL)
                        return rOK;
                else if (char_ctr == 6)
                        return rERROR;

                *val = *val << 4;

                if (curr_char <= '9' && curr_char >= '0')
                        curr_char = curr_char - '0';
                else if (curr_char <= 'F' && curr_char >= 'A')
                        curr_char = curr_char - 'A' + 10;
                else
                        return rERROR;

                *val = *val | curr_char;
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

void replace_char_in_string(char *str,char old_char,char new_char)
{
        for (str; *str != NULL;str++) {
                if(*str == old_char)
                        *str = new_char;
        }
}

void decode_msg(char *str)
{
        token_number = find_tokens_in_string(str);
        replace_char_in_string(str, ' ', NULL);
        decode_tokens();
}

void int_to_hex_str(unsigned int val, char * str)
{

        unsigned char nibble_ctr;
        unsigned char nibble;

        str[0] = '0';
        str[1] = 'x';
        str[6] = NULL;

        for (nibble_ctr = 0; nibble_ctr < 4; nibble_ctr++) {
                nibble = (val >> (nibble_ctr * 4)) & 0x0F;
                if (nibble < 10) {
                        str[5 - nibble_ctr] = '0' + nibble;
                } else {
                        str[5 - nibble_ctr] = 'A' + (nibble - 10);
                }
        }
}

void append_int_to_string(unsigned int val, char * dest_str)
{

        for (dest_str; *dest_str != NULL; dest_str++);
        int_to_hex_str(val, dest_str);

}

void copy_string(char *src_str, char *dest_str)
{
	for (src_str; *src_str != NULL; src_str++) {
		*dest_str = *src_str;
                dest_str++;
	}
	*dest_str = NULL;
}

void append_string(char *src_str,char *dest_str)
{
        for (dest_str; *dest_str != NULL; dest_str++);
	copy_string(src_str, dest_str);
}
