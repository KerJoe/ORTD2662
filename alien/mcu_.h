#include "alien/global_.h"
//----------------------------------------------------------------------------------------------------
// ID Code      : Mcu.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Crystal Frequency
//--------------------------------------------------

#define _MCU_INST_CYCLE             	((DWORD)1000000 * 4 / _MCU_XTAL)
#define _MCU_INST_CYCLE_PD				((DWORD)1000000 * 4 / _RTD_XTAL)		//pwr-dn case(reset 27M xtal clk)

//--------------------------------------------------
// Timer Period (unit: ns)
//--------------------------------------------------
#define _16MS_PERIOD                	(DWORD)16000000
#define _8MS_PERIOD                		(DWORD)8000000
#define _5MS_PERIOD                		(DWORD)5000000
#define _4167uS_PERIOD            		(DWORD)4167000
#define _8333uS_PERIOD              	(DWORD)8333000
#define _10MS_PERIOD                	(DWORD)10000000
#define _1MS_PERIOD                 	(DWORD)1000000		//330000	//380000	//1000000		//eric 20070509 IrDA
#define _HALF_MS_PERIOD             	(DWORD)500000
#define _375uS_PERIOD              		(DWORD)375000
#define _250uS_PERIOD 					(DWORD)250000		//830000	//95000	//250000		//eric 20070509 IrDA
#define _150uS_PERIOD 					(DWORD)150000
#define _125uS_PERIOD 					(DWORD)125000

#define _TIMER0_PERIOD					_250uS_PERIOD
#define _EVENT_PERIOD					_1MS_PERIOD / _TIMER0_PERIOD

//--------------------------------------------------
// Timer0 Settings (1ms)
//--------------------------------------------------
#define _TIMER0_COUNT_NUM				(0xFFFF - (_TIMER0_PERIOD / _MCU_INST_CYCLE))			//pwr-up case(reset 24.3M pll clk)
#define _TIMER0_COUNT_LBYTE				(_TIMER0_COUNT_NUM & 0x00FF)
#define _TIMER0_COUNT_HBYTE				(_TIMER0_COUNT_NUM >> 8)

#define _TIMER0_COUNT_NUM_PD			(0xFFFF - (_TIMER0_PERIOD / _MCU_INST_CYCLE_PD))		//pwr-dn case(reset 27M xtal clk)
#define _TIMER0_COUNT_LBYTE_PD			(_TIMER0_COUNT_NUM_PD & 0x00FF)
#define _TIMER0_COUNT_HBYTE_PD			(_TIMER0_COUNT_NUM_PD >> 8)

