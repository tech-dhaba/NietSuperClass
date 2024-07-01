#include <avr/io.h>
#include <util/delay.h>

// Function to initialize the ADC
void ADC_init() {
    // Select Vref=AVcc with external capacitor at AREF pin
    ADMUX = (1 << REFS0);

    // Set ADC prescaler to 128 for 16 MHz clock (16MHz/128 = 125kHz ADC clock)
    // The ADC clock should be between 50kHz and 200kHz for best results
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Enable the ADC
    ADCSRA |= (1 << ADEN);
}

// Function to read ADC value from a specific channel
uint16_t ADC_read(uint8_t channel) {
    // Select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to finish
    while (ADCSRA & (1 << ADSC));

    // Return the ADC result
    return ADC;
}

// Function to initialize PORTB5 as an output
void PORTB5_init() {
    // Set PORTB5 as output
    DDRB |= (1 << DDB5);
}

// Function to control the LED on PORTB5 based on the ADC value
void control_LED(uint16_t adc_value) {
    // Define a threshold for turning the LED on/off
    uint16_t threshold = 512; // Midpoint of 10-bit ADC (0-1023)

    if (adc_value > threshold) {
        // Turn the LED on
        PORTB |= (1 << PORTB5);
    } else {
        // Turn the LED off
        PORTB &= ~(1 << PORTB5);
    }
}

int main() {
    // Initialize the ADC and PORTB5
    ADC_init();
    PORTB5_init();

    // Variable to store ADC value
    uint16_t adc_value;

    // Infinite loop
    while (1) {
        // Read ADC value from channel 0 (PC0)
        adc_value = ADC_read(0);

        // Control the LED based on the ADC value
        control_LED(adc_value);

        // Add a small delay
        _delay_ms(100);
    }

    return 0;
}

