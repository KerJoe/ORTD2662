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

#include "scaler/compat_funcs.h"
#include "scaler/compat_regs.h"

void SetDPLLFrequncy(uint32_t outFreq)
{
    // FREQUENCY_OUTPUT = FREQUENCY_INPUT * M_VALUE / N_VALUE / (1 << OUTPUT_DIVIDER)
    // M_VALUE = FREQUENCY_OUTPUT * N_VALUE * (1 << OUTPUT_DIVIDER) / FREQUENCY_INPUT   * 2 (?)

    uint8_t dpllN, dpllDiv;
    if (outFreq < 3000000)
        return;
    else if (outFreq < 10000000)
        {dpllN = 5; dpllDiv = 3; } // dpllDiv is 1/8
    else if (outFreq < 40000000)
        {dpllN = 5; dpllDiv = 1; } // dpllDiv is 1/2
    else if (outFreq < 100000000)
        {dpllN = 6; dpllDiv = 1; } // dpllDiv is 1/2
    else
        {dpllN = 12; dpllDiv = 0; } // dpllDiv is 1/1

    uint8_t dpllM = 2 * outFreq * dpllN * (1 << dpllDiv) / BOARD_FREQ;

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
    ScalerWriteBit(S1_DPLL_WDT, 1, BIT_ONE); // Enable DPLL Frequncy Tunning

    // Frequency offset correction
    uint32_t freq = BOARD_FREQ * dpllM / dpllN / 2 / (1 << dpllDiv);
    uint32_t offset = (outFreq - freq) / (freq >> 15);
    offset = MIN(offset, 0x0FFF); // Cap offset at 0x0FFF
    ScalerWriteByte(S1_DCLK_FINE_TUNE_OFFSET_HI, offset >> 8);
    ScalerWriteByte(S1_DCLK_FINE_TUNE_OFFSET_LO, offset);
    ScalerWriteBit(S1_DCLK_FINE_TUNE_OFFSET_HI, 4, BIT_ZERO); // DPLL frequency tuning is UP
    ScalerWriteBit(S1_DCLK_SPREAD_SPECTRUM, 2, BIT_ONE); // Update internal offset values
    ScalerWriteBit(S1_FIXED_LASTLINE_CONTROL, 0, BIT_ONE); // Enable DPLL Offset

    //ScalerWriteByte(S_VDISP_CONTROL, 0xa3); // Display control, generator start
}


