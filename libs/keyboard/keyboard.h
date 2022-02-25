
enum keyboard_state {RELASED, BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3};

void keyboard_init(void);
enum keyboard_state keyboard_read(void);
