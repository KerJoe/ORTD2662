#include <stdint.h>
#include <stdio.h>

#include "config/board_config.h"

#include "interfaces/vga.h"
#include "peripherals/ddc.h"
#include "peripherals/timer.h"
#include "scaler/scaler_tables.h"

#include "scaler/compat_funcs.h"

const uint8_t tYPBPR_TABLE_SET_SCALER[] =
{

//    4,  _NON_AUTOINC,   _SYNC_PROC_ACCESS_PORT_5C,      _SYNC_G_CLAMP_START_00,
  //  7,  _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x10,0x18,0x10,0x18,


    4-3,  AUTOINC_DIS,  S_SYNC_PROC_ADDRESS ,     SP_SYNC_CAPTURE_WINDOW_SET ,

    ///5-3,  AUTOINC_DIS,   S_SYNC_PROC_PORT,        0x21,0x14,
    5-3,  AUTOINC_DIS,   S_SYNC_PROC_PORT,        0x21,0x04,

    4-3,  AUTOINC_DIS,   S_CB_ADDRESS,             0x80,
    9-3,  AUTOINC_DIS,   S_CB_PORT,               0x7e,0x7e,0x7e,0x80,0x80,0x80,
    4-3,  AUTOINC_DIS,   S_CB_ADDRESS,             0x00,

    4-3,  AUTOINC_DIS,   S_YUV_TO_RGB_CONTROL,               0x08,
    21-3, AUTOINC_DIS,   S_YUV_RGB_COEF_DATA,          0x04,0x00,0x00,0x00,0x06,0x60,
                                                        0x04,0x00,0xfe,0x70,0xfc,0xc0,
                                                        0x04,0x00,0x08,0x10,0x00,0x00,

    4-3,  AUTOINC_DIS,   S_YUV_TO_RGB_CONTROL,               0x07,

    4-3,  AUTOINC_DIS,   S_PAGE_SELECT,                0,
    9-3,  AUTOINC_ENA,   S0_RED_GAIN,                0x80,0x80,0x80,0x80,0x80,0x80,


    TABLE_END
};

void CModeStartUpVGA(void)
{
	WORD pixelclock;

    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, 0x00);

	// To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
	CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

	// Calculate pixel clock rate (round to MHz)
	pixelclock  = (((DWORD)248 * (DWORD)848) * 2 / (1000 * 10));
	pixelclock  = (pixelclock >> 1) + (pixelclock & 0x01);

	//cyc_delete    // To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
	//cyc_delete    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

    // ADC differential mode and Set ADC bandwidth to reduce high frequency noise
    CScalerPageSelect(_PAGE0);
    if(pixelclock < 38)
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);                    //75MHz
    else if(pixelclock < 68)
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));          //150MHz
    else if(pixelclock < 160)
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));          //300MHz
    else
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));  //500MHz

    CScalerPageSelect(_PAGE1);
    // Phase interpolation control load modified.   Marvin 0812
    if(pixelclock < 50)
        CScalerSetBit(_P1_PLL_PHASE_INTERPOLATION_B5, ~(_BIT7 | _BIT6), 0x00);
    else
        CScalerSetBit(_P1_PLL_PHASE_INTERPOLATION_B5, ~(_BIT7 | _BIT6), _BIT6);

    // Fine-tune R/G/B delay and enable the ADC frame-modulation
    CScalerPageSelect(_PAGE0);
	CScalerSetBit(_P0_ADC_RED_CTL_CF, ~(_BIT2 | _BIT1 | _BIT0), (0 & 0x07));
	CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~(_BIT2 | _BIT1 | _BIT0), (0 & 0x07));
	CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~(_BIT2 | _BIT1 | _BIT0), (0 & 0x07));

	if(0) //_GET_INPUT_SOURCE() == _SOURCE_YPBPR
		CScalerSetBit(_P0_ADC_CLAMP_CTRL1_D5,~(_BIT0 | _BIT1 | _BIT2 |_BIT3 | _BIT4 |_BIT5 ),
		((0 << 2) | 0 |(0 <<4)| (0<<2)));
	else //VGA
		CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);
	//CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);

    // HSYNC positive/negtive tracking
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL_DIV_CTRL_A0, ~_BIT7, 0x00);


	CScalerPageSelect(_PAGE0);
    if(1)
	{
	    CScalerSetBit(_P0_ADC_CLAMP_CTRL0_D4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    	CTimerDelayXms(10);
    	CScalerSetBit(_P0_ADC_DCR_CTRL_D3, ~_BIT4, 0x00);
    }

    if (1)
    {
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, 0x0F, (1 << 4) & 0xF0);
    }

	CScalerPageSelect(_PAGE1);
	CScalerSetByte(_P1_I_CODE_M_A1,0);
	CScalerSetByte(_P1_I_CODE_L_A2, 1);
}

bit CSourceScanInputPortVGA(BYTE ucAnalogSource)
{
//	BYTE	ucSearchIndex;
    BYTE cnt, synctypetemp = 0;;

	if(ucAnalogSource == 0)
		CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((0 << 4) | (0 << 5)| (0 << 6)));
	else if(ucAnalogSource == 1)
		CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((0 << 4) | (0 << 5)| (0 << 6)));

    CScalerPageSelect(_PAGE0);
    if(ucAnalogSource == 0 || ucAnalogSource == 2)
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, ~(_BIT5 | _BIT4), _BIT5); //off-line ADC clamp Enable
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~_BIT3, 0x00);// ADC input0
        CScalerSetBit(_P0_ADC_I_BAIS0_C7, ~_BIT0, _BIT0);  //SOG0 input MUX
        CScalerSetBit(_P0_ADC_I_BAIS1_C8, ~(_BIT7 | _BIT6), 0x00);
        CScalerSetBit(_P0_ADC_RED_CTL_CF, ~_BIT7, 0x00);//RGB clamp voltage sel
        CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~_BIT7, 0x00);
        CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~_BIT7, 0x00);
    }
    else if(ucAnalogSource == 1 || ucAnalogSource == 3)
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~_BIT3, _BIT3);
        CScalerSetBit(_P0_ADC_SOG_CTRL_D6, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        CScalerSetBit(_P0_ADC_RED_CTL_CF, ~_BIT7, _BIT7);
        CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~_BIT7, _BIT7);
        CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~_BIT7, _BIT7);
    }

    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT1);// ADC_HS/ADC_VS


        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, 0x00);



    for(cnt=0;cnt<2;cnt++)
    {
        synctypetemp = 1;//CSyncGetSyncTypeAutoRun();

        if(synctypetemp != 0)
        {
            return 1;
        }

        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, _BIT4);

    }

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, 0x00);// manual
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
    return 0;


}

void InitVGA()
{
    #define WINDOW_HSTA 10
    #define WINDOW_VSTA 10
    #define WINDOW_HLEN 800
    #define WINDOW_VLEN 600
    #define WINDOW_HS_DELAY 50
    #define WINDOW_VS_DELAY 50

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
    ScalerWriteByte(S0_VADC_POWER, 0x3f);
    ScalerWriteByte(S0_HSYNC_SCHMITT_TRIGGER_CONTROL, 0xcf);

    //CModeStartUpVGA();
    //CSourceScanInputPortVGA(0);
}