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
#include "config/misc_config.h"

#include "osd/osd.h"
#include "osd/osd_ui.h"
#include "osd/1bit_font.h"

#include "controls/buttons.h"

#include "interfaces/composite.h"
#include "interfaces/hdmi.h"
#include "interfaces/vga.h"

#include "peripherals/ddc.h"

#include "scaler/scaling.h"

void main()
{
    // Write EDID at first opportunity, else some video cards may mark the scaler as unavailable if using cold plug with constant Hot Plug Detection
    UploadEDID(DDC0, testEDID);
    UploadEDID(DDC1, testEDID);
    UploadEDID(DDC2, testEDID);

    for (uint16_t i = 0; i < 0xffff; i++) FeedWatchdog(); // Add grace period to allow I2C Programming before switching to UART

    CKCON = InsertBits8(CKCON, 0, 3, 0b000); // Set MOVX stretch value to 0 (REF: RTD2660 datasheet, page 278)
    ISP_MCU_CLOCK_CONTROL |= (1 << 6); // Keep timers running while MCU is stopped by SPI flash access
    InitSysTimer();
    InitUART(UART_BAUD, UART_TIMER2); SwitchToUART(); putchar('\n');
    EA = 1; // Enable all interrupts

    SetGPIOShare(DISPLAY_POWER_ENABLE_PIN, PUSH_PULL_OUT);
    SetGPIO(DISPLAY_POWER_ENABLE_PIN, 1^!DISPLAY_POWER_ACTIVE_LEVEL);
    SetGPIOShare(BACKLIGHT_ENABLE_PIN, PUSH_PULL_OUT);
    SetGPIO(BACKLIGHT_ENABLE_PIN, 1^!BACKLIGHT_ENABLE_ACTIVE_LEVEL);

    SetGPIOShare(MIRROR_HORIZONTAL_PIN, PUSH_PULL_OUT);
    SetGPIOShare(MIRROR_VERTICAL_PIN, PUSH_PULL_OUT);
    SetGPIO(MIRROR_HORIZONTAL_PIN, HOR_MIRRROR);
    SetGPIO(MIRROR_VERTICAL_PIN, VER_MIRRROR);

    InitScaler();
    SetOverlayColor(0x75, 0x18, 0xA1);

    OSDInit();
    const char* entries[]= { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
    OSDCreateMenu("Main", entries, 5);

    InitHDMI(TMDS1);

    while (1)
    {
        delayMS(100);
    }
}
