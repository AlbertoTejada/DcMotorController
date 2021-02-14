#ifndef __Wire_h__
#define __Wire_h__
#include <stdint.h>
#include <gmock/gmock.h>
#include <string.h>

#define BUFFER_LENGTH 32
#define I2C2 0x4819c000
#define I2C1 0x00000000
#define WIRE_INTERFACES_COUNT 1

class Wire_ {
  public:
    void begin();
    void begin(uint8_t);
    void begin(int);
    void beginTransmission(uint8_t);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    uint8_t write(uint8_t);
    uint8_t write(char*);
    uint8_t write(uint8_t, uint8_t);
    uint8_t available(void);
    uint8_t read(void);
    void onReceive(uint8_t*);
    void onRequest(uint8_t*);
    inline size_t write(unsigned long n) {
      return write((uint8_t)n);
    }
    inline size_t write(long n) {
      return write((uint8_t)n);
    }
    inline size_t write(unsigned int n) {
      return write((uint8_t)n);
    }
    inline size_t write(int n) {
      return write((uint8_t)n);
    }
};
extern Wire_ Wire;

class WireMock {
  public:
    MOCK_METHOD(void, begin, ());
    MOCK_METHOD(void, begin, (uint8_t));
    MOCK_METHOD(void, begin, (int));
    MOCK_METHOD(void, beginTransmission, (uint8_t));
    MOCK_METHOD(uint8_t, endTransmission, ());
    MOCK_METHOD(uint8_t, endTransmission, (uint8_t));
    MOCK_METHOD(uint8_t, requestFrom, (uint8_t, uint8_t));
    MOCK_METHOD(uint8_t, requestFrom, (uint8_t, uint8_t, uint8_t));
    MOCK_METHOD(uint8_t, write, (uint8_t));
    MOCK_METHOD(uint8_t, write, (char*));
    MOCK_METHOD(uint8_t, write, (uint8_t, uint8_t));
    MOCK_METHOD(uint8_t, available, ());
    MOCK_METHOD(uint8_t, read, ());
    MOCK_METHOD(void, onReceive, (uint8_t*));
    MOCK_METHOD(void, onRequest, (uint8_t*));
};

WireMock* WireMockInstance();
void releaseWireMock();

#endif
