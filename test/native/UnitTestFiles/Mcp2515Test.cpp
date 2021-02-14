//#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "SPI.h"
#include "Arduino.h"
#include "Mcp2515.h"

// Common parameters:
static const uint8_t _CS = 10;
static const uint32_t SPI_CLOCK = 10000000U;
static const SPISettings settings(SPI_CLOCK, MSBFIRST, SPI_MODE0);

// Registers mask definitions:
static const uint8_t CANCTRL_REQOP = 0xE0;
static const uint8_t CANCTRL_ABAT = 0x10;
static const uint8_t CANCTRL_OSM = 0x08;
static const uint8_t CANCTRL_CLKEN = 0x04;
static const uint8_t CANCTRL_CLKPRE = 0x03;
static const uint8_t CNF3_SOF = 0x80;
static const uint8_t TXB_ABTF = 0x40;
static const uint8_t TXB_MLOA = 0x20;
static const uint8_t TXB_TXERR = 0x10;
static const uint8_t TXB_TXREQ = 0x08;
static const uint8_t TXB_TXIE = 0x04;
static const uint8_t TXB_TXP = 0x03;
static const uint8_t CANINTF_RX0IF = 0x01;
static const uint8_t CANINTF_RX1IF = 0x02;

// Operation modes:
static const uint8_t CANCTRL_REQOP_CONFIG = 128U;
static const uint8_t CANCTRL_REQOP_LISTENONLY = 96U;
static const uint8_t CANCTRL_REQOP_SLEEP = 32U;
static const uint8_t CANCTRL_REQOP_LOOPBACK = 64U;
static const uint8_t CANCTRL_REQOP_NORMAL = 0U;

// Instructuions definitions:
static const uint8_t INSTRUCTION_RESET = 192U;
static const uint8_t INSTRUCTION_WRITE = 2U;
static const uint8_t INSTRUCTION_BITMOD = 5U;
static const uint8_t INSTRUCTION_READ = 3U;
static const uint8_t INSTRUCTION_READ_STATUS = 160U;

// Registers definitions:
static const uint8_t MCP_TXB0CTRL = 48U;
static const uint8_t MCP_TXB1CTRL = 64U;
static const uint8_t MCP_TXB2CTRL = 80U;
static const uint8_t MCP_RXB0CTRL = 96U;
static const uint8_t MCP_RXB1CTRL = 112U;
static const uint8_t MCP_CANINTE = 43U;
static const uint8_t MCP_CANCTRL = 15U;
static const uint8_t MCP_CANSTAT = 14U;
static const uint8_t MCP_RXF0SIDH = 0U;
static const uint8_t MCP_RXF1SIDH = 4U;
static const uint8_t MCP_RXF2SIDH = 8U;
static const uint8_t MCP_RXF3SIDH = 16U;
static const uint8_t MCP_RXF4SIDH = 20U;
static const uint8_t MCP_RXF5SIDH = 24U;
static const uint8_t MCP_RXM0SIDH = 32U;
static const uint8_t MCP_RXM1SIDH = 36U;
static const uint8_t MCP_CNF3 = 40U;
static const uint8_t MCP_CNF2 = 41U;
static const uint8_t MCP_CNF1 = 42U;
static const uint8_t MCP_TXB0SIDH = 49U;
static const uint8_t MCP_TXB0DATA = 54U;
static const uint8_t MCP_TXB1SIDH = 65U;
static const uint8_t MCP_TXB1DATA = 70U;
static const uint8_t MCP_TXB2SIDH = 81U;
static const uint8_t MCP_TXB2DATA = 86U;
static const uint8_t MCP_RXB0SIDH = 97U;
static const uint8_t MCP_RXB0DATA = 102U;
static const uint8_t MCP_RXB1SIDH = 114U;
static const uint8_t MCP_RXB1DATA = 118U;
static const uint8_t MCP_CANINTF = 44U;
static const uint8_t MCP_EFLG = 45U;

