/*=============================================
  * Copyright (c)      Realtek Semiconductor Corporation, 2005
  * All rights reserved.
  * ============================================ */

/*================= File Description ================= */
/**
 * @file
 * 	This file is for global structure's declaration.
 *
 * @author 	$Author: Dgoetz $
 * @date 	$Date: 2/12/15 11:01a $
 * @version 	$Revision: 2 $
 * @ingroup 	global
 */

/**
* @addtogroup global
* @{
*/

#ifndef  _GLOBAL_H
#define  _GLOBAL_H
/*===================== Module Dependency  ================== */

/*========================== Types ========================== */

/*======================== Definitions ====================== */
//--------------------------------------------------
// Data Type Redefine
//--------------------------------------------------
typedef unsigned char bit;
typedef unsigned char BYTE;
typedef unsigned char UINT8;
typedef char SBYTE;
typedef char INT8;
typedef unsigned int  WORD;
typedef unsigned int UINT16;
typedef	int  SWORD;
typedef int INT16;
typedef unsigned long DWORD;
typedef unsigned long UINT32;
typedef long SDWORD;
typedef long INT32;
typedef bit BOOL;
typedef bit BIT;

//--------------------------------------------------
// Definitions of Page
//--------------------------------------------------
#define _PAGE0                          0x00
#define _PAGE1                          0x01
#define _PAGE2                          0x02
#define _PAGE3                          0x03
#define _PAGE4                          0x04
#define _PAGE5                          0x05
#define _PAGE6                          0x06
#define _PAGE7                          0x07
//
#define _PAGE8                          0x08
#define _PAGE9                          0x09
#define _PAGEA                          0x0A
#define _PAGEB                          0x0B
#define _PAGEC                          0x0C
#define _PAGED                          0x0D
#define _PAGEE                          0x0E
#define _PAGEF                          0x0F

//--------------------------------------------------
// Definations of Physical Boolean
//--------------------------------------------------
#define _LOCK        						1
#define _UNLOCK              				0
#define _TRUE                           	1
#define _FALSE                          	0
#define _HIGH                           	1
#define _LOW                            	0
#define _ENABLE                         	1
#define _DISABLE                        	0
#define _READ                           	1
#define _WRITE                          	0
#define _ON                             	1
#define _OFF                            	0
#define _SUCCESS                        	1
#define _FAIL                           	0
#define _STABLE                         	1
#define _UNSTABLE                       	0
#define _POSITIVE                       	1
#define _NEGATIVE                       	0
#define NULL								0

#define _NEWMODE                        	1
#define _OLDMODE                        	0

#define _NON_LOOP							0
#define _LOOP								_BIT1

#define _DEC								0
#define _INC								1

#define _PREV								0
#define _NEXT								1

#define _MENU_ADJ_DEC						0
#define _MENU_ADJ_INC						1
#define _MENU_RUN							2
#define _SET_MUTE							3


//--------------------------------------------------
// Definitions of Bits
//--------------------------------------------------
#define _BIT0                           0x0001
#define _BIT1                           0x0002
#define _BIT2                           0x0004
#define _BIT3                           0x0008
#define _BIT4                           0x0010
#define _BIT5                           0x0020
#define _BIT6                           0x0040
#define _BIT7                           0x0080
#define _BIT8                           0x0100
#define _BIT9                           0x0200
#define _BIT10                          0x0400
#define _BIT11                          0x0800
#define _BIT12                          0x1000
#define _BIT13                          0x2000
#define _BIT14                          0x4000
#define _BIT15                          0x8000


//--------------------------------------------------
// Definitions for Panel Settings
//--------------------------------------------------
// PanelType.PanelStyle Define's

// BIT 0 ~ 2
#define _PANEL_TTL                     	0
#define _PANEL_HZ                       1
#define _PANEL_LVDS                   	2
#define _PANEL_RSDS                   	3

#define _AUTOCALC_PIXCLK 				_BIT2

