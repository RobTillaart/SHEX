#pragma once
//
//    FILE: SHEX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library to generate hex dump over Serial
//    DATE: 2020-05-24
//     URL: https://github.com/RobTillaart/SHEX
//
 

#include "Arduino.h"
#include "Print.h"

class SHEX: public Print
{
public:
  SHEX(Print* stream = &Serial, uint8_t len = 16);

  size_t write(uint8_t c);

  void setHEX(bool hexOutput = true);

private:
  Print *   _stream;
  bool      _hexOutput;
  uint8_t   _length;
  uint32_t  _charCount;
};

// -- END OF FILE --
