#include<LPC21xx.H>

void Delay(){
int i;
for(i=0;i<1000;i++){};
}

int main(){
	IO1DIR=0x00010000;
	
	while(1){
		IO1SET=0x00010000;
		Delay();
		IO1CLR=0x00010000;
	}
}
