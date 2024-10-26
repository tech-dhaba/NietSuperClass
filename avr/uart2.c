#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

volatile char received_char;         // Stores the received character
  // Flag to indicate if we're in configuration mode
volatile uint16_t baud_rate = 9600;  // Variable to store the new baud rate
volatile char tx_char = 'A';         // Character to transmit
volatile uint8_t tx_count = 1;       // Number of times to transmit the character
int BAUDS[]={9600,4800,19200};
char *BAUDSS[]={"9600","4800","19200"};

// Function to initialize UART
void abc(void);
void UART_init(unsigned int ubrr) {
    // Disable receiver and transmitter before reconfiguring
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));

    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Set frame format: 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Enable receiver interrupt
    UCSR0B |= (1 << RXCIE0);

    // Clear the receive buffer by reading UDR0 if any data is pending
    unsigned char dummy;
    while (UCSR0A & (1 << RXC0)) {
        dummy = UDR0;  // Discard any incoming data
    }
    // Enable global interrupts
    sei();
}

// Function to send a character over UART
void UART_transmit(char data) {
    // Wait for the transmit buffer to be empty
    while (!(UCSR0A & (1 << UDRE0)));
    // Send the data
    UDR0 = data;
}

// UART Receive Function
unsigned char UART_receive(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));

    // Get and return received data from buffer
    return UDR0;
}

// Function to send a string over UART
void UART_sendString(const char* str) {
    while (*str) {
        UART_transmit(*str++);
    }
}

// Interrupt Service Routine (ISR) for UART receive
ISR(USART_RX_vect) {
    // received_char = UART_receive();  // Read the received character
    // UART_transmit(UDR0);
}

int main(void) {
DDRB|=(1<<PB5);
UART_init(MYUBRR);  // Initialize UART with the default baud rate
while (1) {
        switch (UART_receive()) {
        case 'A':
            UART_sendString("Command A received. Performing Action A...\n");
            PORTB ^= (1 << PB5);  // Toggle an LED on pin PB0
            break;
        case 'B':
            UART_sendString("Command B received. Performing Action B...\n");
            OCR1A = 128;  // Set PWM duty cycle to 50% on pin PB1
            break;
        case 'C':
            UART_sendString("Command C received. Entering Config Mode...\n");
            abc();
            break;
        default:
            UART_sendString("Unknown command received.\n");
            break;
    } 
        }
}

void abc(void){
UART_sendString("select Baud rate 0=9600 1=4800, 2=19200\n");
uint8_t z=UART_receive()-'0';
baud_rate = BAUDS[z];
UART_sendString("Baud rate received.\n");
UART_sendString(BAUDSS[z]);
UART_transmit('\n');
// UART_transmit(z+'0');
// // Expect the second byte as the character to transmit
UART_sendString("Enter Character to transmit.\n");
tx_char = UART_receive();
UART_sendString("Character to transmit received.\n");
UART_transmit(tx_char);
UART_transmit('\n');
// Expect the third byte as the number of times to transmit
UART_sendString("Enter Transmission count.\n");
tx_count = UART_receive()-'0';
UART_sendString("Transmission count received.\n");
UART_transmit(tx_count+'0');
UART_transmit('\n');
// Finalize the configuration
UART_sendString("Finalizing configuration...\n");
// Reinitialize UART with the new baud rate
UART_init(F_CPU/16/baud_rate-1);
// _delay_ms(1000);
UART_receive();
// Perform the transmission based on the received config
while(tx_count--) {
    UART_transmit(tx_char);
    _delay_ms(500);
}
}
