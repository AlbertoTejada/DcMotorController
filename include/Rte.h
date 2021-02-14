#ifndef systemenviroment_h
#define systemenviroment_h

#include <stdint.h>


#if defined(__cplusplus)
extern "C" {
#endif

//System environment data types definition:

typedef enum {
    SYS_OFF = 0,
    SYS_INIT = 1,
    SYS_ACTIVE = 2,
    SYS_CONFIG = 3,
    SYS_ERROR = 255
} SystemState;

typedef enum {
    SWC_OFF = 0,
    SWC_INIT = 1,
    SWC_READY = 2,
    SWC_ACTIVE = 3,
    SWC_ERROR = 255
} SwcStatus;

typedef enum {
    ACTIVATION_OFF = 0,
    ACTIVATION_ON = 1
} ActivationFlag;

typedef enum {
    FLAG_NO = 0,
    FLAG_YES = 1
} ControlFlag;

typedef struct {
    double p;
    double i;
    double d;
    uint16_t min_fwd_spd;
    uint8_t min_fwd_pwr;
    uint16_t max_fwd_spd;
    uint16_t min_bwd_spd;
    uint8_t min_bwd_pwr;
    uint16_t max_bwd_spd;
}ControlParameters;

//System environment parameters write functions prototypes:
void Rte_Wr_protocol_Cmd(uint8_t data);
void Rte_Wr_SystemSignalAdapter_Motor_01_State(uint8_t data);
void Rte_Wr_SystemSignalAdapter_Motor_01_Calibration(uint8_t data);
void Rte_Wr_SystemSignalAdapter_Motor_01_Configuration(uint8_t data);
void Rte_Wr_SystemSignalAdapter_Motor_01_Error(uint8_t data);
void Rte_Wr_SystemSignalAdapter_Motor_01_Rgt_Motor(int32_t data);
void Rte_Wr_SystemSignalAdapter_Motor_01_Lft_Motor(int16_t data);
void Rte_Wr_DataBase_Master_01_State(uint8_t data);
void Rte_Wr_DataBase_Master_01_Rgt_Motor(int16_t data);
void Rte_Wr_DataBase_Master_01_Lft_Motor(int16_t data);
void Rte_Wr_SystemSignalAdapter_S_Master_State(SystemState data);
void Rte_Wr_ServicesManager_S_Calibration_Request(ActivationFlag data);
void Rte_Wr_protocol_S_Timeout(ActivationFlag data);
void Rte_Wr_HealthMonitor_S_Health_Status(SwcStatus data);
void Rte_Wr_MemManager_S_Memory_Status(SwcStatus data);
void Rte_Wr_CalibrationManager_S_Calibration_Status(SwcStatus data);
void Rte_Wr_MotionControl_S_Motion_Status(SwcStatus data);
void Rte_Wr_HealthMonitor_S_System_Health(uint8_t data);
void Rte_Wr_ActivationDeactivation_P_System_State(SystemState data);
void Rte_Wr_ActivationDeactivation_S_Motion_On_Off(ActivationFlag data);
void Rte_Wr_ActivationDeactivation_S_Calibration_On_Off(ActivationFlag data);
void Rte_Wr_ActivationDeactivation_S_System_Error_Code(uint8_t data);
void Rte_Wr_MemManager_S_System_Calibrated(ControlFlag data);
void Rte_Wr_MemManager_S_System_Configured(ControlFlag data);
void Rte_Wr_EncodersDriver_S_Rgt_Spd(int16_t data);
void Rte_Wr_EncodersDriver_S_Lft_Spd(int16_t data);
void Rte_Wr_SystemSignalAdapter_S_Rgt_Target(int16_t data);
void Rte_Wr_SystemSignalAdapter_S_Lft_Target(int16_t data);
void Rte_Wr_ServicesManager_S_Set_Control_Params(ControlParameters data);
void Rte_Wr_ServicesManager_S_Set_System_Config(uint8_t data);
void Rte_Wr_MemManager_S_Control_Parameters(ControlParameters data);
void Rte_Wr_MotionControl_S_Rgt_Pwr(int16_t data);
void Rte_Wr_MotionControl_S_Lft_Pwr(int16_t data);
void Rte_Wr_TemperatureDriver_S_Rgt_Temp(uint8_t data);
void Rte_Wr_TemperatureDriver_S_Lft_Temp(uint8_t data);
void Rte_Wr_TemperatureDriver_S_Ctrl_Temp(uint8_t data);
void Rte_Wr_TemperatureDriver_S_Dvr_Temp(uint8_t data);
void Rte_Wr_VoltageDriver_S_Rgt_0_Volt(uint8_t data);
void Rte_Wr_VoltageDriver_S_Rgt_1_Volt(uint8_t data);
void Rte_Wr_VoltageDriver_S_Lft_0_Volt(uint8_t data);
void Rte_Wr_VoltageDriver_S_Lft_1_Volt(uint8_t data);
void Rte_Wr_MemManager_S_System_Configuration(uint8_t data);
void Rte_Wr_MemDriver_S_Data_Rd(char* data);
void Rte_Wr_MemManager_S_Data_Ad(uint16_t data);
void Rte_Wr_MemManager_S_Data_Ln(uint16_t data);
void Rte_Wr_MemManager_S_Data_Wr(char* data);


//System environment parameters read functions prototypes:
uint8_t Rte_Rd_DataBase_Cmd(void);
uint8_t Rte_Rd_DataBase_Motor_01_State(void);
uint8_t Rte_Rd_DataBase_Motor_01_Calibration(void);
uint8_t Rte_Rd_DataBase_Motor_01_Configuration(void);
uint8_t Rte_Rd_DataBase_Motor_01_Error(void);
int32_t Rte_Rd_DataBase_Motor_01_Rgt_Motor(void);
int16_t Rte_Rd_DataBase_Motor_01_Lft_Motor(void);
uint8_t Rte_Rd_SystemSignalAdapter_Master_01_State(void);
int16_t Rte_Rd_SystemSignalAdapter_Master_01_Rgt_Motor(void);
int16_t Rte_Rd_SystemSignalAdapter_Master_01_Lft_Motor(void);
SystemState Rte_Rd_ActivationDeactivation_S_Master_State(void);
ActivationFlag Rte_Rd_ActivationDeactivation_S_Calibration_Request(void);
ActivationFlag Rte_Rd_ActivationDeactivation_S_Timeout(void);
SwcStatus Rte_Rd_ActivationDeactivation_S_Health_Status(void);
SwcStatus Rte_Rd_ActivationDeactivation_S_Memory_Status(void);
SwcStatus Rte_Rd_ActivationDeactivation_S_Calibration_Status(void);
SwcStatus Rte_Rd_ActivationDeactivation_S_Motion_Status(void);
uint8_t Rte_Rd_ActivationDeactivation_S_System_Health(void);
SystemState Rte_Rd_SystemSignalAdapter_P_System_State(void);
ActivationFlag Rte_Rd_MotionControl_S_Motion_On_Off(void);
ActivationFlag Rte_Rd_CalibrationManager_S_Calibration_On_Off(void);
uint8_t Rte_Rd_SystemSignalAdapter_S_System_Error_Code(void);
ControlFlag Rte_Rd_SystemSignalAdapter_S_System_Calibrated(void);
ControlFlag Rte_Rd_SystemSignalAdapter_S_System_Configured(void);
int16_t Rte_Rd_SystemSignalAdapter_S_Rgt_Spd(void);
int16_t Rte_Rd_SystemSignalAdapter_S_Lft_Spd(void);
int16_t Rte_Rd_MotionControl_S_Rgt_Target(void);
int16_t Rte_Rd_MotionControl_S_Lft_Target(void);
ControlParameters Rte_Rd_MemManager_S_Set_Control_Params(void);
uint8_t Rte_Rd_MemManager_S_Set_System_Config(void);
ControlParameters Rte_Rd_MotionControl_S_Control_Parameters(void);
int16_t Rte_Rd_MotorsDriver_S_Rgt_Pwr(void);
int16_t Rte_Rd_MotorsDriver_S_Lft_Pwr(void);
uint8_t Rte_Rd_HealthMonitor_S_Rgt_Temp(void);
uint8_t Rte_Rd_HealthMonitor_S_Lft_Temp(void);
uint8_t Rte_Rd_HealthMonitor_S_Ctrl_Temp(void);
uint8_t Rte_Rd_HealthMonitor_S_Dvr_Temp(void);
uint8_t Rte_Rd_HealthMonitor_S_Rgt_0_Volt(void);
uint8_t Rte_Rd_HealthMonitor_S_Rgt_1_Volt(void);
uint8_t Rte_Rd_HealthMonitor_S_Lft_0_Volt(void);
uint8_t Rte_Rd_HealthMonitor_S_Lft_1_Volt(void);
uint8_t Rte_Rd_HealthMonitor_S_System_Configuration(void);
char* Rte_Rd_MemManager_S_Data_Rd(void);
uint16_t Rte_Rd_MemDriver_S_Data_Ad(void);
uint16_t Rte_Rd_MemDriver_S_Data_Ln(void);
char* Rte_Rd_MemDriver_S_Data_Wr(void);


#if defined(__cplusplus)
} // Closing brace for extern "C"
#endif

#endif // systemenviroment_h