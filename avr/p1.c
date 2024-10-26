#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define UBRR(baud) F_CPU/16/baud-1

uint8_t count=0;

void uart_init(unsigned int ubrr) {
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(char data) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

unsigned char uart_receive(void) {
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

void uart_sendString(const char* str) {
  while (*str) {
    uart_transmit(*str++);
  }
}

void adc_init(uint8_t channel){
  ADMUX   = (1 << REFS0) | (channel & 0x07); 
  ADCSRA  = (1 << ADEN) | (1 << ADIE) | (1 << ADPS1) | (1 << ADPS0); 
  ADCSRA  |= (1 << ADSC);
}

void wdt_init(void) {
    cli();
    WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1);
    sei();
}

void timer_init(void){
  TCCR1A=0x00;
  TCCR1B=(1<<WGM12)|(1<<CS11);
  OCR1A=19990;
  TIMSK1|=(1<<OCIE1A);
}


ISR(TIMER1_COMPA_vect) {
  if(count>=100){
    count=0;    
  }
  count++;
}

ISR(ADC_vect) {
  unsigned int adc_result = ADC;
  char result_str[10];
  snprintf(result_str, sizeof(result_str), "%u", adc_result);
  uart_sendString(result_str);
}

ISR(USART_RX_vect) {
  
}

int num=0;
ISR(WDT_vect) {
  if (num >= 3) {
      WDTCSR = (1 << WDCE) | (1 << WDE); 
      WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1);  
      while (1);  
  } else {
      asm("wdr");
      uart_transmit('0' + num);
      num++;
  }
}

int main(void){
  sei();
  DDRB|=(1<<PB5);
  PORTB|=(1<<PB5);
  _delay_ms(1000);
  PORTB&=~(1<<PB5);
  uart_init(UBRR(9600));
  adc_init(0);
  timer_init();
  count=0;
  for(int i=0;i<10;i++){
    PORTB^=(1<<PB5);
    uart_transmit('l');
    while(count<100){asm("nop");}
    count=0;
  }
  wdt_init();
  while(1);
}
