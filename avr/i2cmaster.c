#include <avr/io.h>
#include <util/delay.h>

#define SDA_PIN 4 // Arduino pin for SDA (Analog pin 4)
#define SCL_PIN 5 // Arduino pin for SCL (Analog pin 5)
#define SLAVE_ADDRESS 0x08 // Address of the slave Arduino

void i2c_init() {
  // Set prescaler to 1 (no prescaling)
  TWSR = 0;
  // Set bit rate to 100 kHz
  TWBR = ((F_CPU / 100000) - 16) / 2;
}

void i2c_start() {
  // Start condition: TWSTA = 1, TWEN = 1
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  // Wait for TWINT flag to be set, indicating start condition sent
  while (!(TWCR & (1 << TWINT)));
}

void i2c_stop() {
  // Stop condition: TWSTO = 1, TWEN = 1
  TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
  // Wait for TWSTO flag to be cleared, indicating stop condition sent
  while (TWCR & (1 << TWSTO));
}

void i2c_write(uint8_t data) {
  // Load data into TWDR register
  TWDR = data;
  // Clear TWINT flag to start transmission
  TWCR = (1 << TWEN) | (1 << TWINT);
  // Wait for TWINT flag to be set, indicating data transmitted
  while (!(TWCR & (1 << TWINT)));
}

int main() {
  // Initialize I2C
  i2c_init();
  // Initialize Serial communication
  Serial.begin(9600);
  
  while (1) {
    // Start I2C transmission
    i2c_start();
    // Send slave address with write bit
    i2c_write((SLAVE_ADDRESS << 1) | 0);
    // Send data byte
    i2c_write('H');
    // Send data byte
    i2c_write('i');
    // Send stop condition
    i2c_stop();
    // Wait for some time
    _delay_ms(500);
  }
  return 0;
}
