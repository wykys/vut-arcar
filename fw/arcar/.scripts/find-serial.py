#!/usr/bin/env python3
# wykys 2018
# The script prints a port corresponding to
# the description of the device you are looking for.

from sys import stderr
from argparse import ArgumentParser
from serial.tools import list_ports


def serial_dev_list():
    print('\nList all serial devices:', file=stderr)
    for port in list_ports.comports():
        print('\t{:17} {}'.format(port.device, port.description), file=stderr)
    print('\n', file=stderr)


def find_device(name):
    for port in list_ports.comports():
        if name in port.description:
            print(port.device)
            exit()

    print('Error: Device is not connect!', file=stderr)
    serial_dev_list()
    exit(-1)


if __name__ == '__main__':
    parser = ArgumentParser(
        prog='find-serial',
        description='The script prints a port corresponding to'
        ' the description of the device you are looking for.'
    )
    parser.add_argument(
        '-d',
        '--device',
        dest='device',
        action='store',
        default='Serial',
        help='the name of the device'
    )

    find_device(parser.parse_args().device)
