#include "stdio.h"
#include "stdlib.h"
#include "peripherals/sfr.h"
#include "peripherals/pins.h"
#include "core/debug.h"

uint8_t readSFR(uint8_t address) __naked
{
    address; // Avoid unrefrenced warning; Available in DPL register
    __asm
    push    a
    push    b
    lcall   00002$
    mov     dpl,a
    pop     b
    pop     a
    ret
    00002$:
    mov     a,  dpl         ; Address to accumulator
    anl     a,  #0x7f
    mov     b,  #3          ; Dispatch table entry size
    mul     ab              ; Get offset
	add	    a,  #<00001$	; Add offset to dispatch table
	push	a			    ; Place SFR dispatch address on stack
	mov	    a,  b
	addc 	a,  #>00001$
	push	a
    ret				        ; `call` into dispatch table will return to our caller
    00001$:
    SFR_REPT_COUNT .equ 128
    .rept 128
    mov	    a,  SFR_REPT_COUNT
	ret
    SFR_REPT_COUNT = SFR_REPT_COUNT + 1
    .endm
    __endasm;
}
#define writeSFR(__adr, __data) _writeSFR((__data << 8) | (__adr & 0xff));
void _writeSFR(uint8_t data_address) __naked
{
    data_address; // Avoid unrefrenced warning; Data in DPH, Address in DPL
    __asm
    push    a
    push    b
    acall   00002$
    pop     b
    pop     a
    ret
    00002$:
    mov     a,  dpl         ; Address to accumulator
    anl     a,  #0x7f
    mov     b,  #3          ; Dispatch table entry size
    mul     ab              ; Get offset
	add	    a,  #<00001$	; Add offset to dispatch table
	push	a			    ; Place SFR dispatch address on stack
	mov	    a,  b
	addc 	a,  #>00001$
	push	a
    mov     a,  dph
    ret				        ; `call` into dispatch table will return to our caller
    00001$:
    SFR_REPT_COUNT .equ 128
    .rept 128
    mov	    SFR_REPT_COUNT, a
	ret
    SFR_REPT_COUNT = SFR_REPT_COUNT + 1
    .endm
    __endasm;
}

char hex2int(char ch)
{
    return ch - '0' > 0x09 ? (ch & 0x20) - 'A' + 11 : ch - '0';
}

uint8_t sp_val;
#define PC_STACKOFFSET      15
#define BITS_STACKOFFSET    13
#define A_STACKOFFSET       12
#define B_STACKOFFSET       11
#define DPL_STACKOFFSET     10
#define DPH_STACKOFFSET     9
#define R7_STACKOFFSET      8
#define R6_STACKOFFSET      7
#define R5_STACKOFFSET      6
#define R4_STACKOFFSET      5
#define R3_STACKOFFSET      4
#define R2_STACKOFFSET      3
#define R1_STACKOFFSET      2
#define R0_STACKOFFSET      1
#define PSW_STACKOFFSET     0

__near uint8_t  a_tmp, psw_tmp;
__near uint16_t bp0 = 0x012E;//NULL;

void DebugTimerIRQ() __interrupt (5) __naked
{
    __asm
    ; push  pcl ; Done by hardware
    ; push  pch ; ...
    mov     _psw_tmp, psw
    mov     _a_tmp, a
    pop     a
    cjne    a,      _bp0+1, 00001$
    pop     a
    cjne    a,      _bp0,   00002$
    ; Hit break point
    inc     sp
    inc     sp
    mov     a,      _a_tmp
    mov     psw,    _psw_tmp
    ajmp    00003$
    00002$:
    inc     sp
    00001$:
    inc     sp
    mov     a,      _a_tmp
    mov     psw,    _psw_tmp
    reti
    00003$:
    push	0x20    ; bits
    push	a
    push	b
    push	dpl
    push	dph
    push	(0 + 7) ; r7
    push	(0 + 6) ; r6
    push	(0 + 5) ; r5
    push	(0 + 4) ; r4
    push	(0 + 3) ; r3
    push	(0 + 2) ; r2
    push	(0 + 1) ; r1
    push	(0 + 0) ; r0
    push	psw
    mov     psw, #0
    __endasm;

    sp_val = SP;

    printf("Breakpoint Hit");
    getchar();

    /*pc_val = *((__near uint16_t*)(SP-PC_STACK_OFFSET));

    printf("%x:", pc_val);
    switch (getchar())
    {
        case 'g':
            adr = (hex2int(getchar())<<4) + hex2int(getchar());
            printf("\n%x\n", readSFR(adr));
            break;
        case 's':
            adr = (hex2int(getchar())<<4) + hex2int(getchar());
            dat = (hex2int(getchar())<<4) + hex2int(getchar());
            writeSFR(adr, dat);
            break;
        case 'e':
            SwitchToI2C();
            StopDebug();
            break;

        case 'z':
            bp0 = (hex2int(getchar())<<12) + (hex2int(getchar())<<8) + (hex2int(getchar())<<4) + hex2int(getchar());
            break;

        default:
            printf("\n?\n");
            break;
    }*/
    //putchar('x');
    //StopDebug();



    __asm
    push	psw
    push	(0 + 0) ; r0
    push	(0 + 1) ; r1
    push	(0 + 2) ; r2
    push	(0 + 3) ; r3
    push	(0 + 4) ; r4
    push	(0 + 5) ; r5
    push	(0 + 6) ; r6
    push	(0 + 7) ; r7
    push	dph
    push	dpl
    push	b
    push	a
    push	0x20   ; bits
    ; push pch ; ...
    ; push pcl ; Done by hardware
    reti
    __endasm;
}

void InitDebug()
{
    // T2CON = 0b00000000; // Disable Timer 2
    // ET2 = 1;            // Enable Timer 2 interrupt
    // IP = 0b00100000;    // Timer 2 interrupt - Highest priority
    ET2 = 1;
}

// StartDebug() // See header file
// StopDebug()  // See header file