//#define _TIMER1_COUNT_NUM           	(0xFFFF - (_16MS_PERIOD / _MCU_INST_CYCLE))
//#define _TIMER1_COUNT_NUM            	(0xFFFF - (_1MS_PERIOD / _MCU_INST_CYCLE))//(0x1)
#define _TIMER1_COUNT_NUM           	(1)
#define _TIMER1_COUNT_LBYTE         	(_TIMER1_COUNT_NUM & 0x00FF)
#define _TIMER1_COUNT_HBYTE         	(_TIMER1_COUNT_NUM >> 8)

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of mcu I/O pin
//--------------------------------------------------
// MCU Port 5
#define _MCU_PORT52                     MCU_PORT52_PIN_REG_FFC1
#define _MCU_PORT53                     MCU_PORT53_PIN_REG_FFC2
#define _MCU_PORT54                     MCU_PORT54_PIN_REG_FFC3
#define _MCU_PORT55                     MCU_PORT55_PIN_REG_FFC4
#define _MCU_PORT56                     MCU_PORT56_PIN_REG_FFC5
#define _MCU_PORT57                     MCU_PORT57_PIN_REG_FFC6
// MCU Port 6
#define _MCU_PORT60                     MCU_PORT60_PIN_REG_FFC7
#define _MCU_PORT61                     MCU_PORT61_PIN_REG_FFC8
#define _MCU_PORT62                     MCU_PORT62_PIN_REG_FFC9
#define _MCU_PORT63                     MCU_PORT63_PIN_REG_FFCA
#define _MCU_PORT64                     MCU_PORT64_PIN_REG_FFCB
#define _MCU_PORT65                     MCU_PORT65_PIN_REG_FFCC
#define _MCU_PORT66                     MCU_PORT66_PIN_REG_FFCD
#define _MCU_PORT67                     MCU_PORT67_PIN_REG_FFCE
// MCU Port 7
#define _MCU_PORT70                     MCU_PORT70_PIN_REG_FFCF
#define _MCU_PORT71                     MCU_PORT71_PIN_REG_FFD0
#define _MCU_PORT72                     MCU_PORT72_PIN_REG_FFD1
#define _MCU_PORT73                     MCU_PORT73_PIN_REG_FFD2
#define _MCU_PORT74                     MCU_PORT74_PIN_REG_FFD3
#define _MCU_PORT75                     MCU_PORT75_PIN_REG_FFD4
#define _MCU_PORT76                     MCU_PORT76_PIN_REG_FFD5
// MCU Port 8
#define _MCU_PORT80                     MCU_PORT80_PIN_REG_FFD6
#define _MCU_PORT81                     MCU_PORT81_PIN_REG_FFD7
// MCU Port 9
#define _MCU_PORT90                     MCU_PORT90_PIN_REG_FFD8
#define _MCU_PORT91                     MCU_PORT91_PIN_REG_FFD9
#define _MCU_PORT92                     MCU_PORT92_PIN_REG_FFDA
#define _MCU_PORT93                     MCU_PORT93_PIN_REG_FFDB
#define _MCU_PORT94                     MCU_PORT94_PIN_REG_FFDC


#define MCU_IRQ_STATUS_FF00			 0x00
#define MCU_IRQ_PRIORITY_FF01		 0x01
//#define MCU_PORT6_OE_FF04 0x04

#define MCU_THRESHOLD_VALUE_FF0F 0x0F//new add

#define MCU_VGA_DDC_ENA_FF1B 0x1B	// VGA DDC1
#define MCU_DVI_DDC_ENA_FF1E 0x1E	// DVI DDC2
#define MCU_DDCRAM_PART_FF21 0x21

#define MCU_I2C_SET_SLAVE_FF23 0x23
#define MCU_I2C_SUB_IN_FF24 0x24
#define MCU_I2C_DATA_IN_FF25 0x25
#define MCU_I2C_DATA_OUT_FF26 0x26
#define MCU_I2C_STATUS_FF27 0x27
#define MCU_I2C_IRQ_CTRL_FF28 0x28
#define MCU_I2C_STATUS2_FF29 0x29
#define MCU_I2C_IRQ_CTRL2_FF2A 0x2A
#define MCU_I2C_CHANNEL_CTRL_FF2B 0x2B
#define MCU_HDMI_DDC_ENA_FF2C 0x2C	// HDMI DDC3

#define MCU_PWM_CK_SEL_FF3A        	 0x3A
#define MCU_PWM03_M_FF3B       		 0x3B
#define MCU_PWM45_M_FF3C       		 0x3C

#define MCU_PWM01_N_MSB_FF3D       	 0x3D
#define MCU_PWM0_N_LSB_FF3E       	 0x3E
#define MCU_PWM1_N_LSB_FF3F       	 0x3F

#define MCU_PWM23_N_MSB_FF40       	 0x40
#define MCU_PWM2_N_LSB_FF41       	 0x41
#define MCU_PWM3_N_LSB_FF42       	 0x42

#define MCU_PWM45_N_MSB_FF43       	 0x43
#define MCU_PWM4_N_LSB_FF44       	 0x44
#define MCU_PWM5_N_LSB_FF45       	 0x45

#define MCU_PWML_FF46				 0x46
#define MCU_PWM_VS_CTRL_FF47			 0x47
#define MCU_PWM_EN_FF48        		 0x48

#define MCU_PWM_CK_FF49        		 0x49

