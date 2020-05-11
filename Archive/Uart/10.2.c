#include "uart.h"
#include "Led.h"

extern char cOdebranyZnak;


int main(){
	UART_InitWithInt(9600);
	LedInit();
	
	while(1){
	
		LedOn((cOdebranyZnak-0x31));
		
	}

}

