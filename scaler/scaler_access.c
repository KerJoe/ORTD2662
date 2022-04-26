#include <stdint.h>
#include <stdio.h>

#include "scaler/scaler_access.h"
#include "scaler/scaler_registers.h"
#include "scaler/scaler_tables.h"
#include "peripherals/xsfr.h"

#include "core/misc.h"

void ScalerWriteByte(uint8_t address, uint8_t data)
{
    XSFRWriteByte(SCALER_ADDRESS, address);
    XSFRWriteByte(SCALER_DATA, data);
}

uint8_t ScalerReadByte(uint8_t address)
{
    XSFRWriteByte(SCALER_ADDRESS, address);
    return XSFRReadByte(SCALER_DATA);
}

void ScalerWriteBytes(uint8_t address, uint8_t data[], uint16_t count)
{
    for (uint16_t i = address; i < address + count; i++)
        ScalerWriteByte(i, data[i]);
}

void ScalerReadBytes(uint8_t address, uint8_t data[], uint16_t count)
{
    for (uint16_t i = address; i < address + count; i++)
        data[i] = ScalerReadByte(i);
}

void ScalerWriteBits(uint8_t address, uint8_t bitsPosition, uint8_t bitsLength, uint8_t bits)
{
    ScalerWriteByte(address, InsertBits8(ScalerReadByte(address), bitsPosition, bitsLength, bits));
}

uint8_t ScalerReadBits(uint8_t address, uint8_t bitsPosition, uint8_t bitsLength)
{
    return ExtractBits8(ScalerReadByte(address), bitsPosition, bitsLength);
}

void ScalerWriteBit(uint8_t address, uint8_t bitPosition, uint8_t bit)
{
    ScalerWriteBits(address, bitPosition, 1, bit);
}

uint8_t ScalerReadBit(uint8_t address, uint8_t bitPosition)
{
    return ExtractBits8(ScalerReadByte(address), bitPosition, 1);
}

void ScalerWritePortByte(uint8_t dataPort, uint8_t address, uint8_t data)
{
    ScalerWriteByte(dataPort - 1, address);
    ScalerWriteByte(dataPort, data);
}

uint8_t ScalerReadPortByte(uint8_t dataPort, uint8_t address)
{
    ScalerWriteByte(dataPort - 1, address);
    return ScalerReadByte(dataPort);
}

void ScalerWritePortBytes(uint8_t dataPort, uint8_t address, uint8_t data[], uint16_t count)
{
    ScalerWriteByte(dataPort - 1, address);
    EnableScalerAutoIncrement(1);
    for (uint16_t i = address; i < address + count; i++)
        ScalerWriteByte(dataPort, data[i]);
}

void ScalerReadPortBytes(uint8_t dataPort, uint8_t address, uint8_t data[], uint16_t count)
{
    ScalerWriteByte(dataPort - 1, address);
    EnableScalerAutoIncrement(1);
    for (uint16_t i = address; i < address + count; i++)
        data[i] = ScalerReadByte(dataPort);
}

void ScalerWritePortBits(uint8_t dataPort, uint8_t address, uint8_t bitsPosition, uint8_t bitsLength, uint8_t bits)
{
    ScalerWritePortByte(dataPort, address, InsertBits8(ScalerReadPortByte(dataPort, address), bitsPosition, bitsLength, bits));
}

void ScalerWritePortBit(uint8_t dataPort, uint8_t address, uint8_t bitPosition, uint8_t bit)
{
    ScalerWritePortByte(dataPort, address, InsertBits8(ScalerReadPortByte(dataPort, address), bitPosition, 1, bit));
}

void ScalerWriteTable(const uint8_t table[])
{
#   define TABLE_DATA_SIZE     (*(table + DATA_SIZE_INDEX))
#   define TABLE_BASE_ADDRESS  (*(table + BASE_ADDRESS_INDEX))
#   define TABLE_AUTOINC       (*(table + AUTOINC_INDEX))
#   define TABLE_DATA(__off)   (*(table + DATA_INDEX + __off))

    while (TABLE_DATA_SIZE != TABLE_END)
    {
        EnableScalerAutoIncrement(TABLE_AUTOINC);

        XSFRWriteByte(SCALER_ADDRESS, TABLE_BASE_ADDRESS);
        for (uint16_t i = 0; i < TABLE_DATA_SIZE; i++)
            XSFRWriteByte(SCALER_DATA, TABLE_DATA(i));

        table = table + 3 + TABLE_DATA_SIZE;
    }
}