#define _LVDS_MAP1						_BIT3   			//LVDS Bit-Mapping Table 1
#define _LVDS_MAP2						0x00   			    //LVDS Bit-Mapping Table 2

#define _DISP_24_BIT                    0x00
#define _DISP_18_BIT                    _BIT4

#define _RSDS_GC_SWAP                   _BIT7
#define _RSDS_HL_SWAP                   _BIT6
#define _RSDS_PN_SWAP                   _BIT5

#define GET_PNL_OUTPUT_BUS()			(Panel[ucPanelSelect]->PanelStyle & 0x03)
#define GET_AUTOCALC_PIXCLK()			(Panel[ucPanelSelect]->PanelStyle & _BIT2)
#define GET_LVDS_MAP()					(Panel[ucPanelSelect]->PanelStyle & _BIT3)
#define GET_18BIT_EN()					(Panel[ucPanelSelect]->PanelStyle & _BIT4)

//--------------------------------------------------
// Definitions for Display Single/Double Port, Even/Odd Swap,
// Red/Blue Swap, MSB/LSB Swap, 24/18 Bit, Green/Clock Swap,
// High/Low Swap and PN Swap
//--------------------------------------------------
#define _DHS_MASK							_BIT7
#define _DISP_EO_SWAP                   	_BIT6
#define _DISP_RB_SWAP                   	_BIT5
#define _DISP_ML_SWAP                   	_BIT4

#define _DISP_SINGLE_PORT               	0x00
#define _DISP_DOUBLE_PORT               	_BIT3

#define _DVS_INVERT                     	_BIT2
#define _DHS_INVERT                     	_BIT1
#define _DEN_INVERT                     	_BIT0

#define GET_DOUBLE_PORT_EN()                (Panel[ucPanelSelect]->PanelConfig & _BIT3)

//--------------------------------------------------
// Definitions of Input Source Type
//--------------------------------------------------
#define _SOURCE_VGA                     0
#define _SOURCE_DVI                     1
#define _SOURCE_VIDEO_AV                2
#define _SOURCE_VIDEO_SV                3
#define _SOURCE_VIDEO_YUV               4
#define _SOURCE_VIDEO_TV                5
#define _SOURCE_VIDEO_SCART             6
#define _SOURCE_HDMI                    7
#define _SOURCE_YPBPR                   8
#define _SOURCE_VIDEO8                  9
#define _SOURCE_NONE                    10

//--------------------------------------------------
// Definitions of ModeHandler State
//--------------------------------------------------
#define _PWOFF_STATE                    	0
#define _INITIAL_STATE                  	1
#define _SEARCH_STATE                   	2
#define _ACTIVE_STATE                   	3
#define _NOSUPPORT_STATE                	4
#define _NOSIGNAL_STATE                 	5
#define _SLEEP_STATE                    	6
//#define _PROCESS_STATE              		7
#define _SOURCE_CHANGE_STATE         		8
#define _DTV_SCAN_STATE                    	9
#define _DTV_POWER_ON_STATE           		10

//--------------------------------------------------
// Definitions of Hsync Type Detection Auto Run Result
//--------------------------------------------------
#define _NO_SIGNAL                      0
#define _NOT_SUPPORT                    1
#define _YPBPR_SYNC                     2
#define _SERRATION_CS                   3
#define _XOR_OR_TYPE_CS_WITH_EQR        4
#define _XOR_OR_TYPE_CS_WITHOUT_EQR     5
#define _SEPARATE_HSYNC                 6
#define _HSYNC_WITHOUT_VS               7

//--------------------------------------------------
// Definitions of Input Sync Type State
//--------------------------------------------------
#define _NO_SYNC_STATE              		0
#define _SS_STATE                       	1
#define _CS_STATE                       	2
#define _SOG_STATE                      	3
#define _SOY_STATE                      	4
#define _DSS_STATE                      	5
#define _VIDEO8_STATE                		6

//--------------------------------------------------
// Definitions of Mode Search Type
//--------------------------------------------------
#define _PRESET_MODE_TYPE               	0
#define _USER_MODE_TYPE                 	1

