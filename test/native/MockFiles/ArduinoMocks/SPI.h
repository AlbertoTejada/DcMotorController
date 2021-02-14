// Header for SPI Mock

#ifndef __SPI_h__
#define __SPI_h__

#include <gmock/gmock.h>
#include <stdint.h>

class SPISettings {
    uint32_t _a;
    uint8_t _b;
    uint8_t _c;
  public:
    SPISettings(uint32_t a, uint8_t b, uint8_t c): _a(a), _b(b), _c(c) {}
    SPISettings();
    bool operator==(const SPISettings& rhs)const {
      return _a == rhs._a && _b == rhs._b && _c == rhs._c;
    }
};

class SPI_ {
  public:
  
    void begin();
    void usingInterrupt(uint8_t );
    void notUsingInterrupt(uint8_t );
    void beginTransaction(SPISettings );
    uint8_t transfer(uint8_t );
    uint16_t transfer16(uint16_t );
    void transfer(void *, size_t );
    void endTransaction(void);
    void end();
    void setBitOrder(uint8_t);
    void setDataMode(uint8_t );
    void setClockDivider(uint8_t clockDiv);
    void attachInterrupt();
    void detachInterrupt();
};

extern SPI_ SPI;

class SPIMock {
  public:
    virtual ~SPIMock(){}  
    MOCK_METHOD(void, begin, ());
    MOCK_METHOD(void, usingInterrupt, (uint8_t));
    MOCK_METHOD(void, notUsingInterrupt, (uint8_t));
    MOCK_METHOD(void, beginTransaction, (SPISettings));
    MOCK_METHOD(uint8_t, transfer, (uint8_t));
    MOCK_METHOD(uint16_t, transfer16, (uint16_t));
    MOCK_METHOD(void, transfer, (void *, size_t));
    MOCK_METHOD(void, endTransaction, ());
    MOCK_METHOD(void, end, ());
    MOCK_METHOD(void, setBitOrder, (uint8_t));
    MOCK_METHOD(void, setDataMode, (uint8_t));
    MOCK_METHOD(void, setClockDivider, (uint8_t));
    MOCK_METHOD(void, attachInterrupt, ());
    MOCK_METHOD(void, detachInterrupt, ());
};

SPIMock* SPIMockInstance();
void releaseSPIMock();

#endif
