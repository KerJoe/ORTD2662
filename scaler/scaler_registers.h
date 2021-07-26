#pragma once

//--------------------------------------------------
// Global Event Flag
//--------------------------------------------------
#define S_ID_REGISTER                          	0x00        // ID Code Register
#define S_HOST_CONTROL                         	0x01        // Host Control Register
#define S_STATUS0                            	0x02        // Status0 Register
#define S_STATUS1                            	0x03        // Status1 Register
#define S_IRQ_CONTROL0                         	0x04        // IRQ Control Register0
#define S_HDMI_STATUS0                       	0x05        // HDMI Status0 Register
#define S_HDMI_STATUS1                       	0x06        // HDMI Status1 Register
#define S_NEW_STATUS0           	       		0x07        // NEW Added Status0 Register
#define S_NEW_STATUS1   			       		0x08        // NEW Added Status1 Registe
//Address: 0x09~0x0B Reserved

//--------------------------------------------------
// Scaler Watch Dog
//--------------------------------------------------
#define S_WDT_CONTROL0                    0x0C        // Watch Dog Control Register0
#define S_WDT_CONTROL1            		0x0D        // Watch Dog Control Register1
//Address: 0x0E~0x0F Reserved

//--------------------------------------------------
// Input Video Capture
//--------------------------------------------------
#define S_VGIP_CONTROL                         	0x10        // Video Graphic Input Port(VGIP) Control Register
#define S_VGIP_SIGINV                        	0x11        // Input Control Signal Inverted Register
#define S_VGIP_DELAY_CONTROL                   	0x12        // VGIP Delay Control Register
#define S_VGIP_ODD_CONTROL                     	0x13        // VGIP Odd Control Register

//--------------------------------------------------
// Input Frame Window
//-------------------------------------------------
#define S_IFW_HACT_STA_HI                     	0x14        // Input Horizontal Active Start HByte
#define S_IFW_HACT_STA_LO                     	0x15        // Input Horizontal Active Start LByte
#define S_IFW_HACT_LEN_HI                     	0x16        // Input Horizontal Active Width HByte
#define S_IFW_HACT_LEN_LO                     	0x17        // Input Horizontal Active Width LByte
#define S_IFW_VACT_STA_HI                     	0x18        // Input Vertical Active Start HByte
#define S_IFW_VACT_STA_LO                     	0x19        // Input Vertical Active Start LByte
#define S_IFW_VACT_LEN_HI                     	0x1A        // Input Vertical Active Length HByte
#define S_IFW_VACT_LEN_LO                     	0x1B        // Input Vertical Active Length LByte
#define S_IFW_VSYNC_DELAY                      	0x1C        // Internal Input Vertical Sync Delay Control Register
#define S_IFW_HSYNC_DELAY                      	0x1D        // Internal Input Horizontal Sync Delay Control Register
#define S_IFW_HV_DELAY                      	0x1E        // Input HS/VS Delay
#define S_IFW_HPORCH_NUM_HI          			0x1F        // Input Video Horizontal Porch HByte
#define S_IFW_HPORCH_NUM_LO                  	0x20        // Input Video Horizontal Porch LByte
//Address: 0x21 Reserved

//--------------------------------------------------
// Input Pattern Generator
//--------------------------------------------------
#define S_FIFO_FREQUENCY                     	0x22        // FIFO Frequency
#define S_FIFO_BIST_CONTROL                     0x23        // FIFO BIST Control Register
#define S_IPG_ADDRESS       		            0x24        // Input Pattern Generator Access Port Control
#define S_IPG_PORT               		        0x25        // Input Pattern Generator Data Port
//Address: 26~27 Reserved

//--------------------------------------------------
// Display Format
//--------------------------------------------------
#define S_VDISP_CONTROL                         0x28        // Video Display Control Register
#define S_VDISP_SIGINV                       	0x29        // Display Control Signal Inversion Register
#define S_VDISP_ADDRESS                		    0x2A        // Display Format Address Register
#define S_VDISP_PORT                         	0x2B        // Display Format Data Port
#define S_OUT_CRC_CONTROL                      	0x2C        // Output CRC Control Register
#define S_OUT_CRC_CHECKSUM                 		0x2D        // Output CRC Checksum
//Address: 2E~2F Reserved

//--------------------------------------------------
// FIFO Window
//--------------------------------------------------
#define S_FIFO_WIN_ADDRESS                     	0x30        // FIFO Window Address Port
#define S_FIFO_WIN_PORT                        	0x31        // FIFO Window Data Port

//--------------------------------------------------
// Scaling Up Function
//--------------------------------------------------
#define S_SCALE_CONTROL                        	0x32        // Scale Control Register
#define S_SCALE_FACTOR_ADDRESS                 	0x33        // Scale Up Factor Access Port
#define S_SCALE_FACTOR_PORT                    	0x34        // Scale Up Factor Data Port
#define S_FILTER_CONTROL                       	0x35        // Filter Control Register
#define S_FILTER_DATA                        	0x36        // User Defined Filter Access Port
//Address: 37~3F Reserved

//--------------------------------------------------
// Frame Sync Fine Tune
//--------------------------------------------------
#define S_IVS2DVSYNC_DELAY_LINES                	0x40        // IVS to DVS Delay Lines
#define S_FS_DELAY_CLK_ODD              		0x41        // Frame Sync Delay Fine Tuning ODD
#define S_FS_DELAY_CLK_EVEN              		0x42        // Frame Sync Delay Fine Tuning EVEN
#define S_FS_DELAY_FINE_TUNING           		0x43        // Frame Sync Delay Fine Tuning Control Register
#define S_LAST_LINE_HI                        	0x44        // Last Line HByte
#define S_LAST_LINE_LO                        	0x45        // Last Line LByte
//Address: 46 Reserved

//--------------------------------------------------
// Sync Processor(Port)
//--------------------------------------------------
#define S_SYNC_SELECT                        	0x47        // Sync Select Control Register
#define S_SYNC_INVERT                        	0x48        // Sync Invert Control Register
#define S_SYNC_CONTROL                         	0x49        // Sync Processor Control Register
#define S_STABLE_HIGH_PERIOD_HI            		0x4A        // Stable High Period HByte
#define S_STABLE_HIGH_PERIOD_LO            		0x4B        // Stable High Period LByte
#define S_VSYNC_COUNTER_LEVEL_HI     			0x4C        // Vertifcal Sync Counter Level HI
#define S_VSYNC_COUNTER_LEVEL_LO    			0x4D        // Vertical Sync Counter Level LO
#define S_HSYNC_TYPE_DETECTION_FLAG   			0x4E        // Hsync Type Detection Flag
#define S_STABLE_MEASURE                     	0x4F        // Stable Measure
#define S_STABLE_PERIOD_HI                    	0x50        // Stable Period HByte
#define S_STABLE_PERIOD_LO                    	0x51        // Stable Period LByte
#define S_MEAS_HSYNC_PERIOD_HI                	0x52        // HSync Period Measured Result HByte
#define S_MEAS_HSYNC_PERIOD_LO                  0x53        // HSync Period Measured Result LByte
#define S_MEAS_VSYNC_PERIOD_HI                  0x54        // VSync Period Measured Result HByte
#define S_MEAS_VSYNC_PERIOD_LO                  0x55        // VSync Period Measured Result LByte
#define S_MEAS_HSYNC_VSYNC_HIGH_PERIOD_HI   	0x56        // HSync and VSync High Period Measured Results HByte
#define S_MEAS_HSYNC_HIGH_PERIOD_LO          	0x57        // HSync High Period Measured Results LByte
#define S_MEAS_HSYNC_VSYNC_HIGH_PERIOD_SELECT  	0x58        // HSync and VSync High Period Measured Select
#define S_MEAS_ACT_REGION                 	    0x59        // Active Region Measured by Crystal Clock
#define S_SYNC_TEST_MISC                     	0x5A        // Sync Test MISC Register
//Address: 5B Reserved
#define S_SYNC_PROC_ADDRESS         			0x5C        // Sync Processor Access Port Address
#define S_SYNC_PROC_PORT                 		0x5D        // Sync Processor Access Port Data
//Address: 5E~5F Reserved

//--------------------------------------------------
// Hightlight Window
//--------------------------------------------------
#define S_HW_ADDRESS                         	0x60        // Highlight Window Control
#define S_HW_PORT                              	0x61        // Highlight Window Data Port

//--------------------------------------------------
// Color Processor Control(Port)
//--------------------------------------------------
#define S_COLOR_CONTROL                        	0x62        // Color Processor Control Register
#define S_SRGB_DATA                            	0x63        // sRGB Access Port
#define S_CB_ADDRESS                        	0x64        // Contrast/Brightness Access Port
#define S_CB_PORT                              	0x65        // Contrast/Brightness Data Port

//--------------------------------------------------
// Gamma Control
//--------------------------------------------------
#define S_GAMMA_DATA                         	0x66        // Gamma Access Port
#define S_GAMMA_CONTROL                        	0x67        // Gamma Control Register
#define S_GAMMA_BIST                         	0x68        // Gamma BIST Control Register


//--------------------------------------------------
// Dithering Control
//--------------------------------------------------
#define S_DITHER_DATA                      		0x69        // Dithering Table DATA ACCESS
#define S_DITHER_CONTROL                   		0x6A        // Dithering Control Register
//Address: 6B Reserved


//--------------------------------------------------
// Overlay/Color Palette/Background Color Control
//--------------------------------------------------
#define S_OVERLAY_CONTROL                      	0x6C        // Overlay Display Control Register
#define S_BG_COLOR_CONTROL                   	0x6D        // Background Color Control Register
#define S_OVERLAY_LUT_ADDRESS                  	0x6E        // Overlay Look Up Table (LUT) Address
#define S_COLOR_LUT_PORT                     	0x6F        // Color LUT Access Port

//--------------------------------------------------
// Image Auto Function
//--------------------------------------------------
#define S_HBOUNDARY_HI                       	0x70        // Horizontal Start/End Boundary HByte
#define S_HBOUNDARY_STA_LO                   	0x71        // Horizontal Start Boundary HByte
#define S_HBOUNDARY_END_LO                   	0x72        // Horizontal End Boundary HByte
#define S_VBOUNDARY_HI                       	0x73        // Vertical Start/End Boundary HByte
#define S_VBOUNDARY_STA_LO                   	0x74        // Vertical Start Boundary LByte
#define S_VBOUNDARY_END_LO                   	0x75        // Vertical End Boundary LByte
#define S_RED_NOISE_MARGIN                   	0x76        // Red Noise Margin Control Register
#define S_GRN_NOISE_MARGIN                   	0x77        // Green Noise Margin Control Register
#define S_BLU_NOISE_MARGIN                   	0x78        // Blue Noise Margin Control Register
#define S_DIFF_THRESHOLD                     	0x79        // Difference Threshold
#define S_AUTO_ADJ_CONTROL0                    	0x7A        // Auto Adjusting Control Register 0
#define S_AUTO_PHASE_CONTROL0           		0x7B        // Hardware Auto Phase Control Register 0
#define S_AUTO_PHASE_CONTROL1           		0x7C        // Hardware Auto Phase Control Register 1
#define S_AUTO_ADJ_CONTROL1                    	0x7D        // Auto Adjusting Control Register 1
#define S_V_STA_END_HI                        	0x7E        // Actuve Region Vertical Start/End HByte
#define S_V_STA_LO                          	0x7F        // Actuve Region Vertical Start LByte
#define S_V_END_LO                            	0x80        // Actuve Region Vertical End LByte
#define S_H_STA_END_HI                      	0x81        // Actuve Region Horizontal Start/End HByte
#define S_HSTA_LO                           	0x82        // Actuve Region Horizontal Start LByte
#define S_HEND_LO                            	0x83        // Actuve Region Horizontal End LByte
#define S_AUTO_PHASE_DATA3                 		0x84        // Auto Phase Result Register Byte 3
#define S_AUTO_PHASE_DATA2                     	0x85        // Auto Phase Result Register Byte 2
#define S_AUTO_PHASE_DATA1                     	0x86        // Auto Phase Result Register Byte 1
#define S_AUTO_PHASE_DATA0                     	0x87        // Auto Phase Result Register Byte 0
//Address: 88~8A Reserved

//--------------------------------------------------
// Embedded Timing Controller(Port)
//--------------------------------------------------
#define S_TCON_ADDRESS                       	0x8B        // TCON Address Port for Embedded TCON Access
#define S_TCON_PORT                          	0x8C        // TCON Data Port for Embedded TCON Access
//
#define S_LVDS_CONTROL0                        	0xA0        //
#define S_LVDS_CONTROL1                        	0xA1        //
#define S_LVDS_CONTROL2                        	0xA2        //
#define S_LVDS_CONTROL3                        	0xA3        //
#define S_LVDS_CONTROL4                        	0xA4        //
#define S_LVDS_CONTROL5                        	0xA5        //

