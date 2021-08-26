#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "peripherals/xsfr.h"
#include "scaler/scaler_access.h"
#include "scaler/scaler.h"

#include "peripherals/timer.h"

#include "osd/1bit_font.h"

#include "osd/osd_registers.h"
#include "osd/osd.h"



const uint8_t palette[16][3]=
{
    {0x00, 0x00, 0x00}, // TRANSPARENT/BLACK
    {0xFF, 0xFF, 0xFF}, // WHITE
    {0xC0, 0xC0, 0xC0}, // LIGHT GRAY
    {0x80, 0x80, 0x80}, // DARK GRAY
    {0x80, 0x00, 0x00}, // RED
    {0xFF, 0x00, 0x00}, // MAROON
    {0xFF, 0xFF, 0x00}, // YELLOW
    {0xFF, 0x80, 0x00}, // ORANGE
    {0x00, 0xFF, 0x00}, // LIME
    {0x00, 0x80, 0x00}, // GREEN
    {0x00, 0xFF, 0xFF}, // AQUA
    {0x00, 0x80, 0x80}, // TEAL
    {0x00, 0x00, 0xFF}, // BLUE
    {0x00, 0x00, 0x80}, // NAVY
    {0xFF, 0x00, 0xFF}, // FUCHSIA
    {0x80, 0x00, 0x80}, // PURPLE
};

#define TEXT_FG_COLOR       1
#define TEXT_BG_COLOR       0
#define WINDOW_COLOR        5
#define WINDOW_BORDER_COLOR 2

const OSDWindow defaultWindow =
{
    .enable = 1,
    .color = WINDOW_COLOR,
    .borderColor = WINDOW_BORDER_COLOR,
    .gradientEnable = 0,
    .effectEnable = 1,
    .effectHeight = 1,
    .effectWidth = 1,
    .effectType = 7,
};

const OSDRow defaultRow =
{
    .notStop = 1,
    .charHeight2X = 0,
    .charWidth2X = 0,
    .charEffect = 0,
    .vbiFunction = 1,
};


void OSDWriteByte(uint16_t address, uint8_t data)
{
    // TODO: Datasheet sugest delay for OSD write on high speeds
    ScalerWriteByte(S_OSD_ADDRESS_HI, address >> 8);
    ScalerWriteByte(S_OSD_ADDRESS_LO, address);
    ScalerWriteByte(S_OSD_PORT, data);
}

void OSDWriteTriplet(uint16_t address, uint8_t byte0, uint8_t byte1, uint8_t byte2)
{
    ScalerWriteByte(S_OSD_ADDRESS_HI, (address | OSD_BYTEALL) >> 8);
    ScalerWriteByte(S_OSD_ADDRESS_LO, address);
    ScalerWriteByte(S_OSD_PORT, byte0);
    ScalerWriteByte(S_OSD_PORT, byte1);
    ScalerWriteByte(S_OSD_PORT, byte2);
}

void OSDWriteTriplets(uint16_t address, uint8_t* data, uint16_t count)
{
    ScalerWriteByte(S_OSD_ADDRESS_HI, (address | OSD_BYTEALL) >> 8);
    ScalerWriteByte(S_OSD_ADDRESS_LO, address);
    for (uint16_t i = 0; i < count; i++)
        ScalerWriteByte(S_OSD_PORT, *data);
}

uint8_t OSDReadByte(uint16_t address)
{
    ScalerWriteByte(S_OSD_ADDRESS_HI, address >> 8);
    ScalerWriteByte(S_OSD_ADDRESS_LO, address);
    return ScalerReadByte(S_OSD_PORT);
}

void UploadColorPallete(uint8_t pallete[][3])
{
    ScalerWriteByte(S_OVERLAY_LUT_ADDRESS, 0x80 | 0);
    for (int i = 0; i < 16; i++)
        for (int k = 0; k < 3; k++)
            ScalerWriteByte(S_COLOR_LUT_PORT, pallete[i][k]);
}

// TODO: Try to find ways to increase speed
void UploadFont_1Bit_8x16(uint8_t font[][16])
{
    ScalerWriteByte(S_OSD_ADDRESS_HI, (0x13 >> 0) | (0b11 << 6));
    ScalerWriteByte(S_OSD_ADDRESS_LO, 0x00);
    EnableScalerAutoIncrement(0);
    SCALER_ADDRESS = S_OSD_PORT;
    for (uint16_t i = 0; i < 128; i++)
        for (uint8_t k = 1; k < 19; k+=2)
        {
            SCALER_DATA = font[i][k] << 4;
            SCALER_DATA = font[i][k] >> 4;
            SCALER_DATA = font[i][k-1];
        }
}