//--------------------------------------------------
// Definitions of Waiting Events
//--------------------------------------------------
#define _EVENT_IVS                      	0x01
#define _EVENT_IEN_START                	0x02
#define _EVENT_IEN_STOP                 	0x04
#define _EVENT_DVS                      	0x08
#define _EVENT_DEN_START                	0x10
#define _EVENT_DEN_STOP                 	0x20
#define _EVENT_UNDERFLOW                	0x40
#define _EVENT_OVERFLOW                 	0x80

//--------------------------------------------------
// Definations of Scaler Write/Read Type
//--------------------------------------------------
#define _NON_AUTOINC                  		1
#define _AUTOINC                        	0
#define _BURST                          	2
#define _END                            	0

//--------------------------------------------------
// Definations of Load OSD Font Table Type
//--------------------------------------------------
#define _NORMAL_FONT                    	0x00
#define _COMPRESS_FONT                  	0x01

//--------------------------------------------------
// Definations of Red/Green/Blue
//--------------------------------------------------
#define _RED                            0
#define _GREEN                          1
#define _BLUE                           2
#define USER_RED                      	3
#define USER_GREEN                  	4
#define USER_BLUE                     	5

#define _PR                            	0
#define _SY                          	1
#define _PB                           	2

//--------------------------------------------------
// Definations of DDC Channel
//--------------------------------------------------
#define _DDC2                           0
#define _DDC3                           _BIT1

//--------------------------------------------------
// Definations of Scaling
//--------------------------------------------------
#define _SCALE_DOWN                 	0
#define _SCALE_UP                       1

//--------------------------------------------------
// Definitions of Display Delay
//--------------------------------------------------
#define _CAPTURE_HDELAY                 	3
#define _PROGRAM_HDELAY                 	10
#define _PROGRAM_VDELAY                 	2
#define _MEASURE_HDEALY                 	7

//--------------------------------------------------
// Signal Mode
//--------------------------------------------------
#define _SIG_MODE_MAX				4
#define _SIG_MODE_NTSC            	1//0   //for tv system //yf_zhang 2007-6-18 12:30
#define _SIG_MODE_PAL				0//1
#define _SIG_MODE_PAL_DK            2
#define _SIG_MODE_SECAM             3

// Scaler Type
#define _RTD3580D					1

// Debug Tool
#define _NONE                                   0
#define _ISP_FOR_RTD3580D_EMCU                  1

// Video Input Selection
#define _VIDEO_8_IN                     		0
#define _VIDEO_16_IN                    		1

// MCU Type
#define _REALTEK_RTD3580D_EMCU		    		0

// Definations of RTD/MCU Crystal Frequency in KHz
#define _XTAL12000K                     		12000
#define _XTAL24576K                     		24576   // If using kingmice, please select this option
#define _XTAL24000K                     		24000
#define _XTAL40000K                     		40000
#define _XTAL27000K                     		27000
#define _XTAL24300K                     		24300

#define _HSYNC_ONLY                     		0
#define _HSYNC_WITH_SOG                 		1
#define _HSYNC_WITH_SOG_SOY         			2

// YPbPr Sync Source
#define _SOG0                         			0
#define _SOG1                              		1

// Set Last Line Finetune Method
#define _LAST_LINE_METHOD_NONE          		0
#define _LAST_LINE_METHOD_0             		1   // Formula: Tne DEN End to DEN Start Length must be (1280*N)
#define _LAST_LINE_METHOD_1             		2   // Formula: Tne DEN End to DEN Start Length must be (4096*N + 128)
#define _LAST_LINE_METHOD_2             		3   // Formula: Last line limit

// Audio PLL Lock Mode
#define _HARDWARE_TRACKING              		0
#define _N_CTS                          		1

// Set Adjusting Vertical Position Direction Method
#define _V_POSITION_METHOD_0            		0
#define _V_POSITION_METHOD_1            		1

