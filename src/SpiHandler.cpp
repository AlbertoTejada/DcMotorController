#include "Arduino.h"
#include <SPI.h>
#include "SpiHandler.h"

uint8_t mcp2515_slave_pin = 10;

void spi_init(uint8_t cs)
{
	mcp2515_slave_pin = cs;

	SPI.begin();
	pinMode(mcp2515_slave_pin, OUTPUT);
	spi_end();
}

void spi_start()
{
	SPI.beginTransaction(SPISettings(MCP2515_SPI_CLOCK, MSBFIRST, SPI_MODE0));
	digitalWrite(mcp2515_slave_pin, LOW);
}

void spi_end()
{
	digitalWrite(mcp2515_slave_pin, HIGH);
	SPI.endTransaction();
}

uint8_t spi_transfer(uint8_t inb)
{
	uint8_t value = SPI.transfer(inb);
	return value;
}