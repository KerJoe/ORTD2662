#pragma once

#include "core/config_defines.h"

/**
 * Panel interface select
**/

#define PANEL_TYPE LVDS

#define PANEL_DOUBLE_PORT 0
#define PANEL_18_BIT      0

/**
 * Panel resolution and timings
**/
//          |HPW|   HBP   |     HACT     | HFP |
//          ┐   ┌───────────────────────────────
//          └───┘         |              |     |
// ---- └─┐ +----------------------------------+
//  VPW   │ |             |              |     |
// ---- ┌─┘ |                                  |
//  VBP │   |             |              |     |
// ---- │- -|- - - - - - -+--------------+     |
//      │   |             |              |     |
// VACT │   |             | ACTIVE VIDEO |     |
//      │   |             |              |     |
// ---- │- -|- - - - - - -+--------------+     |
//  VFP │   |                                  |
// ---- │   +----------------------------------+
//

// Panel pixel clock (aka data clock) (Hz)
#define PANEL_DCLK          50250000UL

// Horizontal timings
#define PANEL_H_SYNC_WIDTH  54     // HPW
#define PANEL_H_BACK_PORCH  129    // HBP
#define PANEL_H_ACTIVE      1024   // HACT, AKA: Horizontal resolution
#define PANEL_H_FRONT_PORCH 146    // HFP

// Vertical timings
#define PANEL_V_SYNC_WIDTH  5      // VPW
#define PANEL_V_BACK_PORCH  10     // VBP
#define PANEL_V_ACTIVE      600    // VACT, AKA: Vertical resolution
#define PANEL_V_FRONT_PORCH 5      // VFP

/**
 * Panel signal polarity and data order
**/
#define PANEL_INVERT_DCLK       0
#define PANEL_INVERT_DHS        0
#define PANEL_INVERT_DVS        0
#define PANEL_INVERT_DEN        0

#define PANEL_SWAP_BIT_ORDER    0
#define PANEL_SWAP_RED_BLU      0
#define PANEL_SWAP_ODD_EVEN     0