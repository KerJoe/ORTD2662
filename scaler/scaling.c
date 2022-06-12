#include <stdint.h>
#include "peripherals/xsfr.h"
#include "scaler/scaler_access.h"
#include "scaler/scaler_registers.h"

void SetCaptureWindow(uint16_t HStart, uint16_t VStart, uint16_t HActive, uint16_t VActive, uint16_t HDelay, uint16_t VDelay)
{
    ScalerWriteBits(S_IFW_HACT_STA_HI, 0, 4, HStart >> 8);
    ScalerWriteByte(S_IFW_HACT_STA_LO, HStart);
    ScalerWriteBits(S_IFW_VACT_STA_HI, 0, 4, VStart >> 8);
    ScalerWriteByte(S_IFW_VACT_STA_LO, VStart);
    ScalerWriteBits(S_IFW_HACT_LEN_HI, 0, 4, HActive >> 8);
    ScalerWriteByte(S_IFW_HACT_LEN_LO, HActive);
    ScalerWriteBits(S_IFW_VACT_LEN_HI, 0, 4, VActive >> 8);
    ScalerWriteByte(S_IFW_VACT_LEN_LO, VActive);
    ScalerWriteBits(S_IFW_HV_DELAY,    0, 1, HDelay >> 8);
    ScalerWriteByte(S_IFW_HSYNC_DELAY, HDelay);
    ScalerWriteBits(S_IFW_HV_DELAY,    1, 1, VDelay >> 8);
    ScalerWriteByte(S_IFW_VSYNC_DELAY, VDelay);
}
// FIFO Window
void SetFIFOWindow(uint16_t HActive, uint16_t VActive)
{
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRWL_BSU_HI, ((HActive >> 8) << 4) | (VActive >> 8));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRW_BSU_LO,  HActive);
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRL_BSU_LO,  VActive);
}

// TODO: Research Finite impulse response tap coeficients
uint8_t coef_up[] =
{
    0x04,0x00, 0x03,0x00, 0x02,0x00, 0x00,0x00, 0xFE,0x0F, 0xFA,0x0F, 0xF6,0x0F, 0xF2,0x0F,
    0xEC,0x0F, 0xE6,0x0F, 0xE0,0x0F, 0xD9,0x0F, 0xD2,0x0F, 0xCA,0x0F, 0xC3,0x0F, 0xBB,0x0F,
    0xCA,0x0F, 0xE0,0x0F, 0xF7,0x0F, 0x13,0x00, 0x31,0x00, 0x54,0x00, 0x78,0x00, 0xA1,0x00,
    0xCB,0x00, 0xFA,0x00, 0x28,0x01, 0x5B,0x01, 0x8D,0x01, 0xC3,0x01, 0xF7,0x01, 0x2E,0x02,
    0x79,0x04, 0x72,0x04, 0x68,0x04, 0x55,0x04, 0x40,0x04, 0x25,0x04, 0x07,0x04, 0xE2,0x03,
    0xBD,0x03, 0x91,0x03, 0x65,0x03, 0x34,0x03, 0x03,0x03, 0xCE,0x02, 0x99,0x02, 0x63,0x02,
    0xB9,0x0F, 0xAB,0x0F, 0x9F,0x0F, 0x98,0x0F, 0x91,0x0F, 0x8D,0x0F, 0x8B,0x0F, 0x8B,0x0F,
    0x8C,0x0F, 0x8F,0x0F, 0x93,0x0F, 0x98,0x0F, 0x9E,0x0F, 0xA5,0x0F, 0xAD,0x0F, 0xB4,0x0F,
};
uint8_t coef_down[] =
{
	0x08,0x00, 0x09,0x00, 0x0c,0x00, 0x10,0x00, 0x15,0x00, 0x1c,0x00, 0x24,0x00, 0x2e,0x00,
	0xe9,0x00, 0x07,0x01, 0x25,0x01, 0x45,0x01, 0x64,0x01, 0x83,0x01, 0xa2,0x01, 0xbe,0x01,
	0x43,0x02, 0x3f,0x02, 0x37,0x02, 0x2a,0x02, 0x1b,0x02, 0x08,0x02, 0xf2,0x01, 0xda,0x01,
	0xcc,0x00, 0xb1,0x00, 0x98,0x00, 0x81,0x00, 0x6c,0x00, 0x59,0x00, 0x48,0x00, 0x3a,0x00,
};


// This should probably disable any filtering
uint8_t coef0[] =
{
    0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01,
    0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01,
    0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01,
    0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01,
    0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01,
    0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01,
    0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01,
    0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01, 0x00,0x01,
};

