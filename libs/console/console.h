#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 6

enum token_type {KEYWORD, NUMBER, STRING};
enum keyword_code {ID, CALIB,GOTO,STEP,CALC,TIME};

union token_value{
        enum keyword_code eKeyword;
        unsigned int uiNumber;
        char* pcString;
};
struct token{
        enum  token_type  eType;
        union token_value uValue;
};

void decode_msg(char *);