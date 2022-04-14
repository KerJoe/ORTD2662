#pragma once

#include <stdint.h>

#define UART_TIMER1 1
#define UART_TIMER2 2

#define UART_DIV_TIMER1(__freq, __baud) (256   - (__freq / (__baus * 384)))
#define UART_DIV_TIMER2(__freq, __baud) (65536 - (__freq / (__baud * 64)))

void InitUART(uint32_t baudRate, uint8_t timerSelect);

void SwitchToUART();
void SwitchToI2C();

int putchar(int character);
int getchar();