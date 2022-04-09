#include <stdint.h>

#include "peripherals/pins.h"
#include "core/misc.h"

const _PIN_SHARE_GPIO_STRUCT PIN_SHARE_GPIO_STRUCT[] =
{
    { PIN_SHARE_NUMBER( 1), 3, 3 },   // GPIO10
    { PIN_SHARE_NUMBER( 1), 0, 3 },   // GPIO11
    { PIN_SHARE_NUMBER( 2), 3, 3 },   // GPIO12
    { PIN_SHARE_NUMBER( 2), 0, 3 },   // GPIO13
    { PIN_SHARE_NUMBER( 5), 4, 3 },   // GPIO14
    { PIN_SHARE_NUMBER( 3), 3, 3 },   // GPIO15
    { PIN_SHARE_NUMBER( 3), 0, 3 },   // GPIO16
    { PIN_SHARE_NUMBER( 5), 0, 4 },   // GPIO17
    { PIN_SHARE_NUMBER( 0), 5, 2 },   // GPIO30
    { PIN_SHARE_NUMBER( 0), 3, 2 },   // GPIO31
    { PIN_SHARE_NUMBER(11), 4, 3 },   // GPIO32
    { PIN_SHARE_NUMBER(11), 0, 3 },   // GPIO33
    { PIN_SHARE_NUMBER(12), 4, 3 },   // GPIO34
    { PIN_SHARE_NUMBER(12), 0, 3 },   // GPIO35
    { PIN_SHARE_NUMBER(13), 4, 3 },   // GPIO36
    { PIN_SHARE_NUMBER(13), 0, 3 },   // GPIO37
    { PIN_SHARE_NUMBER( 6), 3, 3 },   // GPIO52
    { PIN_SHARE_NUMBER( 6), 0, 3 },   // GPIO53
    { PIN_SHARE_NUMBER( 9), 6, 2 },   // GPIO54
    { PIN_SHARE_NUMBER( 7), 3, 3 },   // GPIO55
    { PIN_SHARE_NUMBER( 7), 0, 3 },   // GPIO56
    { PIN_SHARE_NUMBER( 9), 3, 3 },   // GPIO57
    { PIN_SHARE_NUMBER( 0), 0, 3 },   // GPIO60
    { PIN_SHARE_NUMBER( 1), 6, 2 },   // GPIO61
    { PIN_SHARE_NUMBER( 2), 6, 2 },   // GPIO62
    { PIN_SHARE_NUMBER( 3), 6, 2 },   // GPIO63
    { PIN_SHARE_NUMBER( 6), 6, 2 },   // GPIO64
    { PIN_SHARE_NUMBER( 4), 5, 3 },   // GPIO65
    { PIN_SHARE_NUMBER( 4), 2, 2 },   // GPIO66
    { PIN_SHARE_NUMBER( 4), 0, 2 },   // GPIO67
    { PIN_SHARE_NUMBER(14), 6, 2 },   // GPIO70
    { PIN_SHARE_NUMBER(14), 4, 2 },   // GPIO71
    { PIN_SHARE_NUMBER(14), 2, 2 },   // GPIO72
    { PIN_SHARE_NUMBER(14), 0, 2 },   // GPIO73
    { PIN_SHARE_NUMBER(10), 1, 3 },   // GPIO74
    { PIN_SHARE_NUMBER(10), 4, 3 },   // GPIO75
    { PIN_SHARE_NUMBER( 8), 3, 3 },   // GPIO76
    { PIN_SHARE_NUMBER( 8), 0, 3 },   // GPIO80
    { PIN_SHARE_NUMBER( 9), 0, 3 },   // GPIO81
    { PIN_SHARE_NUMBER( 7), 6, 2 }    // GPIO_P9_PA
};

