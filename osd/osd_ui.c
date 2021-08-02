#include <string.h>
#include <stdio.h>

#include "osd/osd_ui.h"
#include "osd/osd.h"

// NOTE: Must be even
#define MENU_WIDTH 16

// NOTE: Struct assignment for non constant structs is broken in SDCC
const OSDRow MenuRowConst =
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
OSDRow MenuRow;

const OSDCharacter1 MenuBarCharConst =
{
    .fontSize = 0,
    .width = 8,
    .blinking = 0,
    .isVisible = 1,
    .character = 'X',
    .bgColor = 3,
    .fgColor = 1,
};
OSDCharacter1 MenuBarChar;

const OSDCharacter1 MenuEntryCharConst =
{
    .fontSize = 0,
    .width = 8,
    .blinking = 0,
    .isVisible = 1,
    .character = 'X',
    .bgColor = 2,
    .fgColor = 1,
};
OSDCharacter1 MenuEntryChar;

uint8_t RowLenghtArray[OSD_CHAR_OFFSET];

void OSDWriteRow(OSDRow* row, OSDCharacter1* ch, uint8_t rowNumber, char* str)
{
    RowLenghtArray[rowNumber] = strlen(str);
    row->length = RowLenghtArray[rowNumber];
    OSDSetRow(row, rowNumber);
    uint16_t chStart = 0;
    for (uint16_t i = 0; i < rowNumber; i++)
    {
        chStart += RowLenghtArray[i];
    }
    for (uint16_t i = 0; i < RowLenghtArray[rowNumber]; i++)
    {
        ch->character = str[i];
        OSDSetChar1(ch, i + chStart);
    }
}

void OSDWriteRowPad(OSDRow* row, OSDCharacter1* ch, uint8_t rowNumber, char* str, uint8_t RowLength)
{
    RowLenghtArray[rowNumber] = RowLength;
    row->length = RowLenghtArray[rowNumber];
    OSDSetRow(row, rowNumber);
    uint16_t chStart = 0;
    char str_len = strlen(str);
    for (uint16_t i = 0; i < rowNumber; i++)
    {
        chStart += RowLenghtArray[i];
    }
    for (uint16_t i = 0; i < RowLenghtArray[rowNumber]; i++)
    {
        ch->character = i < str_len ? str[i] : 0x20;
        OSDSetChar1(ch, i + chStart);
    }
}

void OSDCreateMenu(char* title, char* menuItems[], uint8_t menuItemsNum)
{
    memcpy(&MenuRow, &MenuRowConst, sizeof(OSDRow));
    memcpy(&MenuBarChar, &MenuBarCharConst, sizeof(OSDCharacter1));
    memcpy(&MenuEntryChar, &MenuEntryCharConst, sizeof(OSDCharacter1));

    SetOSDOffset(50, 50);

    OSDWriteRowPad(&MenuRow, &MenuBarChar, 0, "Menu", MENU_WIDTH);
    /*OSDWriteRowPad(&MenuRow, &MenuEntryChar, 1, "Test", MENU_WIDTH);
    OSDEndRow(2);*/

    uint8_t menuCount;
    for (menuCount = 0; menuCount < menuItemsNum; menuCount++)
        OSDWriteRowPad(&MenuRow, &MenuEntryChar, menuCount+1, menuItems[menuCount], MENU_WIDTH);
    OSDEndRow(menuCount+1);
}