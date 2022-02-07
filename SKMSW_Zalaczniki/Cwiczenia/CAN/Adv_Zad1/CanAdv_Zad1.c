// Doprowadzic do dzialania ponizszy program
// Uzyc Acceptance Filter
// Nie uzywac przerwan

#include "led.h"
#include "keyboard.h"
#include "can.h"

#define ID 17

int main(){
	unsigned char ucMsgCtr=0;
	Led_Init();
	Can1_InitAsTx();
	Can2_InitAsRx(ID);
  while(1){ 
		unsigned int 	uiID;
		if (eKeyboard_Read()==BUTTON_1) uiID=ID; else uiID=0;
		
		if (ucCan1_TxFree())  Can1_SendByte(uiID,ucMsgCtr++);
		if (ucCan2_RxReady()) Led_ShowByte(ucCan2_ReceiveByte());
	}
}
