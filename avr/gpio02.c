#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>

int main(void)
{
    DDRB=DDRB|(1<<DDB5);
     DDRB=DDRB&~(1<<DDB6);//gpio 13 as input
    while(1)
    {
    volatile uint8_t a=(PINB & (1<<PINB6)) ? 1 : 0;
        if(a){
                    PORTB = PORTB | (1<<PORTB5);
        }
        else{
                    PORTB = PORTB & ~(1<<PORTB5);
        }
    }
}