TEST(Mcp2515, Constructor)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	using ::testing::InSequence;
	InSequence s;

	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, reset)
{
	// Required parameters:;
	static const uint8_t MCP_CANINTE_value = (01U | 02U | 32U | 128U);
	static const uint8_t MCP_RXB0CTRL_mask = (96U | 04U | 03U);
	static const uint8_t MCP_RXB0CTRL_val  = (00U | 04U | 00U);
	static const uint8_t MCP_RXB1CTRL_mask = (96U | 07U);
	static const uint8_t MCP_RXB1CTRL_val  = (00U | 01U);

	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();
	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;
	uint8_t filters[] = {	MCP_RXF0SIDH,
							MCP_RXF1SIDH,
							MCP_RXF2SIDH,
							MCP_RXF3SIDH,
							MCP_RXF4SIDH,
							MCP_RXF5SIDH };

	uint8_t masks[] = { MCP_RXM0SIDH, MCP_RXM1SIDH };

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */

	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);


	/* reset() */

	// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_RESET)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	EXPECT_CALL(*arduinoMock, delay(10)).Times(1); // 10 ms, hardcoded

	// setRegisters(MCP_TXB0CTRL, zeros, 14)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_TXB0CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0U)).Times(14); // n = 14 harcoded
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// setRegisters(MCP_TXB1CTRL, zeros, 14)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_TXB1CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0U)).Times(14); // n = 14 harcoded
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// setRegisters(MCP_TXB2CTRL, zeros, 14)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_TXB2CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0U)).Times(14); // n = 14 harcoded
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// setRegister(MCP_RXB0CTRL, 0)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXB0CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0U)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// setRegister(MCP_RXB1CTRL, 0)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXB1CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0U)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//setRegister(MCP_CANINTE, CANINTF_RX0IF | CANINTF_RX1IF | CANINTF_ERRIF | CANINTF_MERRF);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANINTE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANINTE_value)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//modifyRegister(MCP_RXB0CTRL,
	//	RXBnCTRL_RXM_MASK | RXB0CTRL_BUKT | RXB0CTRL_FILHIT_MASK,
	//	RXBnCTRL_RXM_STDEXT | RXB0CTRL_BUKT | RXB0CTRL_FILHIT);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXB0CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXB0CTRL_mask)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXB0CTRL_val)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//modifyRegister(MCP_RXB1CTRL,
	//	RXBnCTRL_RXM_MASK | RXB1CTRL_FILHIT_MASK,
	//	RXBnCTRL_RXM_STDEXT | RXB1CTRL_FILHIT);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXB1CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXB1CTRL_mask)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXB1CTRL_val)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	for (int i = 0; i < 6; i++)
	{
		bool ext = (i == 1);
		uint8_t reg = filters[i];
		// setFilter(filters[i], ext, 0);
			// setConfigMode()
				// setMode(CANCTRL_REQOP_CONFIG)
					// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode);
						// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
		EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
		EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
		EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_CONFIG)).Times(1);
						// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);

					// millis()
		EXPECT_CALL(*arduinoMock, millis()).Times(2)
											.WillOnce(Return(0))
											.WillOnce(Return(5));
					// readRegister(MCP_CANSTAT);
						// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
		EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
		EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_CONFIG));
						// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);
			// setRegisters(reg, tbufdata, 4)
				// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
		EXPECT_CALL(*spiMock, transfer(reg)).Times(1);
		EXPECT_CALL(*spiMock, transfer(_)).Times(4); // set four registers, hard coded
				// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	}

	for (int i = 0; i < 2; i++)
	{
		uint8_t reg = masks[i];
		// setFilterMask(masks[i], true, 0);
			// setConfigMode()
				// setMode(CANCTRL_REQOP_CONFIG)
					// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode);
						// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
		EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
		EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
		EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_CONFIG)).Times(1);
						// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);

					// millis()
		EXPECT_CALL(*arduinoMock, millis()).Times(2)
			.WillOnce(Return(0))
			.WillOnce(Return(5));
					// readRegister(MCP_CANSTAT);
						// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
		EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
		EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_CONFIG));
						// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);

		// setRegisters(reg, tbufdata, 4)
			// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
		EXPECT_CALL(*spiMock, transfer(reg)).Times(1);
		EXPECT_CALL(*spiMock, transfer(_)).Times(4); // set four registers, hard coded
				// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	}

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	// _error = mcp2515.reset();
	_error = reset();

	EXPECT_EQ(_error, expected_error);

	releaseSPIMock();
	releaseArduinoMock();	
}

