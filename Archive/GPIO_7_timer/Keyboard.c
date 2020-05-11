#include<LPC21xx.H>
#include"keyboard.h"

#define BUT0_bm (1<<4)
#define BUT1_bm (1<<6)
#define BUT2_bm (1<<5)
#define BUT3_bm (1<<7)


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

