#pragma once
//
//    FILE: SHEX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library to generate hex dump over Serial
//    DATE: 2020-05-24
//     URL: https://github.com/RobTillaart/SHEX


#include "Arduino.h"
#include "Print.h"


#define SHEX_LIB_VERSION                (F("0.3.0"))

#define SHEX_DEFAULT_LENGTH             16
#define SHEX_MAX_LENGTH                 32
#define SHEX_COUNTER_DIGITS             4

class SHEX: public Print
{
public:
  SHEX(Print* stream = &Serial, uint8_t length = SHEX_DEFAULT_LENGTH);

  void    reset();

  size_t  write(uint8_t c);

  void    setHEX(bool hexOutput = true);
  bool    getHEX() { return _hexOutput; };

  void    setBytesPerLine(const uint8_t length = SHEX_DEFAULT_LENGTH);
  uint8_t getBytesPerLine() { return _length; };

  void    setSeparator(char c = ' ') { _separator = c; };
  char    getSeparator() { return _separator; };

  void    setCountFlag(bool flag = true) { _countFlag = flag; };
  bool    getCountFlag() { return _countFlag; };

  //      must be 4-8
  void    setCountDigits(uint8_t digits);
  uint8_t getCountDigits() { return _digits; }

private:
  Print *   _stream    = &Serial;
  bool      _hexOutput = true;
  uint8_t   _length    = SHEX_DEFAULT_LENGTH;
  char      _separator = ' ';

  bool      _countFlag = true;
  uint32_t  _charCount = 0;
  uint32_t  _digits    = 4;
};


// -- END OF FILE --

