#pragma once

#include <stdint.h>

extern uint16_t buttonState;

void InitButtons();
uint8_t ReadButtons();