NAME := eeprom
VERSION  := v1.0
DEFS     := -DVERSION=$(VERSION)
OPTIMIZE := -Os
WARNINGS := -Wall
CC       := gcc -c
LD       := gcc
CFLAGS   := -std=c99 -MMD -g $(OPTIMIZE) $(WARNINGS) $(DEFS)
LDFLAGS  := -Wl,-Map,$(NAME).map

CC := gcc -c
LD := gcc
CFLAGS :=
LDFLAGS :=

all: $(NAME)
	$(info $(NAME) $(VERSION))

$(NAME): eeprom.o
	$(LD) $(LDFLAGS) -o $@ $+

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rf $(NAME) *.elf *.d *.o *.hex *.bin *.map

.PHONY: clean
