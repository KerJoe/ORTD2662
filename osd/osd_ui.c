#include <string.h>
#include <stdio.h>

#include "osd/osd_ui.h"
#include "osd/osd.h"

// NOTE: Must be even
#define MENU_WIDTH 16

// Temporary place for Row and Character definitions
#define SetOSDUnion(__struct_pointer) memcpy(&OSDUnion, __struct_pointer, 3);
typedef union
{
    OSDRow              row;
    OSDCharacter1       ch1;
    OSDCharacterBlank   chb;
} _OSDUnion; _OSDUnion OSDUnion;

const OSDRow MenuRow =
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

const OSDCharacter1 MenuBarChar =
{
    .fontSize = 0,
    .width = 8,
    .blinking = 0,
    .isVisible = 1,
    .character = 'X',
    .bgColor = 3,
    .fgColor = 1,
};

const OSDCharacter1 MenuEntryChar =
{
    .fontSize = 0,
    .width = 8,
    .blinking = 0,
    .isVisible = 1,
    .character = 'X',
    .bgColor = 2,
    .fgColor = 1,
};

const OSDCharacterBlank BlankChar =
{
    .blinking = 0,
    .isVisible = 0,
    .length = 12,
    .color = 3,
};

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

uint8_t cursorPos, cursorMax;

void OSDWriteCenteredRow(OSDRow* row, OSDCharacter1* ch, uint8_t rowNumber, char* str)
{
    char str_len = strlen(str);
    uint16_t charItr;
    OSDSetRow(row, rowNumber);
    if (str_len % 2) // If odd
    {
        SetOSDUnion(&BlankChar);
        OSDUnion.chb.length = 12;
        OSDUnion.chb.color = ch->bgColor;
        OSDSetBlank(&OSDUnion.chb, MENU_WIDTH * rowNumber);
        charItr = 1;
        SetOSDUnion(ch);
        OSDUnion.ch1.character = 0x20;
        for(; charItr < (MENU_WIDTH - str_len) / 2; charItr++)
            OSDSetChar1(&OSDUnion.ch1, charItr + MENU_WIDTH * rowNumber);
        for(; charItr < (MENU_WIDTH - str_len) / 2 + str_len; charItr++)
        {
            OSDUnion.ch1.character = str[charItr - (MENU_WIDTH - str_len) / 2];
            OSDSetChar1(&OSDUnion.ch1, charItr + MENU_WIDTH * rowNumber);
        }
        OSDUnion.ch1.character = 0x20;
        for(; charItr < MENU_WIDTH-1; charItr++)
            OSDSetChar1(&OSDUnion.ch1, charItr + MENU_WIDTH * rowNumber);
        SetOSDUnion(&BlankChar);
        OSDUnion.chb.length = 4;
        OSDUnion.chb.color = ch->bgColor;
        OSDSetBlank(&OSDUnion.chb, MENU_WIDTH * rowNumber + MENU_WIDTH - 1);
    }
    else // If even
    {
        charItr = 0;
        SetOSDUnion(ch);
        OSDUnion.ch1.character = 0x20;
        for(; charItr < (MENU_WIDTH - str_len) / 2; charItr++)
            OSDSetChar1(&OSDUnion.ch1, charItr + MENU_WIDTH * rowNumber);
        for(; charItr < (MENU_WIDTH - str_len) / 2 + str_len; charItr++)
        {
            OSDUnion.ch1.character = str[charItr - (MENU_WIDTH - str_len) / 2];
            OSDSetChar1(&OSDUnion.ch1, charItr + MENU_WIDTH * rowNumber);
        }
        OSDUnion.ch1.character = 0x20;
        for(; charItr < MENU_WIDTH; charItr++)
            OSDSetChar1(&OSDUnion.ch1, charItr + MENU_WIDTH * rowNumber);
    }
}

void OSDWriteLeftRow(OSDRow* row, OSDCharacter1* ch, uint8_t rowNumber, char* str, char firstChar) // firstChar may be used for cursor
{
    char str_len = strlen(str);
    uint16_t charItr;
    OSDSetRow(row, rowNumber);
    SetOSDUnion(ch);
    OSDUnion.ch1.character = firstChar;
    OSDSetChar1(&OSDUnion.ch1, MENU_WIDTH * rowNumber);
    charItr = 0;
    for(; charItr < str_len; charItr++)
    {
        OSDUnion.ch1.character = str[charItr];
        OSDSetChar1(&OSDUnion.ch1, charItr + 1 + MENU_WIDTH * rowNumber);
    }
    OSDUnion.ch1.character = 0x20;
    for(; charItr < MENU_WIDTH; charItr++)
        OSDSetChar1(&OSDUnion.ch1, charItr + 1 + MENU_WIDTH * rowNumber);
}

void OSDCreateMenu(char* title, char* menuItems[], uint8_t menuItemsNum)
{
    /*SetOSDOffset(30, 18);
    OSDSetRow(&MenuRow, 0);
    OSDSetChar1(&MenuBarChar, 0);
    OSDEndRow(1);
    return;*/


    cursorPos = 0;
    cursorMax = menuItemsNum - 1;

    SetOSDOffset(200, 50);

    OSDWriteCenteredRow(&MenuRow, &MenuBarChar,   0, title);
    uint8_t i;
    for (i = 0; i < menuItemsNum; i++)
        OSDWriteLeftRow (&MenuRow, &MenuEntryChar, i+1, menuItems[i], i == 0 ? '>' : ' ');

    OSDEndRow(i+1);
}

void OSDActionUp()
{
    SetOSDUnion(&MenuEntryChar);
    OSDUnion.ch1.character = ' ';
    OSDSetChar1(&OSDUnion.ch1, MENU_WIDTH * (cursorPos + 1));
    if (cursorPos < cursorMax)
        cursorPos++;
    else
        cursorPos = 0;
    SetOSDUnion(&MenuEntryChar);
    OSDUnion.ch1.character = '>';
    OSDSetChar1(&OSDUnion.ch1, MENU_WIDTH * (cursorPos + 1));
}

void OSDActionDown()
{
    SetOSDUnion(&MenuEntryChar);
    OSDUnion.ch1.character = ' ';
    OSDSetChar1(&OSDUnion.ch1, MENU_WIDTH * (cursorPos + 1));
    if (cursorPos > 0)
        cursorPos--;
    else
        cursorPos = cursorMax;
    SetOSDUnion(&MenuEntryChar);
    OSDUnion.ch1.character = '>';
    OSDSetChar1(&OSDUnion.ch1, MENU_WIDTH * (cursorPos + 1));
}

void OSDActionSelect()
{

}