#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>

int main(void)
{
    DDRB=DDRB|(1<<DDB5);
    DDRD=DDRD&~(1<<DDD7);
    while(1)
    {
    volatile uint8_t a=(PIND & (1<<PD7)) ? 1 : 0;
    if(a){
                PORTB = PORTB | (1<<PORTB5);
                _delay_ms(500);
                PORTB = PORTB & ~(1<<PORTB5);
                _delay_ms(500);
    }
    else{
                PORTB = PORTB & ~(1<<PORTB5);
    }
    }
}
