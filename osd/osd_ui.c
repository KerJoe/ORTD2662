#include <string.h>

#include "osd/osd_ui.h"
#include "osd/osd.h"

#define MENU_WIDTH 4

OSDRow MenuBarRow =
{
    .notStop = 1,
    .charHeight2X = 1,
    .charWidth2X = 1,
    .vbiFunction = 0,
    .charEffect = 0,
    .width  = 8,
    .height = 16,
    .length = MENU_WIDTH
};

OSDCharacter1 MenuChar =
{
    .fontSize = 0,
    .width = 8,
    .blinking = 0,
    .isVisible = 1,
    .character = 'X',
    .bgColor = 1,
    .fgColor = 4,
};

uint8_t RowLenghtArray[OSD_CHAR_OFFSET];

void OSDWriteRow(OSDRow* row, uint8_t rowNumber, char* str)
{
    RowLenghtArray[rowNumber] = strlen(str);
    row->length = RowLenghtArray[rowNumber];
    OSDSetRow(row, 0);
    uint16_t chStart = 0;
    for (uint16_t i = 0; i < rowNumber; i++)
    {
        chStart += RowLenghtArray[i];
    }
    for (uint16_t i = 0; i < RowLenghtArray[rowNumber]; i++)
    {
        OSDSetChar1(&MenuChar, i);
    }
}

void OSDCreateMenu(char* title, char* menuItems[])
{
    //OSDWriteTriplet(0x1000, )

    OSDSetRow(&MenuBarRow, 0);
    //OSDWriteRow(&MenuBarRow, 0, "Test");
    //OSDSetRow(&MenuBarRow, 1);
    OSDEndRow(1);
    for (int i = 0x00; i < 256; i++)
    {
        //MenuChar.character = i+0x20;
        OSDSetChar1(&MenuChar, i);
    }
}