void SetGPIO(uint8_t gpio, uint8_t state)
{
    if (gpio < GPIO52) // Port access through SFR
    {
#       ifdef __SDCC
        switch (gpio)
        {
            case GPIO10: P1_0 = state; break;
            case GPIO11: P1_1 = state; break;
            case GPIO12: P1_2 = state; break;
            case GPIO13: P1_3 = state; break;
            case GPIO14: P1_4 = state; break;
            case GPIO15: P1_5 = state; break;
            case GPIO16: P1_6 = state; break;
            case GPIO17: P1_7 = state; break;

            case GPIO30: P3_0 = state; break;
            case GPIO31: P3_1 = state; break;
            case GPIO32: P3_2 = state; break;
            case GPIO33: P3_3 = state; break;
            case GPIO34: P3_4 = state; break;
            case GPIO35: P3_5 = state; break;
            case GPIO36: P3_6 = state; break;
            case GPIO37: P3_7 = state; break;
        }
#       else
        XSFRWriteByte(PORT_READ_CONTROL, 0x00); // Read port output state
        if (gpio < GPIO30) // Port 1
            XSFRWriteByte(P1X, InsertBits8(P1X, gpio - GPIO10, 1, state));
        else
            XSFRWriteByte(P3X, InsertBits8(P3X, gpio - GPIO30, 1, state));
#       endif
    }
    else // Port access through XSFR
    {
        XSFRWriteByte((gpio - GPIO52) + P5_2, state);
    }
}

uint8_t GetGPIO(uint8_t gpio)
{
    if (gpio < GPIO52) // Port access through SFR
    {
#       ifdef __SDCC
        switch (gpio)
        {
            case GPIO10: return P1_0;
            case GPIO11: return P1_1;
            case GPIO12: return P1_2;
            case GPIO13: return P1_3;
            case GPIO14: return P1_4;
            case GPIO15: return P1_5;
            case GPIO16: return P1_6;
            case GPIO17: return P1_7;

            case GPIO30: return P3_0;
            case GPIO31: return P3_1;
            case GPIO32: return P3_2;
            case GPIO33: return P3_3;
            case GPIO34: return P3_4;
            case GPIO35: return P3_5;
            case GPIO36: return P3_6;
            case GPIO37: return P3_7;
        }
#       else
        XSFRWriteByte(PORT_READ_CONTROL, 0xFF); // Read port input state
        if (gpio < GPIO30) // Port 1
            return (XSFRReadByte(P1X) >> (gpio - GPIO10)) & 1;
        else
            return (XSFRReadByte(P3X) >> (gpio - GPIO30)) & 1;
#       endif
    }
    else // Port access through XSFR
    {
        XSFRWriteByte(PORT_READ_CONTROL, 0xFF); // Read port input state
        return XSFRReadByte((gpio - GPIO52) + P5_2) & 1;
    }
}

/**
 *
 * Set Pin for basic I/O  (Input, Open-Drain Output, Push-Pull Output)
 * @param shareGPIO
 * GPIO to set. Example: GPIO10
 * @param portType
 * Port setting: INPUT, OPEN_DRAIN_OUT or PUSH_PULL_OUT
 *
**/
void SetGPIOShare(uint8_t gpio, uint8_t portType)
{
    if ((gpio == GPIO70) || // These ports have a selection for DDC I2C on 0b00
        (gpio == GPIO71) || // and the basic IO is shifted by one
        (gpio == GPIO72) ||
        (gpio == GPIO73))
        if (portType == 0b11) portType = 0; // To use DDC I2C 0b11 is passed to function, then converted to 0b00
        else portType + 1;

    XSFRWriteByte(
        PIN_SHARE_GPIO_STRUCT[gpio].PIN_SHARE_ADDRESS,
        InsertBits8(
            XSFRReadByte(PIN_SHARE_GPIO_STRUCT[gpio].PIN_SHARE_ADDRESS),
            PIN_SHARE_GPIO_STRUCT[gpio].BIT_OFFSET,
            PIN_SHARE_GPIO_STRUCT[gpio].ENTRY_SIZE,
            portType
        ));
}

void SetGPIODrivingCurrent(uint8_t pinRange, uint8_t current)
{
    if ((pinRange & 0x10) == 0)
        if (pinRange == DRIVE_74_TO_95)
            XSFRWriteByte(PIN_DRIVING_CURRENT_CONTROL0, InsertBits8(PIN_DRIVING_CURRENT_CONTROL0, pinRange, 2, current));
        else
            XSFRWriteByte(PIN_DRIVING_CURRENT_CONTROL0, InsertBits8(PIN_DRIVING_CURRENT_CONTROL0, pinRange, 1, current));
    else
       XSFRWriteByte(PIN_DRIVING_CURRENT_CONTROL1, InsertBits8(PIN_DRIVING_CURRENT_CONTROL0, pinRange & (~0x10), 1, current));
}