//--------------------------------------------------
// Embedded OSD
//--------------------------------------------------
#define S_OSD_ADDRESS_HI                       	0x90        // OSD Address HI
#define S_OSD_ADDRESS_LO                       	0x91        // OSD Address LO
#define S_OSD_PORT                            	0x92        // OSD Data Port
#define S_OSD_SCRAMBLE                       	0x93        // OSD Scramble
#define S_OSD_TEST                           	0x94        // OSD Test
//Address: 95~97 Reserved

//--------------------------------------------------
// Digital Filter
//--------------------------------------------------
#define S_DIGITAL_FILTER_CONTROL           		0x98        // Digital Filter Control Register
#define S_DIGITAL_FILTER_DATA                	0x99        // Digital Filter Port

//--------------------------------------------------
// VBI
//--------------------------------------------------
#define S_VBI_ADDRESS                       	0x9A        // VBI Access Port
#define S_VBI_PORT                            	0x9B        // VBI Data Port
// TODO: Add full vbi

//--------------------------------------------------
// Video Color Space Conversion
//--------------------------------------------------
#define S_YUV_TO_RGB_CONTROL                    0x9C        // YUV to RGB Control Register
#define S_YUV_RGB_COEF_DATA                  	0x9D        // YUV to RGB Coefficient Data Port
//Address:9E~9F Reserved

//--------------------------------------------------
// Page Control Register
//--------------------------------------------------
#define S_PAGE_SELECT                         	0x9F        // Page Selector (CRA0~CRFF)

// TODO: Add addc

//--------------------------------------------------
// Dynamic Contrast Control(Port)
//--------------------------------------------------
#define S_DCC_CONTROL0                      	0xE4        // DCC Control Register0
#define S_DCC_CONTROL1                      	0xE5        // DCC Control Register1
#define S_DCC_ADDRESS               		    0xE6        // DCC Access Port
#define S_DCC_PORT                        	    0xE7        // DCC Data Port
//Address: E8~EF Reserved

//--------------------------------------------------
// CMDI(Port)
//--------------------------------------------------
#define S_CMDI_ADDRESS                     	    0xF0        // CMDI Access Port
#define S_CMDI_PORT                      	    0xF1        // CMDI Data Port

//--------------------------------------------------
// Cyclic Redundant Check(CRC)
//--------------------------------------------------
#define S_OUTPUT_CRC_CONTROL                   	0xF2        // Output CRC Control Register
#define S_OUTPUT_CRC_CHECKSUM                	0xF3        // Output CRC Checksum

//--------------------------------------------------
// DDC Special Function Access(DDC/CI)
//--------------------------------------------------
#define S_DDC_SET_SLAVE                     	0xF4        // DDC Set Slave Address
#define S_DDC_SUBADDRESS_IN                    	0xF5        // DDC Sub Address Received
#define S_DDC_DATA_IN                        	0xF6        // DDC Data Received
#define S_DDC_CONTROL                       	0xF7        // DDC Control Register
#define S_DDC_STATUS                        	0xF8        // DDC Status
#define S_DDC_IRQ_CONTROL                   	0xF9        // DDC IRQ Control Register

//--------------------------------------------------
// DDC Channel (ADC/DVI)
//--------------------------------------------------
#define S_DDC_ENABLE                         	0xFA        // DDC Channel Enable Control Register
#define S_DDC_INDEX                         	0xFB        // DDC SRAM R/W Index Register
#define S_DDC_DATA                            	0xFC        // DDC Channel Access Port
#define S_DDC_DVI_ENABLE                     	0xFD        // DDC DVI Channel Enable Control Register
#define S_DDC_DVI_INDEX                     	0xFE        // DDC DVI SRAM R/W Index Register
#define S_DDC_DVI_DATA                	    	0xFF        // DDC DVI Channel Access Port

///////////////////////////////////////////////////////////////////////////////
////////////////////////      Page 0: Embedded ADC     ////////////////////////
///////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Video ADC (Page0)
//--------------------------------------------------
#define S0_VADC_SOY_COMPAR                  	0xA0        // Video ADC SOY Comparator Select
#define S0_VADC_CONTROL                        	0xA1        // Video ADC Control Register
#define S0_VADC_CLOCK                         	0xA2        // Video ADC Clock Source
#define S0_VADC_OUTPUT_DELAY         			0xA3        // Video ADC Output Delay
//Address:A4 Reserved
#define S0_VADC_INPUT                      	    0xA5        // Video ADC Input BW
#define S0_VADC1_INPUT_PGA                		0xA6        // Video ADC1 Input PGA
#define S0_VADC0_INPUT_PGA                		0xA7        // Video ADC0 Input PGA
#define S0_VADC_CLAMP                          	0xA8        // Video ADC Clamp
#define S0_VADC_INRANGE                        	0xA9        // Video ADC Input Range
//Address:AA Reserved
#define S0_VADC1_SOY_IBIAS           			0xAB        // Video ADC1 SOY Bias Current
#define S0_VADC_IN_CH_IBIAS           			0xAC        // Video ADC Input Channel Bias Current
#define S0_VADC_POS_IN_SOY_RES     		    	0xAD        // Video ADC Posive Input SOY Restore Resistor
#define S0_VADC_CLAMP_POWER            		    0xAE        // Video ADC Clamp Power
#define S0_VADC_SWITCH                       	0xAF        // Video ADC/Video8 Switch

//--------------------------------------------------
// YPbPr ADC (Page0)
//--------------------------------------------------
#define S0_RED_GAIN                            	0xC0        // Video ADC Red Channel Gain Adjust
#define S0_GRN_GAIN                         	0xC1        // Video ADC Green Channel Gain Adjust
#define S0_BLU_GAIN                           	0xC2        // Video ADC Blue Channel Gain Adjust
#define S0_RED_OFFSET                     	 	0xC3        // Video ADC Red Channel Offset Adjust
#define S0_GRN_OFFSET                         	0xC4        // Video ADC Green Channel Offset Adjust
#define S0_BLU_OFFSET                          	0xC5        // Video ADC Blue Channel Offset Adjust
#define S0_VADC_POWER                      		0xC6        // Video ADC Power Control Register
#define S0_VADC_IBIAS0                        	0xC7        // Video ADC Bais Current Control Register0
#define S0_VADC_IBIAS1                        	0xC8        // Video ADC Bais Current Control Register1
#define S0_VADC_IBIAS2                        	0xC9        // Video ADC Bais Current Control Register2
#define S0_VADC_VBIAS0                       	0xCA        // Video ADC Bais Voltage Control Register0
#define S0_VADC_VBIAS1                       	0xCB        // Video ADC Bais Voltage Control Register1
#define S0_VADC_CLOCK_CONTROL                  	0xCC        // Video ADC Clock Control Register
#define S0_VADC_TEST_CONTROL                   	0xCD        // Video ADC Test Control Register
#define S0_VADC_RGB_CONTROL                    	0xCE        // Video ADC RGB Control Register
#define S0_VADC_RED_CONTROL                    	0xCF        // Video ADC Red Channel Control Register
#define S0_VADC_GREEN_CONTROL                  	0xD0        // Video ADC Green Channel Control Register
#define S0_VADC_BLUE_CONTROL                   	0xD1        // Video ADC Blue Channel Control Register
#define S0_VADC_SOG0_CONTROL                	0xD2        // Video ADC SOG0 Reference Control Register
#define S0_VADC_DCR_CONTROL                    	0xD3        // Video ADC DCR Reference Control Register
#define S0_VADC_CLAMP_CONTROL0              	0xD4        // Video ADC Clamp Control Register0
#define S0_VADC_CLAMP_CONTROL1              	0xD5        // Video ADC Clamp Control Register1
#define S0_VADC_SOG_CONTROL                    	0xD6        // Video ADC SOG Control Register
//Address: D7~E1 Reserved

//--------------------------------------------------
// Auto Black Level (Page0)
//--------------------------------------------------
#define S0_ABL_CONTROL1                       	0xE2        // Auto Black Level Control Register1
#define S0_ABL_CONTROL2                       	0xE3        // Auto Black Level Control Register2
#define S0_ABL_CONTROL3                       	0xE4        // Auto Black Level Control Register3
#define S0_ABL_CONTROL4                       	0xE5        // Auto Black Level Control Register4
#define S0_ABL_CONTROL5                       	0xE6        // Auto Black Level Control Register5
#define S0_ABL_CONTROL6                       	0xE7        // Auto Black Level Control Register6
#define S0_ABL_CONTROL7                       	0xE8        // Auto Black Level Control Register6
#define S0_ABL_RED_VALUE                      	0xE9        // Auto Black Level Value of Red Channel in Test Mode
#define S0_ABL_GRN_VALUE                      	0xEA        // Auto Black Level Value of Green Channel in Test Mode
#define S0_ABL_BLU_VALUE                      	0xEB        // Auto Black Level Value of Blue Channel in Test Mode
#define S0_ABL_RED_NOISE_VALUE                 	0xEC        // Auto Black Level Noise Value of Red Channel in Test Mode
#define S0_ABL_GRN_NOISE_VALUE                 	0xED        // Auto Black Level Noise Value of Green Channel in Test Mode
#define S0_ABL_BLU_NOISE_VALUE                 	0xEE        // Auto Black Level Noise Value of Blue Channel in Test Mode
//Address: EF ~ F2 Reserved

//--------------------------------------------------
// Low Voltage Reset (Page0)
//--------------------------------------------------
#define S0_POWER_ON_RESET                   	0xF3        // Negative Threshold Value For Power On Reset

//--------------------------------------------------
// Schmitt Trigger Control (Page0)
//--------------------------------------------------
#define S0_HSYNC_SCHMITT_TRIGGER_CONTROL      	0xF4        // Schmitt Trigger Control Register
//Address: P0-F5 ~ P0-FF Reserved



///////////////////////////////////////////////////////////////////////////////
/////////////////////////////     Page 1: PLL     /////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// DDS Setting For ADC PLL (Page1)
//--------------------------------------------------
#define S1_PLL_DIV_CONTROL                      0xA0        // PLL DIV Control Register
#define S1_ICODE_HI                             0xA1        // I Code MByte
#define S1_ICODE_LO                             0xA2        // I Code LByte
#define S1_PCODE                             	0xA3        // P Code
#define S1_PFD_CALIBRATED_RESULTS_HI          	0xA4        // PFD Calibrated Result HByte
#define S1_PFD_CALIBRATED_RESULTS_LI          	0xA5        // PFD Calibrated Result LByte
#define S1_PE_MEASURE_HI                       	0xA6        // Phase Error Measure HByte
#define S1_PE_MEASURE_LO                       	0xA7        // Phase Error Measure LByte
#define S1_PE_MAX_MEASURE_HI                   	0xA8        // Phase Error Max MEasure HByte
#define S1_PE_MAX_MEASURE_LO                   	0xA9        // Phase Error Max MEasure LByte
#define S1_FAST_PLL_CONTROL                     0xAA        // Fast PLL Control Register
#define S1_FAST_PLL_ISUM                       	0xAB        // Fast PLL I_SUM

//--------------------------------------------------
// ADC PLL (Page1)
//--------------------------------------------------
#define S1_PLL_M                           	    0xAC        // PLL M code
#define S1_PLL_N                           	    0xAD        // PLL N Code
#define S1_PLL_CURRENT                     	    0xAE        // PLL Current/Resistor Register
#define S1_PLL_WDT                         	    0xAF        // PLL Watch Dog Register
#define S1_PLL_MIX                         	    0xB0        // PLL Mix Register
#define S1_PLL_DIV_HI                      	    0xB1        // PLL DIV HByte
#define S1_PLL_DIV_LO                          	0xB2        // PLL DIV LByte
#define S1_PLL_PHASE_CONTROL0              	    0xB3        // PLL Phase Control Register0
#define S1_PLL_PHASE_CONTROL1              	    0xB4        // PLL Phase Control Register1
#define S1_PLL_PHASE_INTERPOLATION     		    0xB5        // PLL Phase Interpolation
#define S1_P_CODE_MAPPING_METHOD      		    0xB6        // P Code Mapping Method
#define S1_PE_TRACKING_METHOD              	    0xB7        // PE Tracking Method
#define S1_DDS_MIX1                       	    0xB8        // DDS Mix 1
#define S1_DDS_MIX2                       	    0xB9        // DDS Mix 2
#define S1_DDS_MIX3                       	    0xBA        // DDS Mix 3
#define S1_DDS_MIX4                       	    0xBB        // DDS Mix 4
#define S1_DDS_MIX5                       	    0xBC        // DDS Mix 5
#define S1_DDS_MIX6                       	    0xBD        // DDS Mix 6
#define S1_DDS_MIX7                       	    0xBE        // DDS Mix 7
//--------------------------------------------------
// DPLL (Page1)
//--------------------------------------------------
#define S1_DPLL_M                          	    0xBF        // DPLL M Divider
#define S1_DPLL_N                          	    0xC0        // DPLL N Divider
#define S1_DPLL_CURRENT                	 	    0xC1        // DPLL Current/Resistor Register

