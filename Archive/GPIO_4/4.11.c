#include<LPC21xx.H>

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

void Delay(int iTime){
int iLicznikPetli;
iTime=iTime*1277.245693655213;
for(iLicznikPetli=0;iLicznikPetli<iTime;iLicznikPetli++){};
}

int main(){
	IO1DIR=(LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1SET=LED0_bm;
	IO1SET=LED1_bm;
	IO1SET=LED2_bm;
	IO1SET=LED3_bm;	
}
