
"""A setuptools based setup module.
See:
https://packaging.python.org/en/latest/distributing.html
https://github.com/pypa/sampleproject
"""

from setuptools import setup, find_packages
from setuptools.command.test import test as TestCommand
#from distgradle import GradleDistibution
from codecs import open
from os import path, chdir, pardir

here = path.abspath(path.dirname(__file__))

# allow setup.py to be run from any path
chdir(path.normpath(path.join(path.abspath(__file__), pardir)))

# Get the long description from the README file
with open(path.join(here, 'README.md'), encoding='utf-8') as f:
    long_description = f.read()

setup(
    name = 'corewars',
    version = '0.1dev0',
    description = 'CoreWars game project',
    long_description = long_description,
    url = 'https://github.com/sylwiabla/CoreWars',
    author = 'Kamila Lis',
    author_email = 'klis@mion.elka.pw.edu.pl',
    license = 'MIT',
    scripts = ['remote.py'],
    packages = find_packages(),
    #ext_modules = [Extension('foo', ['foo.c'])],
    #package_dir = {'corewars': 'corewars'},
    package_data = {'corewars': ['fonts/*.ttf']},
#    install_requires = ['pygame',
#                        'python-setuptools',
#                        'python-pygame',
#                        'python-psycopg2',
#                        'python-configparser'],
    test_suite = 'unit_tests',

    # If there are data files included in your packages that need to be
    # installed, specify them here.  If using Python 2.6 or less, then these
    # have to be included in MANIFEST.in as well.
#    package_data={
#        'corewars': ['package_data.dat'],
#    },
    #data_files=[('corewars/fonts', ['corewars/fonts/starjedi/Starjedi.ttf','corewars/fonts/starjedi/Starjhol.ttf'])],
    # To provide executable scripts, use entry points in preference to the
    # "scripts" keyword. Entry points provide cross-platform support and allow
    # pip to create the appropriate form of executable for the target platform.
#    entry_points={
#        'console_scripts': [
#            'corewars=corewars:controller',
#        ],
#    },
    entry_points = {'console_scripts': ['corewars = corewars:main',],},
)
