
# define TRANSMITER_SIZE 20
#define NULL '\0'
#define TERMINATOR1 'r'

void UART_InitWithInt(unsigned int uiBaudRate);

void Transmiter_SendString(char cString[]);
char Transmiter_GetCharacterFromBuffer(void);
//unsigned char tablica[10];
enum eTransmiterStatus eTransmiter_Status(void);
enum eTransmiterStatus {FREE, BUSY};

struct TransmiterBuffer{
char cData[TRANSMITER_SIZE];
enum eTransmiterStatus eStatus;
unsigned char fLastCharacter;
unsigned char ucCharCtr;
};

