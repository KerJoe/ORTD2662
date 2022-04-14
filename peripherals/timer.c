#include <stdint.h>

#include "peripherals/timer.h"
#include "peripherals/sfr.h"
#include "peripherals/pins.h"

#include "core/main.h"
#include "core/debug.h"

typedef struct
{
    void*    callback;
    uint32_t lastTime;
    uint32_t period;
    uint8_t  doOnce : 1;
    uint8_t  active : 1;
    uint8_t  acknowledged : 1;
} _EVENT;

#ifdef __SDCC

uint32_t sysTimerCount = 0;

volatile uint8_t delayActive = 0;
volatile uint32_t delayTime;

void delayMS(uint32_t ms)
{
    if (ms == 0) return;
    delayTime = ms * 10;
    delayActive = 1;
    while (delayActive) WDT_CONTROL = (1 << 6);
}

void SysTimerIRQ() __interrupt(1) __naked
{InterruptPrologue
    sysTimerCount++;

    if (delayActive) delayTime--;
    if (delayTime == 0) delayActive = 0;

    TF0 = 0;
InterruptEpilogue}

void InitSysTimer()
{
    TMOD |= 0b00000010;
    //TH0 = SYSTEM_TIMER_DIV(PERIPHERAL_FREQ);
    TH0 = 212;
    TR0 = 1;

    ET0 = 1;
}

#else // #ifdef __SDCC

#include <unistd.h>

void InitSysTimer() { }

void delayMS(uint32_t ms)
{
    usleep(ms*1000);
}

#endif // #ifdef __SDCC