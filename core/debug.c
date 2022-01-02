#include <stdio.h>
#include <stdlib.h>
#include "peripherals/sfr.h"
#include "peripherals/pins.h"
#include "peripherals/uart.h"
#include "core/debug.h"

uint8_t readSFR(uint8_t address) __naked
{
    address; // Avoid unrefrenced warning; Available in DPL register
    __asm__("push    a");
    __asm__("push    b");
    __asm__("lcall   00002$");
    __asm__("mov     dpl,a");
    __asm__("pop     b");
    __asm__("pop     a");
    __asm__("ret");
    __asm__("00002$:");
    __asm__("mov     a,  dpl        ; Address to accumulator");
    __asm__("anl     a,  #0x7f");
    __asm__("mov     b,  #3         ; Dispatch table entry size");
    __asm__("mul     ab             ; Get offset");
    __asm__("add	 a,  #<00001$	; Add offset to dispatch table");
    __asm__("push	 a			    ; Place SFR dispatch address on stack");
    __asm__("mov	 a,  b");
    __asm__("addc 	 a,  #>00001$");
    __asm__("push	 a");
    __asm__("ret				    ; `call` into dispatch table will return to our caller");
    __asm__("00001$:");
    __asm__("SFR_REPT_COUNT .equ 128");
    __asm__(".rept 128");
    __asm__("mov	 a,  SFR_REPT_COUNT");
    __asm__("ret");
    __asm__("SFR_REPT_COUNT = SFR_REPT_COUNT + 1");
    __asm__(".endm");
}
#define writeSFR(__adr, __data) _writeSFR((__data << 8) | (__adr & 0xff));
void _writeSFR(uint8_t data_address) __naked
{
    data_address; // Avoid unrefrenced warning; Data in DPH, Address in DPL
    __asm__("push    a");
    __asm__("push    b");
    __asm__("acall   00002$");
    __asm__("pop     b");
    __asm__("pop     a");
    __asm__("ret");
    __asm__("00002$:");
    __asm__("mov     a,  dpl        ; Address to accumulator");
    __asm__("anl     a,  #0x7f");
    __asm__("mov     b,  #3         ; Dispatch table entry size");
    __asm__("mul     ab             ; Get offset");
    __asm__("add	 a,  #<00001$   ; Add offset to dispatch table");
    __asm__("push	 a	            ; Place SFR dispatch address on stack");
    __asm__("mov	 a,  b");
    __asm__("addc 	 a,  #>00001$");
    __asm__("push	 a");
    __asm__("mov     a,  dph");
    __asm__("ret				    ; `call` into dispatch table will return to our caller");
    __asm__("00001$:");
    __asm__("SFR_REPT_COUNT .equ 128");
    __asm__(".rept 128");
    __asm__("mov     SFR_REPT_COUNT, a");
    __asm__("ret");
    __asm__("SFR_REPT_COUNT = SFR_REPT_COUNT + 1");
    __asm__(".endm");
}

char hex2int(char ch)
{
    return ch - '0' > 9 ? (ch & 0x20) - 'A' + 11 : ch - '0';
}

#define PC_STACKOFFSET      15
#define BITS_STACKOFFSET    13
#define A_STACKOFFSET       12
#define B_STACKOFFSET       11
#define DPTR_STACKOFFSET    10
#define R7_STACKOFFSET      8
#define R6_STACKOFFSET      7
#define R5_STACKOFFSET      6
#define R4_STACKOFFSET      5
#define R3_STACKOFFSET      4
#define R2_STACKOFFSET      3
#define R1_STACKOFFSET      2
#define R0_STACKOFFSET      1
#define PSW_STACKOFFSET     0

__near uint8_t a_tmp, psw_tmp;
__near uint16_t bp0 = 0;

uint8_t rcv_buf[8];

