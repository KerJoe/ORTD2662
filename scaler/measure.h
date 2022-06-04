#pragma once

typedef struct
{
    uint32_t HFreq;             // Horizontal frequency, in Hz
    uint8_t  VFreq;             // Vertical frequency, in Hz
    uint16_t HTotal;            // Horizontal Total Length, analog: in Number of RTD_FREQ ticks, digital: in Pixels
    uint16_t VTotal;            // Vertical Total Length, in Number of lines
    uint16_t HSync;             // Horizontal Sync Period analog: in Number of RTD_FREQ ticks, digital: in Pixels
    uint16_t VSync;             // Vertical Sync Period, in Number of lines
    uint16_t HActive;           // Horizontal Active Picture Width, analog: in Number of RTD_FREQ ticks, digital: in Pixels
    uint16_t VActive;           // Vertical Active Picture Height, in Number of lines
    //uint16_t HStart;            // Horizontal Start Picture Position, analog: in Number of RTD_FREQ ticks, digital: in Pixels
    //uint16_t VStart;            // Vertical Start Picture Position, in Number of lines
    uint8_t  HSPolarity : 1;    // Horizontal Sync Polarity, NEGATIVE_SYNC_POLARITY or POSITIVE_SYNC_POLARITY
    uint8_t  VSPolarity : 1;    // Vertical Sync Polarity, NEGATIVE_SYNC_POLARITY or POSITIVE_SYNC_POLARITY
} _INPUT_MEAS_DATA;

extern _INPUT_MEAS_DATA InputMeasData;

int8_t MeasureSignal(bool isDigital);