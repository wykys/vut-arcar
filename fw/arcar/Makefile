# AVR project Makefile
# wykys 2018


######################################
# project variables
######################################
# target name
TARGET = DEMO
# chip
CHIP = atmega328pb
# usb to uart
USB_TO_UART = CP2102
# baudrate
BAUDRATE = 38400
# programmer: -b baudrate, -P port, -d system name of the usb serial converter
PROGRAMMER = arduino -b 57600 -P $(shell $(WFS) -d $(USB_TO_UART))
# optimalization
OPT = -Os
# build dir
BUILD_DIR = build
# source dir
SRC = src
# includes
INC = -Iinc



######################################
# source
######################################
# C++ sources
CPP_SOURCES = $(wildcard $(SRC)/*.cpp)
# C sources
C_SOURCES = $(wildcard $(SRC)/*.c)
# ASM sources
ASM_SOURCES = $(wildcard $(SRC)/*.S)


#######################################
# toolchain
#######################################
SCRIPTS_DIR = .scripts/
RUN_ANSI_C = $(SCRIPTS_DIR)run-ansi-c.sh
RUN_PYTHON = $(SCRIPTS_DIR)run-python.sh
# atmel tools
TOOLCHAIN_PATH = /opt/avr8-gnu-toolchain-linux_x86_64
BINPATH = $(TOOLCHAIN_PATH)/bin/
PREFIX = avr-
CC  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)gcc -fdiagnostics-color=always
CPP = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)g++ -fdiagnostics-color=always
AS  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)gcc -fdiagnostics-color=always -x assembler-with-cpp
CP  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)objcopy
DP  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)objdump
AR  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)ar
SZ  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
RM  = rm -rf
# wykys scripts
WTR = $(RUN_PYTHON) $(SCRIPTS_DIR)$(PREFIX)translate-mcu.py --mcu=$(CHIP)
WSZ = $(RUN_PYTHON) $(SCRIPTS_DIR)$(PREFIX)size.py --mcu=$(CHIP) --color --size="$(SZ)"
WFS = $(RUN_PYTHON) $(SCRIPTS_DIR)find-serial.py
# miniterm
MINITERM = $(SCRIPTS_DIR)run-miniterm.sh $(shell $(WFS) -d $(USB_TO_UART)) $(BAUDRATE)
# avrdude
AVRDUDE = avrdude -p $(shell $(WTR)) -c $(PROGRAMMER)


#######################################
# Atmel Device Family Packs (DFP) for new devices support.
# http://packs.download.atmel.com/
#######################################
DFP = /opt/Atmel.ATmega_DFP.1.2.272
DEVSPEC = -B $(DFP)/gcc/dev/$(CHIP)
AVRLIB = -I$(DFP)/include


#######################################
# build the application
#######################################
# compile gcc flags
MCU = -mmcu=$(CHIP)
AFLAGS = $(MCU) -Wall $(INC)
CFLAGS = $(MCU) -Wall -std=c99 $(OPT) $(INC) $(DEVSPEC) $(AVRLIB)
CPPFLAGS = $(MCU) -Wall -std=c++11 $(OPT) $(INC) $(DEVSPEC) $(AVRLIB)
LDFLAGS = $(MCU)  -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -Wl,--cref $(DEVSPEC) $(AVRLIB)

# generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"
CPPFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

# list of objects
# add C++ to objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
# add C to objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# add ASM to objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/EEPROM.hex $(BUILD_DIR)/$(TARGET).lss size
# create object files from C++ files
$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@$(CPP) -c $(CPPFLAGS) $< -o $@
# create object files from C files
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@
# create object files from ASM files
$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	@$(AS) -c $(AFLAGS) $< -o $@
# create aplication ELF file
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@$(CPP) $(OBJECTS) $(LDFLAGS) -o $@
# create aplication FLASH intel HEX file
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@$(HEX) -R .eeprom $< $@
# create aplication EEPROM intel HEX file
$(BUILD_DIR)/EEPROM.hex: $(BUILD_DIR)/$(TARGET).elf
	@$(HEX) -j .eeprom --change-section-lma .eeprom=0 $< $@ 2> /dev/null
# disassembly EFL
$(BUILD_DIR)/$(TARGET).lss: $(BUILD_DIR)/$(TARGET).elf
	@$(DP) -h -S $< > $@
# create build directory
$(BUILD_DIR):
	@mkdir $@
# prints memory usage tables
size:
	@$(WSZ) -e $(BUILD_DIR)/$(TARGET).elf
# clean up
clean:
	@$(RM) $(BUILD_DIR)


#######################################
# avrdude
#######################################
terminal:
	@$(AVRDUDE) -t
dump_eeprom:
	@echo "dump eeprom" | $(AVRDUDE) -t
flash:
	@$(AVRDUDE) -U flash:w:$(BUILD_DIR)/$(TARGET).elf:e
flash_all:
	@$(AVRDUDE) -U flash:w:$(BUILD_DIR)/$(TARGET).elf:e -U eeprom:w:$(BUILD_DIR)/$(TARGET).elf:e
chip_test:
	@$(AVRDUDE)
build_and_flash: all flash


#######################################
# miniterm
#######################################
miniterm:
	@$(MINITERM)
