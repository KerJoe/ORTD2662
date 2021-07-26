#include <stdint.h>
#include <stdio.h>

#include "peripherals/sfr.h"
#include "peripherals/xsfr.h"
#include "peripherals/pins.h"
#include "peripherals/uart.h"
#include "peripherals/timer.h"

#include "core/main.h"

#include "scaler/scaler.h"
#include "scaler/scaler_access.h"

#include "config/board_config.h"

#include "osd/osd.h"
#include "osd/1bit_font.h"

#include "controls/buttons.h"

#include "interfaces/composite.h"
#include "interfaces/hdmi.h"

//__idata uint8_t t000[1];

// TODO: Disable watchdog timer ?

/*void init8051IO()
{

}*/


void main()
{
    // TODO: Write EDID at first apportunity, else some video cards may mark the scaler as unavailable if using cold plug with constant Hot Plug Detection

    for (uint16_t i = 0; i < 0xffff; i++) FeedWatchdog(); // Add grace period to allow I2C Programming before switching to UART

    InitSysTimer();
    InitUART(UART_BAUD, UART_TIMER2); SwitchToUART();
    EA = 1; // Enable all interrupts

    SetGPIODrivingCurrent(DRIVE_96_TO_97, DRIVE_HIGH); // Set Driving current for TTL DCLK and DVS

    SetGPIOShare(GPIO36, OPEN_DRAIN_OUT);
    SetGPIO(GPIO36, 0);

    SetGPIOShare(GPIO54, OPEN_DRAIN_OUT);
    SetGPIOShare(GPIO55, OPEN_DRAIN_OUT);
    SetGPIO(GPIO54, 0);
    SetGPIO(GPIO55, 1);

    InitScaler();
    SetOverlayColor(0x75, 0x18, 0xA1);
    OSDInit();

    InitComposite(2);

    InitHDMI();

    int j = 0;
    SetGPIO(GPIO36, 0); SwitchToI2C();
    while (1)
    {
        CSourceScanInputPortDVI(0);
        delayMS(100); j++;

        FeedWatchdog();
    }
}