//--------------------------------------------------
// DCLK Spread Spectrum (Page1)
//--------------------------------------------------
#define S1_DPLL_WDT                       	    0xC2        // DPLL Watch Dog Register
#define S1_DPLL_OTHER                       	0xC3        // DPLL Other Register
#define S1_DCLK_FINE_TUNE_OFFSET_HI       	    0xC4        // Display Clock Fine Tune Offset HI
#define S1_DCLK_FINE_TUNE_OFFSET_LO       	    0xC5        // Display Clock Fine Tune Offset LO
#define S1_DCLK_SPREAD_SPECTRUM             	0xC6        // Display Clock Spread Spectrum
#define S1_EVEN_FIXED_LASTLINE_HI               0xC7        // Even Fixed Last Line HI
#define S1_EVEN_FIXED_LASTLINE_DVTOTAL_LO       0xC8        // Even Fixed Last Line DVTotal LO
#define S1_EVEN_FIXED_LASTLINE_LENGTH_LO        0xC9        // Even Fixed Last Line Length LO
#define S1_FIXED_LASTLINE_CONTROL       	    0xCA        // Fixed Last Line Control Register
#define S1_ODD_FIXED_LASTLINE_HI                0xCB        // Odd Fixed Last Line HI
#define S1_ODD_FIXED_LASTLINE_DVTOTAL_LO        0xCC        // Odd Fixed Last Line DVTotal LO
#define S1_ODD_FIXED_LASTLINE_LENGTH_LO         0xCD        // Odd Fixed Last Line Length LO
// TODO: Complete DCLK Spread Spectrum

//--------------------------------------------------
// Multiply PLL For Input Crystal (Page1)
//--------------------------------------------------
#define S1_M2PLL_CONTROL0                   	0xE0        // M2PLL Control Register0
#define S1_M2PLL_CONTROL1              	        0xE1        // M2PLL Control Register1
//#define S1_RESERVED                        	0xE2        // P1 Reserved E2
//#define S1_RESERVED                        	0xE3        // P1 Reserved E3
#define S1_M2PLL_POWER_DOWN             	    0xE4        // M2PLL Power Down
//Address: P1-E5 ~ P1-E9 Reserved
#define S1_PLL_CHARGE_PUMP_CURRENT_0        	0xEA        // PLL Charge Pump Current 0
#define S1_LOOP_FILTER_CAPACITOR                0xEB        // PLL Loop Filter Capacitor
#define S1_PLL_CHARGE_PUMP_CURRENT_2        	0xEC        // PLL Charge Pump Current 2
//Address: P1-ED ~ P1-FF Reserved



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Page 2: TMDS/HDCP/HDMI//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// TMDS Receiver(Page 2)
//--------------------------------------------------
//#define S2_RESERVED                        	0xA0        // P2 Reserved A0
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
//Address: P2-C5~P2-C6 Reserved

//--------------------------------------------------
// HDMI(Port)
//--------------------------------------------------
#define S2_HDMI_APC                        	0xC8        //
#define S2_HDMI_ADDRESS                  	0xC9        // HDMI Address Port
#define S2_HDMI_PORT                      	0xCA        // HDMI Data Port
#define S2_HDMI_STATUS                     	0xCB        // HDMI Status Register
#define S2_HDMI_GPVS                       	0xCC        // HDMI Packet Variation Status Register
#define S2_HDMI_PACKET_ADDRESS             	0xCD        // HDMI Address For Packet Storage SRAM
#define S2_HDMI_PACKET_PORT             	0xCE        // HDMI Data For Packet Storage SRAM
//Address: P2-CF ~ P2-FF Reserved



///////////////////////////////////////////////////////////////////////////////
//////////////////////////      Page 3: Reserved     //////////////////////////
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//////////////////////////      Page 4: Reserved     //////////////////////////
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//////////////////////////      Page 5: Reserved     //////////////////////////
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
////////////////////////      Page 6: De-interlace     ////////////////////////
///////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// De-interlace (Page6)
//--------------------------------------------------
#define S6_ENABLE_BIST_CONTROL               	0xA0        // Enable and Bist Control Register
#define S6_INTERPOLATION_CONTROL             	0xA1        // Interpolation Control Register
#define S6_PIXEL_DIFF_THRESHOLD              	0xA2        // Pixel Difference Threshold
#define S6_PIXEL_REF_DIFF_THRESHOLD      		0xA3        // Pixel Reference Difference Threshold
#define S6_GRADIENT_THRESHOLD_POS        		0xA4        // Pixel Gradient Threshold Positive
#define S6_GRADIENT_THRESHOLD_NEG              	0xA5        // Pixel Gradient Threshold Negative

//--------------------------------------------------
// Post Processing Control (Page6)
//--------------------------------------------------
#define S6_SMOOTHING_ERROR_CORRECTION_CONTROL	0xA6        // Smoothing and Error Correction Control Register
#define S6_DELETE_LINE_PIXEL_ENABLE         	0xA7        // Delete Line and Pixel Enable
#define S6_MEDIAN_FILTER_THRESHOLD          	0xA8        // Median Filter Threshold

//--------------------------------------------------
// Noise Estimation (Page6)
//--------------------------------------------------
#define S6_HORIZONTAL_ACT_SIZE_HI    		    0xA9        // Horizontal Active Size HI
#define S6_HORIZONTAL_ACT_SIZE_LO     		    0xAA        // Horizontal Active Size LO
#define S6_VERTICAL_ACT_SIZE_HI             	0xAB        // Vertical Active Size HI
#define S6_VERTICAL_ACT_SIZE_LO             	0xAC        // Vertical Active Size LO
#define S6_CALCULATED_REGION_CONTROL          	0xAD        // Calculated Region Control Register
#define S6_H1_ACT_STA_POINT_HI              	0xAE        // Horizontal Active Start Point 1 HI
#define S6_H1_ACT_STA_POINT_LO              	0xAF        // Horizontal Active Start Point 1 LO
#define S6_H1_ACT_END_POINT_HI                 	0xB0        // Horizontal Active End Point 1 HI
#define S6_H1_ACT_END_POINT_LO               	0xB1        // Horizontal Active End Point 1 LO
#define S6_H2_ACT_STA_POINT_HI              	0xB2        // Horizontal Active Start Point 2 HI
#define S6_H2_ACT_STA_POINT_LO      	    	0xB3        // Horizontal Active Start Point 2 LO
#define S6_H2_ACT_END_POINT_HI                 	0xB4        // Horizontal Active End Point 2 HI
#define S6_H2_ACT_END_POINT_LO              	0xB5        // Horizontal Active End Point 2 LO
#define S6_H3_ACT_STA_POINT_HI              	0xB6        // Horizontal Active Start Point 3 HI
#define S6_H3_ACT_STA_POINT_LO              	0xB7        // Horizontal Active Start Point 3 LO
#define S6_H3_ACT_END_POINT_HI              	0xB8        // Horizontal Active End Point 3 HI
#define S6_H3_ACT_END_POINT_LO              	0xB9        // Horizontal Active End Point 3 LO
#define S6_MIN_SPA_NOISE_VALUE_BIN1           	0xBA        // Minimum Spatial Noise Value Within Bin1
#define S6_MIN_SPA_NOISE_VALUE_BIN2           	0xBB        // Minimum Spatial Noise Value Within Bin2
#define S6_MIN_SPA_NOISE_VALUE_BIN3           	0xBC        // Minimum Spatial Noise Value Within Bin3
#define S6_MIN_SPA_NOISE_VALUE_BIN4       		0xBD        // Minimum Spatial Noise Value Within Bin4
#define S6_MIN_SPA_NOISE_VALUE_BIN5          	0xBE        // Minimum Spatial Noise Value Within Bin5
#define S6_MIN_SPA_NOISE_VALUE_BIN6           	0xBF        // Minimum Spatial Noise Value Within Bin6
#define S6_MIN_SPA_NOISE_VALUE_BIN7          	0xC0        // Minimum Spatial Noise Value Within Bin7

//--------------------------------------------------
// Peaking and Coring and EMF/Chroma Lowpass (Page6)
//--------------------------------------------------
#define S6_PEAKING_ENABLE                     	0xC1        // Peaking Enable
#define S6_PEAKING_DATA00                   	0xC2        // Peaking Data 00
#define S6_PEAKING_DATA01                   	0xC3        // Peaking Data 01
#define S6_PEAKING_DATA02                   	0xC4        // Peaking Data 02
#define S6_PEAKING_DATA03                   	0xC5        // Peaking Data 03
#define S6_PEAKING_DATA04                   	0xC6        // Peaking Data 04
#define S6_PEAKING_DATA05                   	0xC7        // Peaking Data 05
#define S6_PEAKING_DATA06                     	0xC8        // Peaking Data 06
#define S6_PEAKING_DATA07                    	0xC9        // Peaking Data 07
#define S6_PEAKING_DATA08                     	0xCA        // Peaking Data 08
#define S6_PEAKING_DATA09                     	0xCB        // Peaking Data 09
#define S6_PEAKING_DATA10                     	0xCC        // Peaking Data 0A
#define S6_PEAKING_DATA11                     	0xCD        // Peaking Data 0B
#define S6_CHROMA_LOWPASS_FACTOR              	0xCE        // Peaking Chroma Lowpass Factor

//--------------------------------------------------
// YUV422 to YUV444 Conversion & 2 to 1 Setup (Page6)
//--------------------------------------------------
#define S6_YUV422_TO_YUV444                 	0xD4        // YUV422 to YUV444 Control Register
#define S6_ACT_BLANK_WINDOW_CONTROL_HI      	0xD5        // Active Window & Blanking Window Control Register HI
#define S6_ACT_WINDOW_CONTROL_LO            	0xD6        // Active Window Control Register LO
#define S6_BLANK_WINDOW_CONTROL_LO           	0xD7        // Blanking Window Control Register LO

//--------------------------------------------------
// DCTi in I-Domain (Page6)
//--------------------------------------------------
#define S6_DCTI_1ST_GAIN                      	0xD8        // DCTi 1st Gain
#define S6_DCTI_1ST_GAIN_THRESHOLD             	0xD9        // DCTi 1st Gain Threshold

//--------------------------------------------------
// Noise Reduction in I-domain (Page6)
//--------------------------------------------------
#define S6_CP_CONTROL                      	0xDA        // CP Control Register
#define S6_SPATIAL_CONTROL                 	0xDB        // Spatial Control Register
#define S6_SPATIAL_THRESHOLD_Y             	0xDC        // Spatial Threshold for Luma
#define S6_SPATIAL_THRESHOLD_C            	0xDD        // Spatial Threshold for Chroma
#define S6_IMPULSE_PIXEL_DIFF_THRESHOLD    	0xDE        // Impulse Pixel Diff Threshold
#define S6_IMPULSE_THRESHOLD_Y              0xDF        // Impulse Threshold for Luma
#define S6_IMPULSE_THRESHOLD_C              0xE0        // Impulse Threshold for Chroma
#define S6_IMPULSE_SMOOTH_THRESHOLD_Y       0xE1        // Impulse Smooth Threshold for Luma
#define S6_IMPULSE_SMOOTH_THRESHOLD_C       0xE2        // Impulse Smooth Threshold for Chroma

//--------------------------------------------------
// Scale Down (Page6)
//--------------------------------------------------
#define S6_UZD_CONTROL0                    	0xE3        // UZD Control Register 0
#define S6_UZD_CONTROL1                    	0xE4        // UZD Control Register 1
#define S6_UZD_SCALE_HOR_FACTOR_HI         	0xE5        // Horizontal Scale Factor HByte
#define S6_UZD_SCALE_HOR_FACTOR_MD         	0xE6        // Horizontal Scale Factor MByte
#define S6_UZD_SCALE_HOR_FACTOR_LO         	0xE7        // Horizontal Scale Factor LByte
#define S6_UZD_SCALE_VER_FACTOR_HI         	0xE8        // Vertical Scale Factor HByte
#define S6_UZD_SCALE_VER_FACTOR_MD         	0xE9        // Vertical Scale Factor MByte
#define S6_UZD_SCALE_VER_FACTOR_LO        	0xEA        // Vertical Scale Factor LByte
#define S6_UZD_HOR_DELTA1_HI               	0xEB        // Horizontal Non-Linear Delta1 HByte
#define S6_UZD_HOR_DELTA1_LO               	0xEC        // Horizontal Non-Linear Delta1 LByte
#define S6_UZD_HOR_SEGMENT1_HI             	0xED        // Horizontal Non-Linear Segment1 HByte
#define S6_UZD_HOR_SEGMENT1_LO             	0xEE        // Horizontal Non-Linear Segment1 LByte
#define S6_UZD_HOR_SEGMENT2_HI             	0xEF        // Horizontal Non-Linear Segment2 HByte
#define S6_UZD_HOR_SEGMENT2_LO             	0xF0        // Horizontal Non-Linear Segment2 LByte
#define S6_UZD_HOR_INITIAL_VALUE           	0xF1        // Horizontal Scaling Initial Value
#define S6_UZD_VER_INITIAL_VALUE           	0xF2        // Vertical Scaling Initial Value
#define S6_UZD_FIR_COEF_INDEX              	0xF3        // Filter Coefficient Index
#define S6_UZD_FIR_COEF_DATA               	0xF4        // Filter Coefficient Port
#define S6_UZD_CRC_CONTROL                 	0xF5        // CRC Control Register
#define S6_UZD_CRC_DATA3                  	0xF6        // CRC [31:24] Byte
#define S6_UZD_CRC_DATA2                    0xF7        // CRC [23:16] Byte
#define S6_UZD_CRC_DATA1                   	0xF8        // CRC [15: 8] Byte
#define S6_UZD_CRC_DATA0                    0xF9        // CRC [ 8: 0] Byte



