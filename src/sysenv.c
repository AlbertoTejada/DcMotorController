#include "sysenv.h"
#include <stdint.h>

#if defined(__cplusplus)
namespace EmbeddedC {
#endif

//System environment global parameters declaration:
uint8_t Sys_protocol_Cmd;
uint8_t Sys_SystemSignalAdapter_Motor_01_State;
uint8_t Sys_SystemSignalAdapter_Motor_01_Calibration;
uint8_t Sys_SystemSignalAdapter_Motor_01_Configuration;
uint8_t Sys_SystemSignalAdapter_Motor_01_Error;
int16_t Sys_SystemSignalAdapter_Motor_01_Rgt_Motor;
int16_t Sys_SystemSignalAdapter_Motor_01_Lft_Motor;
uint8_t Sys_DataBase_Master_01_State;
int16_t Sys_DataBase_Master_01_Rgt_Motor;
int16_t Sys_DataBase_Master_01_Lft_Motor;
SystemState Sys_SystemSignalAdapter_S_Master_State;
ActivationFlag Sys_ServicesManager_S_Calibration_Request;
ActivationFlag Sys_protocol_S_Timeout;
SwcStatus Sys_HealthMonitor_S_Health_Status;
SwcStatus Sys_MemManager_S_Memory_Status;
SwcStatus Sys_CalibrationManager_S_Calibration_Status;
SwcStatus Sys_MotionControl_S_Motion_Status;
uint8_t Sys_HealthMonitor_S_System_Health;
SystemState Sys_ActivationDeactivation_P_System_State;
ActivationFlag Sys_ActivationDeactivation_S_Motion_On_Off;
ActivationFlag Sys_ActivationDeactivation_S_Calibration_On_Off;
uint8_t Sys_ActivationDeactivation_S_System_Error_Code;
ControlFlag Sys_MemManager_S_System_Calibrated;
ControlFlag Sys_MemManager_S_System_Configured;
int16_t Sys_EncodersDriver_S_Rgt_Spd;
int16_t Sys_EncodersDriver_S_Lft_Spd;
int16_t Sys_SystemSignalAdapter_S_Rgt_Target;
int16_t Sys_SystemSignalAdapter_S_Lft_Target;
struct ControlParameters Sys_ServicesManager_S_Set_Control_Params;
uint8_t Sys_ServicesManager_S_Set_System_Config;
struct ControlParameters Sys_MemManager_S_Control_Parameters;
int16_t Sys_MotionControl_S_Rgt_Pwr;
int16_t Sys_MotionControl_S_Lft_Pwr;
uint8_t Sys_TemperatureDriver_S_Rgt_Temp;
uint8_t Sys_TemperatureDriver_S_Lft_Temp;
uint8_t Sys_TemperatureDriver_S_Ctrl_Temp;
uint8_t Sys_TemperatureDriver_S_Dvr_Temp;
uint8_t Sys_VoltageDriver_S_Rgt_0_Volt;
uint8_t Sys_VoltageDriver_S_Rgt_1_Volt;
uint8_t Sys_VoltageDriver_S_Lft_0_Volt;
uint8_t Sys_VoltageDriver_S_Lft_1_Volt;
uint8_t Sys_MemManager_S_System_Configuration;
char* Sys_MemDriver_S_Data_Rd;
uint16_t Sys_MemManager_S_Data_Ad;
uint16_t Sys_MemManager_S_Data_Ln;
char* Sys_MemManager_S_Data_Wr;


//System environment read and write functions definitions:
void SysEnv_Wr_protocol_Cmd(uint8_t data){
    Sys_protocol_Cmd = data;
}
uint8_t SysEnv_Rd_DataBase_Cmd(void){
    return Sys_protocol_Cmd;
}
void SysEnv_Wr_SystemSignalAdapter_Motor_01_State(uint8_t data){
    Sys_SystemSignalAdapter_Motor_01_State = data;
}
uint8_t SysEnv_Rd_DataBase_Motor_01_State(void){
    return Sys_SystemSignalAdapter_Motor_01_State;
}
void SysEnv_Wr_SystemSignalAdapter_Motor_01_Calibration(uint8_t data){
    Sys_SystemSignalAdapter_Motor_01_Calibration = data;
}
uint8_t SysEnv_Rd_DataBase_Motor_01_Calibration(void){
    return Sys_SystemSignalAdapter_Motor_01_Calibration;
}
void SysEnv_Wr_SystemSignalAdapter_Motor_01_Configuration(uint8_t data){
    Sys_SystemSignalAdapter_Motor_01_Configuration = data;
}
uint8_t SysEnv_Rd_DataBase_Motor_01_Configuration(void){
    return Sys_SystemSignalAdapter_Motor_01_Configuration;
}
void SysEnv_Wr_SystemSignalAdapter_Motor_01_Error(uint8_t data){
    Sys_SystemSignalAdapter_Motor_01_Error = data;
}
uint8_t SysEnv_Rd_DataBase_Motor_01_Error(void){
    return Sys_SystemSignalAdapter_Motor_01_Error;
}
void SysEnv_Wr_SystemSignalAdapter_Motor_01_Rgt_Motor(int16_t data){
    Sys_SystemSignalAdapter_Motor_01_Rgt_Motor = data;
}
int16_t SysEnv_Rd_DataBase_Motor_01_Rgt_Motor(void){
    return Sys_SystemSignalAdapter_Motor_01_Rgt_Motor;
}
void SysEnv_Wr_SystemSignalAdapter_Motor_01_Lft_Motor(int16_t data){
    Sys_SystemSignalAdapter_Motor_01_Lft_Motor = data;
}
int16_t SysEnv_Rd_DataBase_Motor_01_Lft_Motor(void){
    return Sys_SystemSignalAdapter_Motor_01_Lft_Motor;
}
void SysEnv_Wr_DataBase_Master_01_State(uint8_t data){
    Sys_DataBase_Master_01_State = data;
}
uint8_t SysEnv_Rd_SystemSignalAdapter_Master_01_State(void){
    return Sys_DataBase_Master_01_State;
}
void SysEnv_Wr_DataBase_Master_01_Rgt_Motor(int16_t data){
    Sys_DataBase_Master_01_Rgt_Motor = data;
}
int16_t SysEnv_Rd_SystemSignalAdapter_Master_01_Rgt_Motor(void){
    return Sys_DataBase_Master_01_Rgt_Motor;
}
void SysEnv_Wr_DataBase_Master_01_Lft_Motor(int16_t data){
    Sys_DataBase_Master_01_Lft_Motor = data;
}
int16_t SysEnv_Rd_SystemSignalAdapter_Master_01_Lft_Motor(void){
    return Sys_DataBase_Master_01_Lft_Motor;
}
void SysEnv_Wr_SystemSignalAdapter_S_Master_State(SystemState data){
    Sys_SystemSignalAdapter_S_Master_State = data;
}
SystemState SysEnv_Rd_ActivationDeactivation_S_Master_State(void){
    return Sys_SystemSignalAdapter_S_Master_State;
}
void SysEnv_Wr_ServicesManager_S_Calibration_Request(ActivationFlag data){
    Sys_ServicesManager_S_Calibration_Request = data;
}
ActivationFlag SysEnv_Rd_ActivationDeactivation_S_Calibration_Request(void){
    return Sys_ServicesManager_S_Calibration_Request;
}
void SysEnv_Wr_protocol_S_Timeout(ActivationFlag data){
    Sys_protocol_S_Timeout = data;
}
ActivationFlag SysEnv_Rd_ActivationDeactivation_S_Timeout(void){
    return Sys_protocol_S_Timeout;
}
void SysEnv_Wr_HealthMonitor_S_Health_Status(SwcStatus data){
    Sys_HealthMonitor_S_Health_Status = data;
}
SwcStatus SysEnv_Rd_ActivationDeactivation_S_Health_Status(void){
    return Sys_HealthMonitor_S_Health_Status;
}
void SysEnv_Wr_MemManager_S_Memory_Status(SwcStatus data){
    Sys_MemManager_S_Memory_Status = data;
}
SwcStatus SysEnv_Rd_ActivationDeactivation_S_Memory_Status(void){
    return Sys_MemManager_S_Memory_Status;
}
void SysEnv_Wr_CalibrationManager_S_Calibration_Status(SwcStatus data){
    Sys_CalibrationManager_S_Calibration_Status = data;
}
SwcStatus SysEnv_Rd_ActivationDeactivation_S_Calibration_Status(void){
    return Sys_CalibrationManager_S_Calibration_Status;
}
void SysEnv_Wr_MotionControl_S_Motion_Status(SwcStatus data){
    Sys_MotionControl_S_Motion_Status = data;
}
SwcStatus SysEnv_Rd_ActivationDeactivation_S_Motion_Status(void){
    return Sys_MotionControl_S_Motion_Status;
}
void SysEnv_Wr_HealthMonitor_S_System_Health(uint8_t data){
    Sys_HealthMonitor_S_System_Health = data;
}
uint8_t SysEnv_Rd_ActivationDeactivation_S_System_Health(void){
    return Sys_HealthMonitor_S_System_Health;
}
void SysEnv_Wr_ActivationDeactivation_P_System_State(SystemState data){
    Sys_ActivationDeactivation_P_System_State = data;
}
SystemState SysEnv_Rd_SystemSignalAdapter_P_System_State(void){
    return Sys_ActivationDeactivation_P_System_State;
}
void SysEnv_Wr_ActivationDeactivation_S_Motion_On_Off(ActivationFlag data){
    Sys_ActivationDeactivation_S_Motion_On_Off = data;
}
ActivationFlag SysEnv_Rd_MotionControl_S_Motion_On_Off(void){
    return Sys_ActivationDeactivation_S_Motion_On_Off;
}
void SysEnv_Wr_ActivationDeactivation_S_Calibration_On_Off(ActivationFlag data){
    Sys_ActivationDeactivation_S_Calibration_On_Off = data;
}
ActivationFlag SysEnv_Rd_CalibrationManager_S_Calibration_On_Off(void){
    return Sys_ActivationDeactivation_S_Calibration_On_Off;
}
void SysEnv_Wr_ActivationDeactivation_S_System_Error_Code(uint8_t data){
    Sys_ActivationDeactivation_S_System_Error_Code = data;
}
uint8_t SysEnv_Rd_SystemSignalAdapter_S_System_Error_Code(void){
    return Sys_ActivationDeactivation_S_System_Error_Code;
}
void SysEnv_Wr_MemManager_S_System_Calibrated(ControlFlag data){
    Sys_MemManager_S_System_Calibrated = data;
}
ControlFlag SysEnv_Rd_SystemSignalAdapter_S_System_Calibrated(void){
    return Sys_MemManager_S_System_Calibrated;
}
void SysEnv_Wr_MemManager_S_System_Configured(ControlFlag data){
    Sys_MemManager_S_System_Configured = data;
}
ControlFlag SysEnv_Rd_SystemSignalAdapter_S_System_Configured(void){
    return Sys_MemManager_S_System_Configured;
}
void SysEnv_Wr_EncodersDriver_S_Rgt_Spd(int16_t data){
    Sys_EncodersDriver_S_Rgt_Spd = data;
}
int16_t SysEnv_Rd_SystemSignalAdapter_S_Rgt_Spd(void){
    return Sys_EncodersDriver_S_Rgt_Spd;
}
void SysEnv_Wr_EncodersDriver_S_Lft_Spd(int16_t data){
    Sys_EncodersDriver_S_Lft_Spd = data;
}
int16_t SysEnv_Rd_SystemSignalAdapter_S_Lft_Spd(void){
    return Sys_EncodersDriver_S_Lft_Spd;
}
void SysEnv_Wr_SystemSignalAdapter_S_Rgt_Target(int16_t data){
    Sys_SystemSignalAdapter_S_Rgt_Target = data;
}
int16_t SysEnv_Rd_MotionControl_S_Rgt_Target(void){
    return Sys_SystemSignalAdapter_S_Rgt_Target;
}
void SysEnv_Wr_SystemSignalAdapter_S_Lft_Target(int16_t data){
    Sys_SystemSignalAdapter_S_Lft_Target = data;
}
int16_t SysEnv_Rd_MotionControl_S_Lft_Target(void){
    return Sys_SystemSignalAdapter_S_Lft_Target;
}
void SysEnv_Wr_ServicesManager_S_Set_Control_Params(struct ControlParameters data){
    Sys_ServicesManager_S_Set_Control_Params = data;
}
struct ControlParameters SysEnv_Rd_MemManager_S_Set_Control_Params(void){
    return Sys_ServicesManager_S_Set_Control_Params;
}
void SysEnv_Wr_ServicesManager_S_Set_System_Config(uint8_t data){
    Sys_ServicesManager_S_Set_System_Config = data;
}
uint8_t SysEnv_Rd_MemManager_S_Set_System_Config(void){
    return Sys_ServicesManager_S_Set_System_Config;
}
void SysEnv_Wr_MemManager_S_Control_Parameters(struct ControlParameters data){
    Sys_MemManager_S_Control_Parameters = data;
}
struct ControlParameters SysEnv_Rd_MotionControl_S_Control_Parameters(void){
    return Sys_MemManager_S_Control_Parameters;
}
void SysEnv_Wr_MotionControl_S_Rgt_Pwr(int16_t data){
    Sys_MotionControl_S_Rgt_Pwr = data;
}
int16_t SysEnv_Rd_MotorsDriver_S_Rgt_Pwr(void){
    return Sys_MotionControl_S_Rgt_Pwr;
}
void SysEnv_Wr_MotionControl_S_Lft_Pwr(int16_t data){
    Sys_MotionControl_S_Lft_Pwr = data;
}
int16_t SysEnv_Rd_MotorsDriver_S_Lft_Pwr(void){
    return Sys_MotionControl_S_Lft_Pwr;
}
void SysEnv_Wr_TemperatureDriver_S_Rgt_Temp(uint8_t data){
    Sys_TemperatureDriver_S_Rgt_Temp = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_Rgt_Temp(void){
    return Sys_TemperatureDriver_S_Rgt_Temp;
}
void SysEnv_Wr_TemperatureDriver_S_Lft_Temp(uint8_t data){
    Sys_TemperatureDriver_S_Lft_Temp = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_Lft_Temp(void){
    return Sys_TemperatureDriver_S_Lft_Temp;
}
void SysEnv_Wr_TemperatureDriver_S_Ctrl_Temp(uint8_t data){
    Sys_TemperatureDriver_S_Ctrl_Temp = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_Ctrl_Temp(void){
    return Sys_TemperatureDriver_S_Ctrl_Temp;
}
void SysEnv_Wr_TemperatureDriver_S_Dvr_Temp(uint8_t data){
    Sys_TemperatureDriver_S_Dvr_Temp = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_Dvr_Temp(void){
    return Sys_TemperatureDriver_S_Dvr_Temp;
}
void SysEnv_Wr_VoltageDriver_S_Rgt_0_Volt(uint8_t data){
    Sys_VoltageDriver_S_Rgt_0_Volt = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_Rgt_0_Volt(void){
    return Sys_VoltageDriver_S_Rgt_0_Volt;
}
void SysEnv_Wr_VoltageDriver_S_Rgt_1_Volt(uint8_t data){
    Sys_VoltageDriver_S_Rgt_1_Volt = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_Rgt_1_Volt(void){
    return Sys_VoltageDriver_S_Rgt_1_Volt;
}
void SysEnv_Wr_VoltageDriver_S_Lft_0_Volt(uint8_t data){
    Sys_VoltageDriver_S_Lft_0_Volt = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_Lft_0_Volt(void){
    return Sys_VoltageDriver_S_Lft_0_Volt;
}
void SysEnv_Wr_VoltageDriver_S_Lft_1_Volt(uint8_t data){
    Sys_VoltageDriver_S_Lft_1_Volt = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_Lft_1_Volt(void){
    return Sys_VoltageDriver_S_Lft_1_Volt;
}
void SysEnv_Wr_MemManager_S_System_Configuration(uint8_t data){
    Sys_MemManager_S_System_Configuration = data;
}
uint8_t SysEnv_Rd_HealthMonitor_S_System_Configuration(void){
    return Sys_MemManager_S_System_Configuration;
}
void SysEnv_Wr_MemDriver_S_Data_Rd(char* data){
    Sys_MemDriver_S_Data_Rd = data;
}
char* SysEnv_Rd_MemManager_S_Data_Rd(void){
    return Sys_MemDriver_S_Data_Rd;
}
void SysEnv_Wr_MemManager_S_Data_Ad(uint16_t data){
    Sys_MemManager_S_Data_Ad = data;
}
uint16_t SysEnv_Rd_MemDriver_S_Data_Ad(void){
    return Sys_MemManager_S_Data_Ad;
}
void SysEnv_Wr_MemManager_S_Data_Ln(uint16_t data){
    Sys_MemManager_S_Data_Ln = data;
}
uint16_t SysEnv_Rd_MemDriver_S_Data_Ln(void){
    return Sys_MemManager_S_Data_Ln;
}
void SysEnv_Wr_MemManager_S_Data_Wr(char* data){
    Sys_MemManager_S_Data_Wr = data;
}
char* SysEnv_Rd_MemDriver_S_Data_Wr(void){
    return Sys_MemManager_S_Data_Wr;
}

#if defined(__cplusplus)
}
#endif