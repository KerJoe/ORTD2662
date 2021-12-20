#pragma once

#include <stdint.h>

void InitScaler();

enum POWER_MODE
{
    POWER_MODE_FULL,
    POWER_MODE_SAVING,
    POWER_MODE_DOWN
};

void SetDPLLFrequncy(uint32_t outFreq);
void SetAPLLFrequncy(uint32_t outFreq, uint32_t horFreq);
void SetVideoBrightness(uint8_t value);
void SetVideoContrast(uint8_t value);
void SetVideoHue(uint8_t value);
void SetVideoSaturation(uint8_t value);
void SetOverlayColor(uint8_t red, uint8_t green, uint8_t blue);
void EnableOverlay(uint8_t state);