#define MCU_PWM0H_DUT_FF4A 0x4A
#define MCU_PWM1H_DUT_FF4B 0x4B
#define MCU_PWM01L_DUT_FF4C 0x4C

#define MCU_PWM2H_DUT_FF4D 0x4D
#define MCU_PWM3H_DUT_FF4E 0x4E
#define MCU_PWM23L_DUT_FF4F 0x4F

#define MCU_PWM4H_DUT_FF50 0x50
#define MCU_PWM5H_DUT_FF51 0x51
#define MCU_PWM45L_DUT_FF52 0x52

#define MCU_COMMON_INST_EN_FF60			 0x60
#define MCU_COMMON_OP_CODE_FF61		 0x61
//#define MCU_WREN_OP_CODE_FF62				 0x62
//#define MCU_EWSR_OP_CODE_FF63				 0x63
#define MCU_FLASH_PROG_ISP0_FF64				 0x64
#define MCU_FLASH_PROG_ISP1_FF65				 0x65
#define MCU_FLASH_PROG_ISP2_FF66				 0x66
#define MCU_COMMON_INST_RD_PT0_FF67		 0x67
#define MCU_COMMON_INST_RD_PT1_FF68		 0x68
#define MCU_COMMON_INST_RD_PT2_FF69		 0x69

//#define MCU_READ_OP_CODE_FF6A			 0x6A
//#define MCU_PROG_OP_CODE_FF6D			 0x6D
#define MCU_PROG_INST_FF6F				 0x6F
//#define MCU_PROG_DATA_PORT_FF70		 0x70
#define MCU_PROG_LEN_FF71				 0x71
//#define MCU_CRC_END_ADDR0_FF72			 0x72
//#define MCU_CRC_END_ADDR1_FF73			 0x73
//#define MCU_CRC_END_ADDR2_FF74			 0x74

#define MCU_PIN_SHARE_CTRL00_FF96 0x96
#define MCU_PIN_SHARE_CTRL01_FF97 0x97
#define MCU_PIN_SHARE_CTRL02_FF98 0x98
#define MCU_PIN_SHARE_CTRL03_FF99 0x99
#define MCU_PIN_SHARE_CTRL04_FF9A 0x9A
#define MCU_PIN_SHARE_CTRL05_FF9B 0x9B
#define MCU_PIN_SHARE_CTRL06_FF9C 0x9C
#define MCU_PIN_SHARE_CTRL07_FF9D 0x9D
#define MCU_PIN_SHARE_CTRL08_FF9E 0x9E
#define MCU_PIN_SHARE_CTRL09_FF9F 0x9F
#define MCU_PIN_SHARE_CTRL0A_FFA0 0xA0
#define MCU_PIN_SHARE_CTRL0B_FFA1 0xA1
#define MCU_PIN_SHARE_CTRL0C_FFA2 0xA2
#define MCU_PIN_SHARE_CTRL0D_FFA3 0xA3
#define MCU_PIN_SHARE_CTRL0E_FFA4 0xA4
#define MCU_FFA6    					 0xA6