// Horizontal: Total 1024 steps, 4 pixels per step, minimum 2
// Vertical: Total 2048 steps, 1 pixel per step, minimum 1
void SetOSDOffset(uint16_t hor, uint16_t ver)
{
    hor = hor / 4;
    OSDWriteByte0(OSD_FRAME_CONTROL0, ver >> 3);
    OSDWriteByte1(OSD_FRAME_CONTROL0, hor >> 2);
    OSDWriteByte2(OSD_FRAME_CONTROL0, InsertBits8(OSDReadByte2(OSD_FRAME_CONTROL0),
                  3, 5, ((hor & 0b11) << 3) | (ver & 0b111)));
    delayMS(4); // HACK: Really crappy solution, find a better way to insure reading of OSD_FRAME_CONTROL0 is done after its double buffer is empty
    // TODO: Try address 003h, byte 2, bit 5
}

void OSDEnable(uint8_t state)
{
    EnableOverlay(1);
    OSDWriteByte2(OSD_FRAME_CONTROL0, InsertBits8(OSDReadByte2(OSD_FRAME_CONTROL0),
                  0, 1, state));
    delayMS(4); // HACK: Really crappy solution, find a better way to insure reading of OSD_FRAME_CONTROL0 is done after its double buffer is empty
}

void SetOSDCharAlignment(uint8_t state)
{
    OSDWriteByte2(OSD_FRAME_CONTROL0, InsertBits8(OSDReadByte2(OSD_FRAME_CONTROL0),
                  1, 2, state));
    delayMS(4); // HACK: Really crappy solution, find a better way to insure reading of OSD_FRAME_CONTROL0 is done after its double buffer is empty
}

void OSDSetWindow(OSDWindow* window, uint8_t windowNumber)
{

    OSDWriteTriplet(OSD_WINDOW_EFFECT(windowNumber),  (window->effectWidth << 3) | window->effectHeight,
                                                      (window->shadowColor << 4) | window->borderColor,
                                                      (window->gradientRedPolarity << 7) | (window->gradientGreenPolarity << 6) | (window->gradientRedPolarity << 5) | (window->gradientSteps << 3) | (window->gradientRedEnable << 2) | (window->gradientGreenEnable << 1) | window->gradientBlueEnable);
    OSDWriteTriplet(OSD_WINDOW_START(windowNumber),   window->horStart << 2,
                                                      (window->verStart << 5) | (window->horStart >> 6),
                                                      window->horStart >> 3);
    OSDWriteTriplet(OSD_WINDOW_END(windowNumber),     window->horEnd << 2,
                                                      (window->verEnd << 5) | (window->horEnd >> 6),
                                                      window->horEnd >> 3);
    OSDWriteTriplet(OSD_WINDOW_CONTROL(windowNumber), 0,
                                                      (window->gradientLevel << 4) | window->color,
                                                      (window->gradientEnable << 6) | (window->gradientDirection << 5) | (window->effectEnable << 4) | (window->effectType << 1) | window->enable);
}

void OSDSetRow(OSDRow* row, uint8_t rowNumber)
{
    OSDWriteTriplet(0x1000 + rowNumber, (row->notStop << 7) | (row->vbiFunction << 6) | (row->charEffect << 2) | (row->charWidth2X << 1) | row->charHeight2X,
                                        (row->height << 3)  | row->width,
                                        row->length);
}

void OSDEndRow(uint8_t rowNumber)
{
    OSDWriteByte0(0x1000 + rowNumber, 0x00);
}

void OSDSetChar1(OSDCharacter1* ch1, uint8_t ch1Number)
{
    OSDWriteTriplet(OSD_CHAR_ADDRESS + ch1Number, (1 << 7) | (ch1->blinking << 6) | ch1->width,
                                                  ch1->character,
                                                  (ch1->fgColor << 4) | ch1->bgColor);
}

void OSDSetBlank(OSDCharacterBlank* chb, uint8_t chbNumber)
{
    OSDWriteTriplet(OSD_CHAR_ADDRESS + chbNumber, (0 << 7) | (chb->blinking << 6),
                                                  chb->length,
                                                  chb->color);
}

void OSDInit()
{
    UploadColorPallete(palette);
    SetOSDOffset(20, 18); // Magic numbers to set offset to start from top-left corner

    OSDWriteByte(0x1000, 0x00); // Set first row to stop

    UploadFont_1Bit_8x16(font_1bit);

    OSDWriteTriplet(OSD_CHAR_FONT_ADDRESSES, OSD_CHAR_OFFSET + 0x1000,
                                             (((OSD_CHAR_OFFSET + 0x1000) >> 8) << 4) | ((OSD_FONT_OFFSET + 0x1000) & 0xFF),
                                             (OSD_FONT_OFFSET + 0x1000) >> 4);
    SetOSDCharAlignment(ALIGN_LEFT);

    OSDWindow tst;
    memcpy(&tst, &defaultWindow, sizeof(OSDWindow));
    tst.horStart = 128;
    tst.verStart = 128;
    tst.horEnd = tst.horStart + 100;
    tst.verEnd = tst.verStart + 100;
    OSDSetWindow(&tst, 0);

    OSDEnable(1);
}
