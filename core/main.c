#include <stdint.h>
#include <stdio.h>

#include "config/board_config.h"
#include "config/panel_config.h"
#include "config/misc_config.h"

#include "scaler/scaler.h"
#include "scaler/scaler_registers.h"
#include "scaler/scaler_access.h"
#include "scaler/measure.h"
#include "scaler/scaling.h"

#include "peripherals/pins.h"
#include "peripherals/xsfr.h"
#include "peripherals/timer.h"
#include "peripherals/ddc.h"

#include "interfaces/hdmi.h"

#include "osd/osd.h"
#include "osd/osd_ui.h"

void main()
{
#   ifdef __SDCC
    XSFRWriteByte(WDT_CONTROL, 0x00); // Disable watchdog
    InitSysTimer();
    EA = 1;
#   endif

    // Upload EDID to DDC port 1
    UploadEDID(1, testEDID);

    // Display and backlight power
    SetGPIOShare(DISPLAY_POWER_ENABLE_PIN, PUSH_PULL_OUT);
    SetGPIO(DISPLAY_POWER_ENABLE_PIN, 1^!DISPLAY_POWER_ACTIVE_LEVEL);
    SetGPIOShare(BACKLIGHT_ENABLE_PIN, PUSH_PULL_OUT);
    SetGPIO(BACKLIGHT_ENABLE_PIN, 1^!BACKLIGHT_ENABLE_ACTIVE_LEVEL);

    // Display mirroring pins
    SetGPIOShare(MIRROR_HORIZONTAL_PIN, PUSH_PULL_OUT);
    SetGPIOShare(MIRROR_VERTICAL_PIN, PUSH_PULL_OUT);
    SetGPIO(MIRROR_HORIZONTAL_PIN, HOR_MIRRROR);
    SetGPIO(MIRROR_VERTICAL_PIN, VER_MIRRROR);

    InitScaler();
    SetOverlayColor(0xff, 0xff, 0x00);

    // On screen display example
    OSDInit();
    char* entries[]= { "scaling", "other" };
    OSDCreateMenu("Settings", entries, 2);
    SetOverlayColor(0x00, 0xff, 0xff);

    // Initialize first TMDS port
    InitHDMI(0);

    // Measure in digital mode
    MeasureSignal(1);
    // After digital measure InputMeasData.HSync = HActive - 1, InputMeasData.VTotal = VActive - 1
    uint32_t hact = InputMeasData.HSync + 1, vact = InputMeasData.VTotal + 1;

    // Scale up and/or down
    ScaleUp  (hact, vact, PANEL_H_ACTIVE, PANEL_V_ACTIVE);
    ScaleDown(hact, vact, PANEL_H_ACTIVE, PANEL_V_ACTIVE);

    // Adjust HStart, VStart, HDelay, VDelay if picture is shifted
    SetCaptureWindow(0, 0, hact, vact, 1, 1);
    SetFIFOWindow(hact, vact);

    // Measure in analog mode for Frequencies
    MeasureSignal(0);

    // Adjust display frequency manualy if picture flickering artifacts present
    // Magic formula Fdisplay = DisplayHTotal*InputHFreq*DisplayVActive/InputVActive
    SetDPLLFrequncy((PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE + PANEL_H_FRONT_PORCH) *
                    InputMeasData.HFreq / vact * PANEL_V_ACTIVE);

    #   ifdef __SDCC
        while(1);
    #   else
        getchar();
    #   endif
}

// Leftover junk
/*

    #include "alien/struct_.h"

    // InitComposite(2);

    // InitVGA();

    // ScalerWriteByte(S_SYNC_CONTROL, 0x06); // Select ADC Sync, Select SeperateHSync
    // SetCaptureWindow(216, 27, 800, 600, 0, 0);
    // SetFIFOWindow(1024, 600);
    // SetAPLLFrequncy(40000000UL, 1056);
    // ScaleUp(800, 600, 1024, 600);
    // Magic formula Fdisplay = DisplayHTotal*InputHFreq*DisplayVActive/InputVActive
    // ScalerWriteBit(SCALER_CONTROL, 4, 0b1); // Enable Full line buffer ?

    #ifndef __SDCC
    stModeInfo.IHWidth = 696;
    stModeInfo.IHStartPos = 141;
    stModeInfo.IHTotal = 858;
    stModeInfo.IHFreq = 157;
    stModeInfo.IVHeight = 232;
    stModeInfo.IVStartPos = 26;
    stModeInfo.IVTotal = 300;
    stModeInfo.IVFreq = 60;
    #endif*/