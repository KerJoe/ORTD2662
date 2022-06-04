#include <stdint.h>

uint8_t InsertBits8(uint8_t value, uint8_t bitsPosition, uint8_t bitsLength, uint8_t bits)
{
    uint8_t clearMask = 0;
    for (uint8_t i = bitsPosition; i < bitsPosition + bitsLength; i++) clearMask |= (1 << i);
    return (value & (~clearMask)) | (bits << bitsPosition);
}

uint8_t ExtractBits8(uint8_t value, uint8_t bitsPosition, uint8_t bitsLength)
{
    uint8_t clearMask = 0;
    for (uint8_t i = bitsPosition; i < bitsPosition + bitsLength; i++) clearMask |= (1 << i);
    return (value & clearMask) >> bitsPosition;
}