#pragma once
#include <stdint.h>

void SetCaptureWindow(uint16_t HStart, uint16_t VStart, uint16_t HActive, uint16_t VActive, uint16_t HDelay, uint16_t VDelay);
void SetFIFOWindow(uint16_t HActive, uint16_t VActive);

void ScaleUp(uint16_t inWidth, uint16_t inHeight, uint16_t outWidth, uint16_t outHeight);
void ScaleDown(uint16_t inWidth, uint16_t inHeight, uint16_t outWidth, uint16_t outHeight);