#pragma once

#include "core/config_defines.h"


#define BOARD_FREQ                      27000000UL


// GPIO Defintions
#define DISPLAY_POWER_ENABLE_PIN        PIN100
#define DISPLAY_POWER_ACTIVE_LEVEL      ACTIVE_LEVEL_HIGH

#define BACKLIGHT_ENABLE_PIN            PIN101
#define BACKLIGHT_ENABLE_ACTIVE_LEVEL   ACTIVE_LEVEL_HIGH

#define MIRROR_VERTICAL_PIN             PIN098
#define MIRROR_HORIZONTAL_PIN           PIN099

#define KEYBOARD_ADC_PIN                PIN053


// Interface settings

// TMDS Port 0
#define TMDS0_TYPE      TMDS_HDMI   // Possible values: TMDS_DVI, TMDS_HDMI
#define TMDS0_DDC       DDC1        // Possible values: DDC0, DDC1, DDC2
#define TMDS0_SWAP_RB   TRUE        // Enable this option if red (channel 2) and blue (channel 0) differntial pairs are swapped on the PCB layout between scaler and connector
#define TMDS0_SWAP_PN   TRUE        // Enable this option if positive and negative traces of a differntial pair are swapped on the PCB layout between scaler and connector

// TMDS Port 1
#define TMDS1_TYPE      TMDS_DVI    // Possible values: TMDS_DVI, TMDS_HDMI
#define TMDS1_DDC       DDC2        // Possible values: DDC0, DDC1, DDC2
#define TMDS1_SWAP_RB   TRUE        // Enable this option if red (channel 2) and blue (channel 0) differntial pairs are swapped on the PCB layout between scaler and connector
#define TMDS1_SWAP_PN   FALSE       // Enable this option if positive and negative traces of a differntial pair are swapped on the PCB layout between scaler and connector