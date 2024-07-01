#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void uart_init(unsigned int ubrr);
void uart_transmit(unsigned char data);

unsigned char uart_receive(void);

int main(void) {

    uart_init(MYUBRR);
    DDRB |= (1 << PB5);
    PORTB &=~(1 << PB5);

    while (1) {
        if (uart_receive() == 'A') {
            PORTB |= (1 << PB5);
            _delay_ms(1000);  
            PORTB &= ~(1 << PB5);  
        }
    }
}

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0))); 
    UDR0 = data; 
}

unsigned char uart_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));  
    return UDR0;  
}

