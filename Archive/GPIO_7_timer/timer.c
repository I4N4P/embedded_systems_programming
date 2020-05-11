#include <LPC21xx.H>
#include "timer.h"

#define mCOUNTER_ENABLE 		1<<0
#define mCOUNTER_RESET  	0x00000002
#define TIM0CALIB_bm  0x3AE8
#define mMR0_INTERRUPT  1<<0

#define NULL 0
 

void InitTimer0(void){
	T0TCR=mCOUNTER_ENABLE;
	T0PR=TIM0CALIB_bm ;
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


void InitTimer0Match0(unsigned int iDelayTime){

	T0MR0=iDelayTime;
	T0MCR=mMR0_INTERRUPT;
	
	T0PR=TIM0CALIB_bm ;
	T0TCR=mCOUNTER_RESET;
	T0TC=NULL;
	T0TCR=mCOUNTER_ENABLE;

}



void WaitOnTimer0Match0(void){
	int Licznik=0;
	InitTimer0Match0(1000);
	
	while(!(T0IR==mMR0_INTERRUPT)){
	Licznik++;
}
	T0IR=mMR0_INTERRUPT;
	T0MCR=mMR0_INTERRUPT;
}
	
