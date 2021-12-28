#pragma once
#include <stdint.h>

void OSDCreateMenu(char* title, char* menuItems[], uint8_t menuItemsNum);
void OSDActionUp();
void OSDActionDown();
void OSDActionSelect();