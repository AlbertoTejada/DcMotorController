
#include <iostream>
#include <stdio.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"
//#include "Fixture.h"
#include "/home/alberto/Documents/PlatformIO/Projects/PlatformIO_project/test/native/MockFiles/Fixture.h"
#include "sysenv.h"
#include "protocol.c"

using namespace EmbeddedC;
using namespace ::testing;



namespace EmbeddedCUnitTest {

class ProtocolTest : public TestFixture
{
public:
	ProtocolTest() : TestFixture(new ModuleMock)
	{
		protocol_init();
	}
};

void reset_line(void){
	uint8_t i;
	for(i = 0; i <= LINE_BUFFER_SIZE; i++){
		line[i] = 0; 
	}	
}


TEST_F(ProtocolTest, SerialWriteTest_001)
{
	// Force the expectad calls to match also the order:
	using ::testing::InSequence;
	InSequence s;

	// Define the sequence for the serial write:
	EXPECT_CALL(*_serial, serial_write('a')).Times(1);
	EXPECT_CALL(*_serial, serial_write('b')).Times(1);
	EXPECT_CALL(*_serial, serial_write('c')).Times(1);
	EXPECT_CALL(*_serial, serial_write('d')).Times(1);
	EXPECT_CALL(*_serial, serial_write('e')).Times(1);
	EXPECT_CALL(*_serial, serial_write('f')).Times(1);
	EXPECT_CALL(*_serial, serial_write('\0')).Times(1);

	char frame[6] = {'a', 'b', 'c', 'd', 'e', 'f'};	 
	protocol_write(frame, (uint8_t)6);
}

TEST_F(ProtocolTest, SerialWriteTest_002)
{ 
	// Force the expectad calls to match also the order:
	using ::testing::InSequence;
	InSequence s;

	// Define the sequence for the serial write:
	EXPECT_CALL(*_serial, serial_write('a')).Times(1);
	EXPECT_CALL(*_serial, serial_write('b')).Times(1);
	EXPECT_CALL(*_serial, serial_write('c')).Times(1);
	EXPECT_CALL(*_serial, serial_write('d')).Times(0);
	EXPECT_CALL(*_serial, serial_write('e')).Times(0);
	EXPECT_CALL(*_serial, serial_write('f')).Times(0);
	EXPECT_CALL(*_serial, serial_write('\0')).Times(1);

	char frame[6] = {'a', 'b', 'c', 'd', 'e', 'f'};	 
	protocol_write(frame, (uint8_t)3);
}

TEST_F(ProtocolTest, SerialReadTest_001)
{ 
	/*
	Validate the correct reception of a complete correct message
	*/

	// For the side effects mocking of the serial_reed:
	using ::testing::SetArgPointee;

	// Reset the related variables:
	reset_line();
	protocol_init();

	// Define auxiliar variables for the serial read:
	uint8_t idx;
	char c[7] = {(char)MASTER_01_ID,
				 (char)'a',
				 (char)'b',
				 (char)'c',
				 (char)'d',
				 (char)'e',
				 (char)'\0'};

	// Verify the initial condition:
	ASSERT_EQ(msglen, 0);
	ASSERT_EQ(char_counter,0);
	ASSERT_THAT(line, Each(0));

	// Set the expeted behaviour of the read function:
	EXPECT_CALL(*_serial, serial_read(_, _)).Times(7)
		.WillOnce(DoAll(SetArgPointee<0>(c[0]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[1]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[2]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[3]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[4]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[5]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[6]), SetArgPointee<1>(SERIAL_AVAIL)));

	// Call the read function:
	protocol_read();
	// Verify the command and length code:
	EXPECT_EQ(msglen, 0);
	EXPECT_EQ(SysEnv_Rd_DataBase_Cmd(), MASTER_01_ID);
	// Verify the counter and the string content:
	EXPECT_EQ(char_counter, 0);
	for(idx = 0; idx < LINE_BUFFER_SIZE; idx++){
		if(idx < MASTER_01_LEN)
		{
			EXPECT_EQ(line[idx], c[idx + 1]);
			//std::cout << line[idx];
		}
		else
		{
			EXPECT_EQ(line[idx], '\0');
			//std::cout << (char)(line[idx] + '0');
		}
	}
}

TEST_F(ProtocolTest, SerialReadTest_002)
{
	/*
	Validate the correct reception of message splited in two parts
	*/

	// For the side effects mocking of the serial_reed:
	using ::testing::SetArgPointee;

	// Reset the related variables:
	reset_line();
	protocol_init();
	SysEnv_Wr_protocol_Cmd(0);

	// Define auxiliar variables for the serial read:
	uint8_t idx;
	char c[7] = {(char)MASTER_01_ID,
				 (char)'a',
				 (char)'b',
				 (char)'c',
				 (char)'d',
				 (char)'e',
				 (char)'\0'};

	// Verify the initial condition:
	ASSERT_EQ(msglen, 0);
	ASSERT_EQ(char_counter,0);
	ASSERT_THAT(line, Each(0));
	ASSERT_EQ(SysEnv_Rd_DataBase_Cmd(), 0);

	// Set the expeted behaviour of the read function for the first read:
	EXPECT_CALL(*_serial, serial_read(_, _))
							.Times(3)
		.WillOnce(DoAll(SetArgPointee<0>(c[0]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[1]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(0xFF), SetArgPointee<1>(SERIAL_NOT_AVAIL)));

	// Call the read function:
	protocol_read();
	// Verify the command and length code:
	EXPECT_EQ(msglen, MASTER_01_LEN);
	EXPECT_EQ(SysEnv_Rd_DataBase_Cmd(), MASTER_01_ID);
	// Verify the counter and the string content:
	EXPECT_EQ(char_counter, 1);
	for(idx = 0; idx < LINE_BUFFER_SIZE; idx++){
		if(idx < 1)
		{
			EXPECT_EQ(line[idx], c[idx + 1]);
		}
		else
		{
			EXPECT_EQ(line[idx], '\0');
		}
	}

	// Set the expeted behaviour of the read function for the second read:
	EXPECT_CALL(*_serial, serial_read(_, _))
							.Times(5)
		.WillOnce(DoAll(SetArgPointee<0>(c[2]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[3]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[4]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[5]), SetArgPointee<1>(SERIAL_AVAIL)))
		.WillOnce(DoAll(SetArgPointee<0>(c[6]), SetArgPointee<1>(SERIAL_AVAIL)));
	
	// Call the read function:
	protocol_read();
	// Verify the command and length code:
	EXPECT_EQ(msglen, 0);
	EXPECT_EQ(SysEnv_Rd_DataBase_Cmd(), MASTER_01_ID);
	// Verify the counter and the string content:
	EXPECT_EQ(char_counter, 0);
	for(idx = 0; idx < LINE_BUFFER_SIZE; idx++){
		if(idx < MASTER_01_LEN)
		{
			EXPECT_EQ(line[idx], c[idx + 1]);
		}
		else
		{
			EXPECT_EQ(line[idx], '\0');
		}
	}
}

TEST_F(ProtocolTest, SerialReadTest_003)
{
	/*
	Validate the correct reception of message with an unknown CANID
	*/

	// For the side effects mocking of the serial_reed:
	using ::testing::SetArgPointee;

	// Reset the related variables:
	reset_line();
	protocol_init();
	SysEnv_Wr_protocol_Cmd(0);

	// Define auxiliar variables for the serial read:
	uint8_t idx;
	char c[7] = {(char)0xCC,
				 (char)'a',
				 (char)'b',
				 (char)'c',
				 (char)'d',
				 (char)'e',
				 (char)'\0'};

	// Verify the initial condition:
	ASSERT_EQ(msglen, 0);
	ASSERT_EQ(char_counter,0);
	ASSERT_THAT(line, Each(0));
	ASSERT_EQ(SysEnv_Rd_DataBase_Cmd(), 0);

	// Set the expected behavior of the read function:
	EXPECT_CALL(*_serial, serial_read(_, _))
							.Times(1)
		.WillOnce(DoAll(SetArgPointee<0>(c[0]), SetArgPointee<1>(SERIAL_AVAIL)));

	// Call the read function:
	protocol_read();
	// Verify the command and length code:
	EXPECT_EQ(msglen, 0);
	EXPECT_EQ(SysEnv_Rd_DataBase_Cmd(), 0);
	// Verify the counter and the string content:
	EXPECT_EQ(char_counter, 0);
	EXPECT_THAT(line, Each(0));
}


}
