#include "Led.h"
#include "keyboard.h"
#include "timer.h" 
 
void Delay(float fTime){
	
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}


int main(){
	LedInit();
	InitTimer0();
	while(1){
		LedStepLeft();
		WaitOnTimer0(250);
	}
}
