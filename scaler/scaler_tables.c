#include <stdint.h>

#include "scaler/scaler_registers.h"
#include "scaler/scaler_tables.h"

#include "config/panel_config.h"

const uint8_t DisplayInitTable[] =
{
    1,  AUTOINC_ENA,    S_VDISP_ADDRESS,    0x00,
    22, AUTOINC_ENA,    S_VDISP_PORT,       REG16BE(PANEL_HTOTAL),
                                            PANEL_HS_END,
                                            REG16BE(PANEL_HBG_STA),
                                            REG16BE(PANEL_HACT_STA),
                                            REG16BE(PANEL_HACT_END),
                                            REG16BE(PANEL_HBG_END),
                                            REG16BE(PANEL_VTOTAL),
                                            PANEL_VS_END,
                                            REG16BE(PANEL_VBG_STA),
                                            REG16BE(PANEL_VACT_STA),
                                            REG16BE(PANEL_VACT_END),
                                            REG16BE(PANEL_VBG_END),

    1,  AUTOINC_DIS,    S_VDISP_SIGINV,     (PANEL_INVERT_DEN << 0) |
                                            (PANEL_INVERT_DHS << 1) |
                                            (PANEL_INVERT_DVS << 2) |
                                            (PANEL_SWAP_BIT_ORDER << 4) |
                                            (PANEL_SWAP_RED_BLU   << 5) |
                                            (PANEL_SWAP_ODD_EVEN  << 6),

    1,  AUTOINC_DIS,    S_VDISP_CONTROL,    (1 << 0) | // Enable timing generator
                                            (1 << 1) | // Enable output
                                            (PANEL_DOUBLE_PORT << 2) |
                                            (PANEL_RGB_18 << 4) |
                                            (1 << 5) | // Force display output to monotone background
                                            (1 << 7),  // Force enable display timing generator


    1,  AUTOINC_DIS,    S_PAGE_SELECT,                      1,
    1,  AUTOINC_DIS,    S1_EVEN_FIXED_LASTLINE_HI,          ((PANEL_HTOTAL >> 8) << 4) | (PANEL_VTOTAL >> 8), // ...
    1,  AUTOINC_DIS,    S1_EVEN_FIXED_LASTLINE_DVTOTAL_LO,  PANEL_VTOTAL, // S1_EVEN_FIXED_LASTLINE_DVTOTAL_LO
    1,  AUTOINC_DIS,    S1_EVEN_FIXED_LASTLINE_LENGTH_LO,   PANEL_HTOTAL, // S1_EVEN_FIXED_LASTLINE_LENGTH_LO


    1,  AUTOINC_DIS,    S_TCON_ADDRESS,     SP_TCON_CONTROL0,
    1,  AUTOINC_DIS,    S_TCON_PORT,        PANEL_TYPE & 1,     // Set display type
    1,  AUTOINC_DIS,    S_TCON_ADDRESS,     SP_LVDS_CONTROL0,
    2,  AUTOINC_ENA,    S_TCON_PORT,        (0b11 << 4),        // Power up LVDS ports
                                            (0b11 << 6),        // Inverse BCKPOLARL and DCKPOLARL // TODO: Always inverted... test

    TABLE_END
};

const uint8_t tSCALER_POWERUP_HDMI[] =
{
	1,  AUTOINC_DIS,    S_PAGE_SELECT,              2,
	8, 	AUTOINC_ENA,    S2_TMDS_OUTPUT_CONTROL,     0x78,0x6F,0x03,0x00,0x70,0x70,0xe3,0x24,
    TABLE_END
};