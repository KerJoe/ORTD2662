#include <stdint.h>
#include <stdio.h>

#include "config/panel_config.h"
#include "config/board_config.h"
#include "core/config_defines.h"

#include "core/misc.h"

#include "scaler/scaler_registers.h"
#include "scaler/scaler_access.h"
#include "scaler/scaler_tables.h"
#include "scaler/scaler.h"

#include "peripherals/timer.h"
#include "peripherals/xsfr.h"

#include "peripherals/pins.h"

void SetDPLLFrequncy(uint32_t dclk)
{
    // FREQUENCY_OUTPUT = FREQUENCY_INPUT * M_VALUE / N_VALUE / (1 << OUTPUT_DIVIDER)
    // M_VALUE = FREQUENCY_OUTPUT * N_VALUE * (1 << OUTPUT_DIVIDER) / FREQUENCY_INPUT   * 2 (?)

    uint8_t dpllN, dpllDiv;
    if (dclk < 3000000)
        return;
    else if (dclk < 10000000)
        {dpllN = 5; dpllDiv = 3; } // dpllDiv is 1/8
    else if (dclk < 40000000)
        {dpllN = 5; dpllDiv = 1; } // dpllDiv is 1/2
    else if (dclk < 100000000)
        {dpllN = 6; dpllDiv = 1; } // dpllDiv is 1/2
    else
        {dpllN = 12; dpllDiv = 0; } // dpllDiv is 1/1

    uint8_t dpllM = 2 * dclk * dpllN * (1 << dpllDiv) / BOARD_FREQ;

    // Datasheet insists on keeping these ratios constant:
    // If LPF_Mode = 0 (dpllN <= 5), DPM / Ich = 5.11;
    // If LPF_Mode = 1 (dpllN > 5),  DPM / Ich = 36.67;
    uint8_t lpfMode, Ich;
    if (dpllN <= 5)
    {
        lpfMode = 0;
        Ich = dpllM * 100 / 511;
    }
    else
    {
        lpfMode = 1;
        Ich = dpllM * 100 / 3667;
    }
    Ich = MIN((uint8_t)(Ich - 1), 15); // Cap Ich at 16 uA

    ScalerWriteByte(S_PAGE_SELECT, 1);
    ScalerWriteByte(S1_DPLL_M, dpllM - 2);
    ScalerWriteByte(S1_DPLL_N, (dpllN - 2) | (dpllDiv << 4)); // Write N and Div, disable power down and unfreeze DPLL
    ScalerWriteByte(S1_DPLL_CURRENT, Ich | (0b10 << 6)); // Set charge pump current and use default loop filter resistor
                                                         // 20K (LPF Mode = 0), 60K (LPF Mode = 1)
    ScalerWriteBit(S1_DPLL_WDT, 0, lpfMode);
    ScalerWriteBit(S1_DPLL_WDT, 1, BIT_ONE); // Enable DPLL Frequncy Tunning

    // Frequency offset correction
    uint32_t freq = BOARD_FREQ * dpllM / dpllN / 2 / (1 << dpllDiv);
    uint32_t offset = (dclk - freq) / (freq >> 15);
    offset = MIN(offset, 0x0FFF); // Cap offset at 0x0FFF
    ScalerWriteByte(S1_DCLK_FINE_TUNE_OFFSET_HI, offset >> 8);
    ScalerWriteByte(S1_DCLK_FINE_TUNE_OFFSET_LO, offset);
    ScalerWriteBit(S1_DCLK_FINE_TUNE_OFFSET_HI, 4, BIT_ZERO); // DPLL frequency tuning is UP
    ScalerWriteBit(S1_DCLK_SPREAD_SPECTRUM, 2, BIT_ONE); // Update internal offset values
    ScalerWriteBit(S1_FIXED_LASTLINE_CONTROL, 0, BIT_ONE); // Enable DPLL Offset

    //ScalerWriteByte(S_VDISP_CONTROL, 0xa3); // Display control, generator start
}