void monitor(uint8_t sp_val)
{
    while(1)
    {
        printf("\n>");
        switch (getchar())
        {
            case 'p':
                printf("\nPC:   0x%04x", (int)*((__idata uint16_t*)(sp_val - PC_STACKOFFSET)));
                printf("\nDPTR: 0x%04x", (int)*((__idata uint16_t*)(sp_val - DPTR_STACKOFFSET)));
                printf("\nSP:   0x%02x", (int)sp_val);
                printf("\nA:    0x%02x", (int)*((__idata  uint8_t*)(sp_val - A_STACKOFFSET)));
                printf("\nB:    0x%02x", (int)*((__idata  uint8_t*)(sp_val - B_STACKOFFSET)));
                printf("\nPSW:  0x%02x", (int)*((__idata  uint8_t*)(sp_val - PSW_STACKOFFSET)));
                printf("\nBITS: 0x%02x", (int)*((__idata  uint8_t*)(sp_val - BITS_STACKOFFSET)));
                printf("\nR0:   0x%02x", (int)*((__idata  uint8_t*)(sp_val - R0_STACKOFFSET)));
                printf("\nR1:   0x%02x", (int)*((__idata  uint8_t*)(sp_val - R1_STACKOFFSET)));
                printf("\nR2:   0x%02x", (int)*((__idata  uint8_t*)(sp_val - R2_STACKOFFSET)));
                printf("\nR3:   0x%02x", (int)*((__idata  uint8_t*)(sp_val - R3_STACKOFFSET)));
                printf("\nR4:   0x%02x", (int)*((__idata  uint8_t*)(sp_val - R4_STACKOFFSET)));
                printf("\nR5:   0x%02x", (int)*((__idata  uint8_t*)(sp_val - R5_STACKOFFSET)));
                printf("\nR6:   0x%02x", (int)*((__idata  uint8_t*)(sp_val - R6_STACKOFFSET)));
                printf("\nR7:   0x%02x", (int)*((__idata  uint8_t*)(sp_val - R7_STACKOFFSET)));
                break;
            case 'm':
                printf("\n    x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xa xb xc xd xe xf");
                for (uint8_t y = 0; y < 16; y++)
                {
                    printf("\n%xx:", y);
                    for (uint8_t x = 0; x < 16; x++)
                    {
                        printf(" %02x", (int)*((__idata uint8_t*)((y<<4)+x)));
                    }
                }
                break;
            case 'r':
                printf("\n    x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xa xb xc xd xe xf");
                for (uint8_t y = 8; y < 16; y++)
                {
                    printf("\n%xx:", y);
                    for (uint8_t x = 0; x < 16; x++)
                    {
                        printf(" %02x", (int)readSFR((y<<4)+x));
                    }
                }
                break;
            case 'b':
                bp0 = (hex2int(getchar())<<12) + (hex2int(getchar())<<8) + (hex2int(getchar())<<4) + hex2int(getchar());
                break;
            case 'g':
                return;
            case 'i':
                SwitchToI2C();
                break;
            default:
                printf("\n?");
                break;
        }
    }
}

void DebugTimerIRQ() __interrupt(5) __naked
{
    __asm__("; push  pcl ; Done by hardware");
    __asm__("; push  pch ; ...");
    __asm__("mov     _psw_tmp, psw");
    __asm__("mov     _a_tmp, a");
    __asm__("pop     a");
    __asm__("cjne    a,      _bp0+1, 00001$"); // TODO: Use < and >
    __asm__("pop     a");
    __asm__("cjne    a,      _bp0,   00002$");
    __asm__("; Hit break point");
    __asm__("inc     sp");
    __asm__("inc     sp");
    __asm__("mov     a,      _a_tmp");
    __asm__("mov     psw,    _psw_tmp");
    __asm__("ajmp    00003$");
    __asm__("00002$:");
    __asm__("inc     sp");
    __asm__("00001$:");
    __asm__("inc     sp");
    __asm__("mov     a,      _a_tmp");
    __asm__("mov     psw,    _psw_tmp");
    __asm__("jb      RI,     00003$      ; UART has recieved something");
    __asm__("reti");
    __asm__("00003$:");
    InterruptPrologue
    a_tmp = SP; // Temporaralt save SP


    monitor(a_tmp);


    InterruptEpilogueNoEnd
    __asm__("reti");
}