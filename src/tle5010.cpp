#include <tle5010.h>

tle5010::tle5010()
{
}

double tle5010::readAngleRadians()
{
  readXY();

  return atan2(y, x);
}

double tle5010::readAngleDegrees()
{
  return readAngleRadians() * (180 / PI);
}

int16_t tle5010::readInteger()
{
  readXY();
  
  return atan2Int16(y, x);
}

tle5010_spi::tle5010_spi(uint8_t _cs)
{
  csBM = _cs;
}

void tle5010_spi::begin()
{
   setCS(csBM);   
   SPI.begin();
}

void tle5010_spi::setCS(uint8_t _cs)
{
  // caching CS PORT/DDR for faster IO
  csO = portOutputRegister(digitalPinToPort(_cs));
  csBM = digitalPinToBitMask(_cs);
  csIBM = ~csBM;

   *csO |= csBM;  // CS high
   *(portModeRegister(digitalPinToPort(_cs))) |= csBM;  // =pinMode(_cs, OUTPUT);
}

void tle5010_spi::readXY()
{
  SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE1));	// speed

  *csO &= csIBM;  // CS low

  #ifndef __TLE5010_TEST_MODE
    // command for reading 4 bytes X&Y
    // 10001100 = 1(read) 0001(register #1) 100 (4 bytes)
    SPI.transfer16(0x008c);
  #else
    // testmode: command for reading 4 reserved bytes (expected FF 00 00 00)
    // 11000100 = 1(read) 1000(register #8) 100 (4 bytes)
    SPI.transfer16(0x00c4);
  #endif

  // reading bytes

  ((uint8_t*)&x)[0] = SPI.transfer(0xff);
  ((uint8_t*)&x)[1] = SPI.transfer(0xff);
  ((uint8_t*)&y)[0] = SPI.transfer(0xff);
  ((uint8_t*)&y)[1] = SPI.transfer(0xff);

  *csO |= csBM; // CS high
  
  SPI.endTransaction();
}
