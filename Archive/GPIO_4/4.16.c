#include<LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19
#define BUT0_bm 1<<4
#define BUT1_bm 1<<6
#define BUT2_bm 1<<5
#define BUT3_bm 1<<7

int iCzasSwiecenia=250;

void LedInit(){
	IO1DIR=(IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1CLR=(LED1_bm|LED2_bm|LED3_bm);
	IO1SET=LED0_bm;	 
}

char cReadButton1(){
	if(!(IO0PIN&BUT0_bm)){
		return 1;
	}
	else{
		return 0;
	}
}

void LedOn(unsigned char ucLedindeks){
	IO1CLR=(IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm);
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
			IO1CLR=(IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm);
			break;
	}
}

void Delay(float fTime){
	int iLicznikPetli;
	fTime=fTime*1277.245693655213;
	for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}

int main(){
	while(1){
		LedOn(cReadButton1());
	}
}
