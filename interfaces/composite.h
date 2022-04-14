#pragma once

#include "peripherals/pins.h"

#define PIN_TO_VIDEO_IN(__pin)  (__pin == PIN41 ? 0 : \
                                (__pin == PIN43 ? 1 : \
                                (__pin == PIN45 ? 2 : 3 )))

void InitComposite(uint8_t videoIn);