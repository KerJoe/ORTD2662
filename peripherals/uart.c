#include <stdint.h>

#include "peripherals/sfr.h"
#include "peripherals/xsfr.h"
#include "peripherals/pins.h"
#include "peripherals/uart.h"

#include "core/main.h"

/**
 *
 * Initialize UART
 *
 * @param baudRate
 * UART Baud rate
 *
 * @param timerSelect
 * Select baud generating timer: UART_TIMER1 or UART_TIMER2
 *
**/
void InitUART(uint32_t baudRate, uint8_t timerSelect)
{
    if (timerSelect == UART_TIMER1)
    {
        uint16_t div16 = UART_DIV_TIMER1(PERIPHERAL_FREQ, baudRate);
        TMOD  |= 0b00100000; // Timer 1, 8-bit auto reload mode
        SCON  |= 0b00000101; // UART Mode 1, Reciever enable
        //TL1   = div16 >> 8; // Load divider value
        //TH1   = 0//TH1   = div16;
        TH1   = div16 >> 8; // Load divider value
        TR1   = 1;          // Start Timer
    }
    else
    {
        uint16_t div16 = UART_DIV_TIMER2(PERIPHERAL_FREQ, baudRate);
        //T2CON  = 0b00000000;
        T2CON  = 0b00110000;            // Timer 2,
        SCON   = 0b01010000;          // UART Mode 1, Reciever enable
        RCAP2H = div16 >> 8;    // Load divider value
        RCAP2L = div16;
        //TH2    = div16 >> 8;    // Load divider value
        //TL2    = div16;
        TR2    = 1;             // Start Timer
    }
}

/**
 *
 * Change Serial port interface from I2C to UART
 * @exception DISABLES I2C FLASH PROGRAMMING, MAY BRICK THE SYSTEM
 *
**/
void SwitchToUART()
{
    PIN_SHARE_CONTROL00 |= 0b11111000; // Disconnect I2C; Set Pin58 (SCL) to RXD; Set Pin59 (SDA) to TXD
}


/**
 *
 * Change Serial port interface from UART to I2C
 *
**/
void SwitchToI2C()
{
    PIN_SHARE_CONTROL00 &= ~(0b11111000); // Connect I2C; Set Pin58 (RXD) to SCL; Set Pin59 (TXD) to SDA
}


/**
 *
 * putchar implementation for stdio library
 * @param character
 * The character to be written
 * @return On success, the character written is returned.
 *         If a writing error occurs, EOF is returned
 *
**/
int putchar(int character)
{
    //SwitchToUART();
    SBUF = character;
    while(!TI) WDT_CONTROL = (1 << 6);
    TI = 0;
    return character;
    //SwitchToI2C();
}

/**
 *
 * getchar implementation for stdio library
 * @return On success, the character read is returned.
 *         If a reading error occurs, EOF is returned
 *
**/
int getchar()
{
    //SwitchToUART();
    while(!RI) WDT_CONTROL = (1 << 6);
    int character = SBUF;
    RI = 0;
    return character;
    //SwitchToI2C();
}