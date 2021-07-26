#pragma once

#include <stdint.h>

extern uint32_t sysTimerCount;

//#define SYSTEM_TIMER_DIV(__FREQ) (256 - (1/(__FREQ / 12) * 0.0001))
#define SYSTEM_TIMER_DIV(__FREQ) (256 - (__FREQ / 120000)) // 100 us

void SysTimerIRQ() __interrupt(1);

void delayMS(uint32_t ms);

void InitSysTimer();