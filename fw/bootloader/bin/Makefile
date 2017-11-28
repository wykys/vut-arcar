# wykys Makefile for AVR

ifndef NAME
NAME = PRJ
endif

SRC = ../src/
LIB = ../inc/

MCU = atmega328pb
SETTINGS = -DF_CPU=8000000UL -DBAUD_RATE=57600 -DUART=1 -DLED_START_FLASHES=3


# Atmel Device Family Packs (DFP) for new devices support.
# http://packs.download.atmel.com/
DFP = ../../../sw/Atmel.ATmega_DFP.1.2.150/
DFP = /home/wykys/projects/vut-arcar/sw/Atmel.ATmega_DFP.1.2.150/
DEVSPEC = -B $(DFP)gcc/dev/$(MCU)
AVRLIB = -I $(DFP)include

# Atmel AVR 8-bit Toolchain 3.5.4
# http://www.atmel.com/tools/ATMELAVRTOOLCHAINFORLINUX.aspx
TOOLCHAIN = ../../../sw/avr8-gnu-toolchain-linux_x86_64/
TOOLCHAIN = /home/wykys/projects/vut-arcar/sw/avr8-gnu-toolchain-linux_x86_64/
TOOLS = $(TOOLCHAIN)bin/

CC = $(TOOLS)avr-gcc -fdiagnostics-color=always
OBJCOPY = $(TOOLS)avr-objcopy
OBJDUMP = $(TOOLS)avr-objdump
BINSIZE = $(TOOLS)avr-size
RM = rm -rf


LDSECTIONS  = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
OPTIMIZE = -Os -fno-split-wide-types -mrelax
CFLAGS = -g -mmcu=$(MCU) -Wall -std=c99 -I $(LIB) $(OPTIMIZE) $(SETTINGS)
LDFLAGS = $(LDSECTIONS) -Wl,--relax -nostartfiles -nostdlib


DEP = dependence.list

OBJFILES = $(shell find $(SRC) -name '*.c' -printf '%f ' | sed -e 's/\.c/\.o/g')

.PHONY: dependence clean $(NAME)

# build all
all: $(NAME)

# genereting dependence
$(DEP): $(SRC)*.c
	$(CC) -mmcu=$(MCU) $(DEVSPEC) $(AVRLIB) -I $(LIB) $(SETTINGS) -MM $(SRC)*.c > $(DEP)

# include genereted dependence
-include $(DEP)

# create object modules
%.o : $(SRC)%.c
	$(CC) -c $(DEVSPEC) $(AVRLIB) $(CFLAGS) $< -o $@

# create ELF
$(NAME).elf: $(DEP) $(OBJFILES)
	$(CC) $(CFLAGS) $(DEVSPEC) $(AVRLIB) $(LDFLAGS) $(OBJFILES) -o $@

# disassembly EFL
$(NAME).lss: $(NAME).elf
	$(OBJDUMP)  -h -S $(NAME).elf > $@

# analyze size ELF
$(NAME): $(NAME).elf $(NAME).lss
	@$(BINSIZE) -C --mcu=$(MCU) $(NAME).elf

# clean files
clean:
	$(RM) *.o *.list *.elf *.hex *.lss
