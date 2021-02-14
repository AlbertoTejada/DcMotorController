#include <Arduino.h>
#include <TaskScheduler.h>
#include "Mcp2515.h"
#include "DataBase.h"
#include "SpeedControl.h"
#include "Pwm.h"
#include "Encoders.h"


#define CS_PIN (10U)

// Callback methods prototypes
void t1Callback();
void t2Callback();
void t3Callback();
//void t4Callback();

//Tasks
Task t4();
Task t1(50, TASK_FOREVER, &t1Callback);
Task t2(100, TASK_FOREVER, &t2Callback);
Task t3(20, TASK_FOREVER, &t3Callback);
//Task t4(10, TASK_FOREVER, &t4Callback);

Scheduler runner; 

void t1Callback()
{
  struct can_frame canMsgRecv;
  MCP2515_ERROR msgrcv = readMessage(&canMsgRecv);

  if (msgrcv == (MCP2515_ERROR)ERROR_OK)
  {
    get_msg(&canMsgRecv);
  }
}

void t2Callback()
{
  uint32_t canid = (uint32_t)0x01u; // DBC_SPEED_AND_DIRECTION_FRAME_ID;
  struct can_frame canMsgSend = set_msg(canid);
  sendMessage(&canMsgSend);
}

void t3Callback()
{
  Encoders_Task();
  SpeedCtrl_Task();
  Pwm_Task();

  Serial.print("enc: ");
  Serial.print(Rte_Rd_SystemSignalAdapter_S_Rgt_Spd());
  Serial.print(", pwm: ");
  Serial.print(Rte_Rd_MotorsDriver_S_Rgt_Pwr());
  Serial.print(", trg: ");
  Serial.print(Rte_Rd_MotionControl_S_Rgt_Target());
  Serial.print(", act: ");  
  Serial.println(Rte_Rd_DataBase_Motor_01_Rgt_Motor());
}

void setup () {

  Serial.begin(9600);

  runner.init();
  runner.addTask(t1);
  runner.addTask(t2);
  runner.addTask(t3);

  mcp2515_init(CS_PIN);
  reset();
  setBitrate(CAN_200KBPS, MCP_8MHZ);
  setNormalMode();

  SpeedCtrl_Init();
  Pwm_Init();
  Encoders_Init();
  
  t1.enable();
  t2.enable();
  t3.enable();
}

void loop ()
{
  runner.execute();
}