///////////////////////////////////////////////////////////////////////////////
/////////////////////////     Page 4: Vivid Color     /////////////////////////
///////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Vivid Color - DLTi/DCTi (Page7)
//--------------------------------------------------
//#define S7_RESERVED                        	0xA0        // P7 Reserved A0
#define S7_DLTI_DCTI_ENABLE                	0xA1        // DLTi DCTi Enable
#define S7_DLTI_HF_THRESHOLD               	0xA2        // DLTi High Frequency Threshold
#define S7_DLTI_GAIN                       	0xA3        // DLTi Gain
#define S7_DLTI_GAIN_THRESHOLD          		0xA4        // DLTi Gain Threshold
#define S7_DLTI_OPTIONS                    	0xA5        // DLTi Options
#define S7_DCTI_1ST_GAIN                   	0xA6        // DCTi 1st Gain
#define S7_DCTI_1ST_GAIN_THRESHOLD       		0xA7        // DCTi 1st Gain Threshold
//#define S7_RESERVED                        	0xA8        // P7 Reserved A0

//--------------------------------------------------
// Peaking and Coring and EMF/Chroma Lowpass (Page7)
//--------------------------------------------------
#define S7_PEAKING_ENABLE                  	0xA9        // Peaking Enable
#define S7_PEAKING_DATA00                  	0xAA        // Peaking Data 00
#define S7_PEAKING_DATA01                  	0xAB        // Peaking Data 01
#define S7_PEAKING_DATA02                  	0xAC        // Peaking Data 02
#define S7_PEAKING_DATA03                  	0xAD        // Peaking Data 03
#define S7_PEAKING_DATA04                  	0xAE        // Peaking Data 04
#define S7_PEAKING_DATA05                  	0xAF        // Peaking Data 05
#define S7_PEAKING_DATA06                  	0xB0        // Peaking Data 06
#define S7_PEAKING_DATA07                  	0xB1        // Peaking Data 07
#define S7_PEAKING_DATA08                  	0xB2        // Peaking Data 08
#define S7_PEAKING_DATA09                  	0xB3        // Peaking Data 09
#define S7_PEAKING_DATA10                  	0xB4        // Peaking Data 0A
#define S7_PEAKING_DATA11                  	0xB5        // Peaking Data 0B
#define S7_CHROMA_LOWPASS_FACTOR        		0xB6        // Peaking Chroma Lowpass Factor

//--------------------------------------------------
// Auto Sharpness (Page7)
//--------------------------------------------------
#define S7_AUTO_SHARPNESS_CONTROL               0xB7        // Auto Sharpness Control Register
#define S7_AUTO_SHARPNESS_ADDRESS               0xB8        // Noise Reduction and Sharpness Port Address
#define S7_AUTO_SHARPNESS_PORT               	0xB9        // Auto Sharpness DATA Port

//Address: P7-BA ~ P7-BE Reserved

//--------------------------------------------------
// Vivid Color - Video Color Space Conversion (Page7)
//--------------------------------------------------
#define S7_YUV_TO_RGB_CONTROL                	0xBF        // YUV2RGB Control Register
#define S7_YUV_TO_RGB_ADDRESS                	0xC0        // YUV2RGB Access Port
#define S7_YUV_TO_RGB_PORT                  	0xC1        // YUV2RGB Data Port

//Address: P7-C2 ~ P7-C6 Reserved

//--------------------------------------------------
// Vivid Color - DCC (Page7)
//--------------------------------------------------
#define S7_DCC_CONTROL0                      	0xC7        // DCC Control Register 0
#define S7_DCC_CONTROL1                      	0xC8        // DCC Control Register 1
#define S7_DCC_ADDRESS                   	    0xC9        // DCC Access Port
#define S7_DCC_PORT                         	0xCA        // DCC Data Port

//Address: P7-CB ~ P7-CF Reserved

//--------------------------------------------------
// Vivid Color - ICM (Page7)
//--------------------------------------------------
#define S7_ICM_CONTROL                        	0xD0        // ICM Control Register
#define S7_ICM_SELECT                          	0xD1        // ICM Accessing Through Data Port Select
#define S7_ICM_ADDRESS                         	0xD2        // ICM Access Port
#define S7_ICM_PORT                          	0xD3        // ICM Data Port
#define S7_PC_ADDRESS				        	0xD6		// peaking & coring Access Port
#define S7_PC_PORT      						0xD7		// peaking & coring Access data Port
// TODO: add Hue/Saturation Control; Contrast/Brightness Control


///////////////////////////////////////////////////////////////////////////////
////////////////////////     Page 8: Video Decoder     ////////////////////////
///////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Chroma Adjustment Registers (Page7)
//--------------------------------------------------
#define S8_VIDEO_CONTROL0                      	0xA0        // Video Control 0
#define S8_VIDEO_CONTROL1                      	0xA1        // Video Control 1
#define S8_ADC_CLAMP_UP_DOWN                   	0xA2        // ADC Switch Control
#define S8_AGC_GATE_THRESHOLD_SWAP         		0xA3        // AGC Gate TH Swap
#define S8_IO_CONTROL                       	0xA4        // Inout Control
//#define S_RESERVED                          	0xA5        // P8 Reserved A5
//#define S_RESERVED                          	0xA6        // P8 Reserved A6
#define S8_OUTPUT_CONTROL                     	0xA7        // Output Control
#define S8_CONTRAST_YADJ                       	0xA8        // Luma Contrast Adjust
#define S8_BRIGHTNESS_YADJ                     	0xA9        // Luma Brightness Adjust
#define S8_SATURATION_CADJ                      0xAA        // Chroma Saturation Adjust
#define S8_HUE_PHASE_CADJ                       0xAB        // Chroma Hue Phase Adjust

//--------------------------------------------------
// DC Balance Control  (Page7)
//--------------------------------------------------
#define S8_DC_HACT_STA               	    	0xAC        // DC Hactive Start
#define S8_DC_VACT_STA               	    	0xAD        // DC Vactive Start
#define S8_THRESHOLD                        	0xAE        // DC Threshold
#define S8_DC_POS_GAIN                       	0xAF        // DC Positive Gain
#define S8_NEG_GAIN                         	0xB0        // DC Negetive Gain
#define S8_YDC_STATUS                       	0xB1        // YDC Status
#define S8_YDC_AVERAGE_STATUS          		    0xB2        // YDC Average Status
#define S8_DC_BALANCE_CONTROL0              	0xB3        // DC Balance Control 0
#define S8_DC_BALANCE_CONTROL1              	0xB4        // DC Balance Control 1
#define S8_IRQ_MASK1                        	0xB5        // IRQ Mask 1
#define S8_IRQ_MASK2                        	0xB6        // IRQ Mask 2
#define S8_IRQ_STATUS1                      	0xB7        // IRQ Status 1
#define S8_IRQ_STATUS1_WCLR              		0xB8        // IRQ Status 1 write 1 to clear
#define S8_IRQ_STATUS2                      	0xB9        // IRQ Status 2
#define S8_IRQ_STATUS2_WCLR              		0xBA        // IRQ Status 2write 1 to clear
#define S8_ADC_LIMIT_THRESHOLD                 	0xBB        // ADC Limit Threshold
#define S8_VIDEO_STATUS1                       	0xBC        // Video Status Register1
#define S8_VIDEO_STATUS2                       	0xBD        // Video Status Register2
#define S8_VIDEO_STATUS3                       	0xBE        // Video Status Register3
#define S8_NOISE_THRESHOLD                     	0xBF        // Noise Threshold
#define S8_HDTO_INC_STATUS4              		0xC0        // HDTO Inc Status 4
#define S8_HDTO_INC_STATUS3              		0xC1        // HDTO Inc Status 3
#define S8_HDTO_INC_STATUS2              		0xC2        // HDTO Inc Status 2
#define S8_HDTO_INC_STATUS1              		0xC3        // HDTO Inc Status 1
#define S8_CDTO_INC_STATUS4              		0xC4        // CDTO Inc Status 4
#define S8_CDTO_INC_STATUS3              		0xC5        // CDTO Inc Status 3
#define S8_CDTO_INC_STATUS2              		0xC6        // CDTO Inc Status 2
#define S8_CDTO_INC_STATUS1              		0xC7        // CDTO Inc Status 1
#define S8_AGC_GAIN_STATUS2                    	0xC8        // Digital ADC Gain Value High byte
#define S8_AGC_GAIN_STATUS1                    	0xC9        // Digital ADC Gain Value Low byte
#define S8_CMAG_STATUS                      	0xCA        // Chroma Magnitude
#define S8_CGAIN_STATUS2                     	0xCB        // Chroma Gain High Byte
#define S8_CGAIN_STATUS1                     	0xCC        // Chroma Gain Low Byte
#define S8_CORDIC_FREQ_STATUS             		0xCD        // SECAM Cordic Frequency
#define S8_NOISE_STATUS                     	0xCE        // Noise Status
#define S8_VIDEO_RESET                       	0xCF        // Video Soft Reset

//--------------------------------------------------
// Auto Mode State Machine Registers
//--------------------------------------------------
#define S8_PALM_COMPENSATION1                  	0xD0        // Palm Flag Compensation Counter.
#define S8_PALM_COMPENSATION2                  	0xD1        // Palm Flag Compensation Threshold
#define S8_MANUAL_MODE                      	0xD2        // AUTO Manual Mode Setting
#define S8_MODE_DETECT_STATUS             		0xD3        // Mode Detect Status
#define S8_STAT_AND_DIS_MODE             		0xD4        // Statistc and Disable Mode
#define S8_PREFER_MODE                      	0xD5        // Prefer Mode
#define S8_STATE_MACHINE_FIX_MODE              	0xD6        // State Machine Fix mode
#define S8_ZORAN_ENABLE                        	0xD7        // Zoran Register Enable
#define S8_AUTO_MODE_STATE_MACHINE_STAT			0xD8        // AUTO Mode State Machine Statistic
//#define S_RESERVED                          	0xD9        // P8 Reserved D9
#define S8_COMB_FILTER_CONFIG                 	0xDA        // COMB Filter Config
#define S8_COMB_FILTER_THRESHOLD1               0xDB        // COMB Filter Threshold 1
#define S8_COMB_FILTER_THRESHOLD2               0xDC        // COMB Filter Threshold 2
#define S8_COMB_FILTER_THRESHOLD3               0xDD        // COMB Filter Threshold 3
#define S8_COMB_FILTER_THRESHOLD4               0xDE        // COMB Filter Threshold 4
//#define S_RESERVED                          	0xDF        // P8 Reserved DF
#define S8_YCSEPARATION_CONTROL                	0xE0        // YC Seperate Control
#define S8_BPF_BW_YSELECT                     	0xE1        // BPF BandWidth Select Y
#define S8_BPF_BW_CSELECT                     	0xE2        // BPF BandWidth Select C
#define S8_ADAP_BPF_CTHRESHOLD1                 0xE3        // Chroma Adaptive BPF Detection Threshold 1
#define S8_ADAP_BPF_CTHRESHOLD2                 0xE4        // Chroma Adaptive BPF Detection Threshold 2
#define S8_ADAP_BPF_CTHRESHOLD3                 0xE5        // Chroma Adaptive BPF Detection Threshold 3
#define S8_ADAP_BPF_CTHRESHOLD4                 0xE6        // Chroma Adaptive BPF Detection Threshold 4
#define S8_ADAP_BPF_YTHRESHOLD1                 0xE7        // Threshold 1 for Y Adaptive BPF detection
#define S8_ADAP_BPF_YTHRESHOLD2                 0xE8        // Threshold 2 for Y Adaptive BPF detection
#define S8_ADAP_BPF_YTHRESHOLD3                 0xE9        // Threshold 3 for Y Adaptive BPF detection
#define S8_YC_BW_CONTROL                       	0xEA        // YC BandWidth Control
#define S8_2D_DEBUG_MODE                    	0xEB        // 2D Debug Mode
#define S8_RESOL_LP_THRESHOLD                  	0xEC        // RESOL LP TH
#define S8_ENVELOPE_THRESHOLD                  	0xED        // ENVELOPE TH
#define S8_COMB_FILTER_THRESHOLD5          		0xEE        // Comb Filter THR5
//#define S_RESERVED                          	0xEF        // P8 Reserved EF
#define S8_BW_DETECTION                   	    0xF0        // Band Width Detection
#define S8_BW_EDGE_THRESHOLD                   	0xF1        // Band Width Edge Threshold
#define S8_2D_ALPHA_MOD_ENABLE      			0xF2        // 2D ALPHA Mode Enable
#define S8_H2V_CORING_THRESHOLD               	0xF3        // H2V Coring Threshold
#define S8_H2V_Y_NOISE_THRESHOLD              	0xF4        // H2V Y Noise Threshold
#define S8_H2V_CVBS_NOISE_THRESHOLD        		0xF5        // H2V CVBS Noise Threshold
#define S8_1D_BLEND_THRESHOLD                  	0xF6        // 1D Blend Threshold
#define S8_1D_BLEND_BPF_YSELECT          		0xF7        // 1D Blend BPF Select for Y
#define S8_1D_BLEND_BPF_CSELECT          		0xF8        // 1D Blend BPF Select for C
//Address: P8-F9 ~ P8-FF Reserved



