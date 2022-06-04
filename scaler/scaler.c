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

void SetDPLLFrequncy(uint32_t outFreq)
{
    // FREQUENCY_OUTPUT = FREQUENCY_INPUT * M_VALUE / N_VALUE / (1 << OUTPUT_DIVIDER)
    // M_VALUE = FREQUENCY_OUTPUT * N_VALUE * (1 << OUTPUT_DIVIDER) / FREQUENCY_INPUT   * 2 (?)

    uint8_t dpllN, dpllDiv;
    if (outFreq < 3*MHZ)
        return;
    else if (outFreq < 10*MHZ)
        { dpllN = 5;  dpllDiv = 3; } // dpllDiv is 1/8
    else if (outFreq < 40*MHZ)
        { dpllN = 5;  dpllDiv = 1; } // dpllDiv is 1/2
    else if (outFreq < 100*MHZ)
        { dpllN = 6;  dpllDiv = 1; } // dpllDiv is 1/2
    else
        { dpllN = 12; dpllDiv = 0; } // dpllDiv is 1/1

    uint8_t dpllM = 2 * outFreq * dpllN * (1 << dpllDiv) / RTD_FREQ;

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
    ScalerWriteBit(S1_DPLL_WDT, 1, 0b1); // Enable DPLL Frequncy Tunning

    // Frequency offset correction
    uint32_t freq = RTD_FREQ * dpllM / dpllN / 2 / (1 << dpllDiv);
    uint32_t offset = (outFreq - freq) / (freq >> 15);
    offset = MIN(offset, 0x0FFF); // Cap offset at 0x0FFF
    ScalerWriteByte(S1_DCLK_FINE_TUNE_OFFSET_HI, offset >> 8);
    ScalerWriteByte(S1_DCLK_FINE_TUNE_OFFSET_LO, offset);
    ScalerWriteBit(S1_DCLK_FINE_TUNE_OFFSET_HI, 4, 0b0); // DPLL frequency tuning is UP
    ScalerWriteBit(S1_DCLK_SPREAD_SPECTRUM, 2, 0b1); // Update internal offset values
    ScalerWriteBit(S1_FIXED_LASTLINE_CONTROL, 0, 0b1); // Enable DPLL Offset
}

