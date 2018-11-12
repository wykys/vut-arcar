# Scripts summary
These scripts are developed to simplify the development of AVR applications.

## avr-size
The script combines memory information from the AVR database and the utility size parsing output. Memory and size information displays in a more readable form.

Te script can automatically find a binary .elf, if the two folders do not exceed the level of the two.

### Demo
`.scripts/avr-size.py --mcu=atmega8`
```
╔════════════════════════╗ ╔════════════════════════╗
║    RAM MEMORY 9.3 %    ║ ║   FLASH MEMORY 9.2 %   ║
╟────────────────────────╢ ╟────────────────────────╢
║All:               1 KiB║ ║All:               8 KiB║
║Use:                95 B║ ║Use:               750 B║
║Free:              929 B║ ║Free:           7.27 KiB║
╚════════════════════════╝ ╚════════════════════════╝
```

### Arguments
`.scripts/avr-size.py -h`
```
usage: avr-size [-h] [-e PATH_ELF] [-c] [-v] [-m MCU] [-s SIZE]

The script parses the memory information from the linkerscript and the size
program, and then displays them in a morereadable form.

optional arguments:
  -h, --help            show this help message and exit
  -e PATH_ELF, --elf PATH_ELF
                        destination elf file
  -c, --color           activated color output
  -v, --vertical        prints the tables underneath
  -m MCU, --mcu MCU     the name of the microcontroller
  -s SIZE, --size SIZE  the path to size utility
```

## avr-translate-mcu
The script translates the names of the microcontrollers used by the AVR toolchain into the format for avrdude.

### Demo
`.scripts/avr-translate-mcu.py --mcu=atmega8a`
```
m8
```

### Arguments
`.scripts/avr-translate-mcu.py -h`
```
usage: avr-transtale-mcu [-h] [-m MCU]

The script parses the memory information from the linker script and the size
program, and then displays them in a more readable form.

optional arguments:
  -h, --help         show this help message and exit
  -m MCU, --mcu MCU  the name of the microcontroller
```

## find-serial
The script prints a port corresponding to the description of the device you are looking for.

### Demo
`.scripts/find-serial.py --device="USB"`
```
/dev/ttyUSB0
```

### Arguments
`.scripts/find-serial.py -h`
```
usage: find-serial [-h] [-d DEVICE]

The script prints a port corresponding to the description of the device you
are looking for.

optional arguments:
  -h, --help            show this help message and exit
  -d DEVICE, --device DEVICE
                        the name of the device
```

## run-ansi-c
Run program with ANSI C localization. It is necessary to successfully launch the tools from Atmel toolchain version 3.6.1.

### Demo
`.scripts/run-ansi-c.sh /opt/avr8-gnu-toolchain-linux_x86_64/bin/avr-readelf build/DEMO.elf -h`
```
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Atmel AVR 8-bit microcontroller
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          52 (bytes into file)
  Start of section headers:          6708 (bytes into file)
  Flags:                             0x5, avr:5
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         3
  Size of section headers:           40 (bytes)
  Number of section headers:         13
  Section header string table index: 10
```

### Arguments
All the arguments passed to this script are run in the system shell.

## venv
If it exists, it will remove the old python virtual environment. Creates a new virtual python environment and installs packages from the `requirements.txt` file.

### Demo
`.scripts/venv.sh`
```
remove old venv
create new venv
activate venv
upgrade pip
Collecting pip
  Using cached https://files.pythonhosted.org/packages/5f/25/e52d3f31441505a5f3af41213346e5b6c221c9e086a166f3703d2ddaf940/pip-18.0-py2.py3-none-any.whl
Installing collected packages: pip
  Found existing installation: pip 9.0.1
    Uninstalling pip-9.0.1:
      Successfully uninstalled pip-9.0.1
Successfully installed pip-18.0
install modules from requirements
Collecting colorama>=0.3.9 (from -r requirements.txt (line 1))
  Using cached https://files.pythonhosted.org/packages/db/c8/7dcf9dbcb22429512708fe3a547f8b6101c0d02137acbd892505aee57adf/colorama-0.3.9-py2.py3-none-any.whl
Collecting pyserial>=3.4 (from -r requirements.txt (line 2))
  Using cached https://files.pythonhosted.org/packages/0d/e4/2a744dd9e3be04a0c0907414e2a01a7c88bb3915cbe3c8cc06e209f59c30/pyserial-3.4-py2.py3-none-any.whl
Installing collected packages: colorama, pyserial
Successfully installed colorama-0.3.9 pyserial-3.4
installed modules
colorama==0.3.9
pkg-resources==0.0.0
pyserial==3.4
```

### Arguments
He has no arguments.


## run-python
It runs a python script in a virtual environment and passes arguments if the environment does not exist, it runs the script `venv.sh` that creates it.

### Demo
`.scripts/run-python.sh .scripts/avr-translate-mcu.py -m attiny13`
```
t13
```

### Arguments
All the arguments passed to this script are run in the system shell with activate python virtual environment.

## install (for Debian Ubuntu and their derivatives)
Just enter the following command into terminal for download and run shell installation script, which automatically installs the necessary tools.

This script will download and install all necessary tools and packages needed to run `AVR Tools` tools. Finally, it will perform a test translation and clean up.

### Demo
```bash
sh -c "$(wget https://raw.githubusercontent.com/wykys/AVR-tools/master/.scripts/install.sh -O -)"
```
