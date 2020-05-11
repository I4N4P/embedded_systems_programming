#include<LPC21xx.H>

enum KeyBoardState {RELASED, BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3};

void KeyboardInit(void);
enum KeyBoardState eKeyBoardRead(void);