TEST(Mcp2515, setConfigMode)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();
	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setConfigMode */
	// setMode(CANCTRL_REQOP_CONFIG)
		// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode)
			// startSPI
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_CONFIG)).Times(1);
			// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
		// readRegister(MCP_CANSTAT);
			// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_CONFIG));
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setConfigMode();
	_error = setConfigMode();

	EXPECT_EQ(_error, expected_error);

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, setListenOnlyMode)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();
	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setConfigMode */
	// setMode(CANCTRL_REQOP_LISTENONLY)
		// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode)
			// startSPI
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_LISTENONLY)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
	// readRegister(MCP_CANSTAT);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_LISTENONLY));
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setListenOnlyMode();
	_error = setListenOnlyMode();

	EXPECT_EQ(_error, expected_error);

	releaseSPIMock();
	releaseArduinoMock();	
}

TEST(Mcp2515, setSleepMode)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();
	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setConfigMode */
	// setMode(CANCTRL_REQOP_SLEEP)
		// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode)
			// startSPI
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_SLEEP)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
	// readRegister(MCP_CANSTAT);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_SLEEP));
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setSleepMode();
	_error = setSleepMode();

	EXPECT_EQ(_error, expected_error);

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, setLoopbackMode)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();
	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setConfigMode */
	// setMode(CANCTRL_REQOP_LOOPBACK)
		// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode)
			// startSPI
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_LOOPBACK)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
	// readRegister(MCP_CANSTAT);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_LOOPBACK));
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setLoopbackMode();
	_error = setLoopbackMode();

	EXPECT_EQ(_error, expected_error);

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, setNormalMode)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();
	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setConfigMode */
	// setMode(CANCTRL_REQOP_NORMAL)
		// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode)
			// startSPI
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_NORMAL)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
	// readRegister(MCP_CANSTAT);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_NORMAL));
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setNormalMode();
	_error = setNormalMode();

	EXPECT_EQ(_error, expected_error);

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, setClkOut)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();
	
	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;
	CAN_CLKOUT clock_divisor;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setClkOut CLKOUT_DISABLE */
	clock_divisor = CAN_CLKOUT(CLKOUT_DISABLE);

	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, 0x00)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CNF3, CNF3_SOF, CNF3_SOF);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CNF3)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CNF3_SOF)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CNF3_SOF)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setClkOut(clock_divisor);
	_error = setClkOut(clock_divisor);

	EXPECT_EQ(_error, expected_error);

	/* setClkOut CLKOUT_DIV1 */
	clock_divisor = CAN_CLKOUT(CLKOUT_DIV1);

	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKPRE, divisor)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKPRE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(clock_divisor)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, CANCTRL_CLKEN)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CNF3, CNF3_SOF, 0x00)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CNF3)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CNF3_SOF)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//_error = mcp2515.setClkOut(clock_divisor);
	_error = setClkOut(clock_divisor);

	/* setClkOut CLKOUT_DIV2 */
	clock_divisor = CAN_CLKOUT(CLKOUT_DIV2);

	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKPRE, divisor)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKPRE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(clock_divisor)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, CANCTRL_CLKEN)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CNF3, CNF3_SOF, 0x00)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CNF3)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CNF3_SOF)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//_error = mcp2515.setClkOut(clock_divisor);
	_error = setClkOut(clock_divisor);

	/* setClkOut CLKOUT_DIV4 */
	clock_divisor = CAN_CLKOUT(CLKOUT_DIV4);

	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKPRE, divisor)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKPRE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(clock_divisor)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, CANCTRL_CLKEN)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CNF3, CNF3_SOF, 0x00)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CNF3)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CNF3_SOF)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//_error = mcp2515.setClkOut(clock_divisor);
	_error = setClkOut(clock_divisor);

	/* setClkOut CLKOUT_DIV8 */
	clock_divisor = CAN_CLKOUT(CLKOUT_DIV8);

	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKPRE, divisor)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKPRE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(clock_divisor)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, CANCTRL_CLKEN)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_CLKEN)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// modifyRegister(MCP_CNF3, CNF3_SOF, 0x00)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CNF3)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CNF3_SOF)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//_error = mcp2515.setClkOut(clock_divisor);
	_error = setClkOut(clock_divisor);

	releaseSPIMock();
	releaseArduinoMock();

}

