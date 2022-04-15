#include "alien/header/Global.h"
//----------------------------------------------------------------------------------------------------
// Copyright of Realtek SemiConductor Corp.
// Model   : RTD2553V
// Version : V0.00c (08.31.2005)
//
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// ID Code      : Main.c No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __MAIN__

#include "alien/header/Include.h"


/**
 * CMainUserInitial
 * Setting some flags for user when initial
 * @param <none>
 * @return {none}
 *
 */
void CMainUserInitial(void)
{
	// User can make some initial settings at firmware startup
	CLR_PANELPOWERSTATUS();
	CLR_LIGHTPOWERSTATUS();
	CLR_FRAMESYNCSTATUS();
	CLR_POWERSWITCH();
	CLR_FIRST_ADCCLOCK();
    CLR_OSD_READYFORDISPLAY();
	#if(_HDMI_SUPPORT == _ON)
    CLR_HDMIINPUT();
	#endif
	SET_FIRST_LOADFONT();
	#if defined(CONFIG_VBI_ENABLE)
	CLR_OSDVBI_INITIAL();
	#endif
	//SET_SOURCE_AUTOCHANGE();
	CLR_SOURCE_AUTOCHANGE();
	SET_PRE_VGA_CONNECT(bVGACONNECT);
	#if(_TMDS_SUPPORT == _ON)
	#if (_HDMI_SUPPORT == _ON)
	SET_PRE_HDMI_CONNECT(bHDMICONNECT);
	#else
	SET_PRE_DVI_CONNECT(bDVICONNECT);
	#endif
	#endif
	CLR_USE_TRANSITION_RESULT();
    CheckLanguage();
}

/**
 * CMainSystemInitial
 * Initial the system for once when power up
 * @param <none>
 * @return {none}
 *
 */
void CMainSystemInitial(void)
{
	#if(_VIDEO_TV_SUPPORT)
    ucAddrIfPllDM = _ADDR_IfPllDM;
	#endif

    // Initial MCU
	CMcuInitial();
    CMuteOn();

	#if( (_HDCP_SUPPORT == _ON) && _HDMI_HOT_PLUG_OPTION)
   	bHot_Plug = _HOT_PLUG_LOW;
	#endif

    // Initial timer events
	CTimerInitialTimerEvent();

    CPowerLightPowerOff();
    CPowerPanelPowerOff();
 	//CScalerPageSelect(_PAGE0);//eric 20070529
	//CScalerSetByte(_P0_POWER_ON_RESET_F3,_BIT7|_BIT6);		

    // Check eeprom and load eeprom settings
	CEepromStartupCheck();

    //_SET_INPUT_SOURCE(_SOURCE_HDMI);
		_SET_INPUT_SOURCE(_SOURCE_VGA);
    //SET_POWERSTATUS();

    // Initial scaler settings
	CScalerInitial();

    // Initial key scan status
	CKeyInitial();

    // Initial user settings
	CMainUserInitial();

	#if(_VIDEO_SUPPORT == _ON)
    // Initial video settings
   	CVideoInitial();
	CVideoOutputDisable();
	#else
    CInitInputSource();
	#endif  // End of #if(_VIDEO_SUPPORT == _ON)

	CDdcciInitial();

	#if(_FAST_READ == _ON)
	CMCUSetFlashClk();
	#endif
	 
    CIrdaInitial();
}


BYTE code DisplayInitTable[] =
{
    1+3, 1, 0x2A, 0x00,
    22+3, 1, 0x2B, (((1 + 32 + 1024 + 287 - 4)) >> 8), ((1 + 32 + 1024 + 287 - 4)),
                                            (1),
                                            (((1 - 10)) >> 8), ((1 - 10)),
                                            (((1 + 32 - 10)) >> 8), ((1 + 32 - 10)),
                                            (((1 + 32 + 1024 - 10)) >> 8), ((1 + 32 + 1024 - 10)),
                                            (((1 + 32 + 1024 + 287 - 10)) >> 8), ((1 + 32 + 1024 + 287 - 10)),
                                            (((1 + 22 + 600 + 12)) >> 8), ((1 + 22 + 600 + 12)),
                                            (1),
                                            (((1)) >> 8), ((1)),
                                            (((1 + 22)) >> 8), ((1 + 22)),
                                            (((1 + 22 + 600)) >> 8), ((1 + 22 + 600)),
                                            (((1 + 22 + 600 + 12)) >> 8), ((1 + 22 + 600 + 12)),

    1+3, 1, 0x29, (0 << 0) |
                                            (0 << 1) |
                                            (0 << 2) |
                                            (0 << 4) |
                                            (0 << 5) |
                                            (0 << 6),

    1+3, 1, 0x28, (1 << 0) |
                                            (1 << 1) |
                                            (0 << 2) |
                                            (0 << 4) |
                                            (1 << 5) |
                                            (1 << 7),


    1+3, 1, 0x9F, 1,
    1+3, 1, 0xC7, ((((1 + 32 + 1024 + 287 - 4) + 4) >> 8) << 4) | ((1 + 22 + 600 + 12) >> 8),
    1+3, 1, 0xC8, (1 + 22 + 600 + 12),
    1+3, 1, 0xC9, ((1 + 32 + 1024 + 287 - 4) + 4),


    1+3, 1, 0x8B, 0x00,
    1+3, 1, 0x8C, 1 & 1,
    1+3, 1, 0x8B, 0xA0,
    2+3, 1, 0x8C, (3 << 4),
                                            (3 << 6),

    0
};

