import os, sys
sys.path.append(os.path.dirname(os.path.abspath(__file__+"../../.."))+"/RTDMultiProg")

import rtdmultiprog


interface = "i2cdev"
device = 2
settings = ""


rtdmultiprog.load_interface(interface)
rtdmultiprog.start_interface(device, settings)

xsfr_write = rtdmultiprog.write_reg
xsfr_read  = rtdmultiprog.read_reg

def scaler_write(address, data, auto_inc = 1):
    xsfr_write(0xF3, (not auto_inc) << 5)
    xsfr_write(0xF4, address)
    xsfr_write(0xF5, data)

def scaler_read(address, count = 1, auto_inc = 1):
    xsfr_write(0xF3, (not auto_inc) << 5)
    xsfr_write(0xF4, address)
    return xsfr_read(0xF5, count)

def _insert_bits8(value, bits_position, bits_length, bits):
    clear_mask = 0
    for i in range(bits_position, bits_position + bits_length, 1):
        clear_mask |= (1 << i)
    return (value & (~clear_mask)) | (bits << bits_position)

def scaler_write_bits(address, bits_position, bits_length, bits):
    scaler_write(address, _insert_bits8(scaler_read(address)[0], bits_position, bits_length, bits))

def scaler_port_byte(data_port, address, data):
    scaler_write(data_port - 1, address)
    scaler_write(data_port, data)

XSFRWriteByte = xsfr_write
XSFRReadByte = xsfr_read
ScalerWriteByte = scaler_write
ScalerReadByte = xsfr_read
ScalerWriteBits = scaler_write_bits
ScalerWritePortByte = scaler_port_byte