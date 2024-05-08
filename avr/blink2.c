#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define DELAY_MS 500
#define COUNT 1024

ISR(TIMER1_COMPA_vect){
    PORTB^=0b00100000;//toggle pin 13
}

int main(void){
    DDRB=DDRB|(1<<DDB5);//set pin 13 as output
    OCR1A=COUNT;//output compare register value

    TCCR1A=0x00;
    TCCR1B|=(1<<WGM12)|(1<<CS10)|(1<<CS12);//clear timer on compare match, prescaler 1024
    TIMSK1|=(1<<OCIE1A);//timer1 output compare A match interrupt enable

    sei();//enable global interrupt

    while (1)
    {
        _delay_ms(DELAY_MS);
    }
    
}