void SetDPLLFrequncy(DWORD dclk)
{
    BYTE dpllN, dpllDiv, dpllM, lpfMode, Ich;
		DWORD freq, offset;
	
    if (dclk < 3000000)
        return;
    else if (dclk < 10000000)
        {dpllN = 5; dpllDiv = 3; }
    else if (dclk < 40000000)
        {dpllN = 5; dpllDiv = 1; }
    else if (dclk < 100000000)
        {dpllN = 6; dpllDiv = 1; }
    else
        {dpllN = 12; dpllDiv = 0; }

    dpllM = 2 * dclk * dpllN * (1 << dpllDiv) / 27000000UL;

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
    Ich = ((((BYTE)(Ich - 1)) < (15)) ? ((BYTE)(Ich - 1)) : (15));

    CScalerSetByte(0x9F, 1);
    CScalerSetByte(0xBF, dpllM - 2);
    CScalerSetByte(0xC0, (dpllN - 2) | (dpllDiv << 4));
    CScalerSetByte(0xC1, Ich | (2 << 6));

    CScalerSetBit(0xC2, ~_BIT0, lpfMode);
    CScalerSetBit(0xC2, ~_BIT1, _BIT1);

    freq = 27000000UL * dpllM / dpllN / 2 / (1 << dpllDiv);
    offset = (dclk - freq) / (freq >> 15);
    offset = (((offset) < (0x0FFF)) ? (offset) : (0x0FFF));
    CScalerSetByte(0xC4, offset >> 8);
    CScalerSetByte(0xC5, offset);
    CScalerSetBit(0xC4, ~_BIT4, 0);
    CScalerSetBit(0xC6, ~_BIT2, _BIT2);
    CScalerSetBit(0xCA, ~_BIT0, _BIT0);
}

BYTE code ttSCALER_RESET_TABLE[] =
{
    4,  _NON_AUTOINC,   _HOST_CTRL_01,                  0x40,

    //5,  _AUTOINC,       _WATCH_DOG_CTRL0_0C,            0x00,0x00,                          //CR[0C] ~ CR[0D]
    //22, _AUTOINC,       _VGIP_CTRL_10,                  0x00,0x00,0x00,0x00,0x00,0x00,0x08, //CR[10] ~ CR[16]
                                                        0x00,0x00,0x00,0x00,0x00,0x00,0x00, //CR[17] ~ CR[1D]
                                                        0x00,0x10,0x00,0x00,0x00, //CR[1E] ~ CR[22]  //fjyang20070712 for FV set
//    5,  _AUTOINC,       _VDISP_CTRL_28,                 0x00,0x00,                          //CR[28] ~ CR[29]
    //6,  _AUTOINC,       _FIFO_ACCESS_PORT_30,           0x00,0x00,0x00,                     //CR[30] ~ CR[32]
    //5,  _AUTOINC,       _FS_DELAY_FINE_TUNING_43,       0x00,0x00,                          //CR[43] ~ CR[44]
    //6,  _AUTOINC,       _SYNC_SELECT_47,                0x00,0x00,0x00,                     //CR[47] ~ CR[49]
    //5,  _AUTOINC,       _STABLE_MEASURE_4F,             0x00,0x00,                          //CR[4F] ~ CR[50]

//    4,  _NON_AUTOINC,   _SYNC_PROC_ACCESS_PORT_5C,      _SYNC_G_CLAMP_START_00,
//    13, _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x04,0x10,0x04,0x10,0x02,0x01,0x20,0x21,0x04,0x00,

    // 4,  _NON_AUTOINC,   _OVERLAY_CTRL_6C,               0x00,//tommy delete
    //4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x00,
    //6,  _AUTOINC,       _P0_ADC_RED_CTL_CF,             0x50,0x50,0x50,

    //4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,
    // Eric Lee mark
    //----------------------------
   // 4,  _NON_AUTOINC,   _P0_VADC_SWITCH_AF,             0x00,

    //6,  _AUTOINC,       _P0_ADC_SOG0_CTRL_D2,           0x20, 0x11, 0x00, //for SOG0 CTRL, DC Restore/Clamp Enable	//v003
	// 4,  _NON_AUTOINC,   _P0_SOG1_CTRL_AC,               0x20, //for SOG1 CTRL
		
//    4,  _NON_AUTOINC,   _P0_ADC_POWER_C6,               0x38,
    //4,  _NON_AUTOINC,   _P0_ADC_V_BAIS1_CB,             0x00,	//v003	
    //4,  _NON_AUTOINC,   _P0_ADC_CLAMP_CTRL1_D5,         0x00, 

    //4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE1,	//v003
    //4,  _NON_AUTOINC,   _P1_MIX_B0,                     0x00,				//v003

	// 4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE2,
	//11, _AUTOINC,       _P2_TMDS_OUTPUT_CTRL_A6,        0x78,0x0f,0x03,0x00,0x31,0x70,0xe3,0x24,

    //4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE6,
	//4,  _NON_AUTOINC,   _P6_UZD_CTRL1_E4,        				0x00,		
    //4,  _NON_AUTOINC,   _P6_ENABLE_BIST_CTRL_A0,        0x00,//v003
    //4,  _NON_AUTOINC,   _P6_PEAKING_ENABLE_C1,          0x00,//v003
    //4,  _NON_AUTOINC,   _P6_YUV422_TO_YUV444_D4,        0x00,

    //4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE7,
    //5,  _AUTOINC,       _P7_YUV2RGB_CTRL_BF,            0x02,0x00,
    //4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x00,

    //4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE3,

    _END
};


