#include <avr/io.h>
#include <util/delay.h>

// Function prototypes
void uart0_init(unsigned int ubrr);
void uart0_transmit(unsigned char data);
void uart1_init(unsigned int ubrr);
void uart1_transmit(unsigned char data);
void uart2_init(unsigned int ubrr);
void uart2_transmit(unsigned char data);
void uart3_init(unsigned int ubrr);
void uart3_transmit(unsigned char data);

// UART baud rate
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

int main(void) {
    // Initialize UART0, UART1, UART2, UART3 with baud rate 9600
    uart0_init(MYUBRR);
    uart1_init(MYUBRR);
    uart2_init(MYUBRR);
    uart3_init(MYUBRR);
    
    // Set pin 13 as input
    DDRB &= ~(1 << DDB7);  // Digital pin 13 is PB7 on ATmega2560

    while (1) {
        int state = PINB & (1 << PINB7);

        if (state) {
            // Send character 'A' via all UARTs
            uart0_transmit('A');
            uart1_transmit('A');
            uart2_transmit('A');
            uart3_transmit('A');
        }
        
        _delay_ms(100);  // Add a small delay to debounce the button
    }
}

void uart0_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0);  // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame: 8 data bits, 1 stop bit
}

void uart0_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));  // Wait for empty transmit buffer
    UDR0 = data;  // Put data into buffer, sends the data
}

void uart1_init(unsigned int ubrr) {
    UBRR1H = (unsigned char)(ubrr >> 8);
    UBRR1L = (unsigned char)ubrr;
    UCSR1B = (1 << TXEN1);  // Enable transmitter
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);  // Set frame: 8 data bits, 1 stop bit
}

void uart1_transmit(unsigned char data) {
    while (!(UCSR1A & (1 << UDRE1)));  // Wait for empty transmit buffer
    UDR1 = data;  // Put data into buffer, sends the data
}

void uart2_init(unsigned int ubrr) {
    UBRR2H = (unsigned char)(ubrr >> 8);
    UBRR2L = (unsigned char)ubrr;
    UCSR2B = (1 << TXEN2);  // Enable transmitter
    UCSR2C = (1 << UCSZ21) | (1 << UCSZ20);  // Set frame: 8 data bits, 1 stop bit
}

void uart2_transmit(unsigned char data) {
    while (!(UCSR2A & (1 << UDRE2)));  // Wait for empty transmit buffer
    UDR2 = data;  // Put data into buffer, sends the data
}

void uart3_init(unsigned int ubrr) {
    UBRR3H = (unsigned char)(ubrr >> 8);
    UBRR3L = (unsigned char)ubrr;
    UCSR3B = (1 << TXEN3);  // Enable transmitter
    UCSR3C = (1 << UCSZ31) | (1 << UCSZ30);  // Set frame: 8 data bits, 1 stop bit
}

void uart3_transmit(unsigned char data) {
    while (!(UCSR3A & (1 << UDRE3)));  // Wait for empty transmit buffer
    UDR3 = data;  // Put data into buffer, sends the data
}