BYTE CAdjustGetAPLLSetting(WORD usClock)
{
    BYTE ucTemp[2];

	usClock -= 1;

    CScalerPageSelect(_PAGE1);
    ucTemp[0] = ScalerReadByte(_P1_PLLDIV_H_B1);
    ucTemp[1] = ScalerReadByte(_P1_PLLDIV_L_B2);

	ucTemp[0] &= 0x0f;

	if((ucTemp[0] != (BYTE)(usClock >> 8)) || (ucTemp[1] != (BYTE)(usClock & 0x00ff)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
#define	_G_VALUE_DIVIDER_0  4
#define	_G_VALUE_DIVIDER_1  16
#define	_G_VALUE_DIVIDER_2  64
#define	_G_VALUE_DIVIDER_3  128
#define	_G_VALUE_DIVIDER_4  256
#define	_G_VALUE_DIVIDER_5  512
#define _APLL_N_CODE                   			3    //default = 3
WORD usPEValue = 120;
void CAdjustAdcClock(WORD usClock, UINT16 IHF)
{
	DWORD pllclock, icode;
	BYTE mcode;
	SBYTE STemp;
	WORD pcode;
	BYTE vco_divider = 2;
    BYTE pData[2];

    if(0)
        ;//CAdjustAPLLFastLock(usClock);
    else if(0)
        ;//CAdjustAdcClock_OSD(usClock);
    else
    {
        //CAdjustEnableWatchDog(_WD_DV_TIMEOUT);
        CScalerPageSelect(_PAGE1);
/********************************************************
Fvco : Frequency of APLL
Fxtal : Frequency of Crystal
IHF : Input Horizontal Frequency
usClock : Divider number of input clock
stModeInfo.IHFreq = 10 * IHF(in KHz)
_RTD_XTAl : Defined crystal clock unit in KHz

Fvco = Fxtal*(M + K/16)/N1 = IHF * usClock * vco_divider
Assum N1 = 2
(M + K/16) = IHF * usClock * N1 * vco_divider / Fxtal
stModeInfo.IHFreq UINT in 100Hz
*********************************************************/
     	//ADC sampling clock, UNIT in KHz
        pllclock = (DWORD)IHF * usClock / 10;
    	vco_divider = pllclock < 100000 ? 4 : 2;
        //Get (M + K/16) * 1024
        pllclock  = ((pllclock * _APLL_N_CODE * vco_divider) << 10 ) / _RTD_XTAL;
        CScalerPageSelect(_PAGE1);
    	CScalerSetByte(_P1_PLL_DIV_CTRL_A0, 0x08);
    	CScalerSetByte(_P1_DDS_MIX_2_B9, 0xff);
    	CScalerSetByte(_P1_PLL_CRNT_AE, 0x65);
     	CScalerSetBit(_P1_PLLDIV_H_B1, ~(_BIT6 | _BIT5 | _BIT4), (vco_divider == 2) ? (_BIT6 | _BIT5) : (_BIT6 | _BIT5 | _BIT4));
    	//Set the divide number
    	CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
    	CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));
        CAdjustGetAPLLSetting(usClock);
        //Set N code
    	CScalerSetBit(_P1_PLL_N_AD, 0xf8, ((_APLL_N_CODE - 2) & 0x07));
        //Get M, K code, M + K/16 = pllclock / 1024
    	mcode = pllclock >> 10; //M is the integer part
        //CScalerSetByte(0x04,mcode );
        //K is the fraction part quantized by 16
    	STemp = ((DWORD)pllclock - ((DWORD)mcode << 10)) >> 6;
    	//K is range from -8 ~ 7
    	if(STemp>7)
    	{
    		mcode +=1;
    		STemp -= 16;
    	}
    	else if(STemp<(-8))
    	{
    		mcode -=1;
    		STemp += 16;
    	}
        //set M, N, K code
       	CScalerSetByte(_P1_PLL_M_AC, (mcode - 3));
    	CScalerSetBit(_P1_PLL_N_AD, 0x0f, (((STemp & 0x0f) << 4) | (_APLL_N_CODE - 2)));
        CScalerSetByte(S1_PFD_CALIBRATED_RESULTS_HI, 0x80);
        CTimerDelayXms(1);
        //CScalerRead(0xA4, 2, pData, _AUTOINC);
        pData[0] = ScalerReadByte(S1_PFD_CALIBRATED_RESULTS_HI);
        pData[1] = ScalerReadByte(S1_PFD_CALIBRATED_RESULTS_LO);
        usPEValue =  ( ((pData[0]&0x0F)<<8) | pData[1] );
        usPEValue = 1000000/(usPEValue*(_RTD_XTAL/1000));   // unit : ps
/****************************************************************************
   	Formula :

   	  I_gain       Ths                    PE(UNIT)                   1
	--------- x  ------- = ------------------------------------ x  -----
	   2^22        Tbck        Txclk x 16N/(16M +- K) x 1/16         8

	  I_gain         Ths                      PE(UNIT)                   1
	--------- x  ----------- = ------------------------------------ x  -----
	   2^22       Tclk x N         Txclk x 16N/(16M +- K) x 1/16         8

	           2^22 x PE_U x (16M +- K)        1
	I_gain = ----------------------------- x -----
	                     Ths                   8

	    2^19 x PE_U x (16M +- K)
	= -----------------------------
	              Ths

	= IHF x 2^19 x PE_U x (16M +- K)
****************************************************************************/
// (M + K/16) = pllclock / 1024
// 16M + K = 16 * pllclock / 1024
// 2^19 * 2^4 / 2^10 = 2^13
// _PE_VALUE UNIT is ps, so result has to multiply 10^(-12)
// stModeInfo.IHFreq/10 UNIT is KHz, so result has to multiply 10^2
    /*
    	icode = (DWORD)((stModeInfo.IHFreq) * usPEValue * pllclock) / (DWORD)1220702;
    	icode &= 0x00007fff;
    	CScalerSetByte(_P1_I_CODE_M_A1,(BYTE)(icode >> 8));
    	CScalerSetByte(_P1_I_CODE_L_A2, (BYTE)icode);
    	// Set the P code
        pcode = (7 * icode * _RTD_XTAL / stModeInfo.IHFreq /_APLL_N_CODE) >> 7;
    //    pcode = 0xC0;
    //*/
    ///*    whhsiao 20080227 update-start
    	icode = (DWORD)((IHF) * usPEValue * pllclock) / (DWORD)1220703;
        //icode = icode>>2;   // n=32
        icode = icode>>6;   // n=512
    	icode &= 0x00007fff;

    	CScalerSetByte(_P1_I_CODE_M_A1,(BYTE)(icode >> 8));
    	CScalerSetByte(_P1_I_CODE_L_A2, (BYTE)icode);

    	// Set the P code
        //pcode = (5 * icode * _RTD_XTAL / (stModeInfo.IHFreq/10) / _APLL_N_CODE ) >> 7;    // Total gain=(1+5)/32
        pcode = (63 * icode * _RTD_XTAL / (IHF/10) / _APLL_N_CODE ) >> 7;    // Total gain=(1+63)/512
    //    pcode = 0xC0;
    //*/    whhsiao 20080227 update-end
    	if(pcode > 255)
    	{
    		for(pData[0] = 9; pData[0] < 15; pData[0]++)
    		{
    			if((pcode >> pData[0]) == 0)
    				break;
    		}
            switch(pData[0]-9)//yc 20080225
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
    		//pcode = pcode / g_value_divider[(pData[0] - 9)];
    		STemp = pData[0] - 7;
    	}

    	if(pcode==0)
        pcode = 1;

    	//g_value = 0x01;
        CScalerSetByte(_P1_P_CODE_MAPPING_METHOD_B6, STemp << 2);

        CScalerSetByte(_P1_DDS_MIX_2_B9, 0x05); //set the P_code_max
        CScalerSetByte(_P1_DDS_MIX_3_BA, 0x1e);
    	CScalerSetByte(_P1_P_CODE_A3, (BYTE)pcode);

    	CScalerSetByte(_P1_PLLPHASE_CTRL1_B4, 0x00);

        //CTimerWaitForEvent(_EVENT_IEN_STOP);
        //CTimerWaitForEvent(_EVENT_IEN_STOP);

        pData[0] = 32;
        do
        {
            CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
    	    CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));
    	    CScalerSetByte(_P1_PLLPHASE_CTRL1_B4, 0x00);

            //CTimerWaitForEvent(_EVENT_IEN_STOP);
            //CTimerWaitForEvent(_EVENT_IEN_STOP);

        }while(CAdjustGetAPLLSetting(usClock) && --pData[0]);

    	//CPowerADCAPLLOn();


        //CTimerWaitForEvent(_EVENT_IEN_STOP);
        //CTimerWaitForEvent(_EVENT_IEN_STOP);
        //CTimerWaitForEvent(_EVENT_IEN_STOP);

        CAdjustGetAPLLSetting(usClock);

        CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x00);

        //CMiscClearStatusRegister();

    }
}