///////////////////////////////////////////////////////////////////////////////
////////////////////////     Page 9: Video Decoder     ////////////////////////
///////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Clamping/AGC Control Registers
//--------------------------------------------------
#define S9_AGC_PEAK_NOMINAL                  	0xA0        //AGC Peak Nominal
#define S9_AGC_PEAK_GATE_CONTROL          	    0xA1        //AGC Peak and Gate Control
#define S9_AGC_PEAK_CONTROL                  	0xA2        //AGC Peak Control
#define S9_VIDEO_CONTROL2                    	0xA3        //Video Control
#define S9_AGC_YVALUE                       	0xA4        //Luma AGC Value
#define S9_AGC_GATE_STA_HI                     	0xA5        //Rough Gate Generator HI
#define S9_AGC_GATE_STA_LO                   	0xA6        //Rough Gate Generator LO
#define S9_AGC_GATE_WIDTH                     	0xA7        //Rough Gate Width
#define S9_AGC_BACKPORCH_DELAY                 	0xA8        //Sync Tip To Backproch Delay
#define S9_CLAMP_COMP_NEW_THRESHOLD2    		0xA9        //ClampAGC CompLuma Threshold2
#define S9_CLAMP_COMP_NEW_THRESHOLD1   			0xAA        //ClampAGC CompLuma Threshold1
#define S9_CLAMP_COMP_NEW_CONTROL     			0xAB        //ClampAGC CompLuma New Control
#define S9_VSYNC_AGC_MIN                       	0xAC        //Vsync AGC minimun
#define S9_VSYNC_AGC_LOCK_END             		0xAD        //Vsync AGC LockOut End
//#define S_RESERVED                          	0xAE        //P9 Reserved AE
//#define S_RESERVED                           	0xAF        //P9 Reserved AF
#define S9_CHPUMP_DELAY_CONTROL                	0xB0        //Charge Pump Delay Control
#define S9_CHPUMP_ADJ                        	0xB1        //Charge Pump Delay Adjustment
#define S9_CHPUMP_DELAY                      	0xB2        //Charge Pump Delay
//#define S_RESERVED                           	0xB3        //P9 Reserved B3
#define S9_CAGC                             	0xB4        //Chrona AGC
#define S9_CKILL                            	0xB5        //Chroma Kill
#define S9_CLOCK_CONFIG                      	0xB6        //Chroma Lock Configuation
#define S9_CLOOP_GAIN                       	0xB7        //Chroma LoopFilter Gain
#define S9_CLOOP_STATE                      	0xB8        //Chroma LoopFilter State
#define S9_CAUTOPOS                         	0xB9        //Chroma AutoPosition
//Address: P9-BA ~ P9-BF Reserved
#define S9_LOCK_COUNT                       	0xC0        //Lock Count
#define S9_HLOOP_MAXSTATE                      	0xC1        //H Loop MaxState
#define S9_CLAMP_CONTROL0                      	0xC2        //ClampAGC Control 0
#define S9_CLAMP_NEWSYNC_STA          			0xC3        //ClampAGC New Coarse Sync Start Position
#define S9_CLAMP_NEWSYNC_END         			0xC4        //ClampAGC New Coarse Sync End Position
#define S9_CLAMP_NEWBP_STA               		0xC5        //ClampAGC New Coarse Back Porch Start Position
#define S9_CLAMP_NEWBP_END              		0xC6        //ClampAGC New Coarse Back Porch End Position
#define S9_HDETECT_PHASE_SEL                   	0xC7        //H Detect Phase Select
#define S9_HDETECT_COUNTER_TIP_STA         		0xC8        //H Detect Counter Tip Start
#define S9_HDETECT_COUNTER_TIP_END         		0xC9        //H Detect Counter Tip End
#define S9_HDETECT_COUNTER_BP_STA          		0xCA        //H Detect Counter Back Porch Start
#define S9_HDETECT_COUNTER_BP_END          		0xCB        //H Detect Counter Back Porch End
#define S9_HPLLECT_INTEGRAL_CONTROL            	0xCC        //HPLL Integral CONTROL
#define S9_HPHASE_ERR_STATUS_HI       			0xCD        //H Detect Phase Error Status High Byte
#define S9_HPHASE_ERR_STATUS_LO        			0xCE        //H Detect Phase Error Status Low Byte
//#define S_RESERVED                            	0xCF        //P9 Reserved CF
#define S9_HSYNC_RISING                        	0xD0        //Hsync Rising Position
#define S9_HSYNC_PHASE_OFFSET                		0xD1        //Hsync Phase Offset
#define S9_HSYNC_GATE_STA                      	0xD2        //Hsync Gate Detect Window Start
#define S9_HSYNC_GATE_END                      	0xD3        //Hsync Gate Detect Window End
#define S9_HSYNC_TIP_STA                       	0xD4        //Hsync Tip Detect Window Start
#define S9_HSYNC_TIP_END                       	0xD5        //Hsync Tip Detect Window End
#define S9_HSYNC_RISING_STA                    	0xD6        //Hsync Rising Detect Window Start
#define S9_HSYNC_RISING_END                    	0xD7        //Hsync rising Detect Window End
#define S9_BACKPORCH_STA                  	    0xD8        //BackPorch Detect Window Start
#define S9_BACKPORCH_END                       	0xD9        //BackPorch Detect Window End
#define S9_HBLANK_STA                       	0xDA        //Hblank Window Start
#define S9_HBLANK_END                       	0xDB        //Hblank Window End
#define S9_BURST_GATE_STA                   	0xDC        //Burst Gate Window Start
#define S9_BURST_GATE_END                    	0xDD        //Burst Gate Window End
#define S9_HACT_STA                         	0xDE        //Hactive Start
#define S9_HACT_WIDTH                         	0xDF        //Hactive Width
#define S9_VACT_STA                         	0xE0        //Vactive Start
#define S9_VACT_HEIGHT                      	0xE1        //Vactive Height
#define S9_VSYNC_HL_MIN                        	0xE2        //HalfLine After Vsync Detect Max
#define S9_VSYNC_HL_MAX                        	0xE3        //HalfLine After Vsync Detect Min
#define S9_VSYNC_VBI_MIN                       	0xE4        //HalfLine After Vsync Detect Min When VBI Data is vaild
#define S9_VSYNC_VBI_LOCK_END                 	0xE5        //VBI LockOut End
#define S9_VSYNC_CONTROL                       	0xE6        //Vsync Control
#define S9_VSYNC_TC                            	0xE7        //Vsync Time Constant
#define S9_VSYNC_TC2                           	0xE8        //Vsync Time Constant 2
#define S9_VSYNC_TC1                           	0xE9        //Vsync Time Constant 1
#define S9_SERR_THRESHOLD                      	0xEA        //Serration Detection Threshold
#define S9_NO_SINGAL_DECREMENT                 	0xEB        //No Singal Counter Decrement Value
//Address: P9-EC ~ P9-EF Reserved
#define S9_CDTO_INC4                        	0xF0        //Chroma DTO INC4
#define S9_CDTO_INC3                        	0xF1        //Chroma DTO INC3
#define S9_CDTO_INC2                        	0xF2        //Chroma DTO INC2
#define S9_CDTO_INC1                        	0xF3        //Chroma DTO INC1
#define S9_HDTO_INC4                        	0xF4        //Hsync  DTO INC4
#define S9_HDTO_INC3                        	0xF5        //Hsync  DTO INC3
#define S9_HDTO_INC2                        	0xF6        //Hsync  DTO INC2
#define S9_HDTO_INC1                        	0xF7        //Hsync  DTO INC1
//Address: P9-F8 ~ P9-FF Reserved



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page A: VD  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#define SA_AUTO_MODE_TB1                    	0xA0        //AutoMode Table 0
#define SA_AUTO_MODE_TB2                     	0xA1        //AutoMode Table 1
#define SA_AUTO_MODE_TB3                    	0xA2        //AutoMode Table 2
#define SA_AUTO_MODE_TB4                    	0xA3        //AutoMode Table 3
#define SA_AUTO_MODE_TB5                    	0xA4        //AutoMode Table 4
#define SA_AUTO_MODE_TB6                    	0xA5        //AutoMode Table 5
#define SA_AUTO_MODE_TB7                    	0xA6        //AutoMode Table 6
#define SA_AUTO_MODE_TB8                    	0xA7        //AutoMode Table 7
#define SA_AUTO_MODE_TB9                    	0xA8        //AutoMode Table 8
#define SA_625_FLAG_COUNTER                 	0xA9        //625 Flag Counter
#define SA_443_FLAG_COUNTER                  	0xAA        //443 Flag Counter
#define SA_SECAM_FLAG_COUNTER                	0xAB        //SECAM Flag Counter
#define SA_PALM_FLAG_COUNTER                 	0xAC        //PALM Flag Counter
#define SA_BURST_VALID_COUNTER              	0xAD        //Burst Magnitude not Vaild Counter
//Address: PA-AE ~ PA-AF Reserved
#define SA_MIDPOINT_ADJ                      	0xB0        //MidPoint adjustment
#define SA_FREQ_FLAG_THRESHOLD                 	0xB1        //Frequence Flag Threshold
#define SA_FREQ_VALID_MAX                     	0xB2        //Frequence Valid Max
#define SA_FREQ_VALID_INNER                   	0xB3        //Frequence Valid Inner
#define SA_FREQ_VALID_MIN                     	0xB4        //Frequence Valid Min
#define SA_SECAM_FLAG_COUNTER_MAX      			0xB5        //SECAM Flag Counter Max
#define SA_SECAM_FLAG_COUNTER_MIN      			0xB6        //SECAM Flag Counter Min
#define SA_PALM_FLAG_PHASE                		0xB7        //PALM Flag Phase
#define SA_BURST_LOW_LIMIT                		0xB8        //Burst Low Limit
#define SA_BURST_MAG_CHOICE              		0xB9        //Burst Magnitude Choice
#define SA_BURST_MAG_STATUS              		0xBA        //Burst Magnitude Status
#define SA_FIFO_CONTROL                        	0xBB        //FIFO control
#define SA_FIFO_STATUS                      	0xBC        //FIFO Status
#define SA_I_GAIN_CONTROL                      	0xBD        //I-Gain Control
#define SA_MISC_CONTROL                        	0xBE        //Misc Control
#define SA_FIFO_DEP_MIN                      	0xBF        //FIFO Depth Min Status
#define SA_FIFO_DEP_MAX                     	0xC0        //FIFO Depth Max Status
#define SA_HSYNC_PULSE_STA                		0xC1        //Hsync Start Position
#define SA_HSYNC_PULSE_WID               		0xC2        //Hsync Width
#define SA_CRESAMP_CONTROL                     	0xC3        //Chroma Hresampler Control
#define SA_SECAM_CONTROL                       	0xC4        //SECAM Control
#define SA_SECAM_DR_OFFSET                		0xC5        //SECAM DR Offset
#define SA_SECAM_DB_OFFSET                		0xC6        //SECAM DB Offset
#define SA_SECAM_HCOUNT_RST             		0xC7        //Hcount Reset
#define SA_PHASE_DIFF_DR_RST             		0xC8        //Secam DR's Phase Diff from Cordic reset value
#define SA_PHASE_DIFF_DB_RST             		0xC9        //Secam DB's Phase Diff from Cordic reset value
#define SA_DRDB_GAIN_TB                     	0xCA        //Secam Gain DrDb Look Up Table
#define SA_Y_GAIN_TB                        	0xCB        //Secam Gain Y Look Up Table
#define SA_SECAM_GAIN_DELAY                   	0xCC        //Secam Y Delay For dr/db gain
#define SA_SECAM_GAIN_DBG_TB           		    0xCD        //SECAM Gain Table Debug
//Address: PA-CE ~ PA-CF Reserved

