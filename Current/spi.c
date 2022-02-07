/* Include header file depending upon part used */ 
#include<LPC21xx.H>
void Initialize(void); 
/* Macro Definitions */ 
#define SPIF (1<<7) 
#define DATA 0xC1 
/************************* MAIN *************************/ 
int main() 
 { 
 Initialize(); 
 
/* Do forever */ 
 while(1) 
 {
/* Write data out */ 
 SPDR=DATA; 
 
/* Wait for transfer to be completed */ 
 while(!(SPSR & SPIF)){} 
 
 }
 }
/*************** System Initialization ***************/ 
void Initialize() 
 { 
/* Configure Pin Connect Block */ 
 PINSEL0=0x5500; 
 
/* Set pclk to same as cclk */ 
 VPBDIV=0x1; 
 
/* Set to highest speed for SPI at 10 MHz- > 1.25 MHz */ 
 SPCCR=0x8; 
 
/* Device selected as master */ 
 SPCR=0x20; 
 } 
/*********************************************************/