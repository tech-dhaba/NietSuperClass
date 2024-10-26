# Makefile for AVR project

# Project settings
PROJECT_NAME = main
SOURCE ?= blink.c  # Replace with your source file(s)
MCU = atmega328p  # Replace with your microcontroller type
F_CPU = 16000000UL  # Clock speed, replace if different
PROGRAMMER = arduino  # Programmer type, replace if different
PORT = /dev/ttyACM0  # Replace with your Arduino's port
BAUD = 115200  # Baud rate for uploading

# Compiler settings
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
LDFLAGS = -mmcu=$(MCU)

# Targets
all: $(PROJECT_NAME).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT_NAME).elf: $(SOURCE:.c=.o)
	$(CC) $(LDFLAGS) $^ -o $@

$(PROJECT_NAME).hex: $(PROJECT_NAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: $(PROJECT_NAME).hex
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -D -U flash:w:$(PROJECT_NAME).hex:i

# Clean up
clean:
	rm -f *.o $(PROJECT_NAME).elf $(PROJECT_NAME).hex

.PHONY: all clean upload