//--------------------------------------------------
// MISC Control Registers
//--------------------------------------------------
#define SA_LDPAUSE_CTL                      	0xD0        //LD pause detected
#define SA_VCR_OPT                          	0xD1        //VCR Option
#define SA_CEN_LINE_COUNT                   	0xD2        //Cenable Line Count
#define SA_MEAS_1ST_V_HI                    	0xD3        //Measure First V HI
#define SA_MEAS_1ST_V_LO                 		0xD4        //Measure First V LOW
#define SA_MEAS_2ND_V_HI                    	0xD5        //Measure Second V HI
#define SA_MEAS_2ND_V_LO                		0xD6        //Measure Second V LOW
#define SA_PORCH_HEIGHT_HI                 	    0xD7        //Porch Height Measurement HI
#define SA_PORCH_HEIGHT_LO                 	    0xD8        //Porch Height Measurement LO
#define SA_SINGAL_STM_CONTROL                  	0xD9        //Singal STM Control
#define SA_CDET_PHASE_ERR2                    	0xDA        //Chroma Detect Phase Error 2
#define SA_CDET_PHASE_ERR1                   	0xDB        //Chroma Detect Phase Error 1
#define SA_MV_DET_WIN                       	0xDC        //MacroVision Detect Window
#define SA_MV_BURST_STA                     	0xDD        //MacroVision Burst Detect Window Start
#define SA_MV_BURST_END                     	0xDE        //MacroVision Burst Detect Window End
#define SA_COLORSTRIPE_CONTROL               	0xDF        //ColorStripe Control
#define SA_DBG_MUX                          	0xE0        //Debug Mux
#define SA_VIDEO_DBG_ANALOG                    	0xE1        //Video Debug Analog
#define SA_VIDEO_DBG_DIGITAL                   	0xE2        //Video Debug Digital
#define SA_BIST_TEST1                       	0xE3        //BIST Test 1
#define SA_BIST_TEST2                       	0xE4        //BIST Test 2
//#define S_RESERVED                          	0xE5        //PA Reserved E5
#define SA_PATTERN_CONTROL                     	0xE6        //Pattern Control
#define SA_CRC_RESULT2                         	0xE7        //CRC Result 2
#define SA_CRC_RESULT1                         	0xE8        //CRC Result 1
#define SA_CRC_RESULT0                         	0xE9        //CRC Result 0
//#define S_RESERVED                           	0xEA        //PA Reserved EA
//#define S_RESERVED                           	0xEB        //PA Reserved EB
#define SA_FPGA_TEST1                       	0xEC        //FPGA Test1
#define SA_FPGA_TEST2                       	0xED        //FPGA Test2
#define SA_FPGA_TEST3                       	0xEE        //FPGA Test3
#define SA_FPGA_TEST4                       	0xEF        //FPGA Test4
#define SA_CLAMP_TEST0                      	0xF0        //Clamp Test Reg 0
#define SA_CLAMP_TEST1                      	0xF1        //Clamp Test Reg 1
#define SA_CLAMP_TEST6                      	0xF2        //Clamp Test Reg 6
#define SA_CLAMP_TEST7                      	0xF3        //Clamp Test Reg 7
#define SA_CLAMP_TEST8                      	0xF4        //Clamp Test Reg 8
#define SA_CLAMP_TEST9                      	0xF5        //Clamp Test Reg 9
#define SA_CLAMP_TEST10                     	0xF6        //Clamp Test Reg 10
#define SA_CLAMP_TEST11                     	0xF7        //Clamp Test Reg 11
#define SA_CLAMP_TEST12                     	0xF8        //Clamp Test Reg 12
#define SA_CLAMP_TEST13                     	0xF9        //Clamp Test Reg 13
#define SA_CLAMP_TEST17                     	0xFA        //Clamp Test Reg 17
//#define S_RESERVED                           	0xFB        //PA Reserved FB
//#define S_RESERVED                           	0xFC        //PA Reserved FC
//#define S_RESERVED                           	0xFD        //PA Reserved FD
#define SA_CHIP_VER_HI                        	0xFE        //Chip Version HI
#define SA_CHIP_VER_LO                        	0xFF        //Chip Version LO



///////////////////////////////////////////////////////////////////////////////
/////////////      Page B: Off Line Sync Processor & Auto SOY     /////////////
///////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Off Line Sync Processor
//--------------------------------------------------
#define SB_SYNC_SELECT                        	0xA0        // Sync Select Control Register
#define SB_SYNC_INVERT                        	0xA1        // Sync Invert Control Register
#define SB_SYNC_CONTROL                        	0xA2        // Sync Processor Control Register
#define SB_STABLE_HIGH_PERIOD_HI            	0xA3        // Stable High Period HByte
#define SB_STABLE_HIGH_PERIOD_LO            	0xA4        // Stable High Period LByte
#define SB_VSYNC_COUNTER_LEVEL_HI         		0xA5        // Vertical Sync Counter Level HI
#define SB_VSYNC_COUNTER_LEVEL_LO           	0xA6        // Vertical Sync Counter Level LO
#define SB_HSYNC_TYPE_DETECTION_FLAG    		0xA7        // Hsync Type Detection Flag
#define SB_STABLE_MEASURE                    	0xA8        // Stable Measure
#define SB_STABLE_PERIOD_HI                 	0xA9        // Stable Period HByte
#define SB_STABLE_PERIOD_LO                 	0xAA        // Stable Period LByte
#define SB_MEAS_HSYNC_PERIOD_HI                	0xAB        // HSync Period Measured Result HByte
#define SB_MEAS_HSYNC_PERIOD_LO                	0xAC        // HSync Period Measured Result LByte
#define SB_MEAS_VSYNC_PERIOD_HI                	0xAD        // VSync Period Measured Result HByte
#define SB_MEAS_VSYNC_PERIOD_LO                	0xAE        // VSync Period Measured Result LByte
#define SB_MEAS_HSYNC_VSYNC_HIGH_PERIOD_HI     	0xAF        // HSync and VSync High Period Measured Results HByte
#define SB_MEAS_HSYNC_VSYNC_HIGH_PERIOD_LO    	0xB0        // HSync and VSync High Period Measured Results LByte
#define SB_MEAS_HYNCS_VSYNC_HIGH_PERIOD_SELECT 	0xB1        // HSync and VSync High Period Measured Select
//#define SB_RESERVED                       	0xB2        // PB Reserved B2
#define SB_SYNC_TEST_MISC                   	0xB3        // Sync Test MISC Register
#define SB_GRN_CLAMP_STA                      	0xB4        // Clamp Signal Output Start of G Channel
#define SB_GRN_CLAMP_END                      	0xB5        // Clamp Signal Output End of G Channel
#define SB_BLU_RED_CLAMP_STA                   	0xB6        // Clamp Signal Output Start of R/B Channel
#define SB_BLU_RED_CLAMP_END                   	0xB7        // Clamp Signal Output End of R/B Channel
#define SB_CLAMP_CONTROL0                     	0xB8        // Clamp Signal Control Register 0
#define SB_CLAMP_CONTROL1                     	0xB9        // Clamp Signal Control Register 1
#define SB_CLAMP_CONTROL2                     	0xBA        // Clamp Signal Control Register 2
#define SB_CLAMP_CONTROL3                     	0xBB        // Clamp Signal Control Register 3
#define SB_COAST_CONTROL                      	0xBC        // Coast Control Register
#define SB_CAPTURE_WINDOW_SETTING            	0xBD        // Capture Window Setting
#define SB_DETECT_TOLERANCE_SETTING            	0xBE        // Detection Tolerance Setting
#define SB_SKIP_LINE_CONTROL                  	0xBF        // Skip Line Control Register

//--------------------------------------------------
// Auto SOY
//--------------------------------------------------
#define SB_SOYCH0_CONTROL00 						0xC0        // Channel 0 SOY Auto Compare Level Detect Control Register 0
#define SB_SOYCH0_CONTROL01 						0xC1        // Channel 0 SOY Auto Compare Level Detect Control Register 1
#define SB_SOYCH0_CONTROL02 						0xC2        // Channel 0 SOY Auto Compare Level Detect Control Register 2
#define SB_SOYCH0_CONTROL03 						0xC3        // Channel 0 SOY Auto Compare Level Detect Control Register 3
#define SB_SOYCH0_CONTROL04 						0xC4        // Channel 0 SOY Auto Compare Level Detect Control Register 4
#define SB_SOYCH0_CONTROL05 						0xC5        // Channel 0 SOY Auto Compare Level Detect Control Register 5
#define SB_SOYCH0_CONTROL06 						0xC6        // Channel 0 SOY Auto Compare Level Detect Control Register 6
#define SB_SOYCH0_CONTROL07 						0xC7        // Channel 0 SOY Auto Compare Level Detect Control Register 7
#define SB_SOYCH0_CONTROL08 						0xC8        // Channel 0 SOY Auto Compare Level Detect Control Register 8
#define SB_SOYCH0_CONTROL09 						0xC9        // Channel 0 SOY Auto Compare Level Detect Control Register 9
#define SB_SOYCH0_CONTROL10 						0xCA        // Channel 0 SOY Auto Compare Level Detect Control Register A
#define SB_SOYCH0_CONTROL11 						0xCB        // Channel 0 SOY Auto Compare Level Detect Control Register B
#define SB_SOYCH0_CONTROL12 						0xCC        // Channel 0 SOY Auto Compare Level Detect Control Register C

#define SB_SOYCH1_CONTROL00 						0xD0        // Channel 0 SOY Auto Compare Level Detect Control Register 0
#define SB_SOYCH1_CONTROL01 						0xD1        // Channel 0 SOY Auto Compare Level Detect Control Register 1
#define SB_SOYCH1_CONTROL02 						0xD2        // Channel 0 SOY Auto Compare Level Detect Control Register 2
#define SB_SOYCH1_CONTROL03 						0xD3        // Channel 0 SOY Auto Compare Level Detect Control Register 3
#define SB_SOYCH1_CONTROL04 						0xD4        // Channel 0 SOY Auto Compare Level Detect Control Register 4
#define SB_SOYCH1_CONTROL05 						0xD5        // Channel 0 SOY Auto Compare Level Detect Control Register 5
#define SB_SOYCH1_CONTROL06 						0xD6        // Channel 0 SOY Auto Compare Level Detect Control Register 6
#define SB_SOYCH1_CONTROL07 						0xD7        // Channel 0 SOY Auto Compare Level Detect Control Register 7
#define SB_SOYCH1_CONTROL08 						0xD8        // Channel 0 SOY Auto Compare Level Detect Control Register 8
#define SB_SOYCH1_CONTROL09 						0xD9        // Channel 0 SOY Auto Compare Level Detect Control Register 9
#define SB_SOYCH1_CONTROL10 						0xDA        // Channel 0 SOY Auto Compare Level Detect Control Register A
#define SB_SOYCH1_CONTROL11 						0xDB        // Channel 0 SOY Auto Compare Level Detect Control Register B
#define SB_SOYCH1_CONTROL12 						0xDC        // Channel 0 SOY Auto Compare Level Detect Control Register C










///////////////////////////////////////////////////////////////////////////////
////////////////////////     Access Port addresses     ////////////////////////
///////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Scale Down Port and Input Pattern Generator (Address: 0x24; Data: 0x25)
//--------------------------------------------------
#define SP_SD_VSCALE_INIT                       0x00        // Vertical Scale Down Initial Select
#define SP_SD_VSCALE_FACTOR_HI                  0x01        // Vertical Scale Down Factor HByte
#define SP_SD_VSCALE_FACTOR_MD                  0x02        // Vertical Scale Down Factor MByte
#define SP_SD_VSCALE_FACTOR_LO                	0x03        // Vertical Scale Down Factor LByte
#define SP_SD_HSCALE_INIT                    	0x04        // Horizontal Scale Down Initial Select
#define SP_SD_HSCALE_FACTOR_HI                  0x05        // Horizontal Scale Down Factor HByte
#define SP_SD_HSCALE_FACTOR_MD                  0x06        // Horizontal Scale Down Factor MByte
#define SP_SD_HSCALE_FACTOR_LO                	0x07        // Horizontal Scale Down Factor LByte
#define SP_SD_HSCALE_ACC_HI                    	0x08        // Horizontal Scale Down Accumulated Factor HByte
#define SP_SD_HSCALE_ACC_LO                    	0x09        // Horizontal Scale Down Accumulated Factor LByte
#define SP_SD_ACC_WIDTH_HI                      0x0A        // Horizontal Scale Down Accumulated Width HByte
#define SP_SD_ACC_WIDTH_LO                      0x0B        // Horizontal Scale Down Accumulated Width LByte
#define SP_SD_FLAT_WIDTH_HI                     0x0C        // Horizontal Scale Down Flat Width HByte
#define SP_SD_FLAT_WIDTH_LO                     0x0D        // Horizontal Scale Down Flat Width LByte
//Address: 25-0E~25-0F Reserved
#define SP_IPG_CONTROL0                 		0x10        // Input Pattern Generator Control Register0
#define SP_IPG_CONTROL1                  		0x11        // Input Pattern Generator Control Register1
#define SP_IPG_RED                            	0x12        // Input Pattern Generator RED Initial Value
#define SP_IPG_GRN          	             	0x13        // Input Pattern Generator GREEN Initial Value
#define SP_IPG_BLU                          	0x14        // Input Pattern Generator BLUE Initial Value

