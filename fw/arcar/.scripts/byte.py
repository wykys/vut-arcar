# wykys 2018
# The object for computing and printing binary units


from collections import OrderedDict


unit_dict_special = OrderedDict(sorted({
    'B': 1,
    'KB': 2**10,
}.items(), key=lambda x: x[1], reverse=True))

unit_dict_two_on_n_short = OrderedDict(sorted({
    'B': 1,
    'K': 2**10,
    'M': 2**20,
    'G': 2**30,
    'T': 2**40,
    'P': 2**50,
    'E': 2**60,
    'Z': 2**70,
    'Y': 2**80,
}.items(), key=lambda x: x[1], reverse=True))

unit_dict_two_on_n = OrderedDict(sorted({
    'B': 1,
    'KiB': 2**10,
    'MiB': 2**20,
    'GiB': 2**30,
    'TiB': 2**40,
    'PiB': 2**50,
    'EiB': 2**60,
    'ZiB': 2**70,
    'YiB': 2**80,
}.items(), key=lambda x: x[1], reverse=True))

unit_dict_ten_on_n = OrderedDict(sorted({
    'B': 1,
    'kB': 10**3,
    'MB': 10**6,
    'GB': 10**9,
    'TB': 10**12,
    'PB': 10**15,
    'EB': 10**18,
    'ZB': 10**21,
    'YB': 10**24,
}.items(), key=lambda x: x[1], reverse=True))


default_unit_format = 'KiB'


class WrongUnitError(KeyError):
    def __init__(self, name: str):
        self.error_text = '{} is wrong unit!'.format(name)

    def __str__(self):
        return self.error_text


def find_correct_unit_dict(unit):
    if unit in unit_dict_special:
        return unit_dict_special
    elif unit in unit_dict_ten_on_n:
        return unit_dict_ten_on_n
    elif unit in unit_dict_two_on_n:
        return unit_dict_two_on_n
    elif unit in unit_dict_two_on_n_short:
        return unit_dict_two_on_n_short
    else:
        raise WrongUnitError(unit)


class Byte:
    def __init__(self, number=0, unit_format=None):
        self.value = number
        if unit_format is None:
            self.unit_dict = default_unit_format
        else:
            self.unit_dict = unit_format

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, number):
        if isinstance(number, str):
            if number.isdigit():
                self._value = int(number)
            else:
                for i, num in enumerate(number):
                    if num.isalpha():
                        unit = number[i:].strip()
                        number = float(number[:i])
                        break
                unit_dict = find_correct_unit_dict(unit)
                self._value = number * unit_dict[unit]
        else:
            self._value = int(number)

    @property
    def unit_dict(self):
        return self._unit_dict

    @unit_dict.setter
    def unit_dict(self, unit):
        self._unit_dict = find_correct_unit_dict(unit)

    def __add__(self, other):
        return Byte(self.value + other.value)

    def __sub__(self, other):
        return Byte(self.value - other.value)

    def __str__(self):
        find_unit = False
        for unit, value in self.unit_dict.items():
            if abs(self.value) >= value:
                find_unit = True
                break
        if not find_unit:
            value = 1
            unit = 'B'
        return '{:.3g} {}'.format(self.value / value, unit)

    def __repr__(self):
        return self.__str__()
