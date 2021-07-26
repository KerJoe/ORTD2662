#pragma once

#include <stdint.h>

#include "scaler/scaler_registers.h"
#include "core/misc.h"

// Auto increment of access port address (not SCALER_ADDRESS)
//#define EnableScalerAutoIncrement(__state) SCALER_CONTROL = InsertBits8(SCALER_CONTROL, 5, 1, !(__state))
#define EnableScalerAutoIncrement(__state) SCALER_CONTROL = (SCALER_CONTROL & (~(1 << 5))) | ((!(__state)) << 5)

void ScalerWriteByte(uint8_t address, uint8_t data);
uint8_t ScalerReadByte(uint8_t address);
void ScalerWriteBits(uint8_t address, uint8_t bitsPosition, uint8_t bitsLength, uint8_t bits);
void ScalerWriteBit(uint8_t address, uint8_t bitPosition, uint8_t bit);

void ScalerWritePortByte(uint8_t dataPort, uint8_t address, uint8_t data);
uint8_t ScalerReadPortByte(uint8_t dataPort, uint8_t address);
void ScalerWritePortBits(uint8_t dataPort, uint8_t address, uint8_t bitsPosition, uint8_t bitsLength, uint8_t bits);
void ScalerWritePortBit(uint8_t dataPort, uint8_t address, uint8_t bitPosition, uint8_t bit);

void ScalerWriteTable(uint8_t table[]);