//--------------------------------------------------
// Display Format Port (Address: 0x2A; Data: 0x2B)
//--------------------------------------------------
#define SP_VDISP_HTOTAL_HI                    	0x00        // Display Horizontal Total Pixels HByte
#define SP_VDISP_HTOTAL_LO                    	0x01        // Display Horizontal Total Pixels LByte
#define SP_VDISP_HSYNC_END                     	0x02        // Display Horizontal Sync Pixel Width
#define SP_VDISP_HBG_STA_HI                  	0x03        // Display Horizontal Background Start HByte
#define SP_VDISP_HBG_STA_LO                 	0x04        // Display Horizontal Background Start LByte
#define SP_VDISP_HACT_STA_HI                  	0x05        // Display Horizontal Active Start HByte
#define SP_VDISP_HACT_STA_LO                  	0x06        // Display Horizontal Active Start LByte
#define SP_VDISP_HACT_END_HI             		0x07        // Display Horizontal Active End HByte
#define SP_VDISP_HACT_END_LO                  	0x08        // Display Horizontal Active End LByte
#define SP_VDISP_HBG_END_HI           		    0x09        // Display Horizontal Background End HByte
#define SP_VDISP_HBG_END_LO           	    	0x0A        // Display Horizontal Background End LByte
#define SP_VDISP_VTOTAL_HI                     	0x0B        // Display Vertical Total Lines HByte
#define SP_VDISP_VTOTAL_LO                    	0x0C        // Display Vertical Total Lines LByte
#define SP_VDISP_VSYNC_END                     	0x0D        // Display Vertical Sync End Lines
#define SP_VDISP_VBG_STA_HI          	    	0x0E        // Display Vertical Background Start HByte
#define SP_VDISP_VBG_STA_LO          	    	0x0F        // Display Vertical Background Start LByte
#define SP_VDISP_VACT_STA_HI                  	0x10        // Display Vertical Active Start HByte
#define SP_VDISP_VACT_STA_LO                  	0x11        // Display Vertical Active Start LByte
#define SP_VDISP_VACT_END_HI                  	0x12        // Display Vertical Active End HByte
#define SP_VDISP_VACT_END_LO                  	0x13        // Display Vertical Active End LByte
#define SP_VDISP_VBG_END_HI         			0x14        // Display Vertical Background End HByte
#define SP_VDISP_VBG_END_LO          		    0x15        // Display Vertical Background End LByte
//Address: 2B-16~2B-1F Reserved
#define SP_VDISP_TIMING                        	0x20        // Display Clock Fine Tuning Register
#define SP_VDISP_OSD_REFERENCE_DEN    			0x21        // Position Of Reference DEN for OSD
#define SP_VDISP_NEW_DV_CONTROL                 0x22        // New DV Control Register
#define SP_VDISP_NEW_DV_DLY                    	0x23        // New DV Delay

//--------------------------------------------------
// FIFO Window Port (Address: 0x30; Data: 0x31)
//--------------------------------------------------
#define SP_FIFO_DWRWL_BSU_HI                   	0x00        // Display Window Read Width/Length HByte Before Scaling Up
#define SP_FIFO_DWRW_BSU_LO                    	0x01        // Display Window Read Width LByte Before Scaling Up
#define SP_FIFO_DWRL_BSU_LO                    	0x02        // Display Window Read Length LByte Before Scaling Up

//--------------------------------------------------
// Scale Up Port (Address: 0x32; Data: 0x33)
//--------------------------------------------------
#define SP_SU_HSCALE_FACTOR_HI                	0x00        // Horizontal Scale Up Factor HByte
#define SP_SU_HSCALE_FACTOR_MD                	0x01        // Horizontal Scale Up Factor MByte
#define SP_SU_HSCALE_FACTOR_LO                	0x02        // Horizontal Scale Up Factor LByte
#define SP_SU_VSCALE_FACTOR_HI                	0x03        // Vertical Scale Up Factor HByte
#define SP_SU_VSCALE_FACTOR_MD                	0x04        // Vertical Scale Up Factor MByte
#define SP_SU_VSCALE_FACTOR_LO                	0x05        // Vertical Scale Up Factor LByte
#define SP_SU_HFACTOR_SEGMENT_1PIXEL_HI        	0x06        // Horizontal Scale Up Factor Segment 1 Pixel HByte
#define SP_SU_HFACTOR_SEGMENT_1PIXEL_LO        	0x07        // Horizontal Scale Up Factor Segment 1 Pixel LByte
#define SP_SU_HFACTOR_SEGMENT_2PIXEL_HI        	0x08        // Horizontal Scale Up Factor Segment 2 Pixel HByte
#define SP_SU_HFACTOR_SEGMENT_2PIXEL_LO        	0x09        // Horizontal Scale Up Factor Segment 2 Pixel LByte
#define SP_SU_HFACTOR_SEGMENT_3PIXEL_HI        	0x0A        // Horizontal Scale Up Factor Segment 3 Pixel HByte
#define SP_SU_HFACTOR_SEGMENT_3PIXEL_LO        	0x0B        // Horizontal Scale Up Factor Segment 3 Pixel LByte
#define SP_SU_HFACTOR_DELTA_1PIXEL_HI          	0x0C        // Horizontal Scale Up Factor DELTA 1 Pixel HByte
#define SP_SU_HFACTOR_DELTA_1PIXEL_LO         	0x0D        // Horizontal Scale Up Factor DELTA 1 Pixel LByte
#define SP_SU_HFACTOR_DELTA_2PIXEL_HI         	0x0E        // Horizontal Scale Up Factor DELTA 2 Pixel HByte
#define SP_SU_HFACTOR_DELTA_2PIXEL_LO          	0x0F        // Horizontal Scale Up Factor DELTA 2 Pixel LByte
#define SP_SU_HCOEF_INIT_VALUE                	0x10        // Accumulate Horizontal Filter Coefficient Initial Value
#define SP_SU_VCOEF_INIT_VALUE                	0x11        // Accumulate Vertical Filter Coefficient Initial value


//--------------------------------------------------
// Sync Processor Port and Macro Vision (Address: 0x5C; Data: 0x5D)
//--------------------------------------------------
#define SP_SYNC_G_CLAMP_STA                 	0x00        // G/Y Channle Clamp Signal Output Start
#define SP_SYNC_G_CLAMP_END                   	0x01        // G/Y Channle Clamp Signal Output End
#define SP_SYNC_BR_CLAMP_STA             		0x02        // B/Pb & R/Pr Channle Clamp Signal Output Start
#define SP_SYNC_BR_CLAMP_END                  	0x03        // B/Pb & R/Pr Channle Clamp Signal Output End
#define SP_SYNC_CLAMP_CONTROL0                 	0x04        // Clamp Signal Control Register 0
#define SP_SYNC_CLAMP_CONTROL1                 	0x05        // Clamp Signal Control Register 1
#define SP_SYNC_CLAMP_CONTROL2                 	0x06        // Clamp Signal Control Register 2
#define SP_SYNC_CAPTURE_WINDOW_SET       	    0x07        // Capture Window Setting
#define SP_SYNC_DETECT_TOLERANCE_SET      		0x08        // Detection Tolerance Setting
//Address: 5D-08~5D-0F Reserved
#define SP_SYNC_MV_CONTROL              		0x10        // Macro Vision Control Register
#define SP_SYNC_MV_STA_LINE_EVEN         		0x11        // Macro Vision Start Line in Even Field
#define SP_SYNC_MV_END_LINE_EVEN              	0x12        // Macro Vision End Line in Even Field
#define SP_SYNC_MV_STA_LINE_ODD           	    0x13        // Macro Vision Start Line in Odd Field
#define SP_SYNC_MV_END_LINE_ODD               	0x14        // Macro Vision End Line in Odd Field


//--------------------------------------------------
// Hightlight Window Port (Address: 0x60; Data: 0x61)
//--------------------------------------------------
#define SP_HW_HSTA_HI                       	0x00        // Highlight Window Horizontal Start HByte
#define SP_HW_HSTA_LO                       	0x01        // Highlight Window Horizontal Start LByte
#define SP_HW_HEND_HI                         	0x02        // Highlight Window Horizontal End HByte
#define SP_HW_HEND_LO                         	0x03        // Highlight Window Horizontal End LByte
#define SP_HW_VSTA_HI                       	0x04        // Highlight Window Vertical Start HByte
#define SP_HW_VSTA_LO                       	0x05        // Highlight Window Vertical Start LByte
#define SP_HW_VEND_HI                         	0x06        // Highlight Window Vertical End HByte
#define SP_HW_VEND_LO                         	0x07        // Highlight Window Vertical End LByte
#define SP_HW_BORDER_WIDTH                    	0x08        // Highlight Window Border Width
#define SP_HW_BORDER_COLOR_RED                 	0x09        // Highlight Window Border Red Color HI 6bit (Red Color 2-bit LO = 00)
#define SP_HW_BORDER_COLOR_GRN                 	0x0A        // Highlight Window Border Green Color HI 6bit (Red Color 2-bit LO = 00)
#define SP_HW_BORDER_COLOR_BLU                 	0x0B        // Highlight Window Border Blue Color HI 6bit (Red Color 2-bit LO = 00)
#define SP_HW_WINDOW_CONTROL0                  	0x0C        // Highlight Window Control Register0
#define SP_HW_WINDOW_CONTROL1                  	0x0D        // Highlight Window Control Register1

//--------------------------------------------------
// Contrast/Brightness Coefficient Port (Address: 0x64; Data: 0x65)
//--------------------------------------------------
#define SP_CB_BRI_RED_COEF_A                   	0x00        // Brightness Red Coefficient Set.A
#define SP_CB_BRI_GRN_COEF_A                   	0x01        // Brightness Green Coefficient Set.A
#define SP_CB_BRI_BLU_COEF_A                   	0x02        // Brightness Blue Coefficient Set.A
#define SP_CB_CTS_RED_COEF_A                   	0x03        // Contrast Red Coefficient Set.A
#define SP_CB_CTS_GRN_COEF_A                   	0x04        // Contrast Green Coefficient Set.A
#define SP_CB_CTS_BLU_COEF_A                   	0x05        // Contrast Blue Coefficient Set.A
#define SP_CB_BRI_RED_COEF_B                   	0x06        // Brightness Red Coefficient Set.B
#define SP_CB_BRI_GRN_COEF_B                   	0x07        // Brightness Green Coefficient Set.B
#define SP_CB_BRI_BLU_COEF_B                   	0x08        // Brightness Blue Coefficient Set.B
#define SP_CB_CTS_RED_COEF_B                   	0x09        // Contrast Red Coefficient Set.B
#define SP_CB_CTS_GRN_COEF_B                   	0x0A        // Contrast Green Coefficient Set.B
#define SP_CB_CTS_BLU_COEF_B                   	0x0B        // Contrast Blue Coefficient Set.B

//--------------------------------------------------
// Timing Controller Port, Dot Masking and LVDS (Address: 0x8B; Data: 0x8C)
//--------------------------------------------------
#define SP_TCON_CONTROL0                       	0x00        // Timing Controller Control Register0
#define SP_TCON_CONTROL1                       	0x01        // Timing Controller Control Register1
#define SP_TCON_PIXEL_THRESHOLD_HI         		0x02        // Pixel Threshold High Value for Smart Polarity
#define SP_TCON_PIXEL_THRESHOLD1_LO        		0x03        // 2 Line Sum of Difference Threshold 1 Value: bit [7:0], ie:TH1 (Also refer to CR8C-02[7])
#define SP_TCON_PIXEL_THRESHOLD2_LO        		0x04        // 2 Line Sum of Difference Threshold 2 Value: bit [7:0], ie:TH2 (Also refer to CR8C-02[6])
#define SP_TCON_LINE_THRESHOLD                	0x05        // Line Threshold Value for Smart Polarity
//Address: 8C-06~8C-07 Reserved to 0
#define SP_TCON0_VSTA_LO               	        0x08        // TCON[0] Vertical Start LO Register
#define SP_TCON0_VSE_HI                     	0x09        // TCON[0] Vertical Start/End HI Register
#define SP_TCON0_VEND_LO                    	0x0A        // TCON[0] Vertical End LO Register
#define SP_TCON0_HSTA_LO                     	0x0B        // TCON[0] Horizontal Start LO Register
#define SP_TCON0_HSE_HI                      	0x0C        // TCON[0] Horizontal Start/End HI Register
#define SP_TCON0_HEND_LO                     	0x0D        // TCON[0] Horizontal End LO Register
#define SP_TCON0_CONTROL                    	0x0E        // TCON[0] Control Register
//#define SP_TCON0_RESERVED                    	0x0F        // TCON[0] Reserved Register(TCON[0]~TCON[9] Have This Register)
#define SP_TCON1_VSTA_LO                    	0x10        // TCON[13] Vertical Start LO Register
#define SP_TCON2_VSTA_LO                     	0x18        // TCON[13] Vertical Start LO Register
#define SP_TCON3_VSTA_LO                    	0x20        // TCON[13] Vertical Start LO Register
#define SP_TCON4_VSTA_LO                     	0x28        // TCON[13] Vertical Start LO Register
#define SP_TCON5_VSTA_LO               	        0x30        // TCON[13] Vertical Start LO Register
#define SP_TCON6_VSTA_LO                     	0x38        // TCON[13] Vertical Start LO Register
#define SP_TCON7_VSTA_LO                     	0x40        // TCON[13] Vertical Start LO Register
#define SP_TCON8_VSTA_LO                     	0x48        // TCON[13] Vertical Start LO Register
#define SP_TCON9_VSTA_LO                     	0x50        // TCON[13] Vertical Start LO Register
#define SP_TCON10_VSTA_LO           	    	0x58        // TCON[13] Vertical Start LO Register
#define SP_TCON11_VSTA_LO             	    	0x60        // TCON[13] Vertical Start LO Register
#define SP_TCON12_VSTA_LO             	    	0x68        // TCON[13] Vertical Start LO Register
#define SP_TCON13_VSTA_LO             	    	0x70        // TCON[13] Vertical Start LO Register
//TCON[0]:08~0F    //TCON[1]:10~17    //TCON[2]:18~1F   //TCON[3]:20~27    //TCON[4]:28~2F
//TCON[5]:30~37    //TCON[6]:38~3F    //TCON[7]:40~47   //TCON[8]:48~4F    //TCON[9]:50~57
//TCON[10]:58~5F   //TCON[11]:60~67   //TCON[12]:68~6F  //TCON[13]:70~77

