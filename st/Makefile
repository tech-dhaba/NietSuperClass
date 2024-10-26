upload:
	make all && make convert && make flash
all:
	arm-none-eabi-gcc -nostdlib -nostartfiles main.c startup.s -o exe.elf -mcpu=cortex-m4 -T FLASH.ld -static -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb 
convert:
	arm-none-eabi-objcopy -O binary exe.elf exe.bin
flash:
	st-flash write exe.bin 0x8000000
clean:
	rm exe.*
