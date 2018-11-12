#!/usr/bin/env python3
# wykys 2018
# The script combines memory information from
# the AVR database and the utility size parsing output.
# Memory and size information displays in a more readable form.

import argparse
import sys
import subprocess
from pathlib import Path
from byte import Byte
from avr import Database, NotDefinedMCUError
from colorama import Back, Fore, Style, init
init()


class NotExistError(IOError):
    def __init__(self, name: str):
        self.error_text = '{} is not exists!'.format(name)

    def __str__(self):
        return self.error_text


def is_exact_file(path, suffix):
    path = Path(path)
    return path.suffix == suffix and path.is_file()


def is_elf(path):
    return is_exact_file(path, '.elf')


def check_path(path, is_ok, max_recursive=None, recursive_index=0):
    path = Path(path)
    if path.is_dir():
        for sub_path in path.iterdir():
            if sub_path.is_dir() and (recursive_index < max_recursive or recursive_index is None):
                sub_path = check_path(sub_path, is_ok, max_recursive, recursive_index + 1)
            if is_ok(sub_path):
                path = sub_path
                break

    if (path.exists() and is_ok(path)) or recursive_index:
        return path
    else:
        raise NotExistError(path)


def check_elf_path(path):
    return check_path(path, is_elf, max_recursive=2)


def print_memory(memory):
    for name, length in memory.items():
        print('{}\t{}'.format(name, length))


def size_parser(path_elf, path_size='size'):
    import re
    regex = r'^(\.\S+)\s*(\d+)'
    size = path_size.split()
    result = subprocess.run(
        [size[0], *size[1:], '-A', str(path_elf)],
        stdout=subprocess.PIPE,
    ).stdout.decode('utf-8')
    return {
        match.group(1): Byte(match.group(2)) for match in re.finditer(
            regex, result, re.MULTILINE
        )
    }


def calculate_percentages(use_memory, all_memory):
    return use_memory.value / (all_memory.value / 100)


def create_table(name, use_memory, all_memory, color=True):
    columns = 26
    width = columns - 2
    percent = calculate_percentages(use_memory, all_memory)
    bar = width if percent >= 100 else int(width*percent/100)

    head_str = '{} MEMORY {:.2g} %'.format(name, percent)
    all_str = 'All:'
    use_str = 'Use:'
    free_str = 'Free:'

    head_width_tag = '{:^' + str(width) + '}'
    all_width_tag = all_str + '{:>' + str(width - len(all_str)) + '}'
    use_width_tag = use_str + '{:>' + str(width - len(use_str)) + '}'
    free_width_tag = free_str + '{:>' + str(width - len(free_str)) + '}'

    if color:
        if percent < 60:
            color = Back.GREEN + Fore.WHITE + Style.BRIGHT
        elif percent < 80:
            color = Back.LIGHTRED_EX + Fore.BLACK + Style.BRIGHT
        else:
            color = Back.RED + Fore.BLACK + Style.BRIGHT
    else:
        color = Style.BRIGHT

    head = head_width_tag.format(head_str)
    head = ''.join((color, head[:bar], Style.RESET_ALL + Style.BRIGHT, head[bar:], Style.RESET_ALL))

    table = []
    table.append('╔{}╗'.format('═'*width))
    table.append('║{}║'.format(head))
    table.append('╟{}╢'.format('─'*width))
    table.append('║{}║'.format(all_width_tag.format(str(all_memory))))
    table.append('║{}║'.format(use_width_tag.format(str(use_memory))))
    table.append('║{}║'.format(free_width_tag.format(str(all_memory - use_memory))))
    table.append('╚{}╝'.format('═'*width))
    return table


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        prog='avr-size',
        description='The script combines memory information from the AVR'
        ' database and the utility size parsing output. Memory and size' ' information displays in a more readable form.'
    )
    parser.add_argument(
        '-e',
        '--elf',
        dest='path_elf',
        action='store',
        default='.',
        help='destination elf file',
    )
    parser.add_argument(
        '-c',
        '--color',
        dest='color',
        action='store_true',
        default=False,
        help='activated color output'
    )
    parser.add_argument(
        '-v',
        '--vertical',
        dest='table_rate',
        action='store_true',
        default=False,
        help='prints the tables underneath'
    )
    parser.add_argument(
        '-m',
        '--mcu',
        dest='mcu',
        action='store',
        default=None,
        help='the name of the microcontroller'
    )
    parser.add_argument(
        '-s',
        '--size',
        dest='size',
        action='store',
        default='size',
        help='the path to size utility'
    )

    try:
        mcu = Database.get_mcu(parser.parse_args().mcu)
        path_elf = check_elf_path(parser.parse_args().path_elf)
        path_size = parser.parse_args().size

    except NotDefinedMCUError as e:
        print(str(e), file=sys.stderr)
        Database.print_table()
        exit(-1)

    except NotExistError as e:
        print(str(e), file=sys.stderr)
        exit(-1)

    size = size_parser(path_elf, path_size)

    use_ram = size['.data']
    if '.bss' in size:
        use_ram += size['.bss']
    if '.noinit' in size:
        use_ram += size['.noinit']

    use_flash = size['.text'] + size['.data']
    if '.bootloader' in size:
        use_flash += size['.bootloader']

    color = parser.parse_args().color
    ram = create_table('RAM', use_ram, mcu['RAM'], color)
    flash = create_table('FLASH', use_flash, mcu['FLASH'], color)

    if '.eeprom' in size:
        eeprom = create_table('EEPROM', size['.eeprom'], mcu['EEPROM'], color)
        if parser.parse_args().table_rate:
            for line in ram + flash + eeprom:
                print(line)
        else:
            for line_ram, line_flash, line_eeprom in zip(ram, flash, eeprom):
                print('{} {} {}'.format(line_ram, line_flash, line_eeprom))

    else:
        if parser.parse_args().table_rate:
            for line in ram + flash:
                print(line)
        else:
            for line_ram, line_flash in zip(ram, flash):
                print('{} {}'.format(line_ram, line_flash))
