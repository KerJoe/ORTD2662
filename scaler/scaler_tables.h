#pragma once

#include <stdint.h>

#include "scaler/scaler_registers.h"

#define BIT_ZERO 0
#define BIT_ONE  1

#define AUTOINC_ENA 1 // Enable auto access port address increase
#define AUTOINC_DIS 0 // Disable auto access port address increase

// Scaler Table Structure:
#define DATA_SIZE_INDEX     0 // Size of data array written to the scaler to/from the base address
#define AUTOINC_INDEX       1 // Whether to enable auto address increment
#define BASE_ADDRESS_INDEX  2 // Address of scaller register to/from which to write data
#define DATA_INDEX          3 // Data to write to scaler

#define TABLE_END           0 // Table end is indicated by Data size being zero

#define REG16BE(__val) ((__val) >> 8), ((uint8_t)__val)

extern const uint8_t DisplayInitTable[];
extern const uint8_t tSCALER_POWERUP_HDMI[];