#define SP_TCON10_DOT_MASK_CONTROL          	0x5F        // TCON[10] Dot Masking Control Register
#define SP_TCON11_DOT_MASK_CONTROL          	0x67        // TCON[11] Dot Masking Control Register
#define SP_TCON12_DOT_MASK_CONTROL          	0x6F        // TCON[12] Dot Masking Control Register
#define SP_TCON13_DOT_MASK_CONTROL          	0x77        // TCON[13] Dot Masking Control Register
//Address: 8C-78~8C-9F Reserved

#define SP_LVDS_CONTROL0                    	0xA0        // LVDS Control Register0
#define SP_LVDS_CONTROL1                    	0xA1        // LVDS Control Register1
#define SP_LVDS_CONTROL2                    	0xA2        // LVDS Control Register2
#define SP_LVDS_CONTROL3                    	0xA3        // LVDS Control Register3
#define SP_LVDS_CONTROL4                    	0xA4        // LVDS Control Register4
#define SP_LVDS_CONTROL5                    	0xA5        // LVDS Control Register5


#define SP_RSDS_OUTPUT_CONTROL0               	0xC0        // RSDS Output Control Register
#define SP_RSDS_INTERLEAVING_HI              	0xC1        // RSDS Display Data Bus Interleaving Line Buffer Length High Byte
#define SP_RSDS_INTERLEAVING_LO             	0xC2        // RSDS Display Data Bus Interleaving Line Buffer Length Low Byte
//Address: 8C-A6~8C-BF Reserved

//--------------------------------------------------
// ICM Port (Address: 0xD2; Data: 0xD3; Page: 0x7)
//--------------------------------------------------
#define SP7_ICM_MASTER_HUE_HI                   0x00        // High Byte Of Master Hue For Chroma Modifier N
#define SP7_ICM_MASTR_HUE_LO                    0x01        // Low Byte Of Master Hue For Chroma Modifier N
#define SP7_ICM_HUE_SET                        	0x02        // ICM HUE Setting
#define SP7_ICM_U_OFFSET                       	0x03        // U Offset 00, -128~127
#define SP7_ICM_V_OFFSET                       	0x04        // V Offset 00, -128~127
// From E3-0x03 To E3-0x32 Is U/V Offset

//--------------------------------------------------
// HDCP Acess Port (Address: 0xC3; Data: 0xC4; Page: 0x2)
//--------------------------------------------------
#define SP2_HDCP_FRAME_COUNTER              	0xC0        // HDCP Frame Counter Register
#define SP2_HDCP_SYS_INFO                   	0xC1        // HDCP System Information Register

//--------------------------------------------------
// HDMI Acess Port (Address: 0xC9; Data: 0xCA; Page: 0x2)
//--------------------------------------------------
//Port C9&CA Referance To Specification
//Following Register is Assigned By Port CD&CE
#define SP2_HDMI_SCR                        	0x00        // HDMI Switch Control Register
#define SP2_HDMI_NR                          	0x01        // HDMI N Value Register
#define SP2_HDMI_BCHCR                      	0x02        // HDMI BCH Control Register
#define SP2_HDMI_AFCR                        	0x03        // HDMI Audio FIFO Control Register
#define SP2_HDMI_AFSR                       	0x04        // HDMI Audio FIFO BIST Start Register
#define SP2_HDMI_MGCR0                      	0x05        // HDMI Maunal Gain Control Register0
#define SP2_HDMI_MGCR1                       	0x06        // HDMI Maunal Gain Control Register1
//Address: P2-CE-07 ~ P2-CE-0F Reserved
#define SP2_HDMI_CMCR                        	0x10        // HDMI Input Clock MUX Control Register
#define SP2_HDMI_MCAPR                       	0x11        // HDMI M code
#define SP2_HDMI_SCAPR                       	0x12        // HDMI S code
#define SP2_HDMI_DCAPR0                      	0x13        // HDMI D code HByte
#define SP2_HDMI_DCAPR1                     	0x14        // HDMI D code LByte
#define SP2_HDMI_PSCR                        	0x15        // HDMI Phase Tracking Enable Control Register
#define SP2_HDMI_FTR                         	0x1A        // HDMI Target Time For Summation Of One Trent To Decide The Trent
#define SP2_HDMI_FBR                         	0x1B        // HDMI Target FIFO Depth and Boundary Address Distance
#define SP2_HDMI_ICTPSR1                     	0x21        // HDMI I Code of Trend
#define SP2_HDMI_ICBPSR1                     	0x25        // HDMI I Code of Boundary
#define SP2_HDMI_PCBPSR0                     	0x26        // HDMI P Code of Boundary HByte
#define SP2_HDMI_PCBPSR1                     	0x27        // HDMI P Code of Boundary LByte
#define SP2_HDMI_NTX1024TR0                  	0x28        // HDMI Masure the length of 1024 TV by Crystal
#define SP2_HDMI_STBPR                       	0x2A        // HDMI Boundary Tracking Update Response Time
#define SP2_HDMI_AAPNR                       	0x2D        // HDMI Phase Swallow Enable Control Register
#define SP2_HDMI_AVMCR                       	0x30        // HDMI Audio/Video Mute Control Register
#define SP2_HDMI_WDCR0                       	0x31        // HDMI Watch Dog Control Register0
#define SP2_HDMI_WDCR1                       	0x32        // HDMI Watch Dog Control Register1
#define SP2_HDMI_DBCR                        	0x34        // HDMI Auto Load Double Buffer Enable
#define SP2_HDMI_DPCR0                       	0x38        // HDMI DPLL Control Register0
#define SP2_HDMI_DPCR1                       	0x39        // HDMI DPLL Control Register1
#define SP2_HDMI_DPCR3                       	0x3B        // HDMI DPLL Control Register3
#define SP2_HDMI_VWDSR                       	0x41        // HDMI Video Watch Dog For Packet Variation Status
#define SP2_HDMI_PVGCR0                      	0x45        // HDMI Packet Variation Status Enable Control Register0
#define SP2_HDMI_VCR                         	0x50        // HDMI Video Mode Control Register
#define SP2_HDMI_ACRCR                       	0x51        // HDMI Color Space Control Register0
#define SP2_HDMI_ACRSR0                      	0x52        // HDMI CTS in usage Register(CTS[19:12])
#define SP2_HDMI_AOCR                        	0x62        // HDMI SPDIF/I2S Switch Control Register

//--------------------------------------------------
// Dynamic contrast control Access (Address: 0xC9; Data: 0xCA; Page: 0x7)
// Page 0 (For Histogram / Ymin-max / Soft-Clamping / Scene-Change)
//--------------------------------------------------
#define SP7_DCC_P0_NOR_FACTOR_HI                0x00        // DCC Normalized Factor HByte
#define SP7_DCC_P0_NOR_FACTOR_MD                0x01        // DCC Normalized Factor MByte
#define SP7_DCC_P0_NOR_FACTOR_LO                0x02        // DCC Normalized Factor LByte
#define SP7_DCC_P0_BBE_CONTROL                  0x03        // DCC Black Background Exception Control Register
#define SP7_DCC_P0_NFLT_CONTROL                	0x04        // DCC Noise Filter Control Register
#define SP7_DCC_P0_HIST_CONTROL                 0x05        // DCC Histogram Control Register
#define SP7_DCC_P0_SOFT_CLAMP                  	0x06        // DCC Slope Of Soft Clamping
#define SP7_DCC_P0_Y_MAX_LOW_BOUND             	0x07        // DCC Lower Bound Of Y_MAX
#define SP7_DCC_P0_Y_MIN_HIGH_BOUND           	0x08        // DCC Higher Bound Of Y_MIN
#define SP7_DCC_P0_SCG_PERIOD                  	0x09        // DCC Scene Change Mode Period
#define SP7_DCC_P0_SCG_LOW_BOUND              	0x0A        // SCG_DIFF Lower Bound For Exiting Scene Change Mode
#define SP7_DCC_P0_SCG_HIGH_BOUND              	0x0B        // SCG_DIFF Higher Bound For Exiting Scene Change Mode
#define SP7_DCC_P0_POPUP_CONTROL               	0x0C        // DCC POP Up Status Register
#define SP7_DCC_P0_SCG_DIFF                    	0x0D        // (Histogram Difference Between Current Frame And Average)/8
#define SP7_DCC_P0_Y_MAX_VAL                   	0x0E        // Max{Y_MAX_LB,(Y Maximum In Current Frame/4)}
#define SP7_DCC_P0_Y_MIN_VAL                   	0x0F        // Min{Y_MIN_HB,(Y Minimum In Current Frame/4)}
#define SP7_DCC_P0_S0_VALUE                    	0x10        // Normalized Histogram S0 Value
#define SP7_DCC_P0_S1_VALUE                    	0x11        // Normalized Histogram S1 Value
#define SP7_DCC_P0_S2_VALUE                    	0x12        // Normalized Histogram S2 Value
#define SP7_DCC_P0_S3_VALUE                    	0x13        // Normalized Histogram S3 Value
#define SP7_DCC_P0_S4_VALUE                    	0x14        // Normalized Histogram S4 Value
#define SP7_DCC_P0_S5_VALUE                    	0x15        // Normalized Histogram S5 Value
#define SP7_DCC_P0_S6_VALUE                    	0x16        // Normalized Histogram S6 Value
//--------------------------------------------------
// Page 1 (for Y-Curve / WBL Expansion)
//--------------------------------------------------
#define SP7_DCC_P1_DEF_CRV01                   	0x00        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV02                   	0x01        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV03                   	0x02        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV04                   	0x03        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV05                   	0x04        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV06                   	0x05        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV07                   	0x06        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV08                   	0x07        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV09                   	0x08        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV10                   	0x09        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV11                   	0x0A        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV12                   	0x0B        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV13                   	0x0C        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV14                   	0x0D        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_DEF_CRV15                   	0x0E        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
#define SP7_DCC_P1_Y_BL_BIAS                   	0x0F        // Y Offset For Black Level Expansion
#define SP7_DCC_P1_Y_WL_BIAS                   	0x10        // Y Offset For While Level Expansion
#define SP7_DCC_P1_BLEND_UPPER_BOUND            0x11        // Upper Bound Of Blending Factor
#define SP7_DCC_P1_BLEND_LOWER_BOUND            0x12        // Lower Bound Of Blending Factor
#define SP7_DCC_P1_DEV_FACTOR              		0x13        // Deviation Weighting Factor
#define SP7_DCC_P1_BLEND_VAL                    0x14        // Blending Factor Value = Max{BLD    - [(DEV_VAL*DEV_FACTOR)/256], BLD_LB}
#define SP7_DCC_P1_DEV_VAL_HI                  	0x15        // Deviation Value HByte
#define SP7_DCC_P1_DEV_VAL_LO                  	0x16        // Deviation Value LByte
//--------------------------------------------------
// Page 2 (for Calculation Parameter)
//--------------------------------------------------
// E7-00 ~ E7-8F of Page2 is SRAM initial value
#define SP7_DCC_P3_SRAM                        	0x00        // SRAM Initial Value In Register 0x00
//--------------------------------------------------
// Page 3 (for Testing and Debug)
//--------------------------------------------------
#define SP7_DCC_P3_SRAM_BIST                   	0x00        // DCC SRAM BIST Control Register