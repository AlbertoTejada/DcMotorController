#ifndef _PWM_H_
#define _PWM_H_

#include <stdint.h>

#define PWM_MOTOR1_PIN (5U)
#define PWM_MOTOR2_PIN (6U)
#define SERVO_PIN (9U)

#if defined(__cplusplus)
extern "C" {
#endif

void Pwm_Init(void);

void Pwm_ReadInputs(void);

void Pwm_Main(void);

void Pwm_Task(void);

void Pwm_Set(const uint8_t pin, const uint8_t value);

#if defined(__cplusplus)
} // Closing brace for extern C
#endif

#endif // _PWM_H_ 



