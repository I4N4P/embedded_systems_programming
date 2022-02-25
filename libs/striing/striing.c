#include "main.h"
#include "string.h"

#define NULL 0

enum comp_result {DIFFERENT, EQUAL};
enum result {rOK,rERROR};

enum comp_result compare_string(char *str1, char *str2)
{
        for (str1; (*str1 == *str2); str1++) {
                if ((*str1 == NULL) && (*str2 == NULL))
                        return EQUAL;
                str2++;
        }
        return DIFFERENT;
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

void replace_char_in_string(char *str,char old_char,char new_char)
{
        for (str; *str != NULL;str++) {
                if(*str == old_char)
                        *str = new_char;
        }
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
