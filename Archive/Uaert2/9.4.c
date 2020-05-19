#include "keyboard.h"
#include "servo.h"

int main (){
	
	KeyboardInit();
	ServoInit(6);

	while(1){
		
		switch(eKeyboardRead()){
			case BUTTON_0:
				ServoGoTo(12);
			  break;
			case BUTTON_1:
				ServoGoTo(24);
				break;
			case BUTTON_2:
				ServoGoTo(36);
				break;
			case RELASED:
				break;
			default:
				break;
		}
	}
}