// Definitions of MCU Clock Divider Number
#define _DIV_1                          		1
#define _DIV_2                          		2
#define _DIV_3                          		3
#define _DIV_4                          		4
#define _DIV_5                          		5
#define _DIV_6                          		6
#define _DIV_7                          		7
#define _DIV_8                          		8
#define _DIV_9                          		9

#define _M2PLL_CLK_MHZ                  		243
#define _FLASH_CLK_80MHZ                		(_M2PLL_CLK_MHZ/80)
#define _FLASH_CLK_60MHZ                		(_M2PLL_CLK_MHZ/60)
#define _FLASH_CLK_48MHZ                		(_M2PLL_CLK_MHZ/48)
#define _FLASH_CLK_34MHZ                		(_M2PLL_CLK_MHZ/34)
#define _FLASH_CLK_27MHZ                		(_M2PLL_CLK_MHZ/27)

//--------------------------------------------------
// Global Macros
//--------------------------------------------------
#define LOBYTE(w)                       		((BYTE)(w))
#define HIBYTE(w)                       		((BYTE)(((WORD)(w) >> 8) & 0x00FF))
#define SEC(x)                          		(100 * x)
#define SHL(x,y)			    	    		((x) << (y))
#define SHR(x,y)				        		((x) >> (y))
#define AND(n1,n2)  			        		((n1) & (n2))
#define OR(n1,n2)   			        		((n1) | (n2))

//--------------------------------------------------
//            Audio definitions
//--------------------------------------------------
#define _AUDIO_SC7313                0
#define _AUDIO_PWM                   1
#define _AUDIO_NJW1144               2

//--------------------------------------------------
//            PWM definitions
//--------------------------------------------------
#define _RTD_PWM0                    0
#define _RTD_PWM1                    1
#define _RTD_PWM2                    2
#define _RTD_PWM3                    3
#define _RTD_PWM4                    4
#define _RTD_PWM5                    5

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
#define _ANALOG_SOURCE_0               	0
#define _ANALOG_SOURCE_1               	1
#define _DIGISTAL_SOURCE_0              2
#define _DIGISTAL_SOURCE_1              3

#define _DE_ONLY_OFF                    0
#define _DE_ONLY_ON                     1

//--------------------------------------------------
// Definations of Input Port Types
//--------------------------------------------------
/*******************************************************************
Select V8 input path, please modify following define to change input path.
If you select SV port, we only support,  V0 with V1 or V1 with V2 or V2 with V3.
********************************************************************/
#define _NO_PORT                        		0
#define _DSUB_A0_PORT                   		1
#define _DSUB_A1_PORT                   		2
#define _DVI_PORT                       		3
#define _DVI_I_A0_PORT                  		4
#define _YPBPR_A0_PORT                  		8
#define _YPBPR_A1_PORT                  		9
#define _VIDEO_YCBCR_PORT               		10
#define _VIDEO_AV_SV_PORT1              		11
#define _VIDEO_SCART_PORT                		12
#define _HDMI_PORT                      		13
#define _DVI_D0_PORT                            14
#define _DVI_D1_PORT                            15
#define _HDMI_D0_PORT                           16
#define _HDMI_D1_PORT                           17

//--------------------------------------------------
// Definitions of AD KEY
//--------------------------------------------------
#define MCU_ADC0                                0
#define MCU_ADC1                                1
#define MCU_ADC2                                2
#define MCU_ADC3                                3
#define MCU_ADC4                                4
#define MCU_ADC_NONE                            255

/*=====================  Extern Variables =================== */
#ifdef _IR_C
    #define EXTERN
#else
    #define EXTERN   extern
#endif

#undef EXTERN

/*======================= Extern Functions ================== */




#ifdef __SDCC
#define code __code
#define data __data
#define idata __idata
#define xdata __xdata
#else
#define code
#define data
#define idata
#define xdata
#endif

#include <stdint.h>
void delayMS(uint32_t ms);
#define CTimerDelayXms(__t) delayMS(__t)

#endif
