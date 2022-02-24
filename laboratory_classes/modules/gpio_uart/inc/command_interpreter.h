#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 4

enum keyword_code {ID, CALIB,GOTO,STEP};
enum token_type {KEYWORD, NUMBER, STRING};
enum comp_result {DIFFERENT, EQUAL};
enum work_type{TOKEN, DELIMITER};
enum result {rOK,rERROR};

struct keyword{
    enum keyword_code eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
};

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