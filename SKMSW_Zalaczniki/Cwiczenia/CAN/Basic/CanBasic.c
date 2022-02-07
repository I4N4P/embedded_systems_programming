// Doprowadzić do działania poniższy program implementując zawarte w nim funkcje.

// W funkcjach do inicjalizacji CAN: 
// - wykorzystać rejestry PINSEL, MOD, BTR, TFI1, AFMR, CMR.
// - użyć bittimingu z przykładu hitexa
// - wyłączyć filtrowanie komunikatów („Acceptance filter” powinien "przepuszczać" wszystkie komunkiat)
// - ustawić odpowiednio funkcje pinów
//
// W pozostałych funkcjach do CAN: 
// - wykorzystać rejestry SR, TID1, TDA1, CMR, RDA.

// UWAGI: 
// - nie modyfikować zawartości tego pliku
// - nie dawać komentarzy w kodzie 
// - nie używać przerwań
// - mieć na uwadze fakt, że nadajnik CAN sygnalizuje wysłanie komunikatu tylko wtedy kiedy któryś z odbiorników potwierdził odbiór
 
// Test1: Test przeprowadzić używając jednego EVM-a.
//
// Test2: Test przeprowadzić używając dwóch EVM-ów.
//        - które CAN-y ? 
//        - co i gdzie powinno sie wyswietlać ?
//        - co sie dzieje kiedy zatrzymamy nadajnik resetem ?
//
// Test3: Test przeprowadzić używając trzech EVM-ów.

#include "can.h"
main (){
	unsigned char ucMsgCtr=0;
	Led_Init();
    Can1_InitAsTX();
    Can2_InitAsRX();
    while(1){
        if (ucCan1_TxFree())  Can1_SendByte(ucMsgCtr++);
        if (ucCan2_RxReady()) Led_ShowByte(ucCan2_ReceiveByte());
    }
}