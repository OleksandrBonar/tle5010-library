#ifndef TLE5010_H
#define TLE5010_H

#include <Arduino.h>
#include <SPI.h>

// Base class
class tle5010
{
  public:
    int16_t x;
    int16_t y;
    tle5010();
    virtual void readXY() {};
    atan2Function atan2Func;
    atan2FunctionInteger atan2FuncInt;
    double readAngleRadians();
    double readAngleDegrees();
    int16_t readInteger();
};

// SPI class
class tle5010_spi: public tle5010
{
  private:
    volatile uint8_t* csO;
    uint8_t  csBM;
    uint8_t  csIBM;
  public:
    tle5010_spi(uint8_t _cs);
    void begin(atan2Function _atan2Func=_atan2default);
    void readXY();
    void setCS(uint8_t _cs);
};

#endif
