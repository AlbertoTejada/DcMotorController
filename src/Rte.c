#include "Rte.h"
#include <stdint.h>


//System environment global parameters declaration:
uint8_t Rte_protocol_Cmd;
uint8_t Rte_SystemSignalAdapter_Motor_01_State;
uint8_t Rte_SystemSignalAdapter_Motor_01_Calibration;
uint8_t Rte_SystemSignalAdapter_Motor_01_Configuration;
uint8_t Rte_SystemSignalAdapter_Motor_01_Error;
int32_t Rte_SystemSignalAdapter_Motor_01_Rgt_Motor;
int16_t Rte_SystemSignalAdapter_Motor_01_Lft_Motor;
uint8_t Rte_DataBase_Master_01_State;
int16_t Rte_DataBase_Master_01_Rgt_Motor;
int16_t Rte_DataBase_Master_01_Lft_Motor;
SystemState Rte_SystemSignalAdapter_S_Master_State;
ActivationFlag Rte_ServicesManager_S_Calibration_Request;
ActivationFlag Rte_protocol_S_Timeout;
SwcStatus Rte_HealthMonitor_S_Health_Status;
SwcStatus Rte_MemManager_S_Memory_Status;
SwcStatus Rte_CalibrationManager_S_Calibration_Status;
SwcStatus Rte_MotionControl_S_Motion_Status;
uint8_t Rte_HealthMonitor_S_System_Health;
SystemState Rte_ActivationDeactivation_P_System_State;
ActivationFlag Rte_ActivationDeactivation_S_Motion_On_Off;
ActivationFlag Rte_ActivationDeactivation_S_Calibration_On_Off;
uint8_t Rte_ActivationDeactivation_S_System_Error_Code;
ControlFlag Rte_MemManager_S_System_Calibrated;
ControlFlag Rte_MemManager_S_System_Configured;
int16_t Rte_EncodersDriver_S_Rgt_Spd;
int16_t Rte_EncodersDriver_S_Lft_Spd;
int16_t Rte_SystemSignalAdapter_S_Rgt_Target;
int16_t Rte_SystemSignalAdapter_S_Lft_Target;
ControlParameters Rte_ServicesManager_S_Set_Control_Params;
uint8_t Rte_ServicesManager_S_Set_System_Config;
ControlParameters Rte_MemManager_S_Control_Parameters;
int16_t Rte_MotionControl_S_Rgt_Pwr;
int16_t Rte_MotionControl_S_Lft_Pwr;
uint8_t Rte_TemperatureDriver_S_Rgt_Temp;
uint8_t Rte_TemperatureDriver_S_Lft_Temp;
uint8_t Rte_TemperatureDriver_S_Ctrl_Temp;
uint8_t Rte_TemperatureDriver_S_Dvr_Temp;
uint8_t Rte_VoltageDriver_S_Rgt_0_Volt;
uint8_t Rte_VoltageDriver_S_Rgt_1_Volt;
uint8_t Rte_VoltageDriver_S_Lft_0_Volt;
uint8_t Rte_VoltageDriver_S_Lft_1_Volt;
uint8_t Rte_MemManager_S_System_Configuration;
char* Rte_MemDriver_S_Data_Rd;
uint16_t Rte_MemManager_S_Data_Ad;
uint16_t Rte_MemManager_S_Data_Ln;
char* Rte_MemManager_S_Data_Wr;


