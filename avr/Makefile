zz ?=blink 

board_path:=/dev/ttyACM0

ifeq ($(board),red)
		board_path:=/dev/serial/by-path/platform-vhci_hcd.0-usb-0:1:1.0-port0
endif



default:
		avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o avr.o $(zz).c
		avr-gcc -o avr.bin avr.o
		avr-objcopy -O ihex -R .eeprom avr.bin avr.hex
		sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(board_path) -b 115200 -U flash:w:avr.hex

.PHONY: clean

clean:
		rm -f avr.o avr.bin avr.hex
