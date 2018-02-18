clock1.o: clock1.c
	avr-gcc -c -o clock1.o -Os -mmcu=atmega16 -DF_CPU=1000000UL clock1.c

clock1.elf: clock1.o
	avr-gcc -mmcu=atmega16 -o clock1.elf clock1.o

clock1.hex: clock1.elf
	avr-objcopy -O ihex -R .eeprom clock1.elf clock1.hex
	
magic: clock1.hex
	avrdude -c avrispmkii -p m16 -B 10 -U flash:w:clock1.hex 
	
defuse: 
	avrdude -c avrispmkii -p m16 -B 10 -U lfuse:w:0xe1:m -U hfuse:w:0xd9:m
