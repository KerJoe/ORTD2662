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

    CKCON &= InsertBits8(CKCON, 0, 3, 0b000); // Set MOVX stretch value to 0 (REF: RTD2660 datasheet, page 278)
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

EnableScalerAutoIncrement(1);
ScalerWriteByte(0x16, 0x00); delayMS(1);
ScalerWriteByte(0x9F, 0x00); delayMS(1);
ScalerWriteByte(0x47, 0x00); delayMS(1);
ScalerWriteByte(0x5C, 0x06); delayMS(1);
ScalerWriteByte(0x5C, 0x06); delayMS(1);
ScalerWriteByte(0x5D, 0x20); delayMS(1);
ScalerWriteByte(0x5C, 0x00); delayMS(1);
ScalerWriteByte(0xCE, 0x56); delayMS(1);
ScalerWriteByte(0xC7, 0x55); delayMS(1);
ScalerWriteByte(0xC8, 0x15); delayMS(1);
ScalerWriteByte(0xCF, 0x50); delayMS(1);
ScalerWriteByte(0xD0, 0x50); delayMS(1);
ScalerWriteByte(0xD1, 0x50); delayMS(1);
ScalerWriteByte(0x49, 0x02); delayMS(1);
ScalerWriteByte(0x47, 0x00); delayMS(1);
ScalerWriteByte(0x9F, 0x00); delayMS(1);
ScalerWriteByte(0xC6, 0x38); delayMS(1);
ScalerWriteByte(0x16, 0x00); delayMS(1);
ScalerWriteByte(0x32, 0x00); delayMS(1);
ScalerWriteByte(0x49, 0x06); delayMS(1);
ScalerWriteByte(0xD5, 0x00); delayMS(1);
ScalerWriteByte(0xD6, 0x58); delayMS(1);
ScalerWriteByte(0x4F, 0x00); delayMS(1);
ScalerWriteByte(0x4F, 0x01); delayMS(1);
ScalerWriteByte(0x4F, 0x83); delayMS(1);
ScalerWriteByte(0x4C, 0x60); delayMS(1);
ScalerWriteByte(0x4D, 0xB2); delayMS(1);
ScalerWriteByte(0x4F, 0xC0); delayMS(1);
ScalerWriteByte(0x47, 0x00); delayMS(1);
ScalerWriteByte(0x47, 0x40); delayMS(1);
ScalerWriteByte(0x47, 0x60); delayMS(1);
ScalerWriteByte(0x47, 0x60); delayMS(1);
ScalerWriteByte(0x9F, 0x00); delayMS(1);
ScalerWriteByte(0xC6, 0x38); delayMS(1);
ScalerWriteByte(0x16, 0x00); delayMS(1);
ScalerWriteByte(0x32, 0x00); delayMS(1);
ScalerWriteByte(0x49, 0x66); delayMS(1);
ScalerWriteByte(0xD5, 0x00); delayMS(1);
ScalerWriteByte(0xD6, 0x58); delayMS(1);
ScalerWriteByte(0x4F, 0xC0); delayMS(1);
ScalerWriteByte(0x4F, 0xC1); delayMS(1);
ScalerWriteByte(0x4F, 0xC3); delayMS(1);
ScalerWriteByte(0x4C, 0xE0); delayMS(1);
ScalerWriteByte(0x4D, 0xB2); delayMS(1);
ScalerWriteByte(0x4F, 0xC0); delayMS(1);
ScalerWriteByte(0x47, 0x20); delayMS(1);
ScalerWriteByte(0x47, 0x40); delayMS(1);
ScalerWriteByte(0x9F, 0x00); delayMS(1);
ScalerWriteByte(0xC6, 0x38); delayMS(1);
ScalerWriteByte(0x16, 0x00); delayMS(1);
ScalerWriteByte(0x32, 0x00); delayMS(1);
ScalerWriteByte(0x49, 0x66); delayMS(1);
ScalerWriteByte(0xD5, 0x00); delayMS(1);
ScalerWriteByte(0xD6, 0x58); delayMS(1);
ScalerWriteByte(0x4F, 0xC0); delayMS(1);
ScalerWriteByte(0x4F, 0xC1); delayMS(1);
ScalerWriteByte(0x4F, 0xC3); delayMS(1);
ScalerWriteByte(0x4C, 0xE0); delayMS(1);
ScalerWriteByte(0x4D, 0xB2); delayMS(1);
ScalerWriteByte(0x4F, 0xC0); delayMS(1);
ScalerWriteByte(0x47, 0x20); delayMS(1);
ScalerWriteByte(0x47, 0x40); delayMS(1);
ScalerWriteByte(0x9F, 0x00); delayMS(1);
ScalerWriteByte(0xC6, 0x38); delayMS(1);
ScalerWriteByte(0x16, 0x00); delayMS(1);
ScalerWriteByte(0x32, 0x00); delayMS(1);
ScalerWriteByte(0x49, 0x66); delayMS(1);
ScalerWriteByte(0xD5, 0x00); delayMS(1);
ScalerWriteByte(0xD6, 0x58); delayMS(1);
ScalerWriteByte(0x4F, 0xC0); delayMS(1);
ScalerWriteByte(0x4F, 0xC1); delayMS(1);
ScalerWriteByte(0x4F, 0xC3); delayMS(1);
ScalerWriteByte(0x4C, 0xE0); delayMS(1);
ScalerWriteByte(0x4D, 0xB2); delayMS(1);
ScalerWriteByte(0x4F, 0xC0); delayMS(1);
ScalerWriteByte(0x47, 0x20); delayMS(1);
ScalerWriteByte(0x47, 0x40); delayMS(1);
ScalerWriteByte(0x52, 0x20); delayMS(1);
ScalerWriteByte(0x52, 0x40); delayMS(1);
ScalerWriteByte(0x58, 0x00); delayMS(1);
ScalerWriteByte(0x11, 0x00); delayMS(1);
ScalerWriteByte(0x47, 0x60); delayMS(1);
ScalerWriteByte(0x52, 0x22); delayMS(1);
ScalerWriteByte(0x52, 0x42); delayMS(1);
ScalerWriteByte(0x58, 0x00); delayMS(1);
ScalerWriteByte(0x11, 0x00); delayMS(1);
ScalerWriteByte(0x9F, 0x02); delayMS(1);


