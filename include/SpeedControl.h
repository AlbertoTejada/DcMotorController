#ifndef _SPEED_CONTROL_H_
#define _SPEED_CONTROL_H_

#include <stdint.h>
#include "Rte.h"

#define PULSES_PER_REVOLUTION (16U)
#define MM_PER_REVOLUTION (32U)

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct{
    // Errors parameters for PID response calculation:
    double error;
    double lastError;
    double cumError;
    double rateError;

    // Time parameters for PID response calculation:
    uint32_t currentTime;
    uint32_t previousTime;
    uint16_t elapsedTime;

    // PID parameters:
    float kp;
    float ki;
    float kd;

    // Motion control parameters:
    int16_t targetSpeed;
    

} PidController;

typedef struct{
    uint8_t motor_activation;
    ActivationFlag status;
    int32_t actual_speed;
    int16_t target_speed;
    int16_t encoder_cnt;
    uint16_t encoder_time;
    int16_t motor_pwr;

} SpeedCtrl;

void SpeedCtrl_Init(void);

void SpeedCtrl_ReadInputs(void);

void SpeedCtrl_WriteOutputs(void);

void SpeedCtrl_Task(void);

void SpeedCtrl_Main(void);

void SpeedCtrl_ResetErrors(void);

void SpeedCtrl_ReadCtrlParams(void);

double SpeedCtrl_ComputePID(void);

//void SpeedCtrl_SetError(double error_in);

#if defined(__cplusplus)
} // Closing brace for extern "C"
#endif


#endif // _SPEED_CONTROL_H_