#define MCU_PORT_READ_CTRL_FFC0 0xC0
#define MCU_PORT52_PIN_REG_FFC1 0xC1
#define MCU_PORT53_PIN_REG_FFC2 0xC2
#define MCU_PORT54_PIN_REG_FFC3 0xC3
#define MCU_PORT55_PIN_REG_FFC4 0xC4//eric 20070515 IrDA
#define MCU_PORT56_PIN_REG_FFC5 0xC5//eric 20070515 power key
#define MCU_PORT57_PIN_REG_FFC6 0xC6
#define MCU_PORT60_PIN_REG_FFC7 0xC7//eric 20070515 AMP_STB_A
#define MCU_PORT61_PIN_REG_FFC8 0xC8//eric 20070515 PANEL_ON
#define MCU_PORT62_PIN_REG_FFC9 0xC9//eric 20070515 un-use pin
#define MCU_PORT63_PIN_REG_FFCA 0xCA//eric 20070515 Write_Protect
#define MCU_PORT64_PIN_REG_FFCB 0xCB
#define MCU_PORT65_PIN_REG_FFCC 0xCC
#define MCU_PORT66_PIN_REG_FFCD 0xCD
#define MCU_PORT67_PIN_REG_FFCE 0xCE
#define MCU_PORT70_PIN_REG_FFCF 0xCF
#define MCU_PORT71_PIN_REG_FFD0 0xD0
#define MCU_PORT72_PIN_REG_FFD1 0xD1
#define MCU_PORT73_PIN_REG_FFD2 0xD2
#define MCU_PORT74_PIN_REG_FFD3 0xD3
#define MCU_PORT75_PIN_REG_FFD4 0xD4
#define MCU_PORT76_PIN_REG_FFD5 0xD5
#define MCU_PORT80_PIN_REG_FFD6 0xD6//eric 20070531
#define MCU_PORT81_PIN_REG_FFD7 0xD7
#define MCU_PORT90_PIN_REG_FFD8 0xD8
#define MCU_PORT91_PIN_REG_FFD9 0xD9
#define MCU_PORT92_PIN_REG_FFDA 0xDA
#define MCU_PORT93_PIN_REG_FFDB 0xDB
#define MCU_PORT94_PIN_REG_FFDC 0xDC


#define MCU_WATCHDOG_TIMER_FFEA 0xEA
#define MCU_CTRL_FFED 0xED
#define MCU_CLOCK_CTRL_FFEE 0xEE

#define MCU_SCA_INF_CTRL_FFF3 0xF3
#define MCU_SCA_INF_ADDR_FFF4 0xF4
#define MCU_SCA_INF_DATA_FFF5 0xF5

#define MCU_BANK_SWITCH_CTRL_FFFC 0xFC
#define MCU_BANK_START_FFFD 0xFD
#define MCU_BANK_SEL_FFFE 0xFE

//eric 20070613 mcu
#if(_FAST_READ == _ON)
#define MCU_FAST_READ_OP_CODE_FF6B 0x6B
#define MCU_READ_INSTRUCTION_FF6C 0x6C
#define MCU_CEN_CTRL_FF76 0x76
#endif


#if(_KEY_SCAN_TYPE == _KEY_SCAN_AD)
#define MCU_ADC_ACONTROL_FF08			 0x08
#define MCU_ADC_A0_CONVERT_RESULT_FF09	 0x09
#define MCU_ADC_A1_CONVERT_RESULT_FF0A	 0x0A
#define MCU_ADC_A2_CONVERT_RESULT_FF0B	 0x0B
#define MCU_ADC_A3_CONVERT_RESULT_FF0C	 0x0C
#define MCU_ADC_A4_CONVERT_RESULT_FF0D	 0x0D
#endif

//-----------Irda-----20070625-----------------------
//=======================================
#if(1)// _IR_HANDLER_MODE==_HW_MODE)

#define MCU_IR_CTRL1_FF80 0x80
#define MCU_IR_DEBOUNCE_FF81 0x81
#define MCU_IR_BURST_LENGTH_FF82 0x82
#define MCU_IR_SILENCE_LENGTH_FF83 0x83
#define MCU_IR_REPEAT_LENGTH_FF84 0x84
#define MCU_IR_MOD_LENGTH_FF85 0x85
#define MCU_IR_DATA0_LENGTH_FF86 0x86
#define MCU_IR_DATA1_LENGTH_FF87 0x87
#define MCU_IR_CTRL2_FF88 0x88
#define MCU_IR_STATUS_FF89 0x89
#define MCU_IR_DATA0_FF8A 0x8A
#define MCU_IR_DATA1_FF8B 0x8B
#define MCU_IR_DATA2_FF8C 0x8C
#define MCU_IR_DATA3_FF8D 0x8D
#define MCU_IR_DATA4_FF8E 0x8E
#define MCU_IR_DATA5_FF8F 0x8F

#define MCU_IR_ONE_CMD_TIME_FF90 0x90
#define MCU_IR_IDLE_TIME_FF91 0x91
#define MCU_IR_CTRL3_FF92 0x92
#define MCU_IR_INTRQ_FF93 0x93


