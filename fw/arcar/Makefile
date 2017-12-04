# Main AVR project Makefile
# wykys 27.11.2017

NAME = ARCAR
export

BIN = bin
CHIP = m328pb
PROG = arduino
ELF = $(BIN)/$(NAME).elf
AVRDUDE = avrdude -p $(CHIP) -c $(PROG) -P /dev/ttyUSB0 -b 57600

.PHONY: all
.PHONY: flash
.PHONY: clean
.PHONY: terminal
.PHONY: dump_eeprom
.PHONY: flash_all
.PHONY: chip_test

all:
	+@make --no-print-directory -C $(BIN)

clean:
	+@make --no-print-directory -C $(BIN) $@

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
