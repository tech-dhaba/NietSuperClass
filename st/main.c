
// Base addresses for UART4 and GPIOA
#define UART4_BASE 0x40004C00
#define GPIOA_BASE 0x40020000
#define GPIOG_BASE 0x40021800
#define RCC_BASE   0x40023800

// UART4 Register Offsets
#define USART_SR   *((volatile unsigned int *)(UART4_BASE + 0x00)) // Status Register
#define USART_DR   *((volatile unsigned int *)(UART4_BASE + 0x04)) // Data Register
#define USART_BRR  *((volatile unsigned int *)(UART4_BASE + 0x08)) // Baud Rate Register
#define USART_CR1  *((volatile unsigned int *)(UART4_BASE + 0x0C)) // Control Register 1

// GPIOA Register Offsets
#define GPIOA_MODER  *((volatile unsigned int *)(GPIOA_BASE + 0x00)) // Mode Register
#define GPIOG_MODER  *((volatile unsigned int *)(GPIOG_BASE + 0x00)) // Mode Register
#define GPIOG_ODR  *((volatile unsigned int *)(GPIOG_BASE + 0x14)) // Mode Register
#define GPIOA_AFRL   *((volatile unsigned int *)(GPIOA_BASE + 0x20)) // Alternate Function Low Register

// RCC Register Offsets
#define RCC_AHB1ENR *((volatile unsigned int *)(RCC_BASE + 0x30)) // AHB1 Peripheral Clock Enable Register
#define RCC_APB1ENR *((volatile unsigned int *)(RCC_BASE + 0x40)) // APB1 Peripheral Clock Enable Register

// Function to configure GPIO for UART4
void GPIO_Config(void) {
    // Enable GPIOA clock
    RCC_AHB1ENR |= (1 << 0)|(1<<6); // Enable clock for GPIOA

    // Set PA0 and PA1 to alternate function mode
    GPIOA_MODER &= ~(0x3 << (0 * 2));      // Clear mode bits for PA0
    GPIOA_MODER |= (0x2 << (0 * 2));       // Set PA0 to alternate function (01)

    GPIOA_MODER &= ~(0x3 << (1 * 2));      // Clear mode bits for PA1
    GPIOA_MODER |= (0x2 << (1 * 2));       // Set PA1 to alternate function (01)
    GPIOG_MODER |= (0x1 << (13 * 2));       // Set PA1 to alternate function (01)
    GPIOG_MODER |= (0x1 << (14 * 2));       // Set PA1 to alternate function (01)

    // Set the alternate function for PA0 and PA1 (AF8 for UART4)
    GPIOA_AFRL &= ~(0xF << (0 * 4));        // Clear AF bits for PA0
    GPIOA_AFRL |= (0x8 << (0 * 4));         // Set AF8 (0b1000) for PA0

    GPIOA_AFRL &= ~(0xF << (1 * 4));        // Clear AF bits for PA1
    GPIOA_AFRL |= (0x8 << (1 * 4));         // Set AF8 (0b1000) for PA1
}

// Function to configure UART4
void UART4_Config(void) {
    // Enable UART4 clock
    RCC_APB1ENR |= (1 << 19); // Enable clock for UART4

    // Set the baud rate to 9600 (APB1 is 8 MHz)
    USART_BRR = (104 << 4)|3; // Set BRR (Mantissa: 833, Fraction: 5)

    // Configure the UART: 8 data bits, no parity, 1 stop bit
    USART_CR1 |= (1 << 3) | (1 << 2); // Enable transmitter (TE) and receiver (RE)
    USART_CR1 |= (1 << 13); // Enable UART4 (UE)
}

// Function to send a character via UART4
void UART4_SendChar(char c) {
    while (!(USART_SR & (1 << 7))); // Wait until TXE (Transmit Data Register Empty) is set
    USART_DR = c; // Send character
}

char UART4_ReceiveChar(void){
	while (!(USART_SR & (1 << 5)));
	char c= USART_DR;
	return c;
}

// Function to send a string via UART4
void UART4_SendString(const char *str) {
    while (*str) {
        UART4_SendChar(*str++);
    }
}

void delay(void){
	for(volatile int i=0;i<200000;i++){
		continue;
	}
}

int main(void) {
    GPIO_Config();        // Configure GPIO for UART4
    while (1) {
        // Main loop
        GPIOG_ODR^=(1<<13);
        GPIOG_ODR^=(1<<14);
        delay();
    }
}

