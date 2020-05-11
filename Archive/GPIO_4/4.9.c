#include<LPC21xx.H>

#define LED0_bm 1<<16

int iCzasSwiecenia=50;

void Delay(int iTime){
int iLicznikPetli;
iTime=iTime*1277.245693655213;
for(iLicznikPetli=0;iLicznikPetli<iTime;iLicznikPetli++){};
}

int main(){
	IO1DIR=LED0_bm;
	
	while(1){
		IO1SET=LED0_bm;
		Delay(iCzasSwiecenia);
		IO1CLR=LED0_bm;
		Delay(iCzasSwiecenia);
	}
}
