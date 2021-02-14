#include <stdint.h>
#include <Arduino.h>
#include "Encoders.h"
#include "Os_TimeServices.h"
#include "Rte.h"


volatile uint16_t encoder_ch1;
volatile uint8_t  encoder_ch2;
int16_t pulse_rate;
uint16_t sample_time;


void Encoders_Init()
{
    encoder_ch1 = 0;
    encoder_ch2 = 0;
    pinMode(ENCODER1_PIN, INPUT);
    pinMode(ENCODER2_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER1_PIN), Encoders_Interruption, RISING);
}

void Encoders_Interruption()
{
    // Increase the value of the counter:
    encoder_ch1++;
    encoder_ch2 = digitalRead(ENCODER2_PIN);
}

void Encoders_Main()
{
    static uint16_t prev_sample = os_timer_us();
    uint16_t counter = encoder_ch1;
    uint8_t direction = encoder_ch2;
    encoder_ch1 = 0;

    uint16_t last_sample = os_timer_us();
    if (last_sample > prev_sample)
    {
        sample_time = last_sample - prev_sample;
    } 
    else
    {
        sample_time = (65535 - prev_sample) + last_sample ;
    }
    
    prev_sample = last_sample;

    if(direction == 0)
    {
        pulse_rate = counter;
    }
    else
    {
        pulse_rate = -counter;
    }

}

void Encoders_WriteOutputs()
{
    Rte_Wr_EncodersDriver_S_Rgt_Spd(pulse_rate);
    Rte_Wr_EncodersDriver_S_Lft_Spd(sample_time);
}

void Encoders_Task()
{
    Encoders_Main();
    Encoders_WriteOutputs();
}
