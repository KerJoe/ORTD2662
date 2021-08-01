#include <stdint.h>
#include <stdio.h>

#include "config/board_config.h"

#include "interfaces/hdmi.h"
#include "peripherals/ddc.h"
#include "peripherals/timer.h"
#include "scaler/scaler_tables.h"

uint8_t ucHdmiAVMuteCnt = 0;

const uint8_t tHDMI_YPBPR_ITU601[] =
{
    // 9CH
    18, AUTOINC_DIS,    S_YUV_RGB_COEF_DATA,        0x04,0x00,0x00,0x00,0x05,0x9b,
                                                    0x04,0x00,0xfe,0xaa,0xfd,0x25,
                                                    0x04,0x00,0x07,0x16,0x00,0x00,
    TABLE_END
};

const uint8_t tHDMI_YPBPR_ITU709[] =
{
    // 9CH
    18, AUTOINC_DIS,    S_YUV_RGB_COEF_DATA,        0x04,0x00,0x00,0x00,0x06,0x4b,
                                                    0x04,0x00,0xff,0x41,0xfe,0x20,
                                                    0x04,0x00,0x07,0x6c,0x00,0x00,
    TABLE_END
};

uint8_t CHdmiFormatDetect(void)
{
    ScalerWriteByte(S_PAGE_SELECT, 2);

    if((ScalerReadByte(S2_HDMI_STATUS) & 0x01) == 0x01) //Input source is the HDMI format.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t CHdmiVideoSetting(void)
{
	printf("Enter CHdmiVideoSetting\n", 0);
    ScalerWriteByte(S_PAGE_SELECT, 2);
    ScalerWritePortBits(S2_HDMI_PORT, SP2_HDMI_SCR, 0, 2, 0b10);	// Set HDMI/DVI decide condition//731301
    delayMS(50);//731301

   	if(CHdmiFormatDetect())//Input source is the HDMI format.
    {
        ///SET_HDMIINPUT();

        ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 2, 2, 0b00);
        ScalerWritePortBit(S2_HDMI_PORT, SP2_HDMI_ACRCR, 2, 0b1); // Enable Pixel Repetition down sampling auto mode

        //CScalerSetDataPortByte(_P2_HDCP_ADDR_PORT_C3, 0x40, 0x93);//Change to HDCP1.1 for HDMI
        ScalerWritePortByte(S2_HDCP_PORT, 0x40, 0x91);// Change to HDCP1.0 for DVI

        //HDMI Video & Audio Part
        ScalerWriteBits(S2_HDMI_STATUS, 2, 2, 0b11);
        ScalerWriteBit (S2_HDMI_STATUS, 5, 0b1);
    	delayMS(100);
        if(!(ScalerReadByte(S2_HDMI_STATUS) & 0x40))
        {//For Clear_AVMute
            ///SET_AVRESUME();//Audio WD can't action, when Set_AVMute happen.
            ///CAdjustDisableHDMIWatchDog(_WD_SET_AVMUTE_ENABLE);//Disable Set_AVMute Watch Dog //731301
            ScalerWritePortBit(S2_HDMI_PORT, SP2_HDMI_AVMCR, 3, 0b1);//Enable DVI/HDMI video output
            ///CAdjustEnableHDMIWatchDog(_WD_SET_AVMUTE_ENABLE);//Enable Set_AVMute Watch Dog //731301
        }
        else
        {//For AV_Mute Delay
            delayMS(100);
            ///CLR_AVRESUME();
            return 0;
        }
		///SET_VIDEOMODECHANGE();//check color space everytimes
		//HDMI Video Part
        if(((ScalerReadByte(S2_HDMI_GPVS) & 0x01)) || 1/*GET_VIDEOMODECHANGE()*/)//For HDMI switch between RGB/YCbCr
        {
            ///CLR_VIDEOMODECHANGE();
            ScalerWriteBit(S2_HDMI_GPVS, 0, 0b1);
            if((ScalerReadPortByte(S2_HDMI_PACKET_PORT, 0x00) & 0x23) == 0)//Check BCH data(Package error flag)
            {
                ///CScalerGetDataPortByte(_P2_HDMI_PSAP_CD, 0x04, 2, pData, _NON_AUTOINC);
                ///if((bit)(pData[0] & 0x40) != (bit)(pData[0] & 0x20))//For HDMI switch between RGB/YUV
                uint8_t pack4 = ScalerReadPortByte(S2_HDMI_PACKET_PORT, 0x00);
                uint8_t pack5 = ScalerReadPortByte(S2_HDMI_PACKET_PORT, 0x00);
                if(((pack4 & 0x40)>0) != ((pack4 & 0x20)>0))//For HDMI switch between RGB/YUV
                {
					if((pack4&0x20)==0x20)	//422
					{
						ScalerWriteByte(S_PAGE_SELECT, 6);
						ScalerWriteBit(S6_YUV422_TO_YUV444, 7, 0b1);//enable
					}

                    if((pack5 & 0xc0) != 0xc0)//For HDMI switch between ITU601/ITU709
                    {
                        ScalerWriteByte(S_YUV_TO_RGB_CONTROL, 0x08);

                        if((pack5 & 0x40))
                        {
                        	printf("\n ITU601%c ",0x20);
                            ScalerWriteTable(tHDMI_YPBPR_ITU601);
                        }
                        else
                        {
                        	printf("\n ITU709%c ",0x20);
                            ScalerWriteTable(tHDMI_YPBPR_ITU709);
                        }
                        ScalerWriteByte(S_YUV_TO_RGB_CONTROL, 0x05);
                    }
                }
                else if(!(pack4 & 0x60))
                {
                    ScalerWriteByte(S_YUV_TO_RGB_CONTROL, 0x00);
                }
            }
        }
    }
    else
    {
        ///CLR_HDMIINPUT();
        ScalerWritePortBit(S2_HDMI_PORT, SP2_HDMI_ACRCR, 2, 0b0); //Disable Pixel Repetition down sampling auto mode
        ScalerWritePortBits(S2_HDMI_PORT, SP2_HDMI_VCR, 0, 4, 0b0000);
        ///CAdjustDisableHDMIWatchDog(_WD_HDMI_ALL);
        ScalerWritePortBit(S2_HDMI_PORT, SP2_HDMI_AVMCR, 3, 0b1); //Enable DVI/HDMI video output
        ScalerWritePortByte(S2_HDMI_PORT, 0x40, 0x91);// Change to HDCP1.0 for DVI
        ScalerWriteByte(S_YUV_TO_RGB_CONTROL, 0x00);
    }
    return 1;
}

