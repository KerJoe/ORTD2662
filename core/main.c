#include <stdint.h>
#include <stdio.h>

#include "config/board_config.h"
#include "config/misc_config.h"

#include "scaler/scaler.h"

#include "peripherals/pins.h"
#include "peripherals/xsfr.h"
#include "peripherals/timer.h"

#include "interfaces/hdmi.h"

void main()
{
    XSFRWriteByte(WDT_CONTROL, 0x00);

    SetGPIOShare(DISPLAY_POWER_ENABLE_PIN, PUSH_PULL_OUT);
    SetGPIO(DISPLAY_POWER_ENABLE_PIN, 1^!DISPLAY_POWER_ACTIVE_LEVEL);
    SetGPIOShare(BACKLIGHT_ENABLE_PIN, PUSH_PULL_OUT);
    SetGPIO(BACKLIGHT_ENABLE_PIN, 1^!BACKLIGHT_ENABLE_ACTIVE_LEVEL);

    SetGPIOShare(MIRROR_HORIZONTAL_PIN, PUSH_PULL_OUT);
    SetGPIOShare(MIRROR_VERTICAL_PIN, PUSH_PULL_OUT);
    SetGPIO(MIRROR_HORIZONTAL_PIN, HOR_MIRRROR);
    SetGPIO(MIRROR_VERTICAL_PIN, VER_MIRRROR);

    InitScaler();
    SetOverlayColor(0xff, 0x00, 0xff);

    InitHDMI(1);

#   ifdef __SDCC
    while(1);
#   endif
}