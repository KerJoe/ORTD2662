# TMDS Receiver
## S2_TMDS_MEAS_SELECT
| Bits | Read/Write | Reset state | Comments |
| :--: | :--------: | :---------: | :------: |
| 0 | ??? | ??? | ??? |
| 1 | ??? | ??? | ??? |
| 2 | ??? | ??? | ??? |
| 3 | ??? | ??? | ??? |
| 4 | ??? | ??? | ??? |
| 5 | ??? | ??? | ??? |
| 6 | ??? | ??? | ??? |
| 7 | ??? | ??? | ??? |


#define S2_TMDS_MEAS_SELECT              		0xA1        // TMDS Measure Select
#define S2_TMDS_MEAS_RESULT0            		0xA2        // TMDS Measure Result0
#define S2_TMDS_MEAS_RESULT1            		0xA3        // TMDS Measure Result1
#define S2_TMDS_CONTROL                       	0xA4        // TMDS Control Register
#define S2_CRC_OUTPUT_BYTE              		0xA5        // CRC Output Byte2
#define S2_TMDS_OUTPUT_CONTROL              	0xA6        // TMDS Output Control Register
#define S2_POWER_ON_OFF_CONTROL          		0xA7        // TMDS Power On/Off Control Register
#define S2_ANALOG_COMMON_CONTROL0     			0xA8        // Analog Common Control Register 0
#define S2_ANALOG_COMMON_CONTROL1     			0xA9        // Analog Common Control Register 1
#define S2_ANALOG_BIAS_CONTROL             		0xAA        // Analog Bias Control Register
#define S2_ANALOG_COMMON_CONTROL2     			0xAB        // Analog Common Control Register 2
#define S2_Z0_CALIBRATION_CONTROL          		0xAC        // Z0 Calibration Control Register
#define S2_CLOCK_PLL_SETTING             		0xAD        // Clock PLL Setting
#define S2_RGB_PLL_SETTING                    	0xAE        // R/G/B PLL Setting
#define S2_WDT_CONTROL                   		0xAF        // Watch Dog Control Register
#define S2_CDR_CONTROL0                       	0xB0        // CDR Control Register 0
#define S2_CDR_CONTROL1                       	0xB1        // CDR Control Register 1
#define S2_CDR_CONTROL2                       	0xB2        // CDR Control Register 2
#define S2_UP_DOWN_ADJUSTING1        			0xB3        // Up/Down Adjusting 1
#define S2_ADAPTIVE_EQUALIZER1            		0xB4        // Adaptive Equalizer
#define S2_UP_DOWN_CONTROL0                   	0xB5        // Up/Down Control Register 0
#define S2_UP_DOWN_CONTROL1                   	0xB6        // Up/Down Control Register 1
#define S2_UP_DOWN_CONTROL2                   	0xB7        // Up/Down Control Register 2
#define S2_ADAPTIVE_EQUALIZER2         		    0xB8        // Adaptive Equalizer accumulative threshold (LPF1)//731301
#define S2_ADAPTIVE_EQUALIZER3           	    0xB9        // Adaptive Equalizer continuous threshold (LPF2)
#define S2_ADAPTIVE_EQUALIZER4                 	0xBA        // Adaptive Equalizer auto stop threshold

//--------------------------------------------------
// HDCP1.1(Port)
//--------------------------------------------------
#define S2_HDCP_CONTROL                       	0xC0        // HDCP Control Register
#define S2_DEVICE_KEY_ACCESS_PORT      		    0xC1        // Device Key Access Port
#define S2_HDCP_DATA_CONTROL		        	0xC2        // HDCP Port Control Register
#define S2_HDCP_ADDRESS                     	0xC3        // HDCP Address Port
#define S2_HDCP_PORT                        	0xC4        // HDCP Data Port