uint8_t CSourceScanInputPortDVI(uint8_t ucPar)
{
    printf("Enter CSourceScanInputPortDVI\n");
	ScalerWriteByte(S_PAGE_SELECT, 2);
    if((ScalerReadByte(S2_HDMI_STATUS) & 0x40) && (ScalerReadByte(S2_TMDS_CONTROL) & 0xF8))
	{
		ucHdmiAVMuteCnt++;
		if(ucHdmiAVMuteCnt == 20)
		{
            ScalerWritePortBits(S2_HDMI_PORT, SP2_HDMI_SCR, 2, 2, 0b10);	//Set HDMI/DVI switch mode(manual,DVI)//Alanli20070801
			delayMS(200);
			ScalerWritePortBits(S2_HDMI_PORT, SP2_HDMI_SCR, 2, 2, 0b00);	//Set HDMI/DVI switch mode(auto)
			ucHdmiAVMuteCnt = 0;
		}
		printf("Exit CSourceScanInputPortDVI: FALSE 0\n\n", 0);
		return 0;
	}

    ScalerWriteByte(S_PAGE_SELECT, 2);
    ScalerWriteBits(S_SYNC_CONTROL, 0, 2, 0b00); // HSYNC/VSYNC Source: TMDS
    ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 0, 2, 0b11);
    ScalerWriteBit(S2_UP_DOWN_CONTROL0, 7, 0b1);

	ScalerWriteBit(S_IFW_HACT_LEN_HI, 3, 0b1);												//TMDS/Video8:TMDS

    ScalerWriteBit(S2_TMDS_MEAS_RESULT0, 1, 0b0);
    ScalerWriteBit(S2_HDCP_DATA_CONTROL, 1, 0); //  DDC is 2
    // R/B swap & P/N Swap
    ScalerWriteBits(S2_POWER_ON_OFF_CONTROL, 5, 2, 0b11);

	ScalerWriteBit(S2_HDCP_CONTROL, 0, 0b1);

	ScalerWriteByte(S_PAGE_SELECT, 2);

   	if(ucPar == 1)
		ScalerWriteBit(S2_POWER_ON_OFF_CONTROL, 7, 0b1);
	else
		ScalerWriteBit(S2_POWER_ON_OFF_CONTROL, 7, 0b0);

	uint8_t udc1 = ScalerReadByte(S2_UP_DOWN_CONTROL1); // CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);
    printf("udc1: %x\n", udc1);
	udc1 &= 0xf0;
  	/*if(pData[0] == 0xe0)
    	CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x20);
    else if((pData[0] == 0x80) | (pData[0] == 0x60) | (pData[0] == 0x10))
		CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x24);
	else if((pData[0] == 0x40) | (pData[0] == 0x30))
       	CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x2b);
	else
       	CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x24);*/

    if(udc1 == 0xe0)
        ScalerWriteByte(S2_RGB_PLL_SETTING, 0x24);
    else if((udc1 == 0x80) || (udc1 == 0x60) || (udc1 == 0x10))
        ScalerWriteByte(S2_RGB_PLL_SETTING, 0x2c);
    else if((udc1 == 0x40) || (udc1 == 0x30))
        ScalerWriteByte(S2_RGB_PLL_SETTING, 0x30);
    else
    {
        printf("Exit CSourceScanInputPortDVI: FALSE 2\n\n", 0);
        return 0;
    }

	if(udc1 == 0xe0)
		ScalerWriteByte(S2_ADAPTIVE_EQUALIZER2, 0x01);
	else
		ScalerWriteByte(S2_ADAPTIVE_EQUALIZER2, 0x00);

    // EricLee for ATI9250,ATI9550
	ScalerWriteBit(S2_ANALOG_BIAS_CONTROL, 5, 0b0);
	ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 2, 2, 0b00);
	if(0)//_GET_INPUT_SOURCE() == _SOURCE_DVI)
    	ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 4, 3, 0b001);
    else if (1)//_GET_INPUT_SOURCE() == _SOURCE_HDMI)
    {
    	ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 4, 3, 0b111);
    }
    else
    {
    	ScalerWriteBit(S2_ANALOG_BIAS_CONTROL, 5, 0b1);
    	ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 2, 2, 0x00);
    	ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 4, 3, 0b111);
    }

	for(uint8_t cnt0 = 0; cnt0 < 2; cnt0++)
	{
		for(uint8_t cnt1 = 0; cnt1 < 2; cnt1++)
		{
			ScalerWriteByte(S2_TMDS_CONTROL, 0xf8);
			delayMS(25);

			uint8_t tmdsc = ScalerReadByte(S2_TMDS_CONTROL);

			if(ucPar == 1)
				tmdsc = ((tmdsc & 0xe0) == 0xe0) ? 1 : 0;
			else
				tmdsc = ((tmdsc & 0xf8) == 0xf8) ? 1 : 0;

			if(tmdsc)
			{
				udc1 = ScalerReadByte(S2_UP_DOWN_CONTROL1);
				udc1 &= 0xf0;

				if((udc1 == 0xe0) || (udc1 == 0x80) || (udc1 == 0x60) || (udc1 == 0x40) || (udc1 == 0x30))
 		        {
 					if(CHdmiFormatDetect())
 					{
                       	if(!CHdmiVideoSetting())
						    { printf("Exit CSourceScanInputPortDVI: FALSE 3\n\n", 0); return 0; }
 					}
					else
                    {
						CHdmiVideoSetting();
                    }
                    printf("Exit CSourceScanInputPortDVI: TRUE 4\n\n", 0);
					return 1;
				}
			}
                if(!CHdmiFormatDetect())
			        ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 2, 2, 0b01);
        	}

        ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 4, 3, 0b001);
        ScalerWriteBits(S2_ANALOG_COMMON_CONTROL2, 2, 2, 0b00);
	}
	printf("Exit CSourceScanInputPortDVI: FALSE 5\n\n", 0);
	return 0;
}