#ifdef __MCU__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------



#if(_MCU_TYPE == _REALTEK_RTD3580D_EMCU)


//sfr P4 = 0xA5;

#if(_HDMI_EDID==_ON)

    #if(_HDMI_DDC_CHANNEL_SELECT==_DDC2)
    BYTE xdata MCU_DDCRAM_HDMI[256] ;//        _at_ 0xFD80;
    #elif (_HDMI_DDC_CHANNEL_SELECT==_DDC3)
    BYTE xdata MCU_DDCRAM_HDMI[256] ;//        _at_ 0xFE00;
    #endif

#endif

#if(_DVI_EDID==_ON)

    #if(_DVI_DDC_CHANNEL_SELECT==_DDC2)
    BYTE xdata MCU_DDCRAM_DVI[128] ;//        _at_ 0xFD80;
    #elif (_DVI_DDC_CHANNEL_SELECT==_DDC3)
    BYTE xdata MCU_DDCRAM_DVI[128] ;//        _at_ 0xFE80;
    #endif

#endif

#if(_VGA_EDID == _ON)
    #if( (_HDMI_EDID==_ON) || (_DVI_EDID==_ON) )
        #if( ((_HDMI_DDC_CHANNEL_SELECT==_DDC2) && (_HDMI_EDID==_ON)) || ((_DVI_DDC_CHANNEL_SELECT==_DDC2) && (_DVI_EDID==_ON)) )
        BYTE xdata MCU_DDCRAM_VGA[128] ;//    _at_ 0xFD00;
        #else
        BYTE xdata MCU_DDCRAM_VGA[128] ;//    _at_ 0xFD80;
        #endif
    #else
    BYTE xdata MCU_DDCRAM_VGA[128] ;//        _at_ 0xFD80;
    #endif
#endif





#endif

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CMcuInitial(void);

//eric 20070613 mcu
#if(_FAST_READ == _ON)
void CMCUFlashClkDiv(BYTE clkdiv);
void CMCUClkDiv(BYTE clkdiv);
void CMCUSetFlashClk(void);
#endif

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


#if(_MCU_TYPE == _REALTEK_RTD3580D_EMCU)


//BYTE xdata MCU_DDCRAM_VGA[128]        _at_ 0xFD00;
//BYTE xdata MCU_DDCRAM_DVI[128]        _at_ 0xFD80;
//BYTE xdata MCU_DDCRAM_HDMI[256]  		_at_ 0xFE00;

#endif


//extern BYTE xdata MCU_DDCRAM_VGA[128];
//extern BYTE xdata MCU_DDCRAM_DVI[128];
//extern BYTE xdata MCU_DDCRAM_HDMI[256];

// extern BYTE xdata MCU_IRQ_STATUS_FF00;
// extern BYTE xdata MCU_IRQ_PRIORITY_FF01;
// //extern BYTE xdata MCU_PORT6_OE_FF04;

// extern BYTE xdata MCU_THRESHOLD_VALUE_FF0F;//new add

// extern BYTE xdata MCU_VGA_DDC_ENA_FF1B;
// extern BYTE xdata MCU_DVI_DDC_ENA_FF1E;
// extern BYTE xdata MCU_DDCRAM_PART_FF21;

// extern BYTE xdata MCU_I2C_SET_SLAVE_FF23;
// extern BYTE xdata MCU_I2C_SUB_IN_FF24;
// extern BYTE xdata MCU_I2C_DATA_IN_FF25;
// extern BYTE xdata MCU_I2C_DATA_OUT_FF26;
// extern BYTE xdata MCU_I2C_STATUS_FF27;
// extern BYTE xdata MCU_I2C_IRQ_CTRL_FF28;
// extern BYTE xdata MCU_I2C_STATUS2_FF29;
// extern BYTE xdata MCU_I2C_IRQ_CTRL2_FF2A;
// extern BYTE xdata MCU_I2C_CHANNEL_CTRL_FF2B;
// extern BYTE xdata MCU_HDMI_DDC_ENA_FF2C;

