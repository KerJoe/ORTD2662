#include <stdint.h>
#include <stdio.h>

#include "interfaces/composite.h"
#include "scaler/scaler_access.h"

#include "config/board_config.h"
#include "peripherals/timer.h"

// Entry format is fixed-point, each entry has different number of whole and fractional bits:
// K11: 2 - whole, 10 - fraction;
// K13: 1 - whole, 10 - fraction;
// K22: 0 - whole, 10 - fraction;
// K23: 0 - whole, 10 - fraction;
// K32: 2 - whole, 10 - fraction
// Offsets: 4 - whole, 10 - fraction, signed // TODO: How are negative numbers passed?
// TODO: Awfully washed out colors.
#define FR10(__num) ((__num) * 1024)
const uint16_t YUV2RGB_CCIR601[] =
{
    // YUV to RGB conversion coefficients
    // [R]   [K11   0   K13][Y]    R = K11 * Y + K13 * V
    // [G] = [ 1  -K22 -K23][U] => G = Y - K22 * U - K23 * V
    // [B]   [ 1   K32   0 ][V]    B = Y + K32 * U
    // TODO: Or is it ???:
    // [R]   [K11   0   K13][Y]    R = K11 * Y + K13 * V
    // [G] = [K11 -K22 -K23][U] => G = K11 * Y - K22 * U - K23 * V
    // [B]   [K11  K32   0 ][V]    B = K11 * Y + K32 * U

    FR10(0.5596),  // K11
    FR10(0.9063),  // K13
    FR10(0.2461),  // K22
    FR10(0.2793),  // K23
    FR10(0.6933),  // K32

    FR10(0),       // Red offset
    FR10(2.6670),  // Green offset
    FR10(0),       // Blue offset
};

