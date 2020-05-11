#include<LPC21xx.H>

void Delay(){
int iLicznikPetli;
float fTime;
fTime=fTime*1277.245693655213;
for(iLicznikPetli=0;iLicznikPetli<fTime;iLicznikPetli++){};
}

int main(){
	IO1DIR=0x00010000;
	
	while(1){
		IO1SET=0x00010000;
		Delay();
		IO1CLR=0x00010000;
	}
}
