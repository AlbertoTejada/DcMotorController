#if defined(__cplusplus)
namespace EmbeddedC {
#endif

#ifndef database_h
#define database_h

#include <stdint.h>


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


//Received message parse functions declaration:
void get_msg_tester_present(char* frame);
void get_msg_master_01(char* frame);

//Incoming message selector:
void get_msg(char* frame);

//Sent message build functions declaration:
void set_msg_motor_01(void);

//Outgoing message selector:
void set_msg(uint8_t cmd);

#endif // database_h

#if defined(__cplusplus)
} // Closing brace for namespace EmbeddedC
#endif