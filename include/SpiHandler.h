#pragma once

#ifndef _MCP2515_SPI_H_
#define _MCP2515_SPI_H_

#include <stdint.h>

#define MCP2515_SPI_CLOCK 10000000U

#if defined(__cplusplus)
extern "C" {
#endif

void spi_init(uint8_t cc); // SPI initialization and CC pin selection
void spi_start();
void spi_end();
uint8_t spi_transfer(uint8_t inb);  // SPI xfer 1 byte

#if defined(__cplusplus)
} // Closing brace for extern C
#endif

#endif // _MCP2515_SPI_H_