#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "/home/alberto/Documents/PlatformIO/Projects/PlatformIO_project/test/native/MockFiles/Fixture.h"

#include "database.c"
#include "sysenv.h"
#include "protocol.h"


using namespace EmbeddedC;
using namespace ::testing;

namespace EmbeddedCUnitTest {

class DatabaseTest : public TestFixture
{
public:
	DatabaseTest() : TestFixture(new ModuleMock)
	{
		protocol_init();
	}
};

TEST_F(DatabaseTest, SetMessage_001)
{
    // Check that the serial prot is not called when the message ID is not correct:
    EXPECT_CALL(*_serial, serial_write(_)).Times(0);

    set_msg(TESTER_PRESENT_ID);
    set_msg(MASTER_01_ID);
    set_msg((uint8_t)0xFF);
    set_msg((uint8_t)0x88);
}

TEST_F(DatabaseTest, SendMessageMotor_01_001)
{
    // Define the paremeters of the message:
    SystemState state = SYS_OFF;
    ActivationFlag configuration = ACTIVATION_OFF;
    ActivationFlag calibration = ACTIVATION_OFF;
    uint8_t error = 0;
    int16_t rgt_motor = 0;
    int16_t lft_motor = 0;

    // Write the values on the RTE:
    SysEnv_Wr_SystemSignalAdapter_Motor_01_State(state);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Configuration(configuration);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Calibration(calibration);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Error(error);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Rgt_Motor(rgt_motor);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Lft_Motor(lft_motor);

    // Force the expected calls to match also the order:
	using ::testing::InSequence;
	InSequence s;

    // Define the expected message in the serial interface:
    EXPECT_CALL(*_serial, serial_write((char)0x27)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0)).Times(7);

    set_msg(MOTOR_01_ID);
}

TEST_F(DatabaseTest, SendMessageMotor_01_002)
{
    // Define the paremeters of the message:
    SystemState state = SYS_INIT;
    ActivationFlag configuration = ACTIVATION_OFF;
    ActivationFlag calibration = ACTIVATION_ON;
    uint8_t error = 0xF0;
    int16_t rgt_motor = 0x1234;
    int16_t lft_motor = 0x5678;

    // Write the values on the RTE:
    SysEnv_Wr_SystemSignalAdapter_Motor_01_State(state);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Configuration(configuration);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Calibration(calibration);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Error(error);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Rgt_Motor(rgt_motor);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Lft_Motor(lft_motor);

    // Force the expectad calls to match also the order:
	using ::testing::InSequence;
	InSequence s;

    // Define the expected message in the serial interface:
    EXPECT_CALL(*_serial, serial_write((char)0x27)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0b00010001)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)error)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0x34)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0x12)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0x78)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0x56)).Times(1);
    EXPECT_CALL(*_serial, serial_write('\0')).Times(1);

    set_msg(MOTOR_01_ID);
}

TEST_F(DatabaseTest, SendMessageMotor_01_003)
{
    // Define the paremeters of the message:
    SystemState state = SYS_ACTIVE;
    ActivationFlag configuration = ACTIVATION_ON;
    ActivationFlag calibration = ACTIVATION_OFF;
    uint8_t error = 0x0F;
    int16_t rgt_motor = 0x5678;
    int16_t lft_motor = 0x1234;

    // Write the parameters on the RTE:
    SysEnv_Wr_SystemSignalAdapter_Motor_01_State(state);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Configuration(configuration);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Calibration(calibration);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Error(error);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Rgt_Motor(rgt_motor);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Lft_Motor(lft_motor);

    // Force the expected calls to match also the order:
	using ::testing::InSequence;
	InSequence s;

    // Define the expected message in the serial interface:
    EXPECT_CALL(*_serial, serial_write((char)0x27)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0b00001010)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)error)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0x78)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0x56)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0x34)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0x12)).Times(1);
    EXPECT_CALL(*_serial, serial_write('\0')).Times(1);
    
    set_msg(MOTOR_01_ID);
}

TEST_F(DatabaseTest, SendMessageMotor_01_004)
{
    // Define the paremeters of the message:
    SystemState state = SYS_ERROR;
    ActivationFlag configuration = ACTIVATION_ON;
    ActivationFlag calibration = ACTIVATION_ON;
    uint8_t error = 0xFF;
    int16_t rgt_motor = 0xFFFF;
    int16_t lft_motor = 0xFFFF;

    // Write the parameters on the RTE:
    SysEnv_Wr_SystemSignalAdapter_Motor_01_State(state);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Configuration(configuration);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Calibration(calibration);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Error(error);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Rgt_Motor(rgt_motor);
    SysEnv_Wr_SystemSignalAdapter_Motor_01_Lft_Motor(lft_motor);

    // Force the expected calls to match also the order:
	using ::testing::InSequence;
	InSequence s;

    // Define the expected message in the serial interface:
    EXPECT_CALL(*_serial, serial_write((char)0x27)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0b00011111)).Times(1);
    EXPECT_CALL(*_serial, serial_write((char)0xFF)).Times(5);
    EXPECT_CALL(*_serial, serial_write('\0')).Times(1);

    set_msg(MOTOR_01_ID);
}

}