// filterSelect: 0 - Scale down filter, 1 - Scale up filter
// table - 128 bytes
void WriteFilterTable(uint8_t filterSelect, uint8_t* table)
{
    EnableScalerAutoIncrement(0);
    if (filterSelect) // Scale Up
    {
        ScalerWriteByte(S_FILTER_CONTROL, 0xb0);
        ScalerWriteBytes(S_FILTER_DATA, table, 128);
        ScalerWriteByte(S_FILTER_CONTROL, 0xc0);
        ScalerWriteBytes(S_FILTER_DATA, table, 128);
        ScalerWriteByte(S_FILTER_CONTROL, 0x00);

        ScalerWriteByte(S_FILTER_CONTROL, 0x0b);
        ScalerWriteBytes(S_FILTER_DATA, table, 128);
        ScalerWriteByte(S_FILTER_CONTROL, 0x0c);
        ScalerWriteBytes(S_FILTER_DATA, table, 128);
        ScalerWriteByte(S_FILTER_CONTROL, 0x00);
    }
    else // Scale Down
    {
        ScalerWriteByte(S_PAGE_SELECT, 6);
        ScalerWriteByte(S6_UZD_FIR_COEF_INDEX, 0x00);
        ScalerWriteBytes(S6_UZD_FIR_COEF_DATA, table, 64);
        ScalerWriteByte(S6_UZD_FIR_COEF_INDEX, 0x80);
        ScalerWriteBytes(S6_UZD_FIR_COEF_DATA, table, 64);
        ScalerWriteByte(S6_UZD_FIR_COEF_INDEX, 0x00);
    }
}

void ClearTable(uint8_t filterSelect)
{
    uint8_t empt[128];
    for (uint8_t i = 0; i < 128; i++) empt[i] = 0;
    WriteFilterTable(filterSelect, empt);
}

void ScaleUp(uint16_t inWidth, uint16_t inHeight, uint16_t outWidth, uint16_t outHeight)
{
    uint32_t widthScalingFactor  = ((uint32_t)inWidth << 20)  / outWidth;
    uint32_t heightScalingFactor = ((uint32_t)inHeight << 20) / outHeight;

    // Write coeficients
    WriteFilterTable(1, coef_up);

    EnableScalerAutoIncrement(0);
    ScalerWriteByte(S_SCALE_FACTOR_ADDRESS, 0x80);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, widthScalingFactor >> 16);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, widthScalingFactor >> 8);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, widthScalingFactor);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, heightScalingFactor >> 16);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, heightScalingFactor >> 8);
    ScalerWriteByte(S_SCALE_FACTOR_PORT, heightScalingFactor);
    ScalerWriteByte(S_SCALE_FACTOR_ADDRESS, 0x00);

    // If input and output resolutions are different, enable scaling
    ScalerWriteBit(S_SCALE_CONTROL, 0, (inWidth  < outWidth));
    ScalerWriteBit(S_SCALE_CONTROL, 1, (inHeight < outHeight));
}

void ScaleDown(uint16_t inWidth, uint16_t inHeight, uint16_t outWidth, uint16_t outHeight)
{
    uint32_t widthScalingFactor  = ((uint32_t)inWidth << 20)  / outWidth;
    uint32_t heightScalingFactor = ((uint32_t)inHeight << 20) / outHeight;

    // Write coeficients
    //WriteFilterTable(0, coef);
    WriteFilterTable(0, coef_down);

    ScalerWriteByte(S_PAGE_SELECT, 6);

    ScalerWriteByte(S6_UZD_SCALE_HOR_FACTOR_HI, widthScalingFactor >> 16);
    ScalerWriteByte(S6_UZD_SCALE_HOR_FACTOR_MD, widthScalingFactor >> 8);
    ScalerWriteByte(S6_UZD_SCALE_HOR_FACTOR_LO, widthScalingFactor);
    ScalerWriteByte(S6_UZD_SCALE_VER_FACTOR_HI, heightScalingFactor >> 16);
    ScalerWriteByte(S6_UZD_SCALE_VER_FACTOR_MD, heightScalingFactor >> 8);
    ScalerWriteByte(S6_UZD_SCALE_VER_FACTOR_LO, heightScalingFactor);

    // Disable non-linear scaling
    ScalerWriteByte(S6_UZD_HOR_DELTA1_HI, 0x00);
    ScalerWriteByte(S6_UZD_HOR_DELTA1_LO, 0x00);

    ScalerWriteByte(S6_UZD_HOR_SEGMENT1_HI, 0x00);
    ScalerWriteByte(S6_UZD_HOR_SEGMENT1_LO, 0x00);
    ScalerWriteByte(S6_UZD_HOR_SEGMENT2_HI, outWidth >> 8);
    ScalerWriteByte(S6_UZD_HOR_SEGMENT2_LO, outWidth);

    //
    ScalerWriteBit(S6_UZD_CONTROL0, 4, 0b1);
    ScalerWriteBits(S6_UZD_CONTROL1, 2, 2, 0b10);

    // If input and output resolutions are different, enable scaling
    ScalerWriteBit(S6_UZD_CONTROL0, 0, (inWidth  > outWidth));
    ScalerWriteBit(S6_UZD_CONTROL0, 1, (inHeight > outHeight));
}