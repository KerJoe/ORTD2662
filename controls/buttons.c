#include <stdint.h>
#include <stdio.h>

#include "peripherals/sfr.h"
#include "peripherals/xsfr.h"
#include "peripherals/pins.h"

#include "core/misc.h"

#include "controls/buttons.h"
#include "config/board_config.h"

void InitButtons()
{
    PIN_SHARE_CONTROL03 = 0b11000000; // ADC A3 on pin 53
}

uint16_t buttonState = 0;

#define BUTTON_THRESHOLD 5

const uint8_t buttonLevels[] =
{
     0, // First button ADC level
    10, // Second button ADC level
    20, // ...
    30, // ...
    40  // ...
};

void ReadButtons()
{
    ADC_A_CONTROL |= (1 << 7) | (1 << 2); // Start ADC Conversion
    while (ADC_A_CONTROL & (1 << 7)) FeedWatchdog(); // Wait for ADC Conversion to complete
    uint8_t keyboardADCValue = 0;//KEYBOARD_ADC_CHANNEL >> 2;
    printf("Read keyboard value: %i\n", (int)keyboardADCValue);
    for (uint8_t i = 0; i < sizeof(buttonLevels); i++)
    {
        if (keyboardADCValue <= MIN(buttonLevels[i] + BUTTON_THRESHOLD, 63) &&
            keyboardADCValue >= MAX(buttonLevels[i] - BUTTON_THRESHOLD, 0))
            buttonState |=  (1 << i);
        else
            buttonState &= ~(1 << i);
    }
    printf("Button value: %X\n\n", (int)buttonState);
}