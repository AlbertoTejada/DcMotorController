#include "Mcp2515_Cfg.h"
#include "SpiHandler.h"
#include "Os_TimeServices.h"

ERROR_MODE setMode(const CANCTRL_REQOP_MODE mode)
{
    modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode);

    unsigned long endTime = os_timer_ms() + 10;
    uint8_t modeMatch = 0;
    while (os_timer_ms() < endTime) {
        uint8_t newmode = readRegister(MCP_CANSTAT);
        newmode &= CANSTAT_OPMOD;

        modeMatch = newmode == mode;

        if (modeMatch) {
            break;
        }
    }

    return modeMatch ? ERROR_MODE_OK : ERROR_MODE_FAIL;
}

uint8_t readRegister(const REGISTER reg)
{
    spi_start();
    spi_transfer(INSTRUCTION_READ);
    spi_transfer(reg);
    uint8_t ret = spi_transfer(0x00);
    spi_end();

    return ret;
}

void readRegisters(const REGISTER reg, uint8_t values[], const uint8_t n)
{
    spi_start();
    spi_transfer(INSTRUCTION_READ);
    spi_transfer(reg);
    // mcp2515 has auto-increment of address-pointer
    for (uint8_t i = 0; i < n; i++) {
        values[i] = spi_transfer(0x00);
    }
    spi_end();
}

void setRegister(const REGISTER reg, const uint8_t value)
{
    spi_start();
    spi_transfer(INSTRUCTION_WRITE);
    spi_transfer(reg);
    spi_transfer(value);
    spi_end();
}

void setRegisters(const REGISTER reg, const uint8_t values[], const uint8_t n)
{
    spi_start();
    spi_transfer(INSTRUCTION_WRITE);
    spi_transfer(reg);
    for (uint8_t i = 0; i < n; i++) {
        spi_transfer(values[i]);
    }
    spi_end();
}

void modifyRegister(const REGISTER reg, const uint8_t mask, const uint8_t data)
{
    spi_start();
    spi_transfer(INSTRUCTION_BITMOD);
    spi_transfer(reg);
    spi_transfer(mask);
    spi_transfer(data);
    spi_end();
}

void prepareId(uint8_t* buffer, const uint8_t ext, const uint32_t id)
{
    uint16_t canid = (uint16_t)(id & 0x0FFFF);

    if (ext) {
        buffer[MCP_EID0] = (uint8_t)(canid & 0xFF);
        buffer[MCP_EID8] = (uint8_t)(canid >> 8);
        canid = (uint16_t)(id >> 16);
        buffer[MCP_SIDL] = (uint8_t)(canid & 0x03);
        buffer[MCP_SIDL] += (uint8_t)((canid & 0x1C) << 3);
        buffer[MCP_SIDL] |= TXB_EXIDE_MASK;
        buffer[MCP_SIDH] = (uint8_t)(canid >> 5);
    }
    else {
        buffer[MCP_SIDH] = (uint8_t)(canid >> 3);
        buffer[MCP_SIDL] = (uint8_t)((canid & 0x07) << 5);
        buffer[MCP_EID0] = 0;
        buffer[MCP_EID8] = 0;
    }
}