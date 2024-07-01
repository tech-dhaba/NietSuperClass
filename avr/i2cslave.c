#include <avr/io.h>

#define SDA_PIN 4 // Arduino pin for SDA (Analog pin 4)
#define SCL_PIN 5 // Arduino pin for SCL (Analog pin 5)
#define SLAVE_ADDRESS 0x08 // Address of this Arduino (slave)

void i2c_init_slave() {
  // Set slave address (own address)
  TWAR = SLAVE_ADDRESS << 1;
  // Enable TWI, acknowledge any address
  TWCR = (1 << TWEN) | (1 << TWEA);
}

uint8_t i2c_read() {
  // Wait for TWINT flag to be set, indicating data received
  while (!(TWCR & (1 << TWINT)));
  // Read received data from TWDR register
  return TWDR;
}

int main() {
  // Initialize I2C as slave
  i2c_init_slave();
  // Initialize Serial communication
  Serial.begin(9600);
  
  while (1) {
    // Wait for TWINT flag to be set, indicating data received
    while (!(TWCR & (1 << TWINT)));
    // Read received data from TWDR register
    char receivedData = i2c_read();
    // Print received data
    Serial.print("Received: ");
    Serial.println(receivedData);
    // Acknowledge received data
    TWCR |= (1 << TWINT) | (1 << TWEA);
  }
  return 0;
}
