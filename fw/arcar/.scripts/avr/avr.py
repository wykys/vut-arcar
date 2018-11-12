# AVR info object
# wykys 2018

from byte import Byte


class InfoAVR(object):
    def __init__(self, flash, ram, eeprom):
        self.flash = Byte(flash)
        self.ram = Byte(ram)
        self.eeprom = Byte(eeprom)
        self.avrdude = None

    def __getitem__(self, name):
        return getattr(self, name.lower())

    def __str__(self):
        return 'FLASH: {}; RAM: {}; EEPROM: {}'.format(
            str(self.flash), str(self.ram), str(self.eeprom)
        )

    def __repr__(self):
        return self.__str__()
