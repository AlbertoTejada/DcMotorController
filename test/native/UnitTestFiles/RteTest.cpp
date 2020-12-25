#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "sysenv.h"

using namespace EmbeddedC;
using namespace ::testing;

namespace EmbeddedCUnitTest {

TEST(RteTest, WriteReadCmd_001)
{
    uint8_t w_cmd = 2;
    SysEnv_Wr_protocol_Cmd(w_cmd);
    EXPECT_EQ(w_cmd, SysEnv_Rd_DataBase_Cmd());
}

TEST(RteTest, WriteReadMotor_01_State_001)
{
    uint8_t state = 2;
    SysEnv_Wr_SystemSignalAdapter_Motor_01_State(state);
    EXPECT_EQ(state, SysEnv_Rd_DataBase_Motor_01_State());
}

}

