#include "servo.h"
#include "Led.h"
#include "Keyboard.h"


int main (){
	
	
	ServoInit(5);
	ServoCallib();
	

	while(1){
	 	ServoGoTo(12);
	}
}
