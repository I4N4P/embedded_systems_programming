
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
  
