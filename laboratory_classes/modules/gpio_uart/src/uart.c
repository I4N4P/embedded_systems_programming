#include "main.h"
#include "led.h"
#include "uart.h"

#define GPIOAOSPEED (*((volatile unsigned long *) 0x40020008))
#define GPIOAAFRL (*((volatile unsigned long *) 0x40020020))
#define USART2SR (*((volatile unsigned long *) 0x40004400))
#define USART2CR (*((volatile unsigned long *) 0x4000440C))
#define USART2DR (*((volatile unsigned long *) 0x40004404))
#define USART2BRR (*((volatile unsigned long *) 0x40004408))

#define GPIOA_EN        (1 << 0)
#define DATA2READ	(1 << 5)
#define DATASEND	(1 << 6)
#define USART2_EN	(1 << 17)
#define RECEIVED_SIZE 15

char received_data;

struct received_buffer {
	char data[RECEIVED_SIZE];
	unsigned char data_ctr;
	enum received_status status;
};
struct received_buffer rx_data;

void receiver_char_to_buffer(char character)
{
	if (rx_data.data_ctr >= RECEIVED_SIZE) {
		rx_data.status = OVERFLOW;
	} else {
		if (character == '\r') {
			rx_data.data[rx_data.data_ctr] = NULL;
			rx_data.status = READY;
			rx_data.data_ctr = 0;
		} else {
			rx_data.data[rx_data.data_ctr] = character;
			rx_data.status = EMPTY;
			rx_data.data_ctr++;
		}
	}
}

enum received_status receiver_get_status(void){
	return rx_data.status;
}

void receiver_get_string_copy(char * destination){
	for(int i = 0; i < RECEIVED_SIZE; i++) {
		destination[i] = rx_data.data[i];
		if (rx_data.data[i] == NULL)
			break;
	}
	rx_data.status = EMPTY;
}

__attribute__((interrupt)) void USART2_IRQHandler(void)
{
	received_data = USART2DR;
	//USART2SR &= (0<<5);		// clr flag alternative
	receiver_char_to_buffer(received_data);
}

void send(char c)
{
	USART2DR = c;
	while (!(USART2SR & DATASEND));

}

char get(void)
{
	char temp;
	while (!(USART2SR & DATA2READ));
	temp = USART2DR;
	return temp;

}

void uart_init_with_irq (void)
{
	RCCAPB1ENR |= USART2_EN;		// Enable Uart's clock
	RCCAHB1    |= GPIOA_EN;		// Enable GPIO's clock

	GPIOAMODE   |= ((2 << 4) | (2 << 6));	// Change mode to alternate function for PIN A2 and A3
	GPIOAOSPEED |= ((3 << 4) | (3 << 6));// Set pins to work with maximum speed not required
	GPIOAAFRL   |= ((7 << 8) | (7 << 12));	// Selection of source for alternate function for pin A2 and A3 to Usart2

	USART2CR = 0x00000000;		// Clr Uart's control register
	USART2CR |= (1 << 13);		// Enables usart2
	//USART2CR &= ~(1<<12);		// Sets word's length to 8 bit not required
	USART2BRR = ((11 << 0) | (8 << 4));	// values from equation to set uart to work with 115200 baud rate for 16MHz clock in order to set for 45MHz magistral clock USART2BRR = ((7<<0) | (24<<4));

	USART2CR  |= (1 << 5);		// Enable irq for uart
	NVICISER1 |= (1 << 6);		// Enable irq globally

	USART2CR |= (1 << 2);		// Enable reciver
	USART2CR |= (1 << 3);		// Enable transmiter
}