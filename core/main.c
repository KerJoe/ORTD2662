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


// TODO: Disable watchdog timer ?

/*void init8051IO()
{

}*/

void main()
{
    // Write EDID at first opportunity, else some video cards may mark the scaler as unavailable if using cold plug with constant Hot Plug Detection
    UploadEDID(HDMI_DDC_NUMBER, testEDID);

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

    InitVGA();
    //InitHDMI();

    OSDInit();

    char* entries[]= { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
    OSDCreateMenu("Main", entries, 5);

    InitButtons();
    SwitchToI2C(); while (1)
    {
        if (ReadButtons())
        {
            if (buttonState == 0)
            {
                OSDActionUp();
            }
        }
        FeedWatchdog();
    }





    SetOverlayColor(0x75, 0x18, 0xA1);

    //InitHDMI();
    //InitComposite(2);
    InitVGA();
    //SetAPLLFrequncy(40000000UL, 37878UL);

    SwitchToI2C(); while (1)
    {
        FeedWatchdog();
    }




    OSDInit();

    //char* entries[]= { "abc", "dce" };
    OSDCreateMenu("Main", entries, 2);

    InitHDMI();

    //InitVGA();

    //InitComposite(2);

    /*ScalerWriteByte(S_SCALE_CONTROL, 0x01);

    ScalerWriteByte(S_SCALE_FACTOR_ADDRESS, 0x80);
    EnableScalerAutoIncrement(1);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, 0x0a);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, 0xe0);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, 0x00);
    EnableScalerAutoIncrement(0);
    printf("%x",ScalerReadByte(S_SCALE_FACTOR_ADDRESS));*/


    //

    int j = 0;
    SetGPIO(GPIO36, 0); SwitchToI2C();
    while (1)
    {
        FeedWatchdog();
    }
}