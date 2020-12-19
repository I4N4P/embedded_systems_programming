#include <LPC210X.H>
#include "uart.h"
/************ UART ************/
// PIN Function Select Register 0
#define mP0_1_RxD 																	0x00000004

// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   	0x00000080
#define m8BIT_UART_WORD_LENGTH                     	0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE       	0x00000001
#define mTHRE_INTERRUPT_ENABLE                     	0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  	0x0000000F
#define mTHRE_INTERRUPT_PENDING                    	0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       	0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           	0x00000020

////////////// Zmienne globalne ////////////
char cOdebranyZnak;
 struct TransmiterBuffer sTransmiterBuffer;
unsigned char ucCharCtr=0;
unsigned char ucCharCtr1=0;
extern unsigned char ucDane;



///////////////////////////////////////////
__irq void UART0_Interrupt (void) {
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
      cOdebranyZnak = U0RBR;
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
      // narazie nic nie wysylamy
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | mP0_1_RxD;                                	// ustawic pina na odbiornik uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; 	// dlugosc slowa, DLAB = 1
   U0DLL   = (((15000000)/16)/uiBaudRate);                      	// predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       	// DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               	// Wlaczenie przerwan po odebraniu danych z odbiornika RX (RX_DATA - receive data)

   // INT
   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}

char Transmiter_GetCharacterFromBuffer(){
	sTransmiterBuffer.ucCharCtr++;
	if(sTransmiterBuffer.fLastCharacter==1){
		sTransmiterBuffer.eStatus=FREE;
		sTransmiterBuffer.fLastCharacter=0;
		sTransmiterBuffer.ucCharCtr=0;
		return NULL;
	}
	else if(sTransmiterBuffer.cData[ucCharCtr]==NULL){
		sTransmiterBuffer.fLastCharacter=1;
		return TERMINATOR1;
	}
	
	return sTransmiterBuffer.cData[ucCharCtr];
}

void Transmiter_SendString(char cString[]){
	unsigned char ucArrayIndex;
	sTransmiterBuffer.eStatus=BUSY;
	for(ucArrayIndex=0;cString[ucArrayIndex]!=NULL;ucArrayIndex++){
		sTransmiterBuffer.cData[ucArrayIndex]=cString[ucArrayIndex];
	}
	sTransmiterBuffer.cData[ucArrayIndex]=NULL;
	U0THR=sTransmiterBuffer.cData[0];
	
	ucCharCtr=0;
	ucCharCtr1=1;
}

enum eTransmiterStatus eTransmiter_Status(void){
	if(sTransmiterBuffer.eStatus==BUSY)
		return BUSY;
	return FREE;
}
