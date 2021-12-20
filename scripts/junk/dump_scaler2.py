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


port_list = [ # List of access port addresses: PAGE, ADDRESS, NAME, PORT RANGES
    # Common page
    ##[ 0, 0x25, "Input Pattern Generator", list(range(0x0D+1)) + list(range(0x10, 0x14+1)) ],
    ##[ 0, 0x2B, "Display Format", list(range(0x15+1)) + list(range(0x20, 0x24+1)) ],
    ##[ 0, 0x31, "FIFO Window Port", list(range(0x02+1)) ],
    ##[ 0, 0x34, "Scaling Factor", list(range(0x11+1)) ], # Need 7th bit set
    ##[ 0, 0x5D, "Sync Processor", list(range(0x09+1)) + list(range(0x10, 0x15+1)) ],
    ##[ 0, 0x61, "Highlight Window", list(range(0x0D+1)) ],
    ##[ 0, 0x65, "Contrast Brightness", list(range(0x0B+1)) ],
    ##[ 0, 0x6F, "Color LUT", list(range(0x2F+1)) ],
    #[ 0, 0x8C, "Timer Control", list(range(0xFF+1)) ], # Too fragmented and complicated, easier to just copy the whole address range
    #[ 0, 0x92, "On Screen Display", list(range(0xFF+1)) ], # 16 bit address
    ##[ 0, 0x9B, "VBI", list(range(0xFF+1)) ],

    #[ 2, 0xC4, "HDCP", list(range(0xFF+1)) ],
    #[ 2, 0xCA, "HDMI", list(range(0xFF+1)) ],

    ##[ 7, 0xB9, "Auto Sharpness", list(range(0xFF+1)) ],
    ##[ 7, 0xC1, "YUV to RGB LUT", list(range(0xFF+1)) ],
    ##[ 7, 0xCA, "DDC", list(range(0xFF+1)) ],
    ##[ 7, 0xD3, "ICM", list(range(0xFF+1)) ],
    ##[ 7, 0xD7, "Peaking & Coring", list(range(0xFF+1)) ],
]

#if __name__ == "__main__":
use_stdout = 0
if (not use_stdout):
    f = open("dump.txt", "w")

def writeLineDump (text):
    if (use_stdout):
        print(text)
    else:
        f.write(text + '\n')

InitI2C(0x378, 0)
EnterISPMode()

for i in range(0x00, 0x100): # Dump common page
    #writeLineDump("Scaler Value {0:#04x} at {1:#04x} Page {2}".format(ScalerReadRegisters(i)[0], i, "COMMON"))
    writeLineDump("ScalerWriteByte({1:#04x}, {0:#04x});".format(ScalerReadRegisters(i)[0], i))

for p in [ 0, 1 ]: # Dump other pages
    ScalerWriteRegisters(0x9F, p) # Set page select
    writeLineDump("ScalerWriteByte(S_PAGE_SELECT, {0});".format(p))
    for i in range(0xA0, 0x100):
        #writeLineDump("Scaler Value {0:#04x} at {1:#04x} Page {2}".format(ScalerReadRegisters(i)[0], i, p))
        writeLineDump("ScalerWriteByte({1:#04x}, {0:#04x});".format(ScalerReadRegisters(i)[0], i))