uint8_t __code ttSCALER_POWERUP_HDMI[] =
{
	1,  AUTOINC_DIS,    S_PAGE_SELECT,          2,
	8,  AUTOINC_ENA,    S2_TMDS_OUTPUT_CONTROL, 0x78, 0x6F, 0x03, 0x00, 0x70, 0x70, 0xe3, 0x24,
    TABLE_END
};

void InitHDMI()
{
    //ScalerWriteBit(S_HOST_CONTROL, 0, BIT_ONE);
    //delayMS(10); // Wait for at least 8ms
    //ScalerWriteBit(S_HOST_CONTROL, 0, BIT_ZERO);

    // TODO: Fix ScalerWriteTable with auto increment: do not update address.
    ScalerWriteTable(ttSCALER_POWERUP_HDMI);
    
    /*ScalerWriteByte(S_PAGE_SELECT, 2);
    EnableScalerAutoIncrement(1);
    SCALER_ADDRESS = S2_TMDS_OUTPUT_CONTROL;
    SCALER_DATA = 0x78;
    SCALER_DATA = 0x6f;
    SCALER_DATA = 0x03;
    SCALER_DATA = 0x00;
    SCALER_DATA = 0x70;
    SCALER_DATA = 0x70;
    SCALER_DATA = 0xe3;
    SCALER_DATA = 0x24;
    EnableScalerAutoIncrement(0);*/
    
//    UploadEDID(HDMI_DDC_NUMBER, testEDID);    
    //UploadEDID(HDMI_DDC_NUMBER, testEDID);
    //ScalerWriteTable(ttSCALER_POWERUP_HDMI);
    ScalerWriteBits(S_SYNC_CONTROL, 0, 2, 0b00); // Power on TMDS

    ScalerWriteBits(S_IFW_HV_DELAY, 0, 4, 0b0000);
    ScalerWriteBits(S_VGIP_CONTROL, 2, 2, 0b01); // Input Format - Digital (TMDS)
    ScalerWriteBit (S_VGIP_CONTROL, 0, 0b1);      // Sampling input pixels enable

    #define WINDOW_HSTA 2
    #define WINDOW_VSTA 6
    #define WINDOW_HS_DELAY 30
    #define WINDOW_VS_DELAY 30
    #define WINDOW_HLEN 1024
    #define WINDOW_VLEN 600

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

    ScalerWriteBits(S_IFW_VACT_STA_HI, 6, 2, 0b00); // Video 8 Source - TMDS // ?

//    CSourceScanInputPortDVI(0);

    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRWL_BSU_HI, (((WINDOW_HLEN) >> 8) << 4) | ((WINDOW_VLEN) >> 8));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRW_BSU_LO,  (WINDOW_HLEN));
    ScalerWritePortByte(S_FIFO_WIN_PORT, SP_FIFO_DWRL_BSU_LO,  (WINDOW_VLEN));

    ScalerWriteBits(S_VGIP_CONTROL, 2, 2, 0b01); // Input Format - Digital (TMDS)
    ScalerWriteBit (S_VGIP_CONTROL, 0, 0b1);      // Sampling input pixels enable

    ScalerWriteBit (S_IFW_VACT_STA_HI, 4, 0b0); // Video 8
    ScalerWriteBits(S_IFW_VACT_STA_HI, 6, 2, 0b00); // Video 8 Source - TMDS // ?

    ScalerWriteBit(S_SYNC_SELECT, 0, 0b1);


    ScalerWriteByte(S_PAGE_SELECT, 2);
    ScalerWriteTable(tSCALER_POWERUP_HDMI);
    ScalerWriteByte(S_PAGE_SELECT, 2);

    ScalerWritePortBits(S2_HDMI_PORT, SP2_HDMI_SCR, 2, 2, 0b10);	//Set HDMI/DVI switch mode(manual,DVI)//Alanli20070801
    delayMS(200);
    ScalerWritePortBits(S2_HDMI_PORT, SP2_HDMI_SCR, 2, 2, 0b00);	//Set HDMI/DVI switch mode(auto)


    ScalerWriteBit(S_VGIP_CONTROL, 0, 0b1); // Enable video capture

    ScalerWriteBit (S_VDISP_CONTROL, 3, 0b1);
    ScalerWriteBit (S_VDISP_CONTROL, 5, 0b0);

    ScalerWriteByte(S_PAGE_SELECT, 8);
    ScalerWriteBit(S8_VIDEO_RESET, 0, 0b1);
    delayMS(20);
    ScalerWriteBit(S8_VIDEO_RESET, 0, 0b0);
}