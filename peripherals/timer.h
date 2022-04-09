#pragma once

#include <stdint.h>

extern uint32_t sysTimerCount;

#define SYSTEM_TIMER_DIV(__FREQ) (256 - (__FREQ / 120000)) // 100 us
                              // (256 - (1/(__FREQ / 12) * 0.0001))

#ifdef __SDCC
void SysTimerIRQ() __interrupt(1);
#endif

void delayMS(uint32_t ms);

void InitSysTimer();