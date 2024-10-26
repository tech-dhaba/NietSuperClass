#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BAUD          9600
#define MYUBRR        F_CPU/16/BAUD-1
#define MYUBRRB(baud) F_CPU/16/baud-1
#define FRAME_BEGIN   '$'
#define FRAME_END     '#'

typedef struct {
  unsigned char  protocol;
  unsigned char  protocol_class;
  unsigned char  action;
  unsigned char  speed;
  unsigned char  data[512];
  unsigned char  times_repeat;
} frame;

frame _frame;
char FRAME[sizeof(frame)];
int UARTARR[] = {4800, 9600, 19200};

void UART_init(unsigned int ubrr);
void UART_transmit(char data);
unsigned char UART_receive(void);
void UART_sendString(const char* str);
void config(void);
void parse_frame(void);
void failure(void);
void uart(frame _frame);
void adc(frame _frame);
void gpio(frame _frame);
void timer(frame _frame);
void clearStruct();

void (*fptrarr[])(frame) = {uart, adc, gpio, timer};

ISR(USART_RX_vect) {
  if (UDR0 == FRAME_BEGIN) {
    parse_frame();
    config();
  }
}

ISR(ADC_vect) {
  unsigned int adc_result = ADC;
  char result_str[10];
  snprintf(result_str, sizeof(result_str), "%u", adc_result);
  UART_sendString(result_str);
}

int main(void) {
  UART_init(MYUBRR);
  sei();
  while (1) {
    // Main loop does nothing, ADC and UART are handled by interrupts
  }
}

