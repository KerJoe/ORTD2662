#include <stdint.h>
#include <stdbool.h>

#include "scaler/scaler.h"
#include "config/board_config.h"
#include "scaler/scaler_access.h"
#include "scaler/measure.h"
#include "peripherals/timer.h"

_INPUT_MEAS_DATA InputMeasData;

/*uint8_t MeasureResolution(bool isDigital)
{
    if (isDigital)
        ScalerWriteBit(S_SYNC_SELECT, 0, 0b1);

    ScalerWriteBit(S_STABLE_MEASURE, 0, 0b0);
    ScalerWriteBit(S_STABLE_MEASURE, 0, 0b1); // Start measurement

    Poll(10, !ScalerReadBit(S_STABLE_MEASURE, 0));

    ScalerWriteBit(S_STABLE_MEASURE, 1, 0b1); // Shift in the measured data

    INPUT_MEASUREMENT_DATA.HSPolarity = ScalerReadBit(S_STABLE_MEASURE, 6); // Get stable line polarity

    // TODO: Detect Sync type
}*/

int8_t MeasureSignal(bool isDigital)
{
    if (isDigital)
    {
        // HFreq and VFreq can only be calculated in comparision to RTD_FREQ
        // Thus we need to measure them in analog mode
        MeasureSignal(false);
        ScalerWriteBit(S_SYNC_SELECT, 0, 0b1);
    }
    else
        ScalerWriteBit(S_SYNC_SELECT, 0, 0b0);

    // Begin HSync, VSync measurement
    ScalerWriteBit(S_MEAS_HSYNC_PERIOD_HI, 5, 0b1);
    Poll(50, !ScalerReadBit(S_MEAS_HSYNC_PERIOD_HI, 5))
    {
        ScalerWriteBit(S_MEAS_HSYNC_PERIOD_HI, 5, 0b0); // Reset start bit
        return -1;
    }

    // Hsync, Vsync overflow test
    if (ScalerReadBit(S_MEAS_HSYNC_PERIOD_HI, 4) ||
        ScalerReadBit(S_MEAS_VSYNC_PERIOD_HI, 4) ||
        ScalerReadBit(S_MEAS_VSYNC_PERIOD_HI, 5))
    {
        return -2;
    }

    ScalerWriteBit(S_MEAS_HSYNC_PERIOD_HI, 6, 0b1); // Shift in the measured data
    InputMeasData.HTotal = (ScalerReadBits(S_MEAS_HSYNC_PERIOD_HI, 0, 4) << 8) | ScalerReadByte(S_MEAS_HSYNC_PERIOD_LO);
    InputMeasData.VTotal = (ScalerReadBits(S_MEAS_VSYNC_PERIOD_HI, 0, 4) << 8) | ScalerReadByte(S_MEAS_VSYNC_PERIOD_LO);
    ScalerWriteBit(S_MEAS_HSYNC_VSYNC_HIGH_PERIOD_SELECT, 0, 0b0); // Read HSYNC High period measurement result
    InputMeasData.HSync = (ScalerReadBits(S_MEAS_HSYNC_VSYNC_HIGH_PERIOD_HI, 4, 4) << 8) | ScalerReadByte(S_MEAS_HSYNC_VSYNC_HIGH_PERIOD_LO);
    ScalerWriteBit(S_MEAS_HSYNC_VSYNC_HIGH_PERIOD_SELECT, 0, 0b1); // Read VSYNC High period measurement result
    InputMeasData.VSync = (ScalerReadBits(S_MEAS_HSYNC_VSYNC_HIGH_PERIOD_HI, 4, 4) << 8) | ScalerReadByte(S_MEAS_HSYNC_VSYNC_HIGH_PERIOD_LO);

    if (!isDigital)
        InputMeasData.HFreq = RTD_FREQ / InputMeasData.HTotal;
        InputMeasData.VFreq = RTD_FREQ / InputMeasData.HTotal / InputMeasData.VTotal;

    InputMeasData.HSPolarity = ScalerReadBit(S_MEAS_VSYNC_PERIOD_HI, 6);
    InputMeasData.VSPolarity = ScalerReadBit(S_MEAS_VSYNC_PERIOD_HI, 7);
}