void SetAPLLFrequncy(uint32_t outFreq, uint32_t horFreq)
{
    // FREQUENCY_OUTPUT = FREQUENCY_INPUT * (M_VALUE + K_VALUE / 16) / N_VALUE / (1 << OUTPUT_DIVIDER)

    CAdjustAdcClock(1056, 378);

    ScalerWriteByte(S_PAGE_SELECT, 1);
    ScalerWriteBit (S1_PLL_WDT, 0, 0); // Power up the APLL

    return;

    ScalerWriteByte(S_PAGE_SELECT, 1);

    ScalerWriteByte(S1_ICODE_HI, 0);
    ScalerWriteByte(S1_ICODE_LO, 9);
    ScalerWriteByte(S1_PCODE, 16);

    ScalerWriteByte(S1_PLL_M, 15);
    ScalerWriteByte(S1_PLL_N, 0xc1);
    ScalerWriteByte(S1_PLL_CURRENT, 0x65);

    ScalerWriteByte(S1_PLL_DIV_HI, 0x74);
    ScalerWriteByte(S1_PLL_DIV_LO, 0x1f);

    ScalerWriteByte(S1_PLL_PHASE_INTERPOLATION, 0x10);
    ScalerWriteByte(S1_P_CODE_MAPPING_METHOD, 0x10);

    ScalerWriteByte(S1_DDS_MIX1, 0x4d);
    ScalerWriteByte(S1_DDS_MIX2, 0xff);
    ScalerWriteByte(S1_DDS_MIX3, 0xff);

    ScalerWriteByte(S_PAGE_SELECT, 1);
    ScalerWriteBit (S1_PLL_WDT, 0, 0); // Power up the APLL


ScalerWriteByte(S_PAGE_SELECT, 0);
ScalerWriteByte(0xa0, 0x00);
ScalerWriteByte(0xa1, 0x0f);
ScalerWriteByte(0xa2, 0x00);
ScalerWriteByte(0xa3, 0x00);
ScalerWriteByte(0xa4, 0x00);
ScalerWriteByte(0xa5, 0x06);
ScalerWriteByte(0xa6, 0x84);
ScalerWriteByte(0xa7, 0x84);
ScalerWriteByte(0xa8, 0x10);
ScalerWriteByte(0xa9, 0xc1);
ScalerWriteByte(0xaa, 0x00);
ScalerWriteByte(0xab, 0x18);
ScalerWriteByte(0xac, 0x88);
ScalerWriteByte(0xad, 0x00);
ScalerWriteByte(0xae, 0x02);
ScalerWriteByte(0xaf, 0x01);
ScalerWriteByte(0xb0, 0x00);
ScalerWriteByte(0xb1, 0x00);
ScalerWriteByte(0xb2, 0x00);
ScalerWriteByte(0xb3, 0x00);
ScalerWriteByte(0xb4, 0x00);
ScalerWriteByte(0xb5, 0x00);
ScalerWriteByte(0xb6, 0x00);
ScalerWriteByte(0xb7, 0x00);
ScalerWriteByte(0xb8, 0x00);
ScalerWriteByte(0xb9, 0x00);
ScalerWriteByte(0xba, 0x00);
ScalerWriteByte(0xbb, 0x00);
ScalerWriteByte(0xbc, 0x00);
ScalerWriteByte(0xbd, 0x00);
ScalerWriteByte(0xbe, 0x00);
ScalerWriteByte(0xbf, 0x00);
ScalerWriteByte(0xc0, 0x83);
ScalerWriteByte(0xc1, 0x8c);
ScalerWriteByte(0xc2, 0x8b);
ScalerWriteByte(0xc3, 0x82);
ScalerWriteByte(0xc4, 0x89);
ScalerWriteByte(0xc5, 0x80);
ScalerWriteByte(0xc6, 0x3f);
ScalerWriteByte(0xc7, 0x55);
ScalerWriteByte(0xc8, 0x15);
ScalerWriteByte(0xc9, 0x53);
ScalerWriteByte(0xca, 0x29);
ScalerWriteByte(0xcb, 0x00);
ScalerWriteByte(0xcc, 0x01);
ScalerWriteByte(0xcd, 0x00);
ScalerWriteByte(0xce, 0x15);
ScalerWriteByte(0xcf, 0x50);
ScalerWriteByte(0xd0, 0x50);
ScalerWriteByte(0xd1, 0x50);
ScalerWriteByte(0xd2, 0x20);
ScalerWriteByte(0xd3, 0x00);
ScalerWriteByte(0xd4, 0xf0);
ScalerWriteByte(0xd5, 0x00);
ScalerWriteByte(0xd6, 0x58);
ScalerWriteByte(0xd7, 0x00);
ScalerWriteByte(0xd8, 0x00);
ScalerWriteByte(0xd9, 0x00);
ScalerWriteByte(0xda, 0x84);
ScalerWriteByte(0xdb, 0x84);
ScalerWriteByte(0xdc, 0xd4);
ScalerWriteByte(0xdd, 0x00);
ScalerWriteByte(0xde, 0x00);
ScalerWriteByte(0xdf, 0x00);
ScalerWriteByte(0xe0, 0x00);
ScalerWriteByte(0xe1, 0x00);
ScalerWriteByte(0xe2, 0x00);
ScalerWriteByte(0xe3, 0x84);
ScalerWriteByte(0xe4, 0x10);
ScalerWriteByte(0xe5, 0x82);
ScalerWriteByte(0xe6, 0x04);
ScalerWriteByte(0xe7, 0xc0);
ScalerWriteByte(0xe8, 0x60);
ScalerWriteByte(0xe9, 0x24);
ScalerWriteByte(0xea, 0x00);
ScalerWriteByte(0xeb, 0x06);
ScalerWriteByte(0xec, 0x00);
ScalerWriteByte(0xed, 0x00);
ScalerWriteByte(0xee, 0x00);
ScalerWriteByte(0xef, 0x00);
ScalerWriteByte(0xf0, 0x00);
ScalerWriteByte(0xf1, 0x00);
ScalerWriteByte(0xf2, 0x00);
ScalerWriteByte(0xf3, 0xd4);
ScalerWriteByte(0xf4, 0xcf);
ScalerWriteByte(0xf5, 0x00);
ScalerWriteByte(0xf6, 0x00);
ScalerWriteByte(0xf7, 0x00);
ScalerWriteByte(0xf8, 0x00);
ScalerWriteByte(0xf9, 0x00);
ScalerWriteByte(0xfa, 0x00);
ScalerWriteByte(0xfb, 0x00);
ScalerWriteByte(0xfc, 0x00);
ScalerWriteByte(0xfd, 0x00);
ScalerWriteByte(0xfe, 0x00);
ScalerWriteByte(0xff, 0x00);
ScalerWriteByte(S_PAGE_SELECT, 1);
ScalerWriteByte(0xa0, 0x08);
ScalerWriteByte(0xa1, 0x00);
ScalerWriteByte(0xa2, 0x09);
ScalerWriteByte(0xa3, 0x10);
ScalerWriteByte(0xa4, 0x01);
ScalerWriteByte(0xa5, 0x44);
ScalerWriteByte(0xa6, 0x00);
ScalerWriteByte(0xa7, 0x00);
ScalerWriteByte(0xa8, 0x00);
ScalerWriteByte(0xa9, 0x00);
ScalerWriteByte(0xaa, 0x03);
ScalerWriteByte(0xab, 0x00);
ScalerWriteByte(0xac, 0x0f);
ScalerWriteByte(0xad, 0xc1);
ScalerWriteByte(0xae, 0x65);
ScalerWriteByte(0xaf, 0x00);
ScalerWriteByte(0xb0, 0x01);
ScalerWriteByte(0xb1, 0x74);
ScalerWriteByte(0xb2, 0x1f);
ScalerWriteByte(0xb3, 0x30);
ScalerWriteByte(0xb4, 0x00);
ScalerWriteByte(0xb5, 0x10);
ScalerWriteByte(0xb6, 0x10);
ScalerWriteByte(0xb7, 0x02);
ScalerWriteByte(0xb8, 0x4d);
ScalerWriteByte(0xb9, 0xff);
ScalerWriteByte(0xba, 0xff);
ScalerWriteByte(0xbb, 0x1b);
ScalerWriteByte(0xbc, 0xa0);
ScalerWriteByte(0xbd, 0x00);
ScalerWriteByte(0xbe, 0x00);
ScalerWriteByte(0xbf, 0x51);
ScalerWriteByte(0xc0, 0x24);
ScalerWriteByte(0xc1, 0x81);
ScalerWriteByte(0xc2, 0x13);
ScalerWriteByte(0xc3, 0x16);
ScalerWriteByte(0xc4, 0x18);
ScalerWriteByte(0xc5, 0x0c);
ScalerWriteByte(0xc6, 0x00);
ScalerWriteByte(0xc7, 0x42);
ScalerWriteByte(0xc8, 0x72);
ScalerWriteByte(0xc9, 0x84);
ScalerWriteByte(0xca, 0x01);
ScalerWriteByte(0xcb, 0x0d);
ScalerWriteByte(0xcc, 0x40);
ScalerWriteByte(0xcd, 0x39);
ScalerWriteByte(0xce, 0x00);
ScalerWriteByte(0xcf, 0x00);
ScalerWriteByte(0xd0, 0x00);
ScalerWriteByte(0xd1, 0x00);
ScalerWriteByte(0xd2, 0x00);
ScalerWriteByte(0xd3, 0x00);
ScalerWriteByte(0xd4, 0x00);
ScalerWriteByte(0xd5, 0x00);
ScalerWriteByte(0xd6, 0x00);
ScalerWriteByte(0xd7, 0x00);
ScalerWriteByte(0xd8, 0x00);
ScalerWriteByte(0xd9, 0x00);
ScalerWriteByte(0xda, 0x00);
ScalerWriteByte(0xdb, 0x00);
ScalerWriteByte(0xdc, 0x00);
ScalerWriteByte(0xdd, 0x00);
ScalerWriteByte(0xde, 0x00);
ScalerWriteByte(0xdf, 0x00);
ScalerWriteByte(0xe0, 0x82);
ScalerWriteByte(0xe1, 0x94);
ScalerWriteByte(0xe2, 0x00);
ScalerWriteByte(0xe3, 0x00);
ScalerWriteByte(0xe4, 0x00);
ScalerWriteByte(0xe5, 0x00);
ScalerWriteByte(0xe6, 0x00);
ScalerWriteByte(0xe7, 0x00);
ScalerWriteByte(0xe8, 0x00);
ScalerWriteByte(0xe9, 0x00);
ScalerWriteByte(0xea, 0x1b);
ScalerWriteByte(0xeb, 0xdc);
ScalerWriteByte(0xec, 0x78);
ScalerWriteByte(0xed, 0x00);
ScalerWriteByte(0xee, 0x00);
ScalerWriteByte(0xef, 0x00);
ScalerWriteByte(0xf0, 0x00);
ScalerWriteByte(0xf1, 0x00);
ScalerWriteByte(0xf2, 0x00);
ScalerWriteByte(0xf3, 0x00);
ScalerWriteByte(0xf4, 0x00);
ScalerWriteByte(0xf5, 0x00);
ScalerWriteByte(0xf6, 0x00);
ScalerWriteByte(0xf7, 0x00);
ScalerWriteByte(0xf8, 0x00);
ScalerWriteByte(0xf9, 0x00);
ScalerWriteByte(0xfa, 0x00);
ScalerWriteByte(0xfb, 0x00);
ScalerWriteByte(0xfc, 0x00);
ScalerWriteByte(0xfd, 0x00);
ScalerWriteByte(0xfe, 0x00);
ScalerWriteByte(0xff, 0x00);

}

void SetVideoBrightness(uint8_t value)
{
    ScalerWriteBit(S_COLOR_CONTROL, 0, BIT_ONE);
    ScalerWritePortByte(S_CB_PORT, 0x80, value);
    ScalerWritePortByte(S_CB_PORT, 0x81, value);
    ScalerWritePortByte(S_CB_PORT, 0x82, value);
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

void InitScaler()
{
    ScalerWriteBit(S_HOST_CONTROL, 0, BIT_ONE);
    delayMS(10); // Wait for at least 8ms
    ScalerWriteBit(S_HOST_CONTROL, 0, BIT_ZERO);

    SetPowerMode(POWER_MODE_FULL);
    SetDPLLFrequncy(PANEL_DCLK); // DPLL Settings

    // SetVideoContrast(128);
    // SetVideoBrightness(128);
    // SetVideoSaturation(180);
    // SetVideoHue(0);

    ScalerWriteTable(DisplayInitTable);
}