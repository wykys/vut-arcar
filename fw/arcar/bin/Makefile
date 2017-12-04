# wykys Makefile for AVR

ifndef NAME
NAME = PRJ
endif

SRC = ../src/
LIB = ../inc/

MCU = atmega328pb

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
CPP = $(TOOLS)avr-g++ -fdiagnostics-color=always
OBJCOPY = $(TOOLS)avr-objcopy
OBJDUMP = $(TOOLS)avr-objdump
BINSIZE = $(TOOLS)avr-size
RM = rm -rf


OPTIMIZE = -O1
CFLAGS = -g -mmcu=$(MCU) -Wall -std=c99 -I $(LIB) $(OPTIMIZE)
CPPFLAGS = -g -mmcu=$(MCU) -Wall -std=c++11 -I $(LIB) $(OPTIMIZE)



DEP = dependence.list

OBJFILES = $(shell find $(SRC) -name '*.c' -printf '%f ' | sed -e 's/\.c/\.o/g')
OBJFILES += $(shell find $(SRC) -name '*.cpp' -printf '%f ' | sed -e 's/\.cpp/\.o/g')

.PHONY: dependence clean $(NAME)

# build all
all: $(NAME)

# genereting dependence
$(DEP): $(SRC)*.c
	@$(CC) -mmcu=$(MCU) $(DEVSPEC) $(AVRLIB) -I $(LIB) $(SETTINGS) -MM $(SRC)*.c > $(DEP)

# include genereted dependence
-include $(DEP)

# create object modules
%.o : $(SRC)%.c
	@$(CC) -c $(DEVSPEC) $(AVRLIB) $(CFLAGS) $< -o $@

%.o : $(SRC)%.cpp
	@$(CPP) -c $(DEVSPEC) $(AVRLIB) $(CPPFLAGS) $< -o $@

# create ELF
$(NAME).elf: $(DEP) $(OBJFILES)
	@$(CC) $(DEVSPEC) $(AVRLIB) $(CFLAGS) $(OBJFILES) -o $@

# disassembly EFL
$(NAME).lss: $(NAME).elf
	@$(OBJDUMP)  -h -S $(NAME).elf > $@

# analyze size ELF
$(NAME): $(NAME).elf $(NAME).lss
	@$(BINSIZE) -C --mcu=$(MCU) $(NAME).elf

# clean files
clean:
	$(RM) *.o *.list *.elf *.hex *.lss
