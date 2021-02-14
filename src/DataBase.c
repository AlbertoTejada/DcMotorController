#include "DataBase.h"
#include "dbc.h" 
#include "Rte.h"
#include <stdint.h>


void get_msg(struct can_frame* frame){
    uint32_t can_id = frame->can_id;
    switch (can_id){
        case DBC_UDS_MOTOR_01_FRAME_ID:
            get_msg_uds_motor_01(frame->data);
            break;
        case DBC_XCP_MOTOR_01_FRAME_ID:
            get_msg_xcp_motor_01(frame->data);
            break;
        case DBC_MOTION_CONTROL_FRAME_ID:
            get_msg_motion_control(frame->data);
            break;            
        default:
            //Nothing to do
            break;
    }
}

void get_msg_uds_motor_01(uint8_t frame[]){
    struct dbc_uds_motor_01_t uds_motor_01;
    dbc_uds_motor_01_unpack(
        &uds_motor_01,
        frame,
        (size_t)DBC_UDS_MOTOR_01_LENGTH
    );
}

void get_msg_xcp_motor_01(uint8_t frame[]){
    struct dbc_xcp_motor_01_t xcp_motor_01;
    dbc_xcp_motor_01_unpack(
        &xcp_motor_01,
        frame,
        (size_t)DBC_XCP_MOTOR_01_LENGTH
    );
}

void get_msg_motion_control(uint8_t frame[]){
    // /*State requested from the master:
    // 0 = INIT
    // 1 = ACTIVE
    // 2 = CONFIG
    // 255 = Error*/
    // uint8_t state = (frame[0]);
    // Rte_Wr_DataBase_Master_01_State(state);
    // /*Right motor target value*/
    // int16_t rgt_motor = (frame[1]) | ((frame[2]) << 8);
    // Rte_Wr_DataBase_Master_01_Rgt_Motor(rgt_motor);
    // /*Left motor target value*/
    // int16_t lft_motor = (frame[3]) | ((frame[4]) << 8);
    // Rte_Wr_DataBase_Master_01_Lft_Motor(lft_motor);
    struct dbc_motion_control_t motion_control;
    int return_val = dbc_motion_control_unpack(
        &motion_control,
        frame,
        (size_t)DBC_MOTION_CONTROL_LENGTH
    );
    if (!return_val)
    {
        Rte_Wr_SystemSignalAdapter_Motor_01_State(motion_control.enable_motor);
        Rte_Wr_SystemSignalAdapter_S_Rgt_Target(motion_control.target_speed);
        Rte_Wr_SystemSignalAdapter_S_Lft_Target(motion_control.targert_direction);
    } 
}

struct can_frame set_msg(uint32_t can_id){
    struct can_frame canMsgSend;
    canMsgSend.can_id = can_id;
    switch (can_id){
        case DBC_SPEED_AND_DIRECTION_FRAME_ID:
            set_msg_speed_and_direction(&canMsgSend);
            break;
        default:
            //Nothing to do;
            break;
    }
    return canMsgSend;
}

void set_msg_speed_and_direction(struct can_frame* frame){
    // /*Status of the motors:
    // 0 = INIT
    // 1 = ACTIVE
    // 2 = CONFIG
    // 7 = Error*/
    // uint8_t state = Rte_Rd_DataBase_Motor_01_State();
    // frame->data[1] |= (state & MOTOR_01_STATE);
    // /*System configuration state:
    // 0 = No configured
    // 1 = Configured*/
    // uint8_t configuration = Rte_Rd_DataBase_Motor_01_Configuration();
    // frame->data[1] |= ((configuration & MOTOR_01_CONFIGURATION) << 3);
    // /*System calibration state:
    // 0 = No calibrated
    // 1 = Calibrated*/
    // uint8_t calibration = Rte_Rd_DataBase_Motor_01_Calibration();
    // frame->data[1] |= ((calibration & MOTOR_01_CALIBRATION) << 4);
    // /*Error code of the system:
    // 0 = No error
    // 1 = Over speed
    // 2 = Under speed
    // 3 = Right motor over temp
    // 4 = Left motor over temp
    // 8 = Left motor over temp*/
    // uint8_t error = Rte_Rd_DataBase_Motor_01_Error();
    // frame->data[2] = error;
    // /*Rigth motor current value*/
    // int16_t rgt_motor = Rte_Rd_DataBase_Motor_01_Rgt_Motor();
    // frame->data[3] = rgt_motor;
    // frame->data[4] = (rgt_motor >> 8);
    // /*Left motor current value*/
    // int16_t lft_motor = Rte_Rd_DataBase_Motor_01_Lft_Motor();
    // frame->data[5] = lft_motor;
    // frame->data[6] = (lft_motor >> 8);
    struct dbc_speed_and_direction_t speed_and_direction;
    speed_and_direction.motor_speed = Rte_Rd_DataBase_Motor_01_Rgt_Motor();
    speed_and_direction.wheels_direction = Rte_Rd_DataBase_Motor_01_Lft_Motor();
    speed_and_direction.motor_state = (uint8_t)Rte_Rd_MotionControl_S_Motion_On_Off();
    dbc_speed_and_direction_pack(frame->data,
    &speed_and_direction,
    (size_t)DBC_SPEED_AND_DIRECTION_LENGTH
    );
    frame->can_dlc = DBC_SPEED_AND_DIRECTION_LENGTH;
}