//System environment read and write functions definitions:
void Rte_Wr_protocol_Cmd(uint8_t data){
    Rte_protocol_Cmd = data;
}
uint8_t Rte_Rd_DataBase_Cmd(void){
    return Rte_protocol_Cmd;
}
void Rte_Wr_SystemSignalAdapter_Motor_01_State(uint8_t data){
    Rte_SystemSignalAdapter_Motor_01_State = data;
}
uint8_t Rte_Rd_DataBase_Motor_01_State(void){
    return Rte_SystemSignalAdapter_Motor_01_State;
}
void Rte_Wr_SystemSignalAdapter_Motor_01_Calibration(uint8_t data){
    Rte_SystemSignalAdapter_Motor_01_Calibration = data;
}
uint8_t Rte_Rd_DataBase_Motor_01_Calibration(void){
    return Rte_SystemSignalAdapter_Motor_01_Calibration;
}
void Rte_Wr_SystemSignalAdapter_Motor_01_Configuration(uint8_t data){
    Rte_SystemSignalAdapter_Motor_01_Configuration = data;
}
uint8_t Rte_Rd_DataBase_Motor_01_Configuration(void){
    return Rte_SystemSignalAdapter_Motor_01_Configuration;
}
void Rte_Wr_SystemSignalAdapter_Motor_01_Error(uint8_t data){
    Rte_SystemSignalAdapter_Motor_01_Error = data;
}
uint8_t Rte_Rd_DataBase_Motor_01_Error(void){
    return Rte_SystemSignalAdapter_Motor_01_Error;
}
void Rte_Wr_SystemSignalAdapter_Motor_01_Rgt_Motor(int32_t data){
    Rte_SystemSignalAdapter_Motor_01_Rgt_Motor = data;
}
int32_t Rte_Rd_DataBase_Motor_01_Rgt_Motor(void){
    return Rte_SystemSignalAdapter_Motor_01_Rgt_Motor;
}
void Rte_Wr_SystemSignalAdapter_Motor_01_Lft_Motor(int16_t data){
    Rte_SystemSignalAdapter_Motor_01_Lft_Motor = data;
}
int16_t Rte_Rd_DataBase_Motor_01_Lft_Motor(void){
    return Rte_SystemSignalAdapter_Motor_01_Lft_Motor;
}
void Rte_Wr_DataBase_Master_01_State(uint8_t data){
    Rte_DataBase_Master_01_State = data;
}
uint8_t Rte_Rd_SystemSignalAdapter_Master_01_State(void){
    return Rte_DataBase_Master_01_State;
}
void Rte_Wr_DataBase_Master_01_Rgt_Motor(int16_t data){
    Rte_DataBase_Master_01_Rgt_Motor = data;
}
int16_t Rte_Rd_SystemSignalAdapter_Master_01_Rgt_Motor(void){
    return Rte_DataBase_Master_01_Rgt_Motor;
}
void Rte_Wr_DataBase_Master_01_Lft_Motor(int16_t data){
    Rte_DataBase_Master_01_Lft_Motor = data;
}
int16_t Rte_Rd_SystemSignalAdapter_Master_01_Lft_Motor(void){
    return Rte_DataBase_Master_01_Lft_Motor;
}
void Rte_Wr_SystemSignalAdapter_S_Master_State(SystemState data){
    Rte_SystemSignalAdapter_S_Master_State = data;
}
SystemState Rte_Rd_ActivationDeactivation_S_Master_State(void){
    return Rte_SystemSignalAdapter_S_Master_State;
}
void Rte_Wr_ServicesManager_S_Calibration_Request(ActivationFlag data){
    Rte_ServicesManager_S_Calibration_Request = data;
}
ActivationFlag Rte_Rd_ActivationDeactivation_S_Calibration_Request(void){
    return Rte_ServicesManager_S_Calibration_Request;
}
void Rte_Wr_protocol_S_Timeout(ActivationFlag data){
    Rte_protocol_S_Timeout = data;
}
ActivationFlag Rte_Rd_ActivationDeactivation_S_Timeout(void){
    return Rte_protocol_S_Timeout;
}
void Rte_Wr_HealthMonitor_S_Health_Status(SwcStatus data){
    Rte_HealthMonitor_S_Health_Status = data;
}
SwcStatus Rte_Rd_ActivationDeactivation_S_Health_Status(void){
    return Rte_HealthMonitor_S_Health_Status;
}
void Rte_Wr_MemManager_S_Memory_Status(SwcStatus data){
    Rte_MemManager_S_Memory_Status = data;
}
SwcStatus Rte_Rd_ActivationDeactivation_S_Memory_Status(void){
    return Rte_MemManager_S_Memory_Status;
}
void Rte_Wr_CalibrationManager_S_Calibration_Status(SwcStatus data){
    Rte_CalibrationManager_S_Calibration_Status = data;
}
SwcStatus Rte_Rd_ActivationDeactivation_S_Calibration_Status(void){
    return Rte_CalibrationManager_S_Calibration_Status;
}
void Rte_Wr_MotionControl_S_Motion_Status(SwcStatus data){
    Rte_MotionControl_S_Motion_Status = data;
}
SwcStatus Rte_Rd_ActivationDeactivation_S_Motion_Status(void){
    return Rte_MotionControl_S_Motion_Status;
}
void Rte_Wr_HealthMonitor_S_System_Health(uint8_t data){
    Rte_HealthMonitor_S_System_Health = data;
}
uint8_t Rte_Rd_ActivationDeactivation_S_System_Health(void){
    return Rte_HealthMonitor_S_System_Health;
}
void Rte_Wr_ActivationDeactivation_P_System_State(SystemState data){
    Rte_ActivationDeactivation_P_System_State = data;
}
SystemState Rte_Rd_SystemSignalAdapter_P_System_State(void){
    return Rte_ActivationDeactivation_P_System_State;
}
void Rte_Wr_ActivationDeactivation_S_Motion_On_Off(ActivationFlag data){
    Rte_ActivationDeactivation_S_Motion_On_Off = data;
}
ActivationFlag Rte_Rd_MotionControl_S_Motion_On_Off(void){
    return Rte_ActivationDeactivation_S_Motion_On_Off;
}
void Rte_Wr_ActivationDeactivation_S_Calibration_On_Off(ActivationFlag data){
    Rte_ActivationDeactivation_S_Calibration_On_Off = data;
}
ActivationFlag Rte_Rd_CalibrationManager_S_Calibration_On_Off(void){
    return Rte_ActivationDeactivation_S_Calibration_On_Off;
}
void Rte_Wr_ActivationDeactivation_S_System_Error_Code(uint8_t data){
    Rte_ActivationDeactivation_S_System_Error_Code = data;
}
uint8_t Rte_Rd_SystemSignalAdapter_S_System_Error_Code(void){
    return Rte_ActivationDeactivation_S_System_Error_Code;
}
void Rte_Wr_MemManager_S_System_Calibrated(ControlFlag data){
    Rte_MemManager_S_System_Calibrated = data;
}
ControlFlag Rte_Rd_SystemSignalAdapter_S_System_Calibrated(void){
    return Rte_MemManager_S_System_Calibrated;
}
void Rte_Wr_MemManager_S_System_Configured(ControlFlag data){
    Rte_MemManager_S_System_Configured = data;
}
ControlFlag Rte_Rd_SystemSignalAdapter_S_System_Configured(void){
    return Rte_MemManager_S_System_Configured;
}
void Rte_Wr_EncodersDriver_S_Rgt_Spd(int16_t data){
    Rte_EncodersDriver_S_Rgt_Spd = data;
}
int16_t Rte_Rd_SystemSignalAdapter_S_Rgt_Spd(void){
    return Rte_EncodersDriver_S_Rgt_Spd;
}
void Rte_Wr_EncodersDriver_S_Lft_Spd(int16_t data){
    Rte_EncodersDriver_S_Lft_Spd = data;
}
int16_t Rte_Rd_SystemSignalAdapter_S_Lft_Spd(void){
    return Rte_EncodersDriver_S_Lft_Spd;
}
void Rte_Wr_SystemSignalAdapter_S_Rgt_Target(int16_t data){
    Rte_SystemSignalAdapter_S_Rgt_Target = data;
}
int16_t Rte_Rd_MotionControl_S_Rgt_Target(void){
    return Rte_SystemSignalAdapter_S_Rgt_Target;
}
void Rte_Wr_SystemSignalAdapter_S_Lft_Target(int16_t data){
    Rte_SystemSignalAdapter_S_Lft_Target = data;
}
int16_t Rte_Rd_MotionControl_S_Lft_Target(void){
    return Rte_SystemSignalAdapter_S_Lft_Target;
}
void Rte_Wr_ServicesManager_S_Set_Control_Params(ControlParameters data){
    Rte_ServicesManager_S_Set_Control_Params = data;
}
ControlParameters Rte_Rd_MemManager_S_Set_Control_Params(void){
    return Rte_ServicesManager_S_Set_Control_Params;
}
void Rte_Wr_ServicesManager_S_Set_System_Config(uint8_t data){
    Rte_ServicesManager_S_Set_System_Config = data;
}
uint8_t Rte_Rd_MemManager_S_Set_System_Config(void){
    return Rte_ServicesManager_S_Set_System_Config;
}
void Rte_Wr_MemManager_S_Control_Parameters(ControlParameters data){
    Rte_MemManager_S_Control_Parameters = data;
}
ControlParameters Rte_Rd_MotionControl_S_Control_Parameters(void){
    return Rte_MemManager_S_Control_Parameters;
}
void Rte_Wr_MotionControl_S_Rgt_Pwr(int16_t data){
    Rte_MotionControl_S_Rgt_Pwr = data;
}
int16_t Rte_Rd_MotorsDriver_S_Rgt_Pwr(void){
    return Rte_MotionControl_S_Rgt_Pwr;
}
void Rte_Wr_MotionControl_S_Lft_Pwr(int16_t data){
    Rte_MotionControl_S_Lft_Pwr = data;
}
int16_t Rte_Rd_MotorsDriver_S_Lft_Pwr(void){
    return Rte_MotionControl_S_Lft_Pwr;
}
void Rte_Wr_TemperatureDriver_S_Rgt_Temp(uint8_t data){
    Rte_TemperatureDriver_S_Rgt_Temp = data;
}
uint8_t Rte_Rd_HealthMonitor_S_Rgt_Temp(void){
    return Rte_TemperatureDriver_S_Rgt_Temp;
}
void Rte_Wr_TemperatureDriver_S_Lft_Temp(uint8_t data){
    Rte_TemperatureDriver_S_Lft_Temp = data;
}
uint8_t Rte_Rd_HealthMonitor_S_Lft_Temp(void){
    return Rte_TemperatureDriver_S_Lft_Temp;
}
void Rte_Wr_TemperatureDriver_S_Ctrl_Temp(uint8_t data){
    Rte_TemperatureDriver_S_Ctrl_Temp = data;
}
uint8_t Rte_Rd_HealthMonitor_S_Ctrl_Temp(void){
    return Rte_TemperatureDriver_S_Ctrl_Temp;
}
void Rte_Wr_TemperatureDriver_S_Dvr_Temp(uint8_t data){
    Rte_TemperatureDriver_S_Dvr_Temp = data;
}
uint8_t Rte_Rd_HealthMonitor_S_Dvr_Temp(void){
    return Rte_TemperatureDriver_S_Dvr_Temp;
}
void Rte_Wr_VoltageDriver_S_Rgt_0_Volt(uint8_t data){
    Rte_VoltageDriver_S_Rgt_0_Volt = data;
}
uint8_t Rte_Rd_HealthMonitor_S_Rgt_0_Volt(void){
    return Rte_VoltageDriver_S_Rgt_0_Volt;
}
void Rte_Wr_VoltageDriver_S_Rgt_1_Volt(uint8_t data){
    Rte_VoltageDriver_S_Rgt_1_Volt = data;
}
uint8_t Rte_Rd_HealthMonitor_S_Rgt_1_Volt(void){
    return Rte_VoltageDriver_S_Rgt_1_Volt;
}
void Rte_Wr_VoltageDriver_S_Lft_0_Volt(uint8_t data){
    Rte_VoltageDriver_S_Lft_0_Volt = data;
}
uint8_t Rte_Rd_HealthMonitor_S_Lft_0_Volt(void){
    return Rte_VoltageDriver_S_Lft_0_Volt;
}
void Rte_Wr_VoltageDriver_S_Lft_1_Volt(uint8_t data){
    Rte_VoltageDriver_S_Lft_1_Volt = data;
}
uint8_t Rte_Rd_HealthMonitor_S_Lft_1_Volt(void){
    return Rte_VoltageDriver_S_Lft_1_Volt;
}
void Rte_Wr_MemManager_S_System_Configuration(uint8_t data){
    Rte_MemManager_S_System_Configuration = data;
}
uint8_t Rte_Rd_HealthMonitor_S_System_Configuration(void){
    return Rte_MemManager_S_System_Configuration;
}
void Rte_Wr_MemDriver_S_Data_Rd(char* data){
    Rte_MemDriver_S_Data_Rd = data;
}
char* Rte_Rd_MemManager_S_Data_Rd(void){
    return Rte_MemDriver_S_Data_Rd;
}
void Rte_Wr_MemManager_S_Data_Ad(uint16_t data){
    Rte_MemManager_S_Data_Ad = data;
}
uint16_t Rte_Rd_MemDriver_S_Data_Ad(void){
    return Rte_MemManager_S_Data_Ad;
}
void Rte_Wr_MemManager_S_Data_Ln(uint16_t data){
    Rte_MemManager_S_Data_Ln = data;
}
uint16_t Rte_Rd_MemDriver_S_Data_Ln(void){
    return Rte_MemManager_S_Data_Ln;
}
void Rte_Wr_MemManager_S_Data_Wr(char* data){
    Rte_MemManager_S_Data_Wr = data;
}
char* Rte_Rd_MemDriver_S_Data_Wr(void){
    return Rte_MemManager_S_Data_Wr;
}