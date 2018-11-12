# AVR-tools
Tools for development of AVR microcontrollers.

## Project wizard
### First step
Open the terminal and go to a path where you want to create your AVR project. Use the `cd` command to change directory.

### Getting the project template
Getting the template is easy. Just clone this repository.
```bash
# if you prefer SSH
git clone git@github.com:wykys/AVR-tools.git
# else use HTTPS
git clone https://github.com/wykys/AVR-tools.git
```

### Set the name of the project folder
Use the `mv` command to change the folder name.
```bash
# replace the the_name_of_your_project with the desired name
mv AVR-tools the_name_of_your_project
# and go to your project folder
cd the_name_of_your_project
```

### Open project in editor
Open your project in your favorite text editor. Choose one option.
```bash
# for Atom
atom .
# for Visual Studio Code
code .
```

### Makefile settings
`Makefile` describes the build of a project. It also allows you to run auxiliary tools used for programming the target processor, analyzing compilation results and so on.

The `Makefile` file is located in the root directory of your project. Using a text editor, you can edit variables as required by the application.

#### Project name
It affects names of generated files.
```makefile
# find the following line
TARGET = DEMO
# change DEMO for the name of your project
TARGET = the_name_of_your_project
```

#### Target microcontroller
The names of available microcontrollers are shown [here](https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html).
```makefile
# find the following line
CHIP = atmega328p
# change CHIP
CHIP = the_name_of_your_chip
```

#### Code size optimization
It affects size and speed of the application.

| __OPT__ |  __DESCRIPTION__  |
|---------|-------------------|
| -O0 | optimization is off   |
| -O1 | optimization level 1  |
| -O2 | optimization level 2  |
| -O3 | optimization level 3  |
| -Os | size optimization     |

```makefile
# find the following line
OPT = -Os
# change OPT
OPT = required_optimization
```

#### Changing the programmer
List of supported `avrdude` programmers is [here](https://www.nongnu.org/avrdude/user-manual/avrdude_4.html)
```makefile
# find the following line
AVRDUDE = avrdude -p $(shell $(WTR)) -c arduino -P $(shell $(WFS))
# change AVRDUDE
# port is required only for some programmers
AVRDUDE = avrdude -p $(shell $(WTR)) -c your_programmer -P programmer_port
```

### Usage of `make`
`Makefile` allows compilation, programming and debugging of applications.
```bash
# compiling the project, equivalen to make
make all
# flash content
make flash
# compiling the project and programming the flash
make build_and_flash
# deletes the compilation outputs
make clean
# start avrdude terminal
make terminal
# EEPROM dump_eeprom
make dump_eeprom
# flash all (flash, EEPROM)
make flash_all
# chip testing
make chip_test
```

## Application notes
### File template hierarchy
```bash
.
├── inc
│   ├── settings.h
│   └── uart.h
├── LICENSE
├── Makefile
├── README.md
└── src
    ├── main.c
    ├── rand.S
    └── uart.c

2 directories, 8 files
```
Source files `*.c` and `*.S` are located in the `src/` folder. Header files `*.h` are located in the `inc/` folder. The compilation outputs (binary files `*.hex`, `*.elf`, code disassembler [`*.lss`, `*.lst`], dependency files `*.d`, batch files `*.o`, map file `*.map`) are located in the `$(BUILD_DIR)` folder. Project scripts are located in the hidden folder `.scripts`.


### Change of frequency
The `F_CPU` [Hz] constant used for delay functions is defined in the `settings.h` file. The `settings.h` file must be plugged into all files in which you want to use the constant. You can also add additional constants that affect the behavior of the entire program.

```C
#ifndef F_CPU
  #define F_CPU 16000000UL // Hz
#endif
```

## Scripts
These scripts are designed to simplify the development of AVR applications. They are described in a separate [README](https://github.com/wykys/AVR-tools/tree/master/.scripts).

## Installation
To run `AVR-tools` it is required to install these packages:

| __NAME__ | __LINK__ |
|--- | --- |
| `git` | https://git-scm.com/ |
| `make` | https://www.gnu.org/software/make/ |
| `avrdude` | http://savannah.nongnu.org/projects/avrdude |
| `python3` | https://www.python.org/ |
| `python3-pip` | https://docs.python.org/3/installing/index.html |
| `python3-venv` | https://docs.python.org/3/library/venv.html |
| `atmel-avr-toolchain` | http://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers |

### For Debian Ubuntu and their derivatives
Just enter the following command into the terminal for download and run shell installation script, which automatically installs the necessary tools.
```bash
sh -c "$(wget https://raw.githubusercontent.com/wykys/AVR-tools/master/.scripts/install.sh -O -)"
```

### Tested on operating systems

| __NAME__ | __VERSION__ | __RESULT__ |
|:--- | ---: | :---: |
| Linux Mint | 19 | OK |
| Linux Mint | 18.3 | OK |
| Xubuntu | 16.04 | OK |
| Debian | 9.5.0 | OK |
| Windows | 10 | ? |


## Updates
With git you can get a newer version, but if you already have a project, I recommend that you make a backup first because there may be a collision between the files.

```bash
# go to the project folder and use this command
git pull
```
