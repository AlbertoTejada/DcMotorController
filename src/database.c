#include "database.h"
#include "sysenv.h"
#include "protocol.h"
#include <stdint.h>


#if defined(__cplusplus)
namespace EmbeddedC {
#endif

void get_msg(char* frame){
    uint8_t cmd = SysEnv_Rd_DataBase_Cmd();
    switch (cmd){
        case TESTER_PRESENT_ID:
            get_msg_tester_present(frame);
            break;
        case MASTER_01_ID:
            get_msg_master_01(frame);
            break;
        default:
            //Nothing to do
            break;
    }
}

void get_msg_tester_present(char frame[]){
    //Nothing to do
}

void get_msg_master_01(char frame[]){
    /*State requested from the master:
    0 = INIT
    1 = ACTIVE
    2 = CONFIG
    255 = Error*/
    uint8_t state = (frame[0]);
    SysEnv_Wr_DataBase_Master_01_State(state);
    /*Right motor target value*/
    int16_t rgt_motor = (frame[1]) | ((frame[2]) << 8);
    SysEnv_Wr_DataBase_Master_01_Rgt_Motor(rgt_motor);
    /*Left motor target value*/
    int16_t lft_motor = (frame[3]) | ((frame[4]) << 8);
    SysEnv_Wr_DataBase_Master_01_Lft_Motor(lft_motor);
}

void set_msg(uint8_t cmd){
    switch (cmd){
        case MOTOR_01_ID:
            set_msg_motor_01();
            break;
        default:
            //Nothing to do;
            break;
    }
}

void set_msg_motor_01(void){
    //Array for the message motor_01
    char motor_01 [MOTOR_01_LEN] = {0};
    
    //Generate the message header:
    motor_01[0] = MOTOR_01_LEN | (MOTOR_01_ID << 4);
    
    /*Status of the motors:
    0 = INIT
    1 = ACTIVE
    2 = CONFIG
    7 = Error*/
    uint8_t state = SysEnv_Rd_DataBase_Motor_01_State();
    motor_01[1] |= (state & MOTOR_01_STATE);
    /*System configuration state:
    0 = No configured
    1 = Configured*/
    uint8_t configuration = SysEnv_Rd_DataBase_Motor_01_Configuration();
    motor_01[1] |= ((configuration & MOTOR_01_CONFIGURATION) << 3);
    /*System calibration state:
    0 = No calibrated
    1 = Calibrated*/
    uint8_t calibration = SysEnv_Rd_DataBase_Motor_01_Calibration();
    motor_01[1] |= ((calibration & MOTOR_01_CALIBRATION) << 4);
    /*Error code of the system:
    0 = No error
    1 = Over speed
    2 = Under speed
    3 = Right motor over temp
    4 = Left motor over temp
    8 = Left motor over temp*/
    uint8_t error = SysEnv_Rd_DataBase_Motor_01_Error();
    motor_01[2] = error;
    /*Rigth motor current value*/
    int16_t rgt_motor = SysEnv_Rd_DataBase_Motor_01_Rgt_Motor();
    motor_01[3] = rgt_motor;
    motor_01[4] = (rgt_motor >> 8);
    /*Left motor current value*/
    int16_t lft_motor = SysEnv_Rd_DataBase_Motor_01_Lft_Motor();
    motor_01[5] = lft_motor;
    motor_01[6] = (lft_motor >> 8);
    //Call to the write frame function:
    protocol_write(motor_01, MOTOR_01_LEN);
}

#if defined(__cplusplus)
} // Closing brace for namespace EmbeddedC
#endif