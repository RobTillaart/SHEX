//
//    FILE: SHEX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library to generate hex dump over Serial
//    DATE: 2020-05-24
//     URL: https://github.com/RobTillaart/SHEX
//
//  HISTORY:
//  0.1.0   2020-05-24  initial version
//  0.1.1   2020-06-19  fix library.json
//  0.2.0   2021-01-07  Arduino-CI + unit tests + modifiers.
//  0.2.1   2021-12-28  update library.json, readme, license, minor edits
//  0.2.2   2022-05-27  fix #6 set default length
//                      add defines SHEX_DEFAULT_LENGTH + SHEX_MAX_LENGTH
//  0.2.3   2022-05-28  add setVTAB(vtab) getVTAB()
//                      add define SHEX_DEFAULT_VTAB
//  0.3.0   2022-05-28  breaking!  default HEX output instead of pass through.
//                      add get / setCountDigits() => #digits of count 4, 6 or 8 (4 = default)
//                      replaces get / setCounterFlag()
//                      add define SHEX_COUNTER_DIGITS + SHEX_MIN_LENGTH


#include "SHEX.h"


SHEX::SHEX(Print* stream, uint8_t length)
{
  _stream  = stream;
  reset();
  // force multiple of 4; max 32
  _length = ((length + 3) / 4) * 4;
  if (_length > SHEX_MAX_LENGTH)
  {
    _length = SHEX_MAX_LENGTH;
  }
  if (_length < SHEX_MIN_LENGTH)
  {
    _length = SHEX_MIN_LENGTH;
  }
};


void SHEX::reset()
{
  _hexOutput = true;
  _length    = SHEX_DEFAULT_LENGTH;
  _charCount = 0;
  _separator = ' ';
  _digits    = SHEX_COUNTER_DIGITS;
  _vtab      = SHEX_DEFAULT_VTAB;
}


///////////////////////////////////////////
//
// WRITE - the core
//
size_t SHEX::write(uint8_t c)
{
  //  PASS THROUGH MODE
  if (_hexOutput == false) return _stream->write(c);

  //  HEX MODE
  //  handle end of line and position number
  if ((_charCount % _length) == 0)
  {
    //  insert ASCII array here
    
    _stream->println();
    //  separator line every _vtab (default 8) lines
    if ((_charCount % (_length * _vtab)) == 0)
    {
      _stream->println();
    }

    //  next line
    if (_digits > 0)
    {
      uint32_t mask = 0xF000;
      if (_digits > 4) mask = 0xF00000;
      if (_digits > 6) mask = 0xF0000000;
      while((mask > 0xF) && (mask & _charCount) == 0)
      {
        _stream->print('0');
        mask >>= 4;
      }
      _stream->print(_charCount, HEX);
      _stream->print('\t');
    }
  }

  //  Print char as HEX
  if (c < 0x10) _stream->print('0');
  _stream->print(c, HEX);
  _stream->print(_separator);
  _charCount++;
  if ((_charCount % 4) == 0) _stream->print(_separator);

  return 1;
}


void SHEX::setHEX(bool hexOutput)
{
  _hexOutput = hexOutput;
  _charCount = 0;
  //  prevent change in middle of line
  _stream->println();
};


void SHEX::setBytesPerLine(const uint8_t length)
{
  // force multiple of 4; max 32
  _length = ((length + 3) / 4) * 4;
  if (_length > SHEX_MAX_LENGTH)
  {
    _length = SHEX_MAX_LENGTH;
  }
  if (_length < SHEX_MIN_LENGTH)
  {
    _length = SHEX_MIN_LENGTH;
  }
  _charCount = 0;
  //  prevent change in middle of line
  _stream->println();
}


void SHEX::setVTAB(uint8_t vtab)
{
  _vtab = vtab;
  _charCount = 0;
  //  prevent change in middle of line
  _stream->println();
};


void SHEX::setCountDigits(uint8_t digits) 
{
  _digits = digits;
  if (_digits == 0) return;
  if (_digits < 4) _digits = 4;
  if (_digits > 8) _digits = 8;
};


///////////////////////////////////////////////////
//
//  SHEXA
//
SHEXA::SHEXA(Print* stream, uint8_t length) : SHEX(stream, length)
{
}


size_t SHEXA::write(uint8_t c)
{
  // PASS THROUGH MODE
  if (_hexOutput == false) return _stream->write(c);

  //  HEX MODE
  //  handle end of line and position number
  if ((_charCount % _length) == 0)
  {
    //  printable ASCII column
    if (_charCount != 0) flushASCII();

    _stream->println();
    //  separator line every _vtab (default 8) lines
    if ((_charCount % (_length * _vtab)) == 0)
    {
      _stream->println();
    }

    //  next line
    if (_digits > 0)
    {
      uint32_t mask = 0xF000;
      if (_digits > 4) mask = 0xF00000;
      if (_digits > 6) mask = 0xF0000000;
      while((mask > 0xF) && (mask & _charCount) == 0)
      {
        _stream->print('0');
        mask >>= 4;
      }
      _stream->print(_charCount, HEX);
      _stream->print('\t');
    }
  }

  //  Print char as HEX
  if (c < 0x10) _stream->print('0');
  _stream->print(c, HEX);
  _stream->print(_separator);

  //  Store in _txtbuf
  _txtbuf[_charCount % _length] = isPrintable(c) ? c : '.';

  _charCount++;
  if ((_charCount % 4) == 0) _stream->print(_separator);

  return 1;
}


void SHEXA::flushASCII()
{
  for (uint8_t i = 0; i < _length; i++)
  {
    _stream->write(_txtbuf[i]);
    if ((i % 8) == 0)_stream->print("  ");
  }
}

// -- END OF FILE --

