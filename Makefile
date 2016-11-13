NAME        := led-matrix
VERSION     := v1.0
DEFS        := -DF_CPU=16000000 -DVERSION=$(VERSION)
MCU_TARGET  := atmega8
MCU_CC      := avr-gcc
OPTIMIZE    := -Os
WARNINGS    := -Wall
CFLAGS      := -std=c99 -MMD -g -mmcu=$(MCU_TARGET) $(OPTIMIZE) $(WARNINGS) $(DEFS)
ASFLAGS     := -g $(DEFS) -mmcu=$(MCU_TARGET)
LDFLAGS     := -Wl,-Map,$(NAME).map
OBJCOPY     := avr-objcopy
OBJDUMP     := avr-objdump

# USBASP ATMEGA8
FLASHCMD    := avrdude -V -c usbasp -p m8 -U lfuse:w:0x9f:m -U hfuse:w:0xc9:m -U flash:w:$(NAME).hex -U eeprom:w:eeprom.bin:r
# ARDUINO UNO SERIAL ATMEGA328P
# FLASHCMD  := avrdude -V -c arduino -p m328p -b 115200 -P /dev/ttyUSB0 -U lfuse:w:0x9f:m -U hfuse:w:0xc9:m -U flash:w:$(NAME).hex -U eeprom:w:eeprom.bin:r

.PHONY: clean dispatch

all: $(NAME).hex eeprom.bin
	$(info $(NAME) $(VERSION))

dispatch: $(NAME).hex eeprom.bin
	$(FLASHCMD)

eeprom.bin:
	$(MAKE) -C x86 all
	./x86/eeprom > /dev/null

%.o: %.c
	$(MCU_CC) -c $(CFLAGS) $<

%.o: %.S
	$(MCU_CC) $(ASFLAGS) -c $<

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

$(NAME).elf: matrix.o
	$(MCU_CC) $(CFLAGS) $(LDFLAGS) -o $@ $+

clean:
	$(MAKE) -C x86 clean
	rm -rf $(NAME) *.elf *.d *.o *.hex *.bin *.map

