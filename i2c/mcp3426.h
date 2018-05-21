#pragma once

#include "i2c.h"

//#define DEVICECODE (0x68)
#define DEVICECODE (0xD0)

typedef enum { CH1, CH2 } Channel;
typedef enum { CONTINUOUS, ONESHOT } ConversionMode;
typedef enum { R12BIT, R14BIT, R16BIT } Resolution;
typedef enum { GAINX1, GAINX2, GAINX4, GAINX8 } PGA;

typedef struct{
  union{
    uint8_t bits;
    struct{
      PGA            pga        : 2;
      Resolution     resolution : 2;
      ConversionMode mode       : 1;
      Channel        channel    : 2;
      uint8_t        ready      : 1;
    } reg;
  };
} Config;

class MCP3426{
public:
  MCP3426(I2CMaster& i2c, Config config): i2c(i2c), config(config){}

  void setConfig(Config config) {
    this->config = config;
  }
  uint16_t getValue(Channel ch)
  {
    uint8_t buff[2];

    this->config.reg.channel = ch;
    this->config.reg.ready = 1;
    
    this->i2c.write(DEVICECODE, &this->config.bits, 1); // ƒ`ƒƒƒ“ƒlƒ‹‘I‘ð
    _delay_us(30);
    this->i2c.read(DEVICECODE,  buff, sizeof(buff));

    return (buff[1] << 8) | buff[0];
  }
  
private:
  I2CMaster& i2c;
  Config config;
};
