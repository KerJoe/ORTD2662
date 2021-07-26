#pragma once

#include <stdint.h>

#include "scaler/scaler_access.h"
#include "peripherals/xsfr.h"

extern const uint8_t testEDID[];

void UploadEDID(uint8_t ddcNumber, uint8_t* data);