void UART_init(unsigned int ubrr) {
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_transmit(char data) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

unsigned char UART_receive(void) {
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

void UART_sendString(const char* str) {
  while (*str) {
    UART_transmit(*str++);
  }
}

void parse_frame(void) {
  int i = 0;
  FRAME[i++] = FRAME_BEGIN;
  while (i < sizeof(FRAME) - 1) {
    FRAME[i] = UART_receive();
    if (FRAME[i] == FRAME_END) {
      FRAME[i + 1] = '\0';
      break;
    }
    i++;
  }
}

void failure(void) {
  UART_sendString("Decoding Error");
}

void config(void) {
  uint8_t flag = 0;
  if (FRAME[1] && FRAME[1] != ',' && FRAME[1] != '#')
    _frame.protocol = FRAME[1];
  else
    flag = 1;
  if (FRAME[3] && FRAME[3] != ',' && FRAME[3] != '#')
    _frame.protocol_class = FRAME[3];
  else
    flag = 1;
  if (FRAME[5] && FRAME[5] != ',' && FRAME[5] != '#')
    _frame.action = FRAME[5];
  else
    flag = 1;
  if (FRAME[7] && FRAME[7] != ',' && FRAME[7] != '#')
    _frame.speed = FRAME[7];
  else
    flag = 1;
  int i = 9;
  while (FRAME[i] && FRAME[i] != ',' && FRAME[i] != '#') {
    _frame.data[i - 9] = FRAME[i];
    i++;
  }
  _frame.data[i - 9] = '\0';
  i++;
  if (FRAME[i] && FRAME[i] != ',' && FRAME[i] != '#')
    _frame.times_repeat = FRAME[i];
  else
    flag = 1;

  if (flag)
    failure();
  else {
    fptrarr[_frame.protocol - '0'](_frame); // Call appropriate function via function pointer array
  }
  
  for (int j = 0; j < sizeof(FRAME); j++)
    FRAME[j] = 0;
}

void clearStruct() {
  char *p = (char *)&_frame;
  size_t size = sizeof(_frame);
  for (size_t i = 0; i < size; i++) {
    p[i] = 0;
  }
}

void uart(frame _frame) {
  UART_init(MYUBRRB(UARTARR[_frame.speed - '0']));
  for (int i = 0; i < _frame.times_repeat - '0'; i++) {
    UART_sendString(_frame.data);
  }
  clearStruct();
  UART_transmit('\n');
  UART_sendString(_frame.data);
  _delay_ms(2);
  UART_init(MYUBRR);
}

void adc(frame _frame) {
  uint8_t channel = _frame.protocol_class - '0';
  if (channel > 7) {
    UART_sendString("Invalid ADC Channel");
    return;
  }
  ADMUX = (1 << REFS0) | (channel & 0x07); 
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS1) | (1 << ADPS0); 
  ADCSRA |= (1 << ADSC); 
}

void gpio(frame _frame) {
    volatile uint8_t *ddr = NULL;
    volatile uint8_t *port = NULL;
    volatile uint8_t *pin = NULL;

    switch (_frame.protocol_class+'A'-'0') {
        case 'B':
            ddr = &DDRB;
            port = &PORTB;
            pin = &PINB;
            break;
        case 'C':
            ddr = &DDRC;
            port = &PORTC;
            pin = &PINC;
            break;
        case 'D':
            ddr = &DDRD;
            port = &PORTD;
            pin = &PIND;
            break;
        default:
            UART_sendString("Invalid GPIO Port");
            return;
    }

    uint8_t pin_number = _frame.speed - '0';
    if (pin_number > 7) {
        UART_sendString("Invalid Pin Number");
        return;
    }

    if (_frame.action == '0') {
        *ddr &= ~(1 << pin_number);
        uint8_t pin_state = (*pin & (1 << pin_number)) ? '1' : '0';
        UART_transmit(pin_state);
        UART_transmit('\n');
    } else if (_frame.action == '1') {
        *ddr |= (1 << pin_number);
        if (_frame.times_repeat == '1') {
            *port |= (1 << pin_number);
        } else if (_frame.times_repeat == '0') {
            *port &= ~(1 << pin_number);
        } else {
            UART_sendString("Invalid State for Output");
        }
    } else {
        UART_sendString("Invalid Action");
    }

    clearStruct();
}

void timer(frame _frame) {
    // Variables for timer registers
    volatile uint8_t *tccr = NULL;
    volatile uint8_t *ocr = NULL;
    volatile uint8_t *timsk = NULL;
    volatile uint8_t *tcnt = NULL;

    // Select timer based on protocol_class
    switch (_frame.protocol_class) {
        case '0': // Timer0
            tccr = &TCCR0A;
            ocr = &OCR0A;
            timsk = &TIMSK0;
            tcnt = &TCNT0;
            break;
        case '1': // Timer1
            tccr = &TCCR1A;
            ocr = &OCR1A;
            timsk = &TIMSK1;
            tcnt = &TCNT1;
            break;
        case '2': // Timer2
            tccr = &TCCR2A;
            ocr = &OCR2A;
            timsk = &TIMSK2;
            tcnt = &TCNT2;
            break;
        default:
            UART_sendString("Invalid Timer");
            return;
    }

    // Configure timer mode based on action
    if (_frame.action == '0') {
        // Normal mode
        *tccr &= ~(1 << WGM00);
        *tccr &= ~(1 << WGM01);
    } else if (_frame.action == '1') {
        // CTC mode
        *tccr &= ~(1 << WGM00);
        *tccr |= (1 << WGM01);
    } else if (_frame.action == '2') {
        // Fast PWM mode
        *tccr |= (1 << WGM00);
        *tccr |= (1 << WGM01);
    } else {
        UART_sendString("Invalid Timer Mode");
        return;
    }

    // Set prescaler
    *tccr &= ~(0x07); // Clear prescaler bits
    *tccr |= (_frame.speed & 0x07); // Set new prescaler

    // Set timer value
    *ocr = _frame.data[0]; // Assuming single byte for OCR value

    // Configure timer interrupt based on times_repeat
    if (_frame.times_repeat == '1') {
        *timsk |= (1 << OCIE0A); // Enable compare match interrupt
    } else if (_frame.times_repeat == '0') {
        *timsk &= ~(1 << OCIE0A); // Disable compare match interrupt
    } else {
        UART_sendString("Invalid Timer Control");
    }

    clearStruct();
}
