#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stdint.h>
#include "Can.h"


//Messages ID definitions:
#define TESTER_PRESENT_ID 0
#define MASTER_01_ID 1
#define MOTOR_01_ID 2

//Messages length definitions:
#define TESTER_PRESENT_LEN 1
#define MASTER_01_LEN 6
#define MOTOR_01_LEN 7

//Signals mask definitions:
#define MOTOR_01_STATE 0x07 //Signal state from message motor_01
#define MOTOR_01_CONFIGURATION 0x01 //Signal configuration from message motor_01
#define MOTOR_01_CALIBRATION 0x01 //Signal calibration from message motor_01


#if defined(__cplusplus)
extern "C" {
#endif

//Received message parse functions declaration:
void get_msg_uds_motor_01(uint8_t frame[]);
void get_msg_xcp_motor_01(uint8_t frame[]);
void get_msg_motion_control(uint8_t frame[]);

//Incoming message selector:
void get_msg(struct can_frame* frame);

//Sent message build functions declaration:
void set_msg_speed_and_direction(struct can_frame* frame);

//Outgoing message selector:
struct can_frame set_msg(uint32_t can_id);

#if defined(__cplusplus)
} // Closing brace for extern "C"
#endif

#endif // _DATABASE_H_