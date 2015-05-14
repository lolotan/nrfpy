from distutils.core import setup, Extension

module1 = Extension('nrfpy',
                    sources = ['nrfpy_dht22.c', 'nrflib.c', 'spi.c', 'gpio.c', 'timer.c'])

setup (name = 'NrfPy',
       version = '1.0',
       description = 'NrfPy remote sensor librairy',
       ext_modules = [module1])