TEST(Mcp2515, setBitrate)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;
	//CAN_CLKOUT clock_divisor;

	uint8_t cfg1 = MCP_8MHz_5kBPS_CFG1;
	uint8_t cfg2 = MCP_8MHz_5kBPS_CFG2;
	uint8_t cfg3 = MCP_8MHz_5kBPS_CFG3;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setBitrate */
	// setConfigMode()
		// setMode(CANCTRL_REQOP_CONFIG)
			// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode)
				// startSPI
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_CONFIG)).Times(1);
				// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
		// readRegister(MCP_CANSTAT);
			// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_CONFIG));
			// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// setRegister(MCP_CNF1, cfg1)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CNF1)).Times(1);
	EXPECT_CALL(*spiMock, transfer(cfg1)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// setRegister(MCP_CNF2, cfg2)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CNF2)).Times(1);
	EXPECT_CALL(*spiMock, transfer(cfg2)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// setRegister(MCP_CNF3, cfg3)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CNF3)).Times(1);
	EXPECT_CALL(*spiMock, transfer(cfg3)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);


	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setBitrate(CAN_5KBPS, MCP_8MHZ);
	_error = setBitrate(CAN_5KBPS, MCP_8MHZ);

	EXPECT_EQ(_error, expected_error);

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, setFilterMask)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;
	MCP2515_MASK mask;
	const uint32_t ulData = 0x11223344;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setFilterMask  MASK0*/
	mask = MASK0;
		// setConfigMode()
			// setMode(CANCTRL_REQOP_CONFIG)
				// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode);
					// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_CONFIG)).Times(1);
					// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

				// millis()
	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
				// readRegister(MCP_CANSTAT);
					// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_CONFIG));
					// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

		// setRegisters(reg, tbufdata, 4)
			// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXM0SIDH)).Times(1);
	EXPECT_CALL(*spiMock, transfer(_)).Times(4); // set four registers, hard coded
			// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setFilterMask(mask, true, ulData);
	_error = setFilterMask(mask, true, ulData);

	/* setFilterMask  MASK0*/
	mask = MASK1;
	// setConfigMode()
		// setMode(CANCTRL_REQOP_CONFIG)
			// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode);
				// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_CONFIG)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// millis()
	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
	// readRegister(MCP_CANSTAT);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_CONFIG));
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// setRegisters(reg, tbufdata, 4)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_RXM1SIDH)).Times(1);
	EXPECT_CALL(*spiMock, transfer(_)).Times(4); // set four registers, hard coded
			// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//_error = mcp2515.setFilterMask(mask, true, ulData);
	_error = setFilterMask(mask, true, ulData);

	EXPECT_EQ(_error, expected_error);

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, setFilter)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;
	MCP2515_RXF rxf[] = {	RXF0,
							RXF1,
							RXF2,
							RXF3,
							RXF4,
							RXF5};

	uint8_t filters[] = { MCP_RXF0SIDH,
							MCP_RXF1SIDH,
							MCP_RXF2SIDH,
							MCP_RXF3SIDH,
							MCP_RXF4SIDH,
							MCP_RXF5SIDH };
	bool ext = true;
	const uint32_t ulData = 0x11223344;

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* setFilter(RXF0, true, 0) */
	MCP2515_RXF _rxf = rxf[0];
	uint8_t reg = filters[0];
		// setConfigMode()
			// setMode(CANCTRL_REQOP_CONFIG)
				// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode);
					// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
	EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_CONFIG)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// millis()
	EXPECT_CALL(*arduinoMock, millis()).Times(2)
		.WillOnce(Return(0))
		.WillOnce(Return(5));
	// readRegister(MCP_CANSTAT);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_CONFIG));
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
	// setRegisters(reg, tbufdata, 4)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(reg)).Times(1);
	EXPECT_CALL(*spiMock, transfer(_)).Times(4); // set four registers, hard coded
			// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.setFilter(_rxf, ext, ulData);
	_error = setFilter(_rxf, ext, ulData);
	EXPECT_EQ(_error, expected_error);

	for (int i = 1; i < 6; i++)
	{
		uint8_t reg = filters[i];
		MCP2515_RXF _rxf = rxf[i];
		// setFilter(filters[i], ext, 0);
			// setConfigMode()
				// setMode(CANCTRL_REQOP_CONFIG)
					// modifyRegister(MCP_CANCTRL, CANCTRL_REQOP, mode);
						// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
		EXPECT_CALL(*spiMock, transfer(MCP_CANCTRL)).Times(1);
		EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP)).Times(1);
		EXPECT_CALL(*spiMock, transfer(CANCTRL_REQOP_CONFIG)).Times(1);
		// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);

		// millis()
		EXPECT_CALL(*arduinoMock, millis()).Times(2)
			.WillOnce(Return(0))
			.WillOnce(Return(5));
		// readRegister(MCP_CANSTAT);
			// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
		EXPECT_CALL(*spiMock, transfer(MCP_CANSTAT)).Times(1);
		EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(CANCTRL_REQOP_CONFIG));
		// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);
		// setRegisters(reg, tbufdata, 4)
			// startSPI()
		EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

		EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
		EXPECT_CALL(*spiMock, transfer(reg)).Times(1);
		EXPECT_CALL(*spiMock, transfer(_)).Times(4); // set four registers, hard coded
				// endSPI()
		EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
		EXPECT_CALL(*spiMock, endTransaction()).Times(1);

		//_error = mcp2515.setFilter(_rxf, ext, ulData);
		_error = setFilter(_rxf, ext, ulData);
		EXPECT_EQ(_error, expected_error);
	}

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, sendMessage)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();
	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;

	MCP2515_TXBn txbn;

	const struct can_frame frame =
	{
		0x12345678,
		8,
		{0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}
	};
	const struct can_frame* frame_prt = &frame;

	static const struct TXBn_REGS {
		uint8_t CTRL;
		uint8_t SIDH;
		uint8_t DATA;
	} TXB[3] = {
		{MCP_TXB0CTRL, MCP_TXB0SIDH, MCP_TXB0DATA},
		{MCP_TXB1CTRL, MCP_TXB1SIDH, MCP_TXB1DATA},
		{MCP_TXB2CTRL, MCP_TXB2SIDH, MCP_TXB2DATA}
	};

	txbn = TXB0;
	const struct TXBn_REGS* txbuf = &TXB[txbn];

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* SEND MESSAGE */

	// setRegisters(txbuf->SIDH, data, 5 + frame->can_dlc)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_WRITE)).Times(1);
	EXPECT_CALL(*spiMock, transfer(txbuf->SIDH)).Times(1);
	EXPECT_CALL(*spiMock, transfer(_)).Times(5 + frame_prt->can_dlc);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// modifyRegister(txbuf->CTRL, TXB_TXREQ, TXB_TXREQ);;
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(txbuf->CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(TXB_TXREQ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(TXB_TXREQ)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);
;
	// uint8_t ctrl = readRegister(txbuf->CTRL)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(txbuf->CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return((uint8_t)0));
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.sendMessage(txbn, frame_prt);
	_error = sendMessageToRegister(txbn, frame_prt);
	EXPECT_EQ(_error, expected_error);
	// TODO: completar este test para comprobar todos los campor del mensaje

	releaseSPIMock();
	releaseArduinoMock();
}

