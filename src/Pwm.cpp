#include <Arduino.h>
#include "Pwm.h"
#include "Rte.h"

int16_t motor_pwm;
int16_t servo_pwm;

void Pwm_Init(void)
{
    pinMode(PWM_MOTOR1_PIN, OUTPUT);
    pinMode(PWM_MOTOR2_PIN, OUTPUT);
    pinMode(SERVO_PIN, OUTPUT);

    motor_pwm = 0;
    servo_pwm = 0;

    Pwm_Set((uint8_t)PWM_MOTOR1_PIN, 0U);
    Pwm_Set((uint8_t)PWM_MOTOR2_PIN, 0U);
    Pwm_Set((uint8_t)SERVO_PIN, 0U);
}

void Pwm_ReadInputs(void)
{
    motor_pwm = Rte_Rd_MotorsDriver_S_Rgt_Pwr();
    servo_pwm = Rte_Rd_MotorsDriver_S_Lft_Pwr();
}

void Pwm_Main(void)
{
    if((motor_pwm >= 0) && (motor_pwm < 255))
    {
        Pwm_Set((uint8_t)PWM_MOTOR2_PIN, (uint8_t)motor_pwm);
        Pwm_Set((uint8_t)PWM_MOTOR1_PIN, (uint8_t)0);
    }
    else if (motor_pwm > 255)
    {
        Pwm_Set((uint8_t)PWM_MOTOR2_PIN, (uint8_t)255);
        Pwm_Set((uint8_t)PWM_MOTOR1_PIN, (uint8_t)0);

    }
    else if ((motor_pwm < 0) && (motor_pwm > -255))
    {
        Pwm_Set((uint8_t)PWM_MOTOR2_PIN, (uint8_t)0);
        Pwm_Set((uint8_t)PWM_MOTOR1_PIN, (uint8_t)(-motor_pwm));
    }
    else
    {
        Pwm_Set((uint8_t)PWM_MOTOR2_PIN, (uint8_t)0);
        Pwm_Set((uint8_t)PWM_MOTOR1_PIN, (uint8_t)255);
    }
    

}

void Pwm_Set(const uint8_t pin, const uint8_t value)
{
    analogWrite(pin, value);
}

void Pwm_Task(void)
{
    Pwm_ReadInputs();
    Pwm_Main();
 } 