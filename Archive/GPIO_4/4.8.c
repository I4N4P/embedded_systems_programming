#include<LPC21xx.H>

int iCzasSwiecenia=50;

void Delay(int iTime){
int iLicznikPetli;
iTime=iTime*1277.245693655213;
for(iLicznikPetli=0;iLicznikPetli<iTime;iLicznikPetli++){};
}

int main(){
	IO1DIR=0x00010000;
	
	while(1){
		IO1SET=0x00010000;
		Delay(iCzasSwiecenia);
		IO1CLR=0x00010000;
		Delay(iCzasSwiecenia);
	}
}
