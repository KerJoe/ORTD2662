#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "config/board_config.h"

#include "interfaces/vga.h"
#include "peripherals/ddc.h"
#include "peripherals/timer.h"
#include "scaler/scaler_tables.h"
#include "scaler/scaler.h"
#include "scaler/mode_tables.h"

void InitVGA()
{
    ScalerWriteBit (S_VDISP_CONTROL, 3, 0b1); // Enable Frame sync
    ScalerWriteBit (S_VDISP_CONTROL, 5, 0b0); // Disable BG color
    ScalerWriteBits(S_VGIP_CONTROL, 2, 2, 0b00); // Input Format - Embedded ADC (ADC_HS)
    ScalerWriteBit (S_VGIP_CONTROL, 0, 0b1);  // Sampling input pixels enable

    ScalerWriteByte(S_PAGE_SELECT, 0);
    ScalerWriteByte(S0_VADC_POWER, 0x0f); // Enable RGB and bandgap
}

// Define maximum diviation for searching
#define HOR_SEARCH_TOLERANCE 1000
#define VER_SEARCH_TOLERANCE 2
int8_t SearchMode(uint8_t HSPolarity, uint8_t VSPolarity, uint32_t HFreq, uint8_t VFreq)
{
    for (uint8_t i = 0; modeTable[i].HFreq != 0; i++) // modeTable[i].HFreq = 0 - End of array marker
        if (HSPolarity == modeTable[i].HSPolarity &&
            VSPolarity == modeTable[i].VSPolarity &&
            abs(HFreq - modeTable[i].HFreq) < HOR_SEARCH_TOLERANCE &&
            abs(VFreq - modeTable[i].VFreq) < VER_SEARCH_TOLERANCE)
                return i;
    return -1;
}