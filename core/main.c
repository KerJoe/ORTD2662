#include <stdint.h>
#include <stdio.h>

#include "peripherals/sfr.h"
#include "peripherals/xsfr.h"
#include "peripherals/pins.h"
#include "peripherals/uart.h"
#include "peripherals/timer.h"

#include "core/main.h"
#include "core/misc.h"
#include "core/debug.h"

void main()
{
    SetGPIOShare(GPIO11, PUSH_PULL_OUT); SetGPIO(GPIO11, 0);
    SetGPIOShare(GPIO62, PUSH_PULL_OUT); SetGPIO(GPIO62, 0);

    for (uint16_t i = 0; i < 0xffff; i++) FeedWatchdog(); // Add grace period to allow I2C Programming before switching to UART

    CKCON &= InsertBits8(CKCON, 0, 3, 0b000); // Set MOVX stretch value to 0 (REF: RTD2660 datasheet, page 278)
    ISP_MCU_CLOCK_CONTROL |= (1 << 6); // Keep timers running while MCU is stopped by SPI flash access
    //InitSysTimer();
    InitDebug();
    InitUART(9600, UART_TIMER1); SwitchToUART(); putchar('\n');
    EA = 1; // Enable all interrupts

    StartDebug();

    SwitchToI2C();
    volatile int abc = 0;
    for(;;abc++)
        FeedWatchdog();
}