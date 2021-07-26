#pragma once

#include "core/config_defines.h"

#define BOARD_FREQ                  27000000UL

#define DISPLAY_POWER_ENABLE_PIN    GPIO35
#define DISPLAY_POWER_ACTIVE_LEVEL  ACTIVE_LEVEL_LOW

#define BACKLIGHT_ENABLE_PIN        GPIO36
#define PANEL_POWER_ACTIVE_LEVEL    ACTIVE_LEVEL_LOW

#define MIRROR_VERTICAL_PIN         GPIO54
#define MIRROR_HORIZONTAL_PIN       GPIO55

#define KEYBOARD_ADC_PIN            GPIO63

#define COMPOSITE_VIDEO_0_PIN       PIN45

#define HDMI_DDC_NUMBER             1