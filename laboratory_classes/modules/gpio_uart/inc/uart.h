
enum received_status {
	EMPTY,
	READY,
	OVERFLOW,
};

enum transmiter_status {
	FREE,
	BUSY,
};

void uart_init_with_irq (void);
void receiver_get_string_copy(char * destination);
enum received_status receiver_get_status(void);
void transmiter_send_string(unsigned char string[]);
enum transmiter_status transmiter_get_status(void);