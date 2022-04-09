#pragma once

#ifdef __SDCC

#include <8052.h>

__sfr __at (0x8F) SPC_FNC;  // Unused // In the original DW8051 IP - used for writing to ROM (Flash memory) using MOVX
__sfr __at (0x8E) CKCON;    // Set timer divider speed: 0 - 12 clocks per tick (8051 Compatability, Defaults); 1 - 4 clocks per tick
__sfr __at (0x92) _XPAGE;   // aka MPAGE // Sets up high byte of non DPTR MOVX instruction. Required for SDCC to initialize variables in XRAM.

#endif