// pixelClock - MHZ
// linePixelCount - number of pixels (including sync) in a horizontal line
int8_t SetAPLLFrequncy(uint32_t pixelClock, uint16_t linePixelCount)
{
    // FREQUENCY_OUTPUT = FREQUENCY_INPUT * (M_VALUE + K_VALUE / 16) / N_VALUE / (1 << OUTPUT_DIVIDER)

    //       3 bit  8 bit  can be equal to 1 or 2
    uint8_t  apllN, apllM, apllDiv;
    int8_t   apllK; // 4 bit
    uint16_t apllMK; // Temporary value holding integer M and fractional K
    if (pixelClock < 25*MHZ)
        return;
    else if (pixelClock < 100*MHZ)
        { apllN = 3; apllDiv = 2; } // apllDiv is 1/4
    else if (pixelClock < 200*MHZ)
        { apllN = 3; apllDiv = 2; } // apllDiv is 1/4
    else
        { apllN = 3; apllDiv = 2; } // apllDiv is 1/4

    apllMK = (pixelClock/RTD_FREQ) * apllN * (1 << apllDiv) * 16; // Calculate (M_VALUE + K_VALUE / 16) // Multiply by 16, so as to not loose the fractional part
    apllM  = apllMK >> 4;     // Divide by 16 to get the integer part - M_VALUE
    apllK  = apllMK & 0b1111; // Get remainder of 16 to get fractional part - K_VALUE
    // Correct K range from [0;31] to [-16;15]
    apllK -= 16; // Integer part subtracted
    apllM += 1;  // Integer part added

    // Limit K between -8 and 7 // REF:RTD2660 datasheet, page 122, footnote 3 // TODO: Wrong explanation
    if (apllK > 7) // Simlar to converting 1 + 0.6 to 2 - 0.4
    {
        apllM += 1;
        apllK = -apllK;
    }
    else if (apllK < -7) // Simlar to converting 1 - 0.6 to 0 + 0.4
    {
        apllM -= 1;
        apllK = -apllK;
    }

    ScalerWriteByte(S_PAGE_SELECT, 1);

    ScalerWriteBit (S1_PLL_WDT, 0, 0b0); // Power up the APLL

    // TODO: Find actual DPM/Ich ratio
    ScalerWriteBits(S1_PLL_CURRENT, 5, 3, 0b011);   // Set 23K filter resistor
    ScalerWriteBits(S1_PLL_CURRENT, 0, 5, 0b00101); // Set 15uA charge pump current

    ScalerWriteBits(S1_PLL_N, 0, 3, apllN - 2); // Set N
    ScalerWriteByte(S1_PLL_M,       apllM - 3); // Set M
    ScalerWriteBits(S1_PLL_N, 4, 4, apllK);     // Set K
    ScalerWriteBit (S1_PLL_DIV_HI, 4, (1 << apllDiv)==4); // Set output divider
    ScalerWriteByte(S1_PLL_PHASE_CONTROL1, 0); // Apply output divider

    // Set ADC CLK divider
    ScalerWriteBits(S1_PLL_DIV_HI, 0, 4, (linePixelCount - 1) >> 8);
    ScalerWriteByte(S1_PLL_DIV_LO,       (linePixelCount - 1));

    ScalerWriteBit (S_SYNC_SELECT, 6, 0b1); // HSYNC Type Detection: Automatic

    ScalerWriteBit(S1_PFD_CALIBRATED_RESULTS_HI, 7, 0b1); // Begin measurement
    Poll(50, !ScalerReadBit(S1_PFD_CALIBRATED_RESULTS_HI, 7))
    {
        return -1;
    }
    uint16_t pfd = ((ScalerReadByte(S1_PFD_CALIBRATED_RESULTS_HI) & 0x0F) << 8) | ScalerReadByte(S1_PFD_CALIBRATED_RESULTS_LO);

    uint32_t icode = ((pixelClock * 10 / linePixelCount) * pfd * (pixelClock/1000)) / 1220703;
    icode = icode>>6;
    icode &= 0x00007fff;

    uint16_t pcode = (63 * icode * RTD_FREQ / (pixelClock / linePixelCount) / apllN ) >> 7;
    uint8_t pmethod;
    if(pcode > 255)
    {
        for(pmethod = 9; pmethod < 15; pmethod++)
        {
            if((pcode >> pmethod) == 0)
                break;
        }
        #define	_G_VALUE_DIVIDER_0  4
        #define	_G_VALUE_DIVIDER_1  16
        #define	_G_VALUE_DIVIDER_2  64
        #define	_G_VALUE_DIVIDER_3  128
        #define	_G_VALUE_DIVIDER_4  256
        #define	_G_VALUE_DIVIDER_5  512
        switch(pmethod-9)
        {
            case 0:
                pcode = pcode / _G_VALUE_DIVIDER_0;
                break;
            case 1:
                pcode = pcode / _G_VALUE_DIVIDER_1;
                break;
            case 2:
                pcode = pcode / _G_VALUE_DIVIDER_2;
                break;
            case 3:
                pcode = pcode / _G_VALUE_DIVIDER_3;
                break;
            case 4:
                pcode = pcode / _G_VALUE_DIVIDER_4;
                break;
            case 5:
                pcode = pcode / _G_VALUE_DIVIDER_5;
                break;
            default:
                break;
        }
        //pcode = pcode / g_value_divider[(pmethod - 9)];
        pmethod = pmethod - 7;
    }
    if(pcode==0) pcode = 1;
    pmethod = pmethod << 2;

    ScalerWriteByte(S1_PCODE_MAPPING_METHOD, pmethod);
    ScalerWriteByte(S1_PCODE, pcode);
    ScalerWriteByte(S1_ICODE_HI, icode >> 8);
    ScalerWriteByte(S1_ICODE_LO, icode);

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

void SetWindow(uint16_t hsta, uint16_t hlen, uint8_t hsdel, uint16_t vsta, uint16_t vlen, uint8_t vsdel)
{
    // Setup capture window
    ScalerWriteByte(S_IFW_HACT_STA_HI, (hsta) >> 8);
    ScalerWriteByte(S_IFW_HACT_STA_LO, hsta);
    ScalerWriteByte(S_IFW_HACT_LEN_HI, (hlen) >> 8);
    ScalerWriteByte(S_IFW_HACT_LEN_LO, hlen);
    ScalerWriteByte(S_IFW_VACT_STA_HI, (vsta) >> 8);
    ScalerWriteByte(S_IFW_VACT_STA_LO, vsta);
    ScalerWriteByte(S_IFW_VACT_LEN_HI, (vlen) >> 8);
    ScalerWriteByte(S_IFW_VACT_LEN_LO, vlen);
    ScalerWriteByte(S_IFW_HSYNC_DELAY, hsdel);
    ScalerWriteByte(S_IFW_VSYNC_DELAY, vsdel);

    // Setup FIFO window
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRWL_BSU_HI, (((hlen) >> 8) << 4) | ((vlen) >> 8));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRW_BSU_LO,  (hlen));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRL_BSU_LO,  (vlen));
}

void InitScaler()
{
    ScalerWriteBit(S_HOST_CONTROL, 0, BIT_ONE);
    delayMS(10); // Wait for at least 8ms
    //for (long i=0; i < 65535; i++) { __asm NOP __endasm; }
    ScalerWriteBit(S_HOST_CONTROL, 0, BIT_ZERO);

    SetPowerMode(POWER_MODE_FULL);
    SetDPLLFrequncy(PANEL_DCLK); // DPLL Settings

    // SetVideoContrast(128);
    // SetVideoBrightness(128);
    // SetVideoSaturation(180);
    // SetVideoHue(0);

    ScalerWriteTable(DisplayInitTable);
}