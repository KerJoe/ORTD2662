#pragma once

void DebugTimerIRQ() __interrupt (5);
uint8_t readSFR(uint8_t address) __naked;

void InitDebug();

#define StartDebug() TF2 = 1; __asm__("nop") // Begin first interrupt // Next instruction is skipped so add 'nop'
#define StopDebug()  TF2 = 0; // Stop Timer 2 interrupts