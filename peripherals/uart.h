#pragma once

#include <stdint.h>

#define UART_TIMER1 1
#define UART_TIMER2 2

#define UART_DIV_TIMER1(__FREQ, __BAUD) (256   - ((__FREQ / 384) / __BAUD))
#define UART_DIV_TIMER2(__FREQ, __BAUD) (65536 - (__FREQ / (__BAUD * 32)))

void InitUART(uint32_t baudRate, uint8_t timerSelect);

void SwitchToUART();
void SwitchToI2C();

int putchar(int character);
int getchar();