void SetVideoBrightness(uint8_t value)
{
    ScalerWriteBit(S_COLOR_CONTROL, 0, BIT_ONE);
    ScalerWritePortByte(S_CB_PORT, 0x80, value);
    ScalerWritePortByte(S_CB_PORT, 0x81, value);
    ScalerWritePortByte(S_CB_PORT, 0x82, value);
}

void SetVideoContrast(uint8_t value)
{
    uint8_t data[6];
    data[3] = value; data[4] = value; data[5] = value;
    ScalerWriteBit(S_COLOR_CONTROL, 1, BIT_ONE); // Enable contrast control
    data[0] = ScalerReadPortByte(S_CB_PORT, 0x00);
    data[1] = ScalerReadPortByte(S_CB_PORT, 0x01);
    data[2] = ScalerReadPortByte(S_CB_PORT, 0x02);
    ScalerWritePortByte(S_CB_PORT, 0x80, data[0]);
    ScalerWritePortByte(S_CB_PORT, 0x81, data[1]);
    ScalerWritePortByte(S_CB_PORT, 0x82, data[2]);
    ScalerWritePortByte(S_CB_PORT, 0x83, data[3]);
    ScalerWritePortByte(S_CB_PORT, 0x84, data[4]);
    ScalerWritePortByte(S_CB_PORT, 0x85, data[5]); // port data should be written continuously from 0x00
}

void SetVideoHue(uint8_t value)
{
    ScalerWriteByte(S_PAGE_SELECT, 8);
    ScalerWriteByte(S8_HUE_PHASE_CADJ, value);
}

void SetVideoSaturation(uint8_t value)
{
    ScalerWriteByte(S_PAGE_SELECT, 8);
    ScalerWriteByte(S8_SATURATION_CADJ, value);
}

void SetOverlayColor(uint8_t red, uint8_t green, uint8_t blue)
{
    ScalerWriteBit(S_OVERLAY_CONTROL, 5, 1); // Enable overlay port
    ScalerWriteByte(S_BG_COLOR_CONTROL, red);
    ScalerWriteByte(S_BG_COLOR_CONTROL, green);
    ScalerWriteByte(S_BG_COLOR_CONTROL, blue);
    ScalerWriteBit(S_OVERLAY_CONTROL, 5, 0); // Disable overlay port
}

void EnableOverlay(uint8_t state)
{
    ScalerWriteBit(S_OVERLAY_CONTROL, 0, state);
}

void SetPowerMode(uint8_t mode)
{   // TODO: Find what else to disable/enable
    ScalerWriteByte(S_PAGE_SELECT, 1);
    switch (mode)
    {
        case POWER_MODE_FULL:
            ScalerWriteBits(S_HOST_CONTROL, 1, 2, 0b00); // Clear Power Down Mode Enable and Clear Power Saving Mode Enable
            ScalerWriteByte(S1_M2PLL_POWER_DOWN, 0x00); // TODO: Reread datasheet
            break;
        case POWER_MODE_SAVING:
            ScalerWriteBits(S_HOST_CONTROL, 1, 2, 0b01); // Clear Power Down Mode Enable and Clear Power Saving Mode Enable
            ScalerWriteByte(S1_M2PLL_POWER_DOWN, 0x01);
            break;
        case POWER_MODE_DOWN:
            ScalerWriteBits(S_HOST_CONTROL, 1, 2, 0b10); // Clear Power Down Mode Enable and Clear Power Saving Mode Enable
            ScalerWriteByte(S1_M2PLL_POWER_DOWN, 0x01);
            break;
    }
}

void InitScaler()
{
    ScalerWriteBit(S_HOST_CONTROL, 0, BIT_ONE);
    delayMS(10); // Wait for at least 8ms
    ScalerWriteBit(S_HOST_CONTROL, 0, BIT_ZERO);

    SetPowerMode(POWER_MODE_FULL);
    SetDPLLFrequncy(PANEL_DCLK); // DPLL Settings

    // SetVideoContrast(128);
    // SetVideoBrightness(128);
    // SetVideoSaturation(180);
    // SetVideoHue(0);

    ScalerWriteTable(DisplayInitTable);
}