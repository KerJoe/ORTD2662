#include <stdint.h>
#include "peripherals/xsfr.h"
#include "scaler/scaler_access.h"
#include "scaler/scaler_registers.h"

void ScaleUp(uint16_t inWidth, uint16_t inHeight, uint16_t outWidth, uint16_t outHeight)
{
    uint32_t widthScalingFactor  = ((uint32_t)inWidth << 20)  / outWidth;
    uint32_t heightScalingFactor = ((uint32_t)inHeight << 20) / outHeight;

    // Setup FIFO window
    /*ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRWL_BSU_HI, (((WINDOW_HLEN) >> 8) << 4) | ((WINDOW_VLEN) >> 8));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRW_BSU_LO,  (WINDOW_HLEN));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRL_BSU_LO,  (WINDOW_VLEN));*/

    ScalerWriteByte(S_SCALE_FACTOR_ADDRESS, 0x80);
    EnableScalerAutoIncrement(1);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, widthScalingFactor >> 16);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, widthScalingFactor >> 8);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, widthScalingFactor);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, heightScalingFactor >> 16);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, heightScalingFactor >> 8);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, heightScalingFactor);
    EnableScalerAutoIncrement(0);
    ScalerWriteByte(S_SCALE_FACTOR_ADDRESS, 0x00);

    // If input and output resolutions are different, enable scaling
    ScalerWriteBit(S_SCALE_CONTROL, 0, (inWidth != outWidth));
    ScalerWriteBit(S_SCALE_CONTROL, 1, (inHeight != outHeight));
}

void ScaleDown(uint16_t inWidth, uint16_t inHeight, uint16_t outWidth, uint16_t outHeight)
{
    uint32_t widthScalingFactor  = ((uint32_t)inWidth << 20)  / outWidth;
    uint32_t heightScalingFactor = ((uint32_t)inHeight << 20) / outHeight;

    ScalerWriteByte(S_PAGE_SELECT, 6);

    ScalerWriteByte(S6_UZD_SCALE_HOR_FACTOR_HI, widthScalingFactor >> 16);
    ScalerWriteByte(S6_UZD_SCALE_HOR_FACTOR_MD, widthScalingFactor >> 8);
    ScalerWriteByte(S6_UZD_SCALE_HOR_FACTOR_LO, widthScalingFactor);
    ScalerWriteByte(S6_UZD_SCALE_VER_FACTOR_HI, heightScalingFactor >> 16);
    ScalerWriteByte(S6_UZD_SCALE_VER_FACTOR_MD, heightScalingFactor >> 8);
    ScalerWriteByte(S6_UZD_SCALE_VER_FACTOR_LO, heightScalingFactor);

    // If input and output resolutions are different, enable scaling
    ScalerWriteBit(S6_UZD_CONTROL0, 0, (inWidth != outWidth));
    ScalerWriteBit(S6_UZD_CONTROL0, 1, (inHeight != outHeight));
}