// extern BYTE xdata MCU_PWM_CK_SEL_FF3A;
// extern BYTE xdata MCU_PWM03_M_FF3B;
// extern BYTE xdata MCU_PWM45_M_FF3C;

// extern BYTE xdata MCU_PWM01_N_MSB_FF3D;
// extern BYTE xdata MCU_PWM0_N_LSB_FF3E;
// extern BYTE xdata MCU_PWM1_N_LSB_FF3F;

// extern BYTE xdata MCU_PWM23_N_MSB_FF40;
// extern BYTE xdata MCU_PWM2_N_LSB_FF41;
// extern BYTE xdata MCU_PWM3_N_LSB_FF42;

// extern BYTE xdata MCU_PWM45_N_MSB_FF43;
// extern BYTE xdata MCU_PWM4_N_LSB_FF44;
// extern BYTE xdata MCU_PWM5_N_LSB_FF45;

// extern BYTE xdata MCU_PWML_FF46;
// extern BYTE xdata MCU_PWM_VS_CTRL_FF47;
// extern BYTE xdata MCU_PWM_EN_FF48;

// extern BYTE xdata MCU_PWM_CK_FF49;

// extern BYTE xdata MCU_PWM0H_DUT_FF4A;
// extern BYTE xdata MCU_PWM1H_DUT_FF4B;
// extern BYTE xdata MCU_PWM01L_DUT_FF4C;

// extern BYTE xdata MCU_PWM2H_DUT_FF4D;
// extern BYTE xdata MCU_PWM3H_DUT_FF4E;
// extern BYTE xdata MCU_PWM23L_DUT_FF4F;

// extern BYTE xdata MCU_PWM4H_DUT_FF50;
// extern BYTE xdata MCU_PWM5H_DUT_FF51;
// extern BYTE xdata MCU_PWM45L_DUT_FF52;

// extern BYTE xdata MCU_COMMON_INST_EN_FF60;
// extern BYTE xdata MCU_COMMON_OP_CODE_FF61;
// //extern BYTE xdata MCU_WREN_OP_CODE_FF62;
// //extern BYTE xdata MCU_EWSR_OP_CODE_FF63;
// extern BYTE xdata MCU_FLASH_PROG_ISP0_FF64;
// extern BYTE xdata MCU_FLASH_PROG_ISP1_FF65;
// extern BYTE xdata MCU_FLASH_PROG_ISP2_FF66;
// extern BYTE xdata MCU_COMMON_INST_RD_PT0_FF67;
// extern BYTE xdata MCU_COMMON_INST_RD_PT1_FF68;
// extern BYTE xdata MCU_COMMON_INST_RD_PT2_FF69;

// //extern BYTE xdata MCU_READ_OP_CODE_FF6A;
// //extern BYTE xdata MCU_PROG_OP_CODE_FF6D;
// extern BYTE xdata MCU_PROG_INST_FF6F;
// //extern BYTE xdata MCU_PROG_DATA_PORT_FF70;
// extern BYTE xdata MCU_PROG_LEN_FF71;
// //extern BYTE xdata MCU_CRC_END_ADDR0_FF72;
// //extern BYTE xdata MCU_CRC_END_ADDR1_FF73;
// //extern BYTE xdata MCU_CRC_END_ADDR2_FF74;

// extern BYTE xdata MCU_PIN_SHARE_CTRL00_FF96;
// extern BYTE xdata MCU_PIN_SHARE_CTRL01_FF97;
// extern BYTE xdata MCU_PIN_SHARE_CTRL02_FF98;
// extern BYTE xdata MCU_PIN_SHARE_CTRL03_FF99;
// extern BYTE xdata MCU_PIN_SHARE_CTRL04_FF9A;
// extern BYTE xdata MCU_PIN_SHARE_CTRL05_FF9B;
// extern BYTE xdata MCU_PIN_SHARE_CTRL06_FF9C;
// extern BYTE xdata MCU_PIN_SHARE_CTRL07_FF9D;
// extern BYTE xdata MCU_PIN_SHARE_CTRL08_FF9E;
// extern BYTE xdata MCU_PIN_SHARE_CTRL09_FF9F;
// extern BYTE xdata MCU_PIN_SHARE_CTRL0A_FFA0;
// extern BYTE xdata MCU_PIN_SHARE_CTRL0B_FFA1;
// extern BYTE xdata MCU_PIN_SHARE_CTRL0C_FFA2;
// extern BYTE xdata MCU_PIN_SHARE_CTRL0D_FFA3;
// extern BYTE xdata MCU_PIN_SHARE_CTRL0E_FFA4;
// extern BYTE xdata MCU_FFA6;


