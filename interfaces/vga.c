#include <stdint.h>
#include <stdio.h>

#include "config/board_config.h"

#include "interfaces/vga.h"
#include "peripherals/ddc.h"
#include "peripherals/timer.h"
#include "scaler/scaler_tables.h"
#include "scaler/scaler.h"

#include "scaler/compat_funcs.h"

void InitVGA()
{
    #define WINDOW_HSTA 256-40
    #define WINDOW_VSTA 28-1
    #define WINDOW_HLEN 800
    #define WINDOW_VLEN 600
    #define WINDOW_HS_DELAY 0
    #define WINDOW_VS_DELAY 0

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

    ScalerWriteBit (S_VDISP_CONTROL, 3, 0b1); // Enable Frame sync
    ScalerWriteBit (S_VDISP_CONTROL, 5, 0b0); // Disable BG color
    ScalerWriteBits(S_VGIP_CONTROL, 2, 2, 0b00); // Input Format - Embedded ADC (ADC_HS)
    ScalerWriteBit (S_VGIP_CONTROL, 0, 0b1);  // Sampling input pixels enable

    ScalerWriteByte(S_PAGE_SELECT, 0);
    ScalerWriteByte(S0_VADC_POWER, 0x0f); // Enable RGB and bandgap

    SetAPLLFrequncy(40000000UL, 1056);
}