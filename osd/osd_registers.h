#pragma once

// Start/End position include the special effect: All Windows
// Shadow/Border/3D Button:         All Windows
// Gradient function:               Windows 0, 5, 6, 7
// Start/End resolution 1 pixel:    Windows 4, 5, 6, 7
// Start/End resolution 4 pixels:   Windows 0, 1, 2, 3
// Font comes after windows by 10 pixels

#define OSD_FRAME_CONTROL0          0x000
#define OSD_FRAME_CONTROL1          0x003
#define OSD_CHAR_FONT_ADDRESSES     0x004
#define OSD_COMPRESSION0            0x005
#define OSD_COMPRESSION1            0x006
#define OSD_COMPRESSION2            0x007
#define OSD_SPECIAL_CONTROL         0x008
#define OSD_SPECIAL_FONT_OFFSET     0x009
#define OSD_SPECIAL_BOUNDARY        0x00A

#define OSD_WINDOW_EFFECT(__num)    0x100 + __num * 4
#define OSD_WINDOW_START(__num)     0x101 + __num * 4
#define OSD_WINDOW_END(__num)       0x102 + __num * 4
#define OSD_WINDOW_CONTROL(__num)   0x103 + __num * 4


#define OSD_BYTE0   (0 << 14)
#define OSD_BYTE1   (1 << 14)
#define OSD_BYTE2   (2 << 14)
#define OSD_BYTEALL (3 << 14)

#define OSD_BUFFER  (1 << 13)


enum CharAlignment
{
    ALIGN_MIDDLE,
    ALIGN_LEFT,
    ALIGN_RIGHT,
};

#define OSD_SPECIAL_ROLL_UP 0
#define OSD_SPECIAL_POP_ON  1