ScalerWriteByte(0x49, 0x66); delayMS(1);
ScalerWriteByte(0x47, 0x60); delayMS(1);
ScalerWriteByte(0x52, 0x22); delayMS(1);
ScalerWriteByte(0x52, 0x42); delayMS(1);
ScalerWriteByte(0x58, 0x00); delayMS(1);
ScalerWriteByte(0x11, 0x00); delayMS(1);


ScalerWriteByte(0x49, 0x66); delayMS(1);
ScalerWriteByte(0x47, 0x60); delayMS(1);
ScalerWriteByte(0x52, 0x22); delayMS(1);
ScalerWriteByte(0x52, 0x42); delayMS(1);
ScalerWriteByte(0x58, 0x00); delayMS(1);
ScalerWriteByte(0x11, 0x00); delayMS(1);
ScalerWriteByte(0x9F, 0x02); delayMS(1);


ScalerWriteByte(0x49, 0x66); delayMS(1);
ScalerWriteByte(0x47, 0x60); delayMS(1);
ScalerWriteByte(0x52, 0x22); delayMS(1);
ScalerWriteByte(0x52, 0x42); delayMS(1);
ScalerWriteByte(0x58, 0x00); delayMS(1);
ScalerWriteByte(0x11, 0x00); delayMS(1);
ScalerWriteByte(0x9F, 0x02); delayMS(1);


ScalerWriteByte(0x49, 0x66); delayMS(1);
ScalerWriteByte(0x47, 0x60); delayMS(1);
ScalerWriteByte(0x52, 0x22); delayMS(1);
ScalerWriteByte(0x52, 0x42); delayMS(1);
ScalerWriteByte(0x58, 0x00); delayMS(1);
ScalerWriteByte(0x11, 0x00); delayMS(1);
ScalerWriteByte(0x9F, 0x01); delayMS(1);
ScalerWriteByte(0x9F, 0x01); delayMS(1);
ScalerWriteByte(0xA0, 0x08); delayMS(1);
ScalerWriteByte(0xB9, 0xFF); delayMS(1);
ScalerWriteByte(0xAE, 0x65); delayMS(1);
ScalerWriteByte(0xB1, 0x75); delayMS(1);
ScalerWriteByte(0xB1, 0x73); delayMS(1);
ScalerWriteByte(0xB2, 0xE7); delayMS(1);
ScalerWriteByte(0x9F, 0x01); delayMS(1);
ScalerWriteByte(0xAD, 0x21); delayMS(1);
ScalerWriteByte(0xAC, 0x0E); delayMS(1);
ScalerWriteByte(0xAD, 0xD1); delayMS(1);
ScalerWriteByte(0xA4, 0x80); delayMS(1);
ScalerWriteByte(0xA1, 0x00); delayMS(1);
ScalerWriteByte(0xA2, 0x09); delayMS(1);
ScalerWriteByte(0xB6, 0x10); delayMS(1);
ScalerWriteByte(0xB9, 0x05); delayMS(1);
ScalerWriteByte(0xBA, 0x1E); delayMS(1);
ScalerWriteByte(0xA3, 0x10); delayMS(1);
ScalerWriteByte(0xB4, 0x00); delayMS(1);
ScalerWriteByte(0x03, 0x00); delayMS(1);
ScalerWriteByte(0x03, 0x00); delayMS(1);
ScalerWriteByte(0xB1, 0x73); delayMS(1);
ScalerWriteByte(0xB2, 0xE7); delayMS(1);
ScalerWriteByte(0xB4, 0x00); delayMS(1);
ScalerWriteByte(0x03, 0x00); delayMS(1);
ScalerWriteByte(0x03, 0x00); delayMS(1);
ScalerWriteByte(0x9F, 0x01); delayMS(1);
ScalerWriteByte(0x9F, 0x01); delayMS(1);
ScalerWriteByte(0xAF, 0x08); delayMS(1);
ScalerWriteByte(0x9F, 0x00); delayMS(1);
ScalerWriteByte(0xC6, 0x3F); delayMS(1);
ScalerWriteByte(0x9F, 0x01); delayMS(1);
EnableScalerAutoIncrement(0);

InitVGA();

    printf("PLL STATUS: 0x%x", ScalerReadByte(0xB8));

    SwitchToI2C(); while (1)
    {
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

    char* entries[]= { "abc", "dce" };
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