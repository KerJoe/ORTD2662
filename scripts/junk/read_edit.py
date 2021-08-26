from ctypes import *
import sys
import time
import os

if (sys.maxsize > 2**32):
    print ("64 bit Python is not supported! Use a 32 bit version.")
    sys.exit(1)
else:
    i2ci = cdll.LoadLibrary(os.path.dirname(__file__) + "\\i2cinterface.dll")

def InitI2C(address, delay):
    retval = i2ci.I2CInit(address, delay)
    if (retval == 0):
        raise ConnectionError("Failed to initialize I2C")

def WriteI2C(dev, data, expectResponse):
    if (type(data) == int):
        data = [ data ]
    dat  = (c_ubyte * len(data))(*data)
    retval = i2ci.I2CWrite(c_ubyte(dev), dat, c_uint32(len(data)))
    if ((retval == 0) and expectResponse):
        raise ConnectionError("No response from target during Write")

def ReadI2C(dev, count):
    dat  = (c_ubyte * count)(*([0] * count)) #
    retval = i2ci.I2CRead(c_ubyte(dev), dat, c_uint32(count))
    if (retval == 0):
        raise ConnectionError("No response from target during Read")
    data = [i for i in dat]
    return data



def WriteRegisters(dev, data, expectResponse):
    WriteI2C(dev << 1, data, expectResponse)

def WriteRegisters(dev, address, data, expectResponse):
    if (type(data) == int):
        data = [ address, data ]
    else:
        data.insert(0, address)
    WriteI2C(dev << 1, data, expectResponse)

def ReadRegisters(dev, count):
    return ReadI2C((dev << 1) | 1, count, True)

def ReadRegisters(dev, address, count):
    WriteI2C(dev << 1, address, True)
    return ReadI2C((dev << 1) | 1, count)



def RTDWriteRegisters(address, data, expectResponse = True):
    # If not Isp Data Register use address 0x4B
    WriteRegisters(0x4A | (address != 0x70), address, data, expectResponse)

def RTDReadRegisters(address, count = 1):
    # If not Isp Data Register use address 0x4B
    return ReadRegisters(0x4A | (address != 0x70), address, count)



def ScalerWriteRegisters(address, data, autoInc = 1):
    RTDWriteRegisters(0xF3, (not autoInc) << 5)
    RTDWriteRegisters(0xF4, address)
    RTDWriteRegisters(0xF5, data)

def ScalerReadRegisters(address, count = 1, autoInc = 1):
    RTDWriteRegisters(0xF3, (not autoInc) << 5)
    RTDWriteRegisters(0xF4, address)
    return RTDReadRegisters(0xF5, count)



def EnterISPMode():
    RTDWriteRegisters(0x6F, 0x80, True) # Enable ISP, Disable internal MCU
    success = False
    for i in range(10):
        if ((RTDReadRegisters(0x6F)[0] & 0x80) == 0x80):
            success = True
            break
        time.sleep(0.0001)
    if (not success):
        raise ConnectionError("Timed out waiting to enter ISP mode")



InitI2C(0x378, 0)
#EnterISPMode()
