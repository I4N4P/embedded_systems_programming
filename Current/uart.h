#include <LPC21xx.H>

# define TRANSMITER_SIZE 20
#define NULL 0
#define TERMINATOR1 'r'

void UART_InitWithInt(unsigned int uiBaudRate);

void Transmiter_SendString(unsigned char cString[]);
char Transmiter_GetCharacterFromBuffer(void);
//unsigned char tablica[10];

enum eTransmiterStatus {FREE, BUSY};
struct TransmiterBuffer{
char cData[TRANSMITER_SIZE];
enum eTransmiterStatus eStatus;
unsigned char fLastCharacter;
unsigned char cCharCtr;
};

