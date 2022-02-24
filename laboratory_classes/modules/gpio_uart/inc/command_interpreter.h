#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 4

enum KeywordCode {ID, CALIB,GOTO,STEP};
enum TokenType {KEYWORD, NUMBER, STRING};
enum CompResult {DIFFERENT, EQUAL};
enum WorkType{TOKEN, DELIMITER};
enum Result {rOK,rERROR};

struct Keyword{
    enum KeywordCode eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
};

union TokenValue{
    enum KeywordCode eKeyword;
    unsigned int uiNumber;
    char* pcString;
};

struct Token{
    enum  TokenType  eType;
    union TokenValue uValue;
};


void DecodeMsg(char *);
unsigned char ucFindTokensInString(char *);
void ReplaceCharactersInString(char [],char ,char);
void DecodeTokens(void);
enum Result eHexStringToUInt(char [],unsigned int *);
enum Result eStringToKeyword (char [],enum KeywordCode *);
enum CompResult eCompareString(char [],char []);