TEST(Mcp2515, readMessage)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	MCP2515_ERROR _error;
	MCP2515_ERROR expected_error = ERROR_OK;
	struct can_frame frame =
	{
		0x12345678,
		8,
		{0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}
	};
	struct can_frame* frame_prt = &frame;
	static const struct RXBn_REGS {
		uint8_t CTRL;
		uint8_t SIDH;
		uint8_t DATA;
		uint8_t  CANINTF_RXnIF;
	} RXB[2] = {
		{MCP_RXB0CTRL, MCP_RXB0SIDH, MCP_RXB0DATA, CANINTF_RX0IF},
		{MCP_RXB1CTRL, MCP_RXB1SIDH, MCP_RXB1DATA, CANINTF_RX1IF}
	};

	MCP2515_RXBn rxbn = RXB0;
	const struct RXBn_REGS* rxb = &RXB[rxbn];

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* read MESSAGE */
	// readRegisters(rxb->SIDH, tbufdata, 5);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(rxb->SIDH)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(5).WillOnce(Return(0x11))
		.WillOnce(Return(0x22))
		.WillOnce(Return(0x33))
		.WillOnce(Return(0x44))
		.WillOnce(Return(0x08)); //dlc = 8

		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// uint8_t ctrl = readRegister(rxb->CTRL)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(rxb->CTRL)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(0x00));

		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);


	// readRegisters(rxb->DATA, frame->data, dlc)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(rxb->DATA)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(8).WillOnce(Return(0x11))
		.WillOnce(Return(0x22))
		.WillOnce(Return(0x33))
		.WillOnce(Return(0x44))
		.WillOnce(Return(0x55))
		.WillOnce(Return(0x66))
		.WillOnce(Return(0x77))
		.WillOnce(Return(0x88));

		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	// modifyRegister(MCP_CANINTF, rxb->CANINTF_RXnIF, 0)
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_BITMOD)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_CANINTF)).Times(1);
	EXPECT_CALL(*spiMock, transfer(rxb->CANINTF_RXnIF)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0)).Times(1);
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//_error = mcp2515.readMessage(rxbn, frame_prt);
	_error = readMessageFromRegister(rxbn, frame_prt);
	EXPECT_EQ(_error, expected_error);
	EXPECT_EQ(frame.can_dlc, 0x08);
	// TODO: completar este test para comprobar todos los campor del mensaje

	releaseSPIMock();
	releaseArduinoMock();	
}

