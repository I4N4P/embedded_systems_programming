#include <LPC21xx.H>
#include "timer.h"

#define mCOUNTER_ENABLE 	(1<<0)
#define mCOUNTER_RESET  	(1<<1)
#define mPRESCALE_SET			0x3AE8
#define mMR0_INTERRUPT_ENABLE  	(1<<0)
#define mMR0_CLEAN_INTERRUPT  	(1<<0)

#define NULL 0
 

void InitTimer0(void){
	T0TCR=mCOUNTER_ENABLE;
	T0PR=mPRESCALE_SET ;
}


void WaitOnTimer0(unsigned int uiTime){
	
	int Licznik=0;
	
	T0TCR=mCOUNTER_RESET;
	T0TC=NULL;
	T0TCR=mCOUNTER_ENABLE;
	
	while(T0TC<uiTime){
		Licznik++;
	}

}


void InitTimer0Match0(unsigned int uiDelayTime){

	T0MR0=uiDelayTime;
	T0MCR=mMR0_INTERRUPT_ENABLE;
	T0PR=mPRESCALE_SET ;
	
	T0TCR=mCOUNTER_RESET;
	T0TC=NULL;
	T0TCR=mCOUNTER_ENABLE;

}



void WaitOnTimer0Match0(void){
	int Licznik=0;
	InitTimer0Match0(1000);
	
	while(!(T0IR==mMR0_INTERRUPT_ENABLE)){
	Licznik++;
	}
	T0IR=mMR0_CLEAN_INTERRUPT; // jesli sa inne przerwania czekajace mozemy je wyzerowac jesli uzyjemy sumy logicznej
}
	
