#pragma once

#include "stdint.h"
#include "core/main.h"

void DebugTimerIRQ() __interrupt (5);
uint8_t readSFR(uint8_t address) __naked;
void monitor(uint8_t sp_val);

// Begin first interrupt // Next instruction after setting ET2 is skipped, so add 'nop'
#define StartDebug() do { TF2 = 1; ET2 = 1; __asm__("nop"); } while (0);
// Stop debug interrupts
#define StopDebug()  ET2 = 0;

// Breakpoint call
#define $ do { printf("Break at %s:%i\n", __FILE__, __LINE__); InterruptPrologue; monitor(); InterruptEpilogueNoEnd; } while (0);

#define InterruptPrologue \
    __asm__("push	0x20    ; bits");              \
    __asm__("push	a");                           \
    __asm__("push	b");                           \
    __asm__("push	dpl");                         \
    __asm__("push	dph");                         \
    __asm__("push	(0 + 7) ; r7");                \
    __asm__("push	(0 + 6) ; r6");                \
    __asm__("push	(0 + 5) ; r5");                \
    __asm__("push	(0 + 4) ; r4");                \
    __asm__("push	(0 + 3) ; r3");                \
    __asm__("push	(0 + 2) ; r2");                \
    __asm__("push	(0 + 1) ; r1");                \
    __asm__("push	(0 + 0) ; r0");                \
    __asm__("push	psw");                         \
    __asm__("mov    psw, #0");

#define InterruptEpilogueNoEnd \
    __asm__("pop	psw");                         \
    __asm__("pop	(0 + 0) ; r0");                \
    __asm__("pop	(0 + 1) ; r1");                \
    __asm__("pop	(0 + 2) ; r2");                \
    __asm__("pop	(0 + 3) ; r3");                \
    __asm__("pop	(0 + 4) ; r4");                \
    __asm__("pop	(0 + 5) ; r5");                \
    __asm__("pop	(0 + 6) ; r6");                \
    __asm__("pop	(0 + 7) ; r7");                \
    __asm__("pop	dph");                         \
    __asm__("pop	dpl");                         \
    __asm__("pop	b");                           \
    __asm__("pop	a");                           \
    __asm__("pop	0x20   ; bits");

#ifdef DEBUG
#define InterruptEpilogue  \
    InterruptEpilogueNoEnd \
    __asm__("ljmp   _DebugTimerIRQ");
#else
#define InterruptEpilogue  \
    InterruptEpilogueNoEnd \
    __asm__("reti");
#endif