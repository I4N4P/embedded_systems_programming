#include<LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19
#define BUT0_bm 1<<4
#define BUT1_bm 1<<6
#define BUT2_bm 1<<5
#define BUT3_bm 1<<7

unsigned int uiNrDiody=0;

enum KeyBoardState {RELASED, BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3};

void LedInit(void){
	IO1DIR=IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm;//Ustawienie wyjsc w rejestrze wpisanie 1 na odpowiednich pozycjach
	IO1CLR=LED1_bm|LED2_bm|LED3_bm;
	IO1SET=LED0_bm;	 
}

void KeyboardInit(void){
	IO0DIR=IO0DIR&(~(BUT0_bm|BUT1_bm|BUT2_bm|BUT3_bm));//Ustawienie wejsc w rejestrze wpisanie 0 na odpowiednich pozycjach
}

enum KeyBoardState eKeyBoardRead(){
	if((IO0PIN&BUT1_bm)==0){
		return BUTTON_0;
	}
	else if((IO0PIN&BUT1_bm)==0){//Przycisk Nie Wcisniety 0x7BFFFFBF&0x00000040=0x00000040 Przycisk Wcisniety 0x00000000
		return BUTTON_1;
	}
	else if((IO0PIN&BUT2_bm)==0){//  Przycisk Nie Wcisniety 0x7BFFFFDF&0x00000020=0x00000020 Przycisk Wcisniety 0x00000000
		return BUTTON_2;
	}
	else if((IO0PIN&BUT3_bm)==0){
		return BUTTON_3;
	}
	else{
		return RELASED;
	}
}

void LedOn(unsigned char ucLedindeks){
	IO1CLR=LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	switch(ucLedindeks){
		case 0:
			IO1SET=LED0_bm;
			break;
		case 1:
			IO1SET=LED1_bm;
			break;
		case 2:
			IO1SET=LED2_bm;
			break;
		case 3:
			IO1SET=LED3_bm;
			break;
		default:
			break;
	}
}

void StepLeft(){
	uiNrDiody++;
	LedOn(uiNrDiody%4);
}
void Delay(float fTime){
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}

int main(){
	KeyboardInit();
	LedInit();
	while(1){
		Delay(100);
		StepLeft();
	}
}