TEST(Mcp2515, getStatus)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* getStatus() */
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ_STATUS)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(0xCC));

	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//uint8_t return_value = mcp2515.getStatus();
	uint8_t return_value = getStatus();
	EXPECT_EQ(return_value, 0xCC);

	releaseSPIMock();
	releaseArduinoMock();	
}

TEST(Mcp2515, checkReceive)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* getStatus() */
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ_STATUS)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(0x03));

	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//uint8_t return_value = mcp2515.checkReceive();
	uint8_t return_value = checkReceive();
	EXPECT_EQ(return_value, 1);

	/* getStatus() */
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ_STATUS)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(0x04));

		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//return_value = mcp2515.checkReceive();
	return_value = checkReceive();
	EXPECT_EQ(return_value, 0);

	releaseSPIMock();
	releaseArduinoMock();	
}

TEST(Mcp2515, getErrorFlags)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* getErrorFlags() */
	// readRegister(MCP_EFLG);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_EFLG)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(0xCC));
		// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//uint8_t return_value = mcp2515.getErrorFlags();
	uint8_t return_value = getErrorFlags();
	EXPECT_EQ(return_value, 0xCC);

	releaseSPIMock();
	releaseArduinoMock();	
}

TEST(Mcp2515, checkError)
{
	SPIMock* spiMock = SPIMockInstance();
	ArduinoMock* arduinoMock = arduinoMockInstance();

	using ::testing::InSequence;
	using ::testing::Return;
	InSequence s;

	/* CONSTRUCTOR */
	EXPECT_CALL(*spiMock, begin()).Times(1);
	EXPECT_CALL(*arduinoMock, pinMode(_CS, OUTPUT)).Times(1);
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	/* checkError() */

	// getErrorFlags()
		// readRegister(MCP_EFLG);
			// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_EFLG)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(0x01));
			// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//MCP2515 mcp2515(_CS);
	mcp2515_init(_CS);
	//uint8_t return_value = mcp2515.checkError();
	uint8_t return_value = checkError();
	EXPECT_EQ(return_value, 0x00);

	// readRegister(MCP_EFLG);
		// startSPI()
	EXPECT_CALL(*spiMock, beginTransaction(settings)).Times(1);
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, LOW)).Times(1);

	EXPECT_CALL(*spiMock, transfer(INSTRUCTION_READ)).Times(1);
	EXPECT_CALL(*spiMock, transfer(MCP_EFLG)).Times(1);
	EXPECT_CALL(*spiMock, transfer(0x00)).Times(1).WillOnce(Return(0x08));
	// endSPI()
	EXPECT_CALL(*arduinoMock, digitalWrite(_CS, HIGH)).Times(1);
	EXPECT_CALL(*spiMock, endTransaction()).Times(1);

	//return_value = mcp2515.checkError();
	return_value = checkError();
	EXPECT_EQ(return_value, 0x01);

	releaseSPIMock();
	releaseArduinoMock();
}