// extern BYTE xdata MCU_PORT_READ_CTRL_FFC0;
// extern BYTE xdata MCU_PORT52_PIN_REG_FFC1;
// extern BYTE xdata MCU_PORT53_PIN_REG_FFC2;
// extern BYTE xdata MCU_PORT54_PIN_REG_FFC3;
// extern BYTE xdata MCU_PORT55_PIN_REG_FFC4;
// extern BYTE xdata MCU_PORT56_PIN_REG_FFC5;
// extern BYTE xdata MCU_PORT57_PIN_REG_FFC6;
// extern BYTE xdata MCU_PORT60_PIN_REG_FFC7;
// extern BYTE xdata MCU_PORT61_PIN_REG_FFC8;
// extern BYTE xdata MCU_PORT62_PIN_REG_FFC9;
// extern BYTE xdata MCU_PORT63_PIN_REG_FFCA;
// extern BYTE xdata MCU_PORT64_PIN_REG_FFCB;
// extern BYTE xdata MCU_PORT65_PIN_REG_FFCC;
// extern BYTE xdata MCU_PORT66_PIN_REG_FFCD;
// extern BYTE xdata MCU_PORT67_PIN_REG_FFCE;
// extern BYTE xdata MCU_PORT70_PIN_REG_FFCF;
// extern BYTE xdata MCU_PORT71_PIN_REG_FFD0;
// extern BYTE xdata MCU_PORT72_PIN_REG_FFD1;
// extern BYTE xdata MCU_PORT73_PIN_REG_FFD2;
// extern BYTE xdata MCU_PORT74_PIN_REG_FFD3;
// extern BYTE xdata MCU_PORT75_PIN_REG_FFD4;
// extern BYTE xdata MCU_PORT76_PIN_REG_FFD5;
// extern BYTE xdata MCU_PORT80_PIN_REG_FFD6;
// extern BYTE xdata MCU_PORT81_PIN_REG_FFD7;
// extern BYTE xdata MCU_PORT90_PIN_REG_FFD8;
// extern BYTE xdata MCU_PORT91_PIN_REG_FFD9;
// extern BYTE xdata MCU_PORT92_PIN_REG_FFDA;
// extern BYTE xdata MCU_PORT93_PIN_REG_FFDB;
// extern BYTE xdata MCU_PORT94_PIN_REG_FFDC;

// extern BYTE xdata MCU_WATCHDOG_TIMER_FFEA;
// extern BYTE xdata MCU_CTRL_FFED;
// extern BYTE xdata MCU_CLOCK_CTRL_FFEE;

// extern BYTE xdata MCU_SCA_INF_CTRL_FFF3;
// extern BYTE xdata MCU_SCA_INF_ADDR_FFF4;
// extern BYTE xdata MCU_SCA_INF_DATA_FFF5;

// extern BYTE xdata MCU_BANK_SWITCH_CTRL_FFFC;
// extern BYTE xdata MCU_BANK_START_FFFD;
// extern BYTE xdata MCU_BANK_SEL_FFFE;

// //eric 20070613 mcu
// #if(_FAST_READ == _ON)
// extern BYTE xdata MCU_FAST_READ_OP_CODE_FF6B;
// extern BYTE xdata MCU_READ_INSTRUCTION_FF6C;
// extern BYTE xdata MCU_CEN_CTRL_FF76;
// #endif

