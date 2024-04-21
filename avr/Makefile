zz ?= blink



default:
		avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o avr.o $(zz).c
		avr-gcc -o avr.bin avr.o
		avr-objcopy -O ihex -R .eeprom avr.bin avr.hex
		sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:avr.hex

.PHONY: clean

clean:
		rm -f avr.o avr.bin avr.hex