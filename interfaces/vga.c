#include <stdint.h>
#include <stdio.h>

#include "config/board_config.h"

#include "interfaces/vga.h"
#include "peripherals/ddc.h"
#include "peripherals/timer.h"
#include "scaler/scaler_tables.h"

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

    ScalerWriteBit (S_VGIP_CONTROL, 0, 0b1);  // Sampling input pixels enable

    ScalerWriteBit (S_VDISP_CONTROL, 3, 0b1); // Enable Frame sync
    ScalerWriteBit (S_VDISP_CONTROL, 5, 0b0); // Disable BG color

    ScalerWriteBits(S_VGIP_CONTROL, 2, 2, 0b00); // Input Format - Embedded ADC (ADC_HS)


    ScalerWriteBit (S_VGIP_CONTROL, 0, 0b1);  // Sampling input pixels enable

    ScalerWriteBit (S_VDISP_CONTROL, 3, 0b1); // Enable Frame sync
    ScalerWriteBit (S_VDISP_CONTROL, 5, 0b0); // Disable BG color


    ScalerWriteTable(tYPBPR_TABLE_SET_SCALER);


    //return;




	uint16_t pixelclock;
    //DebugPrintf("Enter CModeStartUpVGA\n", 0);
    ///ScalerWriteByte(S_PAGE_SELECT, 2);
    ///CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ///CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    ///CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, 0x00);

	// To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
    ScalerWriteBits(S_VGIP_CONTROL, 0, 4, 0b0001);

	// Calculate pixel clock rate (round to MHz)
	///pixelclock  = (((DWORD)stModeInfo.IHFreq * (DWORD)stModeInfo.IHTotal) * 2 / (1000 * 10));
	///pixelclock  = (pixelclock >> 1) + (pixelclock & 0x01);
    pixelclock = 40;

	//cyc_delete    // To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
	//cyc_delete    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

    // ADC differential mode and Set ADC bandwidth to reduce high frequency noise
    ScalerWriteByte(S_PAGE_SELECT, 0);
    if(pixelclock < 38)
        ScalerWriteBits(S0_VADC_RGB_CONTROL, 0, 3, 0b100);//CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);                    //75MHz
    else if(pixelclock < 68)
        ScalerWriteBits(S0_VADC_RGB_CONTROL, 0, 3, 0b101);//CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));          //150MHz
    else if(pixelclock < 160)
        ScalerWriteBits(S0_VADC_RGB_CONTROL, 0, 3, 0b110);//CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));          //300MHz
    else
        ScalerWriteBits(S0_VADC_RGB_CONTROL, 0, 3, 0b111);////CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));  //500MHz

    ScalerWriteByte(S_PAGE_SELECT, 1);
    // Phase interpolation control load modified.   Marvin 0812
    if(pixelclock < 50)
        ScalerWriteBits(S1_PLL_PHASE_INTERPOLATION, 6, 2, 0b00);//CScalerSetBit(_P1_PLL_PHASE_INTERPOLATION_B5, ~(_BIT7 | _BIT6), 0x00);
    else
        ScalerWriteBits(S1_PLL_PHASE_INTERPOLATION, 6, 2, 0b01);//CScalerSetBit(_P1_PLL_PHASE_INTERPOLATION_B5, ~(_BIT7 | _BIT6), _BIT6);

    // Fine-tune R/G/B delay and enable the ADC frame-modulation
    ScalerWriteByte(S_PAGE_SELECT, 0);
	///CScalerSetBit(_P0_ADC_RED_CTL_CF,   ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_RED & 0x07));
	///CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_GREEN & 0x07));
	///CScalerSetBit(_P0_ADC_BLUE_CTL_D1,  ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_BLUE & 0x07));

	/*if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR)
		CScalerSetBit(_P0_ADC_CLAMP_CTRL1_D5,~(_BIT0 | _BIT1 | _BIT2 |_BIT3 | _BIT4 |_BIT5 ),
		((_ADC1_INPUT_SWAP_RG << 2) | _ADC1_INPUT_SWAP_RG |(_ADC1_INPUT_SWAP_GB <<4)| (_ADC1_INPUT_SWAP_GB<<2)));
	else //VGA*/
		ScalerWriteByte(S0_VADC_CLAMP_CONTROL1, 0);//CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);
	//CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);
    ScalerWriteByte(S_YUV_TO_RGB_CONTROL, 0);//CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);

    // HSYNC positive/negtive tracking
    ScalerWriteByte(S_PAGE_SELECT, 1);
    ScalerWriteBit(S1_PLL_DIV_CONTROL, 7, 0b0);//CScalerSetBit(_P1_PLL_DIV_CTRL_A0, ~_BIT7, 0x00);


	//ScalerWritePortByte(S_SYNC_PROC_PORT, SP_SYNC_BR_CLAMP_STA, 0x04);
	//ScalerWritePortByte(S_SYNC_PROC_PORT, SP_SYNC_BR_CLAMP_END, 0x10);


	ScalerWriteByte(S_PAGE_SELECT, 0);
    /*if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _YPBPR_A0_PORT || CGetSourcePortType(_GET_INPUT_SOURCE()) == _DSUB_A0_PORT)
	{*/
	    ScalerWriteBits(S0_VADC_CLAMP_CONTROL0, 4, 4, 0b1111);//CScalerSetBit(_P0_ADC_CLAMP_CTRL0_D4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    	delayMS(10);
    	ScalerWriteBit (S0_VADC_DCR_CONTROL, 4, 0b0);//CScalerSetBit(_P0_ADC_DCR_CTRL_D3, ~_BIT4, 0x00);
    /*}
    else
	{
	    CScalerSetBit(_P0_ADC_CLAMP_CTRL0_D4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    	CTimerDelayXms(10);
    	CScalerSetBit(_P0_ADC_DCR_CTRL_D3, ~_BIT0, 0x00);
    }*/

    /*if (_GET_INPUT_SOURCE() != _SOURCE_YPBPR)
    {*/
        ScalerWriteBit (S0_VADC_RGB_CONTROL, 4, 0b1);//CScalerSetBit(_P0_ADC_RBG_CTRL_CE, 0x0F, (1 << 4) & 0xF0);
    /*}*/

	ScalerWriteByte(S_PAGE_SELECT, 1);
	ScalerWriteByte(S1_ICODE_HI, 0);//CScalerSetByte(_P1_I_CODE_M_A1,0);
	ScalerWriteByte(S1_ICODE_LO, 1);//CScalerSetByte(_P1_I_CODE_L_A2, 1);









    /*ScalerWriteByte(S_PAGE_SELECT, 0);
    ScalerWriteBit (S0_VADC_SWITCH, 1, 0b1);            // Power up ADC0
    ScalerWriteBit (S0_VADC_SWITCH, 0, 0b1);            // Global power on
    ScalerWriteBits(S0_VADC_POWER, 0, 4, 0b1111);       // Bandgap on, RGB ADCs on

    ScalerWriteByte(S_PAGE_SELECT, 0);
    ScalerWriteBits(S0_VADC0_INPUT_PGA, 3, 3, 0b000);
    ScalerWriteBits(S0_VADC1_INPUT_PGA, 3, 3, 0b000);

    ScalerWriteByte(S_PAGE_SELECT, 1);
    ScalerWriteBit (S1_LOOP_FILTER_CAPACITOR, 4, 0b1);    // Enable PLL2X

    ScalerWriteByte(S_PAGE_SELECT, 0);
    ScalerWriteByte(S0_VADC_CLAMP_CONTROL0, 0xff);       // Clamp on

    ScalerWriteByte(S_PAGE_SELECT, 0xB);
    ScalerWriteBit (SB_SYNC_SELECT, 7, 0b1); // HSYNC Type Detection Auto Run

    ScalerWriteByte(S_PAGE_SELECT, 0);
    ScalerWriteBit (S0_VADC_DCR_CONTROL, 4, 0b0);
    ScalerWriteBits(S0_VADC_RGB_CONTROL, 4, 4, 0b0001);

	//ScalerWriteBits(S_SYNC_SELECT, ~(_BIT3 | _BIT2), 0x00);//SOY0 , 1st HS/VS
	//	else
	//		CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));//SOY1 ,2nd HS/VS*/
}