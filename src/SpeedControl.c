#include "SpeedControl.h"
#include "Os_TimeServices.h"


PidController pid;
SpeedCtrl spd_ctrl;

void SpeedCtrl_Init(void)
{
    SpeedCtrl_ResetErrors();
    SpeedCtrl_ReadCtrlParams();
    pid.previousTime = os_timer_ms();

    spd_ctrl.motor_activation = 0;
    spd_ctrl.target_speed = 0;
    spd_ctrl.encoder_cnt = 0;
    spd_ctrl.encoder_time = 1;

}

void SpeedCtrl_ResetErrors(void)
{
    pid.error = 0;
    pid.lastError = 0;
    pid.cumError = 0;
    pid.rateError = 0;
} 

void SpeedCtrl_ReadCtrlParams(void)
{
    pid.kp = 0.0001;
    pid.ki = 0.0001;
    pid.kd = 0.0001;
} 

void SpeedCtrl_ReadInputs(void)
{
    spd_ctrl.motor_activation = Rte_Rd_DataBase_Motor_01_State();
    spd_ctrl.target_speed = Rte_Rd_MotionControl_S_Rgt_Target();
    spd_ctrl.encoder_cnt = Rte_Rd_SystemSignalAdapter_S_Rgt_Spd();
    spd_ctrl.encoder_time = Rte_Rd_SystemSignalAdapter_S_Lft_Spd();
}

void SpeedCtrl_WriteOutputs(void)
{
    Rte_Wr_SystemSignalAdapter_Motor_01_Rgt_Motor(spd_ctrl.actual_speed);
    Rte_Wr_ActivationDeactivation_S_Motion_On_Off(spd_ctrl.status);
    Rte_Wr_MotionControl_S_Rgt_Pwr(spd_ctrl.motor_pwr);
}

void SpeedCtrl_Main(void)
{
    int16_t displacement;
    int32_t displacement_increased; 
    double correction_signal;

    if (!spd_ctrl.motor_activation)
    {  
        spd_ctrl.status = ACTIVATION_ON;
        displacement = (spd_ctrl.encoder_cnt * MM_PER_REVOLUTION ) / PULSES_PER_REVOLUTION;
        displacement_increased = displacement * 1e6;
        spd_ctrl.actual_speed = displacement_increased / spd_ctrl.encoder_time;
        pid.error = spd_ctrl.target_speed - spd_ctrl.actual_speed;
        correction_signal = SpeedCtrl_ComputePID();

        if ((-255 <= correction_signal) && (correction_signal <= 255))
        {
           spd_ctrl.motor_pwr =  (int16_t)correction_signal;
        }
        else if (-255 > correction_signal)
        {
            spd_ctrl.motor_pwr = (int16_t)-255;
        }
        else
        {
            spd_ctrl.status = ACTIVATION_OFF;
            spd_ctrl.motor_pwr = (int16_t)255;
        }
    }
    else
    {
        spd_ctrl.motor_pwr = (int16_t)0;
    }
    
}

void SpeedCtrl_Task(void)
{
    SpeedCtrl_ReadInputs();
    SpeedCtrl_Main();
    SpeedCtrl_WriteOutputs();
} 

double SpeedCtrl_ComputePID(void)
{
    //Time parameters caculation:
    pid.currentTime = os_timer_ms();                              //get current time
    pid.elapsedTime = (uint16_t)(pid.currentTime - pid.previousTime);  //compute time elapsed from previous computation

    //Error parameter calculation:
    pid.cumError += pid.error * pid.elapsedTime;				// compute integral
    pid.rateError = (pid.error - pid.lastError) / pid.elapsedTime;  // compute derivative

    //PID result caculation:
    double result = pid.kp * pid.error + pid.ki * pid.cumError + pid.kd * pid.rateError;

    //Update time and error parameters:
    pid.previousTime = pid.currentTime;
    pid.lastError = pid.error;

    return result;   
    
}

// void SpeedCtrl_SetError(double error_in)
// {
//     pid.error = error_in;
// } 