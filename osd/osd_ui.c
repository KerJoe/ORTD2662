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

const OSDCharacterBlank BlankCharConst =
{
    .blinking = 0,
    .isVisible = 0,
    .length = 12,
    .color = 3,
};
OSDCharacterBlank BlankChar;

/*
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
    //OSDWriteRowPad(&MenuRow, &MenuEntryChar, 1, "Test", MENU_WIDTH);
    //OSDEndRow(2);

    uint8_t menuCount;
    for (menuCount = 0; menuCount < menuItemsNum; menuCount++)
        OSDWriteRowPad(&MenuRow, &MenuEntryChar, menuCount+1, menuItems[menuCount], MENU_WIDTH);
    OSDEndRow(menuCount+1);
}
*/

void OSDWriteCenteredRow(OSDRow* row, OSDCharacter1* ch, uint8_t rowNumber, char* str)
{
    OSDSetRow(row, rowNumber);
    char str_len = strlen(str);
    uint16_t charItr;
    if (str_len % 2) // If odd
    {
        OSDSetBlank(&BlankChar, MENU_WIDTH * rowNumber);
        charItr = 1;
        ch->character = 0x20;
        for(; charItr < (MENU_WIDTH - str_len) / 2; charItr++)
            OSDSetChar1(ch, charItr + MENU_WIDTH * rowNumber);
        for(; charItr < (MENU_WIDTH - str_len) / 2 + str_len; charItr++)
        {
            ch->character = str[charItr - (MENU_WIDTH - str_len) / 2];
            OSDSetChar1(ch, charItr + MENU_WIDTH * rowNumber);
        }
        ch->character = 0x20;
        for(; charItr < MENU_WIDTH; charItr++)
            OSDSetChar1(ch, charItr + MENU_WIDTH * rowNumber);
    }
    else // If even
    {
        charItr = 0;
        ch->character = 0x20;
        for(; charItr < (MENU_WIDTH - str_len) / 2; charItr++)
            OSDSetChar1(ch, charItr + MENU_WIDTH * rowNumber);
        for(; charItr < (MENU_WIDTH - str_len) / 2 + str_len; charItr++)
        {
            ch->character = str[charItr - (MENU_WIDTH - str_len) / 2];
            OSDSetChar1(ch, charItr + MENU_WIDTH * rowNumber);
        }
        ch->character = 0x20;
        for(; charItr < MENU_WIDTH; charItr++)
            OSDSetChar1(ch, charItr + MENU_WIDTH * rowNumber);
    }
}

void OSDCreateMenu(char* title, char* menuItems[], uint8_t menuItemsNum)
{
    memcpy(&MenuRow, &MenuRowConst, sizeof(OSDRow));
    memcpy(&MenuBarChar, &MenuBarCharConst, sizeof(OSDCharacter1));
    memcpy(&MenuEntryChar, &MenuEntryCharConst, sizeof(OSDCharacter1));
    memcpy(&BlankChar, &BlankCharConst, sizeof(OSDCharacterBlank));

    SetOSDOffset(50, 50);

    OSDWriteCenteredRow(&MenuRow, &MenuBarChar, 0, "Menus");
    OSDWriteCenteredRow(&MenuRow, &MenuBarChar, 1, "Menu");
    OSDEndRow(2);
}