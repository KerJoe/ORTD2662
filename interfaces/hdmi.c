#include <stdint.h>
#include <stdio.h>

#include "config/board_config.h"

#include "interfaces/hdmi.h"
#include "peripherals/ddc.h"
#include "peripherals/timer.h"
#include "scaler/scaler_tables.h"

uint8_t ucHdmiAVMuteCnt = 0;

uint8_t GetTMDSFormat(void) // True - HDMI, False - DVI
{
    ScalerWriteByte(S_PAGE_SELECT, 2);
    return ScalerReadByte(S2_HDMI_STATUS) & 0x01;
}

void InitHDMI()
{
    #define WINDOW_HSTA 0
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

    ScalerWriteBit (S_VGIP_CONTROL, 0, 0b1);  // Digital capture mode

    ScalerWriteBit (S_VDISP_CONTROL, 3, 0b1); // Enable Frame sync
    ScalerWriteBit (S_VDISP_CONTROL, 5, 0b0); // Disable BG color

    ScalerWriteBits(S_VGIP_CONTROL, 2, 2, 0b01); // Input Format - Digital (TMDS)

	ScalerWriteByte(S_PAGE_SELECT, 2);
	ScalerWriteByte(S2_TMDS_OUTPUT_CONTROL, 0x78);    // Enable output Clock and RGB port
    ScalerWriteByte(S2_POWER_ON_OFF_CONTROL, 0x6F);   // Swap B/R Channels and swap P/N, Input channel control is manual, Enable input Clock and RGB port
    ScalerWriteByte(S2_Z0_CALIBRATION_CONTROL, 0xe3); // Z0 impedence is auto, Set 50 ohm calibration, Default Z0 impedence value, REXT is 1kOhm

    ScalerWriteBit(S2_ANALOG_COMMON_CONTROL2, 0, 0b1); // TODO: ???
    ScalerWriteBit(S2_UP_DOWN_CONTROL0, 7, 0b1); // TODO: ???
    ScalerWritePortBit(S2_HDMI_PORT, SP2_HDMI_AVMCR, 3, 0b1); //Enable DVI/HDMI video output

    ScalerWriteBit (S_VGIP_CONTROL, 1, 0b1); // Enable video capture
}