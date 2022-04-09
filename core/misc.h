#pragma once

#include <stdint.h>

#define FeedWatchdog() WDT_CONTROL = (1 << 6)

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define KHZ 1000
#define MHZ 1000000UL

uint8_t InsertBits8(uint8_t value, uint8_t bitsPosition, uint8_t bitsLength, uint8_t bits);
uint8_t ExtractBits8(uint8_t value, uint8_t bitsPosition, uint8_t bitsLength);