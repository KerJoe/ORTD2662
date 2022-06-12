#include <stdint.h>
#include <stdio.h>

#include "config/board_config.h"

#include "interfaces/hdmi.h"
#include "peripherals/ddc.h"
#include "peripherals/timer.h"
#include "scaler/scaler_tables.h"

void InitHDMI(uint8_t tmdsIn)
{
  /*  #define WINDOW_HSTA 0
    #define WINDOW_VSTA 0
    #define WINDOW_HS_DELAY 0
    #define WINDOW_VS_DELAY 0
    #define WINDOW_HLEN 1024
    #define WINDOW_VLEN 600

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

    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRWL_BSU_HI, (((WINDOW_HLEN) >> 8) << 4) | ((WINDOW_VLEN) >> 8));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRW_BSU_LO,  (WINDOW_HLEN));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRL_BSU_LO,  (WINDOW_VLEN));
*/
    ScalerWriteBit (S_VGIP_CONTROL, 0, 0b1);  // Sampling input pixels enable
    ScalerWriteBit (S_VGIP_CONTROL, 1, 0b1); // Sampling mode - digital
    ScalerWriteBits(S_VGIP_CONTROL, 2, 2, 0b01); // Input Format - Digital (TMDS)

    ScalerWriteBit (S_VDISP_CONTROL, 3, 0b1); // Enable Frame sync
    ScalerWriteBit (S_VDISP_CONTROL, 5, 0b0); // Disable BG color


    ScalerWriteByte(S_PAGE_SELECT, 2);

    ScalerWriteByte(S2_Z0_CALIBRATION_CONTROL, 0xe3); // Z0 impedence is auto, Set 50 ohm calibration, Default Z0 impedence value, REXT is 1kOhm
    ScalerWriteBits(S2_TMDS_OUTPUT_CONTROL, 3, 4, 0b1111); // Enable TMDS output Clock and RGB ports
    ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 0, 2, 0b11); // TODO: ???
    ScalerWriteBit (S2_UP_DOWN_CONTROL0, 7, 0b1); // TODO: ???
    ScalerWriteBits(S2_CLOCK_PLL_SETTING, 2, 3, 0b001); // Set PLL charge pump current to 20uA // TODO: Why?

    ScalerWriteBit (S2_POWER_ON_OFF_CONTROL, 5, 0b0);       // Input channel control is manual,
    ScalerWriteBits(S2_POWER_ON_OFF_CONTROL, 0, 4, 0b1111); // Enable TMDS input Clock and RGB ports
    if (tmdsIn == TMDS0)
    {
        ScalerWriteBit(S2_TMDS_MEAS_RESULT0, 1, 0b0);               // Select Port 0
        ScalerWriteBit(S2_POWER_ON_OFF_CONTROL, 5, TMDS0_SWAP_PN);  // Swap P/N Traces
        ScalerWriteBit(S2_POWER_ON_OFF_CONTROL, 6, TMDS0_SWAP_RB);  // Swap R/B Channels
    }
    else
    {
        ScalerWriteBit(S2_TMDS_MEAS_RESULT0, 1, 0b1);               // Select Port 1
        ScalerWriteBit(S2_POWER_ON_OFF_CONTROL, 5, TMDS1_SWAP_PN);  // Swap P/N Traces
        ScalerWriteBit(S2_POWER_ON_OFF_CONTROL, 6, TMDS1_SWAP_RB);  // Swap R/B Channels
    }

    ScalerWritePortBit(S2_HDMI_PORT, SP2_HDMI_AVMCR, 3, 0b1); // Enable TMDS video output
}