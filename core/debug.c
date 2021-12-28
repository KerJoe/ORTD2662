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
    anl     a,  #127
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
    anl     a,  #127
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

uint16_t pc_val;
uint8_t  adr;
uint8_t  dat;
uint16_t bp0 = 0;
#define PC_STACK_OFFSET 15
void DebugTimerIRQ() __interrupt (5)
{
    pc_val = *((__near uint16_t*)(SP-PC_STACK_OFFSET));

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
    }
    //putchar('x');
    //StopDebug();
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