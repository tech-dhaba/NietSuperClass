#include<avr/io.h>
#include<util/delay.h>

int main(void){
    DDRB = DDRB | (1 << PB4);
    DDRB = DDRB | (1 << PB5);
    while (1)
    {
        PORTB = PORTB | (1 << PORTB4);
        _delay_ms(500);
        PORTB = PORTB & ~(1 << PORTB5);
        _delay_ms(500);
        PORTB = PORTB & ~(1 << PORTB4);
        _delay_ms(500);
        PORTB = PORTB | (1 << PORTB5);
        _delay_ms(500);
    }
    
}