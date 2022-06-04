#pragma once

#include <stdint.h>

typedef struct
{
    // Paramaters that are used to determine the mode
    uint8_t  HSPolarity : 1;    // Horizontal Sync Polarity, NEGATIVE_SYNC_POLARITY or POSITIVE_SYNC_POLARITY
    uint8_t  VSPolarity : 1;    // Vertical Sync Polarity, NEGATIVE_SYNC_POLARITY or POSITIVE_SYNC_POLARITY
    uint32_t HFreq;             // Horizontal frequency, in Hz
    uint8_t  VFreq;             // Vertical frequency, in Hz
    // Parameters of the mode
    uint16_t HActive;           // Horizontal Active Picture Width, in Pixels
    uint16_t VActive;           // Vertical Active Picture Height, in Number of lines
    uint16_t HStart;            // Horizontal Start Period (Sync_Pulse + Back_Porch), in Pixels
    uint16_t VStart;            // Vertical Start Period (Sync_Pulse + Back_Porch), in Number of lines
    uint16_t HTotal;            // Horizontal Total Length, in Pixels
    uint16_t VTotal;            // Vertical Total Length, in Number of lines
} _MODE;

extern const _MODE modeTable[];