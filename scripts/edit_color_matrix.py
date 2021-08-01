from ctypes import *
import sys
import time
import os
import PySimpleGUI as sg
from PySimpleGUI.PySimpleGUI import Slider

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


Matrix = [
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,

    0x0000,
    0x0000,
    0x0000,
]

def SendMatrix():
    # ScalerWriteByte(S7_YUV_TO_RGB_CONTROL, 0x02);
    # for(uint8_t i = 0; i < 8; i++)
    # {
    #     ScalerWriteByte(S7_YUV_TO_RGB_ADDRESS, (i * 2) << 4);
    #     ScalerWriteByte(S7_YUV_TO_RGB_PORT, YUV2RGB_CCIR601[i] >> 8);
    #     ScalerWriteByte(S7_YUV_TO_RGB_ADDRESS, (i * 2 + 1) << 4);
    #     ScalerWriteByte(S7_YUV_TO_RGB_PORT, YUV2RGB_CCIR601[i] & 0xFF);
    # }
    # ScalerWriteByte(S7_YUV_TO_RGB_CONTROL, 0x01);       
    ScalerWriteRegisters(0x9F, 7)
    ScalerWriteRegisters(0xBF, 0x02)
    for i in range(8):
        ScalerWriteRegisters(0xC0, (i * 2) << 4)
        ScalerWriteRegisters(0xC1, Matrix[i] >> 8)
        ScalerWriteRegisters(0xC0, (i * 2 + 1) << 4)
        ScalerWriteRegisters(0xC1, Matrix[i] & 0xFF )
    ScalerWriteRegisters(0xBF, 0x01)

InitI2C(0x378, 0)
EnterISPMode()

# Window layout
mainLayout = [[sg.Text("K11"), sg.Slider(range=(0,2**12-1), orientation='horizontal', key="K11S", enable_events=True)],
              [sg.Text("K13"), sg.Slider(range=(0,2**11-1), orientation='horizontal', key="K13S", enable_events=True)],
              [sg.Text("K22"), sg.Slider(range=(0,2**10-1), orientation='horizontal', key="K22S", enable_events=True)],
              [sg.Text("K23"), sg.Slider(range=(0,2**10-1), orientation='horizontal', key="K23S", enable_events=True)],
              [sg.Text("K32"), sg.Slider(range=(0,2**12-1), orientation='horizontal', key="K32S", enable_events=True)],
              [sg.HorizontalSeparator()],
              [sg.Text("ROFF"), sg.Slider(range=(0,2**14-1), orientation='horizontal', key="ROFFS", enable_events=True)],
              [sg.Text("GOFF"), sg.Slider(range=(0,2**14-1), orientation='horizontal', key="GOFFS", enable_events=True)],
              [sg.Text("BOFF"), sg.Slider(range=(0,2**14-1), orientation='horizontal', key="BOFFS", enable_events=True)]]

mainWindow = sg.Window('RTDMultiProg', mainLayout, element_justification='center')
while (True):
    event, values = mainWindow.read(timeout=10)
    if event == sg.WIN_CLOSED:
        break
    if event == "K11S":
        Matrix[0] = int(values["K11S"])
        SendMatrix()
    if event == "K13S":
        Matrix[1] = int(values["K13S"])
        SendMatrix()
    if event == "K22S":
        Matrix[2] = int(values["K22S"])
        SendMatrix()
    if event == "K23S":
        Matrix[3] = int(values["K23S"])
        SendMatrix()                    
    if event == "K32S":
        Matrix[4] = int(values["K32S"])
        SendMatrix()        
    if event == "ROFFS":
        Matrix[5] = int(values["ROFFS"])
        SendMatrix()
    if event == "GOFFS":
        Matrix[6] = int(values["GOFFS"])
        SendMatrix()                    
    if event == "BOFFS":
        Matrix[7] = int(values["BOFFS"])
        SendMatrix()          


        

# #define FR10(__num) ((__num) * 1024)
# const uint16_t YUV2RGB_CCIR601[] =
# {
#     // YUV to RGB conversion coefficients
#     // [R]   [K11   0   K13][Y]    R = K11 * Y + K13 * V
#     // [G] = [ 1  -K22 -K23][U] => G = Y - K22 * U - K23 * V
#     // [B]   [ 1   K32   0 ][V]    B = Y + K32 * U

#     FR10(1.2),  // K11
#     FR10(0.6),  // K13
#     FR10(0.0),  // K22
#     FR10(0.0),  // K23
#     FR10(1.22798),  // K32

#     0x0000, // Red offset
#     0x0000, // Green offset
#     0x0000, // Blue offset
# };        

# ScalerWriteByte(S7_YUV_TO_RGB_CONTROL, 0x02);
# for(uint8_t i = 0; i < 8; i++)
# {
#     ScalerWriteByte(S7_YUV_TO_RGB_ADDRESS, (i * 2) << 4);
#     ScalerWriteByte(S7_YUV_TO_RGB_PORT, YUV2RGB_CCIR601[i] >> 8);
#     ScalerWriteByte(S7_YUV_TO_RGB_ADDRESS, (i * 2 + 1) << 4);
#     ScalerWriteByte(S7_YUV_TO_RGB_PORT, YUV2RGB_CCIR601[i] & 0xFF);
# }
# ScalerWriteByte(S7_YUV_TO_RGB_CONTROL, 0x01);        