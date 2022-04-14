#pragma once

#include "scaler/scaler_access.h"
#include "scaler/scaler_registers.h"
#include "peripherals/timer.h"

#define _BIT0 0
#define _BIT1 1
#define _BIT2 2
#define _BIT3 3
#define _BIT4 4
#define _BIT5 5
#define _BIT6 6
#define _BIT7 7

#define _PAGE0                          0x00
#define _PAGE1                          0x01
#define _PAGE2                          0x02
#define _PAGE3                          0x03
#define _PAGE4                          0x04
#define _PAGE5                          0x05
#define _PAGE6                          0x06
#define _PAGE7                          0x07

#define _PAGE8                          0x08
#define _PAGE9                          0x09
#define _PAGEA                          0x0A
#define _PAGEB                          0x0B
#define _PAGEC                          0x0C
#define _PAGED                          0x0D
#define _PAGEE                          0x0E
#define _PAGEF                          0x0F

typedef unsigned char BYTE;
typedef unsigned char UINT8;
typedef char SBYTE;
typedef char INT8;
typedef unsigned int  WORD;
typedef unsigned int UINT16;
typedef	int  SWORD;
typedef int INT16;
typedef unsigned long DWORD;
typedef unsigned long UINT32;
typedef long SDWORD;
typedef long INT32;
typedef char BOOL;
typedef char BIT;
typedef char bit;

#define _RTD_XTAL (BOARD_FREQ/1000)

#define CScalerPageSelect(_PAGE) ScalerWriteByte(S_PAGE_SELECT, _PAGE)
#define CScalerSetBit(_ADR, _AND, _OR) ScalerWriteByte(_ADR, (ScalerReadByte(_ADR) & (_AND)) | (_OR))
#define CScalerSetByte(_ADR, _BYTE) ScalerWriteByte(_ADR, _BYTE)
#define CTimerDelayXms(_MS) delayMS(_MS)
#define CScalerSetDataPortBit(_PORT_ADR, _ADR, _AND, _OR) ScalerWritePortByte(_PORT_ADR, _ADR, (ScalerReadPortByte(_PORT_ADR, _ADR) & (_AND)) | (_OR))