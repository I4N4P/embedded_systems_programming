#include<LPC21xx.H>

int main(){
	IO1DIR=0x00010000;
	IO1SET=0x00010000;
	IO1CLR=0x00010000;
	
	while(1){}
}