void InitComposite(uint8_t videoIn)
{
    // TODO: DITHERING
    // #define WINDOW_HSTA 26
    // #define WINDOW_VSTA 8
    // #define WINDOW_HLEN 720
    // #define WINDOW_VLEN 244
    // #define WINDOW_HS_DELAY 110
    // #define WINDOW_VS_DELAY 6
    #define WINDOW_HSTA 34
    #define WINDOW_VSTA 5
    #define WINDOW_HLEN 696
    #define WINDOW_VLEN 232
    #define WINDOW_HS_DELAY 110
    #define WINDOW_VS_DELAY 21

    // Setup capture window
    ScalerWriteByte(S_IFW_HACT_STA_HI, (WINDOW_HSTA) >> 8);
    ScalerWriteByte(S_IFW_HACT_STA_LO, WINDOW_HSTA);
    ScalerWriteByte(S_IFW_HACT_LEN_HI, (WINDOW_HLEN) >> 8);
    ScalerWriteByte(S_IFW_HACT_LEN_LO, WINDOW_HLEN);
    ScalerWriteByte(S_IFW_VACT_STA_HI, (WINDOW_VSTA) >> 8);
    ScalerWriteByte(S_IFW_VACT_STA_LO, WINDOW_VSTA);
    ScalerWriteByte(S_IFW_VACT_LEN_HI, (WINDOW_VLEN) >> 8);
    ScalerWriteByte(S_IFW_VACT_LEN_LO, WINDOW_VLEN);
    ScalerWriteByte(S_IFW_HSYNC_DELAY, WINDOW_HS_DELAY);
    ScalerWriteByte(S_IFW_VSYNC_DELAY, WINDOW_VS_DELAY);

    // Setup FIFO window
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRWL_BSU_HI, (((WINDOW_HLEN) >> 8) << 4) | ((WINDOW_VLEN) >> 8));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRW_BSU_LO,  (WINDOW_HLEN));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRL_BSU_LO,  (WINDOW_VLEN));

    ScalerWriteBit (S_VGIP_CONTROL, 1, 0b0);

    ScalerWriteBits(S_VGIP_CONTROL, 2, 2, 0b11);    // Input Format - video decoder input (Video 16)

    ScalerWriteBit (S_IFW_VACT_STA_HI, 4, 0b1);     // Video 16

    ScalerWriteByte(S_PAGE_SELECT, 0);
    ScalerWriteBits(S0_VADC0_INPUT_PGA, 3, 3, 0b000);
    ScalerWriteBits(S0_VADC1_INPUT_PGA, 3, 3, 0b000);

    ScalerWriteByte(S_PAGE_SELECT, 1);
    ScalerWriteBit(S1_LOOP_FILTER_CAPACITOR, 4, 0b1);    // Enable PLL2X

    //
    ScalerWriteByte(S_YUV_TO_RGB_CONTROL, 0x00); // disable RGB -> YUV conversion
    ScalerWriteByte(S_PAGE_SELECT, 7);
    ScalerWriteByte(S7_YUV_TO_RGB_CONTROL, 0x02);
    for(uint8_t i = 0; i < 8; i++)
    {
        ScalerWriteByte(S7_YUV_TO_RGB_ADDRESS, (i * 2) << 4);
        ScalerWriteByte(S7_YUV_TO_RGB_PORT, YUV2RGB_CCIR601[i] >> 8);
        ScalerWriteByte(S7_YUV_TO_RGB_ADDRESS, (i * 2 + 1) << 4);
        ScalerWriteByte(S7_YUV_TO_RGB_PORT, YUV2RGB_CCIR601[i] & 0xFF);
    }
    ScalerWriteByte(S7_YUV_TO_RGB_CONTROL, 0x01);
    ScalerWriteByte(S_PAGE_SELECT, 6);
    ScalerWriteBits(S6_YUV422_TO_YUV444, 5, 3, 0b101); // Enable, format defualt, Swap UV (Y, V, U)

    ScalerWriteBit(S_VGIP_CONTROL, 0, 0b1); // Enable video capture

    ScalerWriteBit (S_VDISP_CONTROL, 3, 0b1);
    ScalerWriteBit (S_VDISP_CONTROL, 5, 0b0);

    ScalerWriteByte(S_PAGE_SELECT, 8);
    ScalerWriteBit(S8_VIDEO_RESET, 0, 0b1);
    delayMS(20);
    ScalerWriteBit(S8_VIDEO_RESET, 0, 0b0);

    // TODO: Rewrite so it's more concise (without switch)
    switch (videoIn)
    {
       /* case 0:
            ScalerWriteByte(S_PAGE_SELECT, 0);
            ScalerWriteBit (S0_VADC_SWITCH, 1, 0b1);            // Power up ADC0
            ScalerWriteBit (S0_VADC_SWITCH, 0, 0b1);            // Global power on
            ScalerWriteBit (S0_VADC_POWER, 3, 0b1);             // Bandgap on
            ScalerWriteBit (S0_VADC_CLAMP_POWER, 4, 0);         // Video In clamp on
            ScalerWriteBit (S0_VADC_CONTROL, 4, 0b0);           // Video In 0 -> VADC0
            ScalerWriteByte(S_PAGE_SELECT, 8);
            ScalerWriteBits(S8_ADC_CLAMP_UP_DOWN, 6, 2, 0b01);  // VADC0 Clamp up disabled, clamp down enabled,
            ScalerWriteBit (S8_ADC_CLAMP_UP_DOWN, 1, 0b0);      // Select VADC0 as composite in for video decoder
            break;
        case 1:
            ScalerWriteByte(S_PAGE_SELECT, 0);
            ScalerWriteBit (S0_VADC_SWITCH, 2, 0b1);            // Power up ADC1
            ScalerWriteBit (S0_VADC_SWITCH, 0, 0b1);            // Global power on
            ScalerWriteBit (S0_VADC_POWER, 3, 0b1);             // Bandgap on
            ScalerWriteBit (S0_VADC_CLAMP_POWER, 4, 1);         // Video In clamp on
            ScalerWriteBit (S0_VADC_CONTROL, 5, 0b0);           // Video In 1 -> VADC1
            ScalerWriteByte(S_PAGE_SELECT, 8);
            ScalerWriteBits(S8_ADC_CLAMP_UP_DOWN, 4, 2, 0b01);  // VADC1 Clamp up disabled, clamp down enabled,
            ScalerWriteBit (S8_ADC_CLAMP_UP_DOWN, 1, 0b1);      // Select VADC1 as composite in for video decoder
            break;*/
        case 2:
            /*ScalerWriteByte(S_PAGE_SELECT, 0);
            ScalerWriteBit (S0_VADC_SWITCH, 1, 0b1);            // Power up ADC0
            ScalerWriteBit (S0_VADC_SWITCH, 0, 0b1);            // Global power on
            ScalerWriteBit (S0_VADC_POWER, 3, 0b1);             // Bandgap on
            ScalerWriteBit (S0_VADC_CLAMP_POWER, 4, 2);         // Video In clamp on
            ScalerWriteBit (S0_VADC_CONTROL, 4, 0b1);           // Video In 2 -> VADC0
            ScalerWriteByte(S_PAGE_SELECT, 8);
            ScalerWriteBits(S8_ADC_CLAMP_UP_DOWN, 6, 2, 0b01);  // VADC0 Clamp up disabled, clamp down enabled,
            ScalerWriteBit (S8_ADC_CLAMP_UP_DOWN, 1, 0b0);  */    // Select VADC0 as composite in for video decoder
            ScalerWriteByte(S_PAGE_SELECT, 0);
            ScalerWriteBit (S0_VADC_CLAMP_POWER, 2, 0b1);       // Video In clamp on
            ScalerWriteBit (S0_VADC_CONTROL, 4, 0b1);           // Video In 2 -> VAD
            ScalerWriteByte(S_PAGE_SELECT, 8);
            ScalerWriteByte(S8_ADC_CLAMP_UP_DOWN, 0x40);
            /*ScalerWriteBits(S8_ADC_CLAMP_UP_DOWN, 6, 2, 0b01);  // VADC0 Clamp up disabled, clamp down enabled,
            ScalerWriteBit (S8_ADC_CLAMP_UP_DOWN, 1, 0b0);      // Select VADC0 as composite in for video decoder*/
            ScalerWriteByte(S_PAGE_SELECT, 0);
            ScalerWriteBit (S0_VADC_SWITCH, 1, 0b1);            // Power up ADC0
            ScalerWriteBit (S0_VADC_SWITCH, 0, 0b1);            // Global power on
            ScalerWriteBit (S0_VADC_POWER, 3, 0b1);             // Bandgap on
            break;
        /*case 3:
            ScalerWriteByte(S_PAGE_SELECT, 0);
            ScalerWriteBit (S0_VADC_SWITCH, 2, 0b1);            // Power up ADC1
            ScalerWriteBit (S0_VADC_SWITCH, 0, 0b1);            // Global power on
            ScalerWriteBit (S0_VADC_POWER, 3, 0b1);             // Bandgap on
            ScalerWriteBit (S0_VADC_CLAMP_POWER, 4, 3);         // Video In clamp on
            ScalerWriteBit (S0_VADC_CONTROL, 5, 0b1);           // Video In 3 -> VADC1
            ScalerWriteByte(S_PAGE_SELECT, 8);
            ScalerWriteBits(S8_ADC_CLAMP_UP_DOWN, 4, 2, 0b01);  // VADC1 Clamp up disabled, clamp down enabled,
            ScalerWriteBit (S8_ADC_CLAMP_UP_DOWN, 1, 0b1);      // Select VADC1 as composite in for video decoder
            break;*/
    }
}