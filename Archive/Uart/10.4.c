#include "uart.h"
#include "keyboard.h"
#include "servo.h"

#define NULL '\0'

int main ()
{	
	//extern char cOdebranyZnak;
//	unsigned int uiCurrentServoPosition = 1;
	//UART_InitWithInt(9600);
	ServoInit(5);
	KeyboardInit();
	
	while(1)
	{

		switch(eKeyBoardRead())
		{
			case BUTTON_0:
				ServoCallib();
				break;	
			
			case BUTTON_1:
				ServoGoTo(4);
				break;
			
			case BUTTON_2:
				ServoGoTo(8);
				break;
			
			default:
				break;
		}
	}
}

