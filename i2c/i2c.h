#pragma once

#include <avr/io.h>

#define T2_TWI 5
#define T4_TWI 4

// ATTiny85用ピン設定
#define PORT_USI     PORTB
#define DDR_USI      DDRB
#define PIN_USI      PINB
#define PORT_USI_SDA PORTB0
#define PORT_USI_SCL PORTB2
#define PIN_USI_SDA  PINB0
#define PIN_USI_SCL  PINB2

#define USISR_8BIT (1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|(0x0<<USICNT0)
#define USISR_1BIT (1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|(0xE<<USICNT0)

class I2CMaster{
 public:
  I2CMaster()
  {
    PORT_USI |= (1<<PIN_USI_SDA); // SDAプルアップ
    PORT_USI |= (1<<PIN_USI_SCL); // SDLプルアップ
  
    DDR_USI  |= (1<<PIN_USI_SCL); // SCL出力モード
    DDR_USI  |= (1<<PIN_USI_SDA); // SDA出力モード
  
    USIDR    =  0xFF;                                // USIデータレジスタ初期化
    USICR    =  (0<<USISIE)|(0<<USIOIE)|             // 割り込み無効
                (1<<USIWM1)|(0<<USIWM0)|             // 2Wireモード
                (1<<USICS1)|(0<<USICS0)|(1<<USICLK)| // 
                (0<<USITC);
    USISR   =   (1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)| 
                (0x0<<USICNT0);                                     
  }

  uint8_t read(uint8_t address, uint8_t *data, uint8_t size)
  {
    startCondition();
    // address指定
    this->write1Byte(address | 1);
    
    // size分受信
    for (int i = 0; i < size; i++) {
      DDR_USI &= ~_BV(PIN_USI_SDA);
      data[i] = this->transfer(USISR_8BIT);
      if (i == size-1) {
	USIDR = 0xFF;
      } else {
	USIDR = 0x00;
      }
      this->transfer(USISR_1BIT);
    }
    endCondition();
    return true;
  }

  uint8_t write(uint8_t address, uint8_t *data, uint8_t size)
  {
    startCondition();
    // address指定
    this->write1Byte(address);

    // size分送信
    for (int i = 0; i < size; i++) {
      this->write1Byte(data[i]);
    }
    endCondition();
    return true;
  }
  
  inline void write1Byte(uint8_t data)
  {
    // 1byte送信
    PORT_USI &= ~_BV(PIN_USI_SCL);
    USIDR = data;
    this->transfer(USISR_8BIT);

    // 1bit受信(NACK)
    USIDR &= ~_BV(PIN_USI_SDA);
    this->transfer(USISR_1BIT);
  }
  
 private:
  bool transfer(uint8_t temp)
  {
    USISR = temp;
    temp  = (0<<USISIE) |(0<<USIOIE) |
            (1<<USIWM1) |(0<<USIWM0) |
            (1<<USICS1) |(0<<USICS0) |(1<<USICLK) |
            (1<<USITC);
    do {
      _delay_us(T2_TWI);
      USICR = temp;
      loop_until_bit_is_set(PIN_USI, PIN_USI_SCL);
      _delay_us(T4_TWI);
      USICR = temp;
    } while( bit_is_clear(USISR, USIOIF) );
    _delay_us(T2_TWI);
    temp = USIDR;
    USIDR = 0xFF;
    DDR_USI |= _BV(PIN_USI_SDA);
    return temp;
  }
  
  bool startCondition()
  {
    // SCL Release
    PORT_USI |= _BV(PIN_USI_SCL);
    loop_until_bit_is_set(PORT_USI, PIN_USI_SCL);
    _delay_us(T2_TWI);

    // SDA OFF
    PORT_USI &= ~_BV(PIN_USI_SDA);
    _delay_us(T4_TWI);

    // SCL OFF
    PORT_USI &= ~_BV(PIN_USI_SCL);
    // SDA Release
    PORT_USI |= _BV(PIN_USI_SDA);
    return true;
  }
  bool endCondition()
  {
    // SDA OFF
    PORT_USI &= ~_BV(PIN_USI_SDA);
    // SDA Release
    PORT_USI |= _BV(PIN_USI_SCL);
    loop_until_bit_is_set(PIN_USI, PIN_USI_SCL);
    _delay_us(T4_TWI);

    // SDA Release
    PORT_USI |= _BV(PIN_USI_SDA);
    _delay_us(T2_TWI);
    return true;
  }
  
};
