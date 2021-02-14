#include "Os_TimeServices.h"
#include "Arduino.h"

uint32_t os_timer_ms(void)
{
	return (uint32_t)millis();
}

uint32_t os_timer_us(void)
{
	return (uint32_t)micros();
}

void os_wait_ms(uint16_t)
{
	delay(10);
}