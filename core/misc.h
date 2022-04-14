#pragma once

#include <stdint.h>

#define FeedWatchdog() WDT_CONTROL = (1 << 6)

#define MIN(__a,__b) (((__a) < (__b)) ? (__a) : (__b))
#define MAX(__a,__b) (((__a) > (__b)) ? (__a) : (__b))

#define KHZ 1000
#define MHZ 1000000UL

uint8_t InsertBits8(uint8_t value, uint8_t bitsPosition, uint8_t bitsLength, uint8_t bits);
uint8_t ExtractBits8(uint8_t value, uint8_t bitsPosition, uint8_t bitsLength);

#define WRITE_BITS(__address, __bits_position, __bits_length, __bits, __read_byte_func, __write_byte_func) \ 
    __write_byte_func(InsertBits8(__read_byte_func(__address), __bits_position, __bits_length, __bits))
#define  WRITE_BIT(__address, __bit_position, __bit, __read_byte_func, __write_byte_func) \ 
    WRITE_BITS(__address, __bit_position, 1, __read_byte_func, __write_byte_func)
    