/**
 * main
 * main process
 * first system initial, then main loop
 * @param <none>
 * @return {none}
 *
*/
void main(void)
{          
	volatile BYTE fTest = 1;
    
	
	//CMainSystemInitial();

    // Initial MCU
	//CMcuInitial();
    IE      = 0x00;                         // Disable all interrupts
    TMOD    = 0x11;                         // Program Timer0 & Timer1 to Mode#1
    TR0     = 0;                            // Stop Timer0
    TF0     = 0;                            // Clear Timer0 Overflow Bit
    TL0     = _TIMER0_COUNT_LBYTE;          // Load Timer0 low-byte   (for 1ms)
    TH0     = _TIMER0_COUNT_HBYTE;          // Load Timer0 high-byte  (for 1ms)
    TR1     = 0;                            // Stop Timer1
    TF1     = 0;                            // Clear Timer1 Overflow Bit
    IE      = 0x8a;                         // Enable interrupts of Timer0

	MCU_WATCHDOG_TIMER_FFEA		= 0x00; 	//dis wdt, wdt default enable
    MCU_WATCHDOG_TIMER_FFEA		|= 0x40;	//clr wdt.//eric 20070627
    MCU_CTRL_FFED				= 0x80; 		//FlashDIV=1
    MCU_CLOCK_CTRL_FFEE 		|= 0x40;		    //keep mcu peripheral running while mcu stopped by spi flash access
    // Initial timer events
	CTimerInitialTimerEvent();
		  CUartInit();
		CSwitchToUart();

    //_SET_INPUT_SOURCE(_SOURCE_HDMI);
		_SET_INPUT_SOURCE(_SOURCE_VGA);
    //SET_POWERSTATUS();

	    CScalerSetBit(_HOST_CTRL_01, ~_BIT0, _BIT0);
    CTimerDelayXms(20);
    CScalerSetBit(_HOST_CTRL_01, ~_BIT0, 0x00);
    

		//CScalerCodeW(ttSCALER_RESET_TABLE);
		CScalerSetByte(_HOST_CTRL_01, 0x40);

	//CAdjustDisableWatchDog(_WD_ALL);

	
	
	
	
	
    
	bLED1 = _LED_OFF;
	bLED2 = _LED_OFF;

	bHot_Plug = _HOT_PLUG_HI;
	
	bPANELPOWER = 1;
	bLIGHTPOWER = 0;
	
	//CTimerDelayXms(4000);

	/*while(fTest)
    {
        //bPANELPOWER ^= 1;
        //bLIGHTPOWER ^= 1;

      //  bLED1 ^= 1;
		//bLED2 ^= bLED1;

		CTimerDelayXms(250);
    }*/
		
		//CScalerCodeW(DisplayInitTable);
		
		//SetDPLLFrequncy(52000000);		

		
		//CModeSetupModeVGA();
		//CModeDetectCommon();
		//CSyncProcess();   
	//CScalerCodeW(tSCALER_POWERUP_INITIAL);
		ucCurrState = _SEARCH_STATE;
		DebugPrintf("CALL 1\n",0);
		CModeHandler();//CModeHandler();
		DebugPrintf("CALL 2\n",0);
		CModeHandler();
		DebugPrintf("CALL 3\n",0);
		CModeHandler();
		DebugPrintf("CALL 4\n",0);
		CModeHandler();
		DebugPrintf("CALL 5\n",0);
		CModeHandler();
		//DebugPrintf("CALL 7\n",0);
		//sCModeHandler();				
		while(fTest);
		
    do
	{
		#if(_DEBUG_EN)
		//CMiscIspDebugProc();
        #endif

		//CTimerHandler();
        //CKeyHandler();
		DebugPrintf("CALL %i\n",fTest++);
		CModeHandler();
		//COsdHandler();
	}	

    while(_TRUE);
}

