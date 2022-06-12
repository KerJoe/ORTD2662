import sys, os
sys.path.append(os.path.dirname(os.path.abspath(__file__+"../../")))

from i2c_iface import *
import PySimpleGUI as sg

HStart = 10
HActive = 720
HDelay = 10
VStart = 10
VActive = 480
VDelay = 10

def SendWindow():
    ScalerWriteBits(0x14, 0, 4, HStart >> 8)
    ScalerWriteByte(0x15, HStart)
    ScalerWriteBits(0x18, 0, 4, VStart >> 8)
    ScalerWriteByte(0x19, VStart)
    ScalerWriteBits(0x16, 0, 4, HActive >> 8)
    ScalerWriteByte(0x17, HActive)
    ScalerWriteBits(0x1A, 0, 4, VActive >> 8)
    ScalerWriteByte(0x1B, VActive)
    ScalerWriteBits(0x1E, 0, 1, HDelay >> 8)
    ScalerWriteByte(0x1D, HDelay)
    ScalerWriteBits(0x1E, 1, 1, VDelay >> 8)
    ScalerWriteByte(0x1C, VDelay)

    ScalerWritePortByte(0x31, 0x00, ((HActive >> 8) << 4) | (VActive >> 8))
    ScalerWritePortByte(0x31, 0x01,  HActive)
    ScalerWritePortByte(0x31, 0x02,  VActive)

# Window layout
mainLayout = [[sg.Text("HStart"),  sg.Slider(range=(0,2**12-1), orientation='horizontal', default_value=HStart,  key="HStart",  enable_events=True, size=(80, 16))],
              [sg.Text("HActive"), sg.Slider(range=(0,2**12-1), orientation='horizontal', default_value=HActive, key="HActive", enable_events=True, size=(80, 16))],
              [sg.Text("HDelay"),  sg.Slider(range=(0,2**9-1),  orientation='horizontal', default_value=HDelay,  key="HDelay",  enable_events=True, size=(80, 16))],
              [sg.HorizontalSeparator()],
              [sg.Text("VStart"),  sg.Slider(range=(0,2**12-1), orientation='horizontal', default_value=VStart,  key="VStart",  enable_events=True, size=(80, 16))],
              [sg.Text("VActive"), sg.Slider(range=(0,2**12-1), orientation='horizontal', default_value=VActive, key="VActive", enable_events=True, size=(80, 16))],
              [sg.Text("VDelay"),  sg.Slider(range=(0,2**9-1),  orientation='horizontal', default_value=VDelay,  key="VDelay",  enable_events=True, size=(80, 16))]]

mainWindow = sg.Window('RTDMultiProg', mainLayout, element_justification='center')
while (True):
    event, values = mainWindow.read(timeout=10)
    if event == sg.WIN_CLOSED:
        break
    if event == "HStart":
        HStart = int(values["HStart"])
        SendWindow()
    if event == "HActive":
        HActive = int(values["HActive"])
        SendWindow()
    if event == "HDelay":
        HDelay = int(values["HDelay"])
        SendWindow()
    #
    if event == "VStart":
        VStart = int(values["VStart"])
        SendWindow()
    if event == "VActive":
        VActive = int(values["VActive"])
        SendWindow()
    if event == "VDelay":
        VDelay = int(values["VDelay"])
        SendWindow()
