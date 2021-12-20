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


PANEL_H_SYNC_WIDTH  = 0
PANEL_H_BACK_PORCH  = 0
PANEL_H_ACTIVE      = 0
PANEL_H_FRONT_PORCH = 0

PANEL_V_SYNC_WIDTH  = 0
PANEL_V_BACK_PORCH  = 0
PANEL_V_ACTIVE      = 0
PANEL_V_FRONT_PORCH = 0


def SendTimings():
    ScalerWriteRegisters(0x2A, 0)
    #
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE + PANEL_H_FRONT_PORCH - 4) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE + PANEL_H_FRONT_PORCH - 4), 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH), 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH - 10) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH - 10), 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH - 10) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH - 10), 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE - 10) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE - 10), 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE - 10) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_H_SYNC_WIDTH + PANEL_H_BACK_PORCH + PANEL_H_ACTIVE - 10), 0)
    #
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE + PANEL_V_FRONT_PORCH) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE + PANEL_V_FRONT_PORCH), 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH), 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH), 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH), 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE), 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE) >> 8, 0)
    ScalerWriteRegisters(0x2B, (PANEL_V_SYNC_WIDTH + PANEL_V_BACK_PORCH + PANEL_V_ACTIVE), 0)

InitI2C(0x378, 0)
EnterISPMode()

# Window layout
mainLayout = [[sg.Text("PANEL_H_SYNC_WIDTH"),  sg.Slider(range=(0,255),  orientation='horizontal', default_value=32, key="PANEL_H_SYNC_WIDTH_", enable_events=True)],
              [sg.Text("PANEL_H_BACK_PORCH"),  sg.Slider(range=(0,255),  orientation='horizontal', default_value=64, key="PANEL_H_BACK_PORCH_", enable_events=True)],
              [sg.Text("PANEL_H_ACTIVE"),      sg.Slider(range=(0,2048), orientation='horizontal', default_value=1024,key="PANEL_H_ACTIVE_", enable_events=True)],
              [sg.Text("PANEL_H_FRONT_PORCH"), sg.Slider(range=(0,255),  orientation='horizontal', default_value=128,key="PANEL_H_FRONT_PORCH_", enable_events=True)],
              [sg.HorizontalSeparator()],
              [sg.Text("PANEL_V_SYNC_WIDTH"),  sg.Slider(range=(0,255),  orientation='horizontal', default_value=8,key="PANEL_V_SYNC_WIDTH_", enable_events=True)],
              [sg.Text("PANEL_V_BACK_PORCH"),  sg.Slider(range=(0,255),  orientation='horizontal', default_value=16,key="PANEL_V_BACK_PORCH_", enable_events=True)],
              [sg.Text("PANEL_V_ACTIVE"),      sg.Slider(range=(0,1200), orientation='horizontal', default_value=600,key="PANEL_V_ACTIVE_", enable_events=True)],
              [sg.Text("PANEL_V_FRONT_PORCH"), sg.Slider(range=(0,255),  orientation='horizontal', default_value=32,key="PANEL_V_FRONT_PORCH_", enable_events=True)]]

mainWindow = sg.Window('RTDMultiProg', mainLayout, element_justification='center')
while (True):
    event, values = mainWindow.read(timeout=10)
    if event == sg.WIN_CLOSED:
        break
    if event == "PANEL_H_SYNC_WIDTH_":
        PANEL_H_SYNC_WIDTH = int(values["PANEL_H_SYNC_WIDTH_"])
        SendTimings()
    if event == "PANEL_H_BACK_PORCH_":
        PANEL_H_BACK_PORCH = int(values["PANEL_H_BACK_PORCH_"])
        SendTimings()
    if event == "PANEL_H_ACTIVE_":
        PANEL_H_ACTIVE = int(values["PANEL_H_ACTIVE_"])
        SendTimings()
    if event == "PANEL_H_FRONT_PORCH_":
        PANEL_H_FRONT_PORCH = int(values["PANEL_H_FRONT_PORCH_"])
        SendTimings()
    #
    if event == "PANEL_V_SYNC_WIDTH_":
        PANEL_V_SYNC_WIDTH = int(values["PANEL_V_SYNC_WIDTH_"])
        SendTimings()
    if event == "PANEL_V_BACK_PORCH_":
        PANEL_V_BACK_PORCH = int(values["PANEL_V_BACK_PORCH_"])
        SendTimings()
    if event == "PANEL_V_ACTIVE_":
        PANEL_V_ACTIVE = int(values["PANEL_V_ACTIVE_"])
        SendTimings()
    if event == "PANEL_V_FRONT_PORCH_":
        PANEL_V_FRONT_PORCH = int(values["PANEL_V_FRONT_PORCH_"])
        SendTimings()
