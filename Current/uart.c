#include <LPC21XX.H>
#include "uart.h"


/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000000
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE    0x00000020
#define PINEL0ODBIORNAD     0x00000005
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
			if(ucCharCtr1==1){
		 U0THR=Transmiter_GetCharacterFromBuffer();
			
			}
		//	U0THR=ucDane;
		//	ucDane=ucDane+1;
		}

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | PINEL0ODBIORNAD;                                     // ustawic pina na odbiornik uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1
   U0DLL   = ((15000000)/16)/uiBaudRate;                      // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mTHRE_INTERRUPT_ENABLE|mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               // U0IER2 enables the UART0 Rx line status interrupts. The status of this interrupt can be read from U0LSR[4:1].

   // INT
   VICVectAddr2  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl2  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}




char Transmiter_GetCharacterFromBuffer(){
	ucCharCtr++;
	if(sTransmiterBuffer.fLastCharacter==1){
		sTransmiterBuffer.eStatus=FREE;
		sTransmiterBuffer.fLastCharacter=0;
		ucCharCtr1=0;
		return NULL;
	}
	else if(sTransmiterBuffer.cData[ucCharCtr]==NULL){
		sTransmiterBuffer.fLastCharacter=1;
		return TERMINATOR1;
	}
	
	return sTransmiterBuffer.cData[ucCharCtr];
}

void Transmiter_SendString(unsigned char cString[]){
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
