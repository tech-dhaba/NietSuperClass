#include <avr/io.h>
#include<util/delay.h>

#define LED_PIN 5   // Digital Pin 13 on Arduino Uno corresponds to PB5
int main(void) {
    DDRB |= (1 << LED_PIN);
    PORTB |= (1 << LED_PIN);
}

