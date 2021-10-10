As the explanation of banking in the datasheet is so attrociously incoherent. I'll write my own.


Terminology
===========
XMEM - External memory, accessed via MOVX instruction

XRAM - 1 KiB of RAM, situated from 0xFB00 to 0xFEFF of XMEM

XFR - External Special Function Registers, situated from 0xFF00 to 0xFF00 of XMEM

XDATA - A single bank of programm (Flash) memory accessible through XMEM.


XDATA Application
===================
XDATA is a way to access data beyond 64 KiB of directly addressable program memory by mapping ROM banks in XMEM address space.

Here's an example: You have 128 KiB firmware, first 64 KiB (0x00000-0x0FFFF) is taken by programm functions, while the second 64 KiB (0x10000-0x1FFFF) is taken by data (Logos, Pictures, Fonts, etc). To access the data found at flash address 0x12345 whithout changing the current programm bank you can set the XDATA bank to 1, and read from address 0x2345 of XMEM.