// //-----------Irda-----20070625-----------------------
// //=======================================
// #if(1)//_IR_HANDLER_MODE==_HW_MODE)
// extern BYTE xdata MCU_IR_CTRL1_FF80;
// extern BYTE xdata MCU_IR_DEBOUNCE_FF81;
// extern BYTE xdata MCU_IR_BURST_LENGTH_FF82;
// extern BYTE xdata MCU_IR_SILENCE_LENGTH_FF83;
// extern BYTE xdata MCU_IR_REPEAT_LENGTH_FF84;
// extern BYTE xdata MCU_IR_MOD_LENGTH_FF85;
// extern BYTE xdata MCU_IR_DATA0_LENGTH_FF86;
// extern BYTE xdata MCU_IR_DATA1_LENGTH_FF87;
// extern BYTE xdata MCU_IR_CTRL2_FF88;
// extern BYTE xdata MCU_IR_STATUS_FF89;
// extern BYTE xdata MCU_IR_DATA0_FF8A;
// extern BYTE xdata MCU_IR_DATA1_FF8B;
// extern BYTE xdata MCU_IR_DATA2_FF8C;
// extern BYTE xdata MCU_IR_DATA3_FF8D;
// extern BYTE xdata MCU_IR_DATA4_FF8E;
// extern BYTE xdata MCU_IR_DATA5_FF8F;

// extern BYTE xdata MCU_IR_ONE_CMD_TIME_FF90;
// extern BYTE xdata MCU_IR_IDLE_TIME_FF91;
// extern BYTE xdata MCU_IR_CTRL3_FF92;
// extern BYTE xdata MCU_IR_INTRQ_FF93;
// #endif


// #if(_KEY_SCAN_TYPE == _KEY_SCAN_AD)
// extern BYTE xdata MCU_ADC_ACONTROL_FF08;
// extern BYTE xdata MCU_ADC_A0_CONVERT_RESULT_FF09;
// extern BYTE xdata MCU_ADC_A1_CONVERT_RESULT_FF0A;
// extern BYTE xdata MCU_ADC_A2_CONVERT_RESULT_FF0B;
// extern BYTE xdata MCU_ADC_A3_CONVERT_RESULT_FF0C;
// extern BYTE xdata MCU_ADC_A4_CONVERT_RESULT_FF0D;
// #endif

#if(_HDMI_EDID==_ON)

    #if(_HDMI_DDC_CHANNEL_SELECT==_DDC2)
    extern BYTE xdata MCU_DDCRAM_HDMI[256];
    #elif (_HDMI_DDC_CHANNEL_SELECT==_DDC3)
    extern BYTE xdata MCU_DDCRAM_HDMI[256];
    #endif

#endif

#if(_DVI_EDID==_ON)

    #if(_DVI_DDC_CHANNEL_SELECT==_DDC2)
    extern BYTE xdata MCU_DDCRAM_DVI[256];
    #elif (_DVI_DDC_CHANNEL_SELECT==_DDC3)
    extern BYTE xdata MCU_DDCRAM_DVI[256];
    #endif

#endif

#if(_VGA_EDID == _ON)
    #if(_HDMI_EDID==_ON || _DVI_EDID==_ON)
        #if(((_HDMI_DDC_CHANNEL_SELECT==_DDC2) && (_HDMI_EDID==_ON)) || ((_DVI_DDC_CHANNEL_SELECT==_DDC2) && (_DVI_EDID==_ON)))
        extern BYTE xdata MCU_DDCRAM_VGA[128];
        #else
        extern BYTE xdata MCU_DDCRAM_VGA[128];
        #endif
    #else
    extern BYTE xdata MCU_DDCRAM_VGA[128];
    #endif
#endif

#endif  // End of #if(_MCU_TYPE == _REALTEK_RTD3580D_EMCU)

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CMcuInitial(void);

#if(_FAST_READ == _ON)
extern void CMCUFlashClkDiv(BYTE clkdiv);
extern void CMCUClkDiv(BYTE clkdiv);
extern void CMCUSetFlashClk(void);
#endif

#endif


//----------------------------------------------------------------------------------------------------
