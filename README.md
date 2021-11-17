
[![Arduino CI](https://github.com/RobTillaart/SHEX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SHEX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SHEX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SHEX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SHEX/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHEX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHEX.svg?maxAge=3600)](https://github.com/RobTillaart/SHEX/releases)


# SHEX

Arduino library to generate hex dump over Serial (any stream).


## Description

SHEX is a simple library that wraps the Serial output side (by default) and
generates an hex dump of all data that is printed. 16 bytes per row.

The default output format is 
```
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx

0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx 
```
with a separator line after each 8th line.

The constructor has a length parameter which can be used to have another number of bytes per row. 
After construction this cannot be changed, at least not in the initial release. 

The only thing one can toggle is HEX output or pass through by means of **setHEX(bool)**.
This makes it possible to switch between the modes e.g. between 'debugging' and 'release' mode.


## Interface


### Constructor + Core

- **SHEX(Print \* stream = &Serial, uint8_t length = 16)** Constructor, optional set the number of bytes per line.
- **size_t write(uint8_t c)** implements the Print interface.


### Modifiers

- **void setHEX(bool hexOutput = true)** switch between modi, HEX (true) or pass through (false).
- **bool getHEX()** returns mode set above.
- **void setBytesPerLine(uint8_t length = 16)** idem, default 16 bytes per line, forced multiple of 4.
- **uint8_t getBytesPerLine()** returns number of bytes per line.
- **void setSeparator(char c = ' ')** set the separator character, default a space.
Some people like a dot '.', or a tab '\t'. Feel free to experiment.
- **char getSeparator()** return the separator character set.
- **void setCountFlag(bool flag = true)** show the character count at begin of every line.
- **bool getCountFlag()** return flag set.


## Operational

See examples.


## Future

Although no follow up release is planned, some ideas are kept here
so they won't get lost.

- Optional ASCII column in the output format ( . if not printable) e.g.
```
        0xABCDABCD  xx xx xx xx xx xx xx xx xx    c.cc c..c
```
needs a line buffer to do that (double loop)

- line buffering for faster output (e.g Ethernet and SD card)
- header line: runtime configurable; optional combined with separator
  and after how many lines the header should repeat)
  header(str, lines); ???
- HEX reader: converts dump format to a normal stream again.
- better name for the class? - streamHex

