# Main AVR project Makefile
# wykys 9.9.2017

NAME = BOOTLOADER
export

BIN = bin
CHIP = m328pb
PROG = usbasp
ELF = $(BIN)/$(NAME).elf
AVRDUDE = avrdude -p $(CHIP) -c $(PROG)

.PHONY: all
.PHONY: flash
.PHONY: clean
.PHONY: fuses-int-8MHz
.PHONY: terminal
.PHONY: dump_eeprom
.PHONY: flash_all
.PHONY: chip_test

all:
	@make --no-print-directory -C $(BIN)

clean:
	@make --no-print-directory -C $(BIN) $@

fuses-int-8MHz:
	$(AVRDUDE) -U lfuse:w:0xe2:m -U hfuse:w:0xd4:m -U efuse:w:0xff:m
	@echo "Int 8MHz, BOOT 512B"
terminal:
	$(AVRDUDE) -t

dump_eeprom:
	echo "dump eeprom" | $(AVRDUDE) -t

flash:
	$(AVRDUDE) -U flash:w:$(ELF):e

flash_all:
	$(AVRDUDE) -U flash:w:$(ELF):e -U eeprom:w:$(ELF):e

chip_test:
	$(AVRDUDE)

build_and_flash: all flash

test:
	avrdude -p $(CHIP) -c arduino -b 57600 -P /dev/ttyUSB0
