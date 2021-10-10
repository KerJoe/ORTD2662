#pragma once

#include "core/config_defines.h"
#include "config/board_config.h"
#include "config/misc_config.h"

//                              NEC                         RC-5
//  Detect Start Code           1: enable                   0: disable
//  Repeat code                 1: yes                      0: no
//  Input Inversion             0: disable                  1: enable
//  IRSamplingClock             = Xtal/512=24M/512          = Xtal/512=24M/512
//                              = 1/21.33 us                = 1/21.33 us
//  De-Bounce                   0x0A                        0x0A
//                              = 11 IRSampleCLK            = 11 IRSampleCLK
//  Burst Length                0x64 = 8.5ms < 9ms          X
//  Slience Length              0x32 = 4.2ms < 4.5ms        X
//  Repeat Length               0x19 = 2,1 ms < 2.25ms      X
//  Modulation Length           0x19 = 533us < 560us        0x29 = 874us < 900us
//  Data Zero Length            0x19 = 533us < 560us        X
//  Data One Length             0x4C = 1.62ms < 1.69ms      X
//  Infrared Control            0xDF                        0x0C
//                              Data bit coding = Length    Data bit coding = Phase
//                              Start code enable = True    Start code enable = False
//                              Codeing method = Normal     Codeing method = Normal
//                              # Data bit = 32             # Data bit = 13
//                                                          (note: 1st address bit is
//                                                          used as start condition)
//  One Command Time            0xA0 = 109ms < 110ms        0xA5 = 112.6ms < 113.8ms
//  Idle Time                   0xA3 = 111ms > 110ms        X

#define IR_CLK_DIV1024  3
#define IR_CLK_DIV512   0
#define IR_CLK_DIV256   2
#define IR_CLK_DIV128   1

#define IR_PHASE_CODING     0
#define IR_LENGTH_CODING    1

#define IR_CLK_DIV_VAL  (IR_SAMPLING_CLK == IR_CLK_DIV1024 ? 1024 : \
                        (IR_SAMPLING_CLK == IR_CLK_DIV512  ? 512  : \
                        (IR_SAMPLING_CLK == IR_CLK_DIV256  ? 256  : 128)))

#define IR_MS_TO_VAL(__MS)     BOARD_FREQ / 1000 * __MS / IR_CLK_DIV_VAL(IR_SAMPLING_CLK)
#define IR_MS_TO_VAL_X4(__MS)  IR_MS_TO_VAL(__MS) / 4
#define IR_MS_TO_VAL_X32(__MS) IR_MS_TO_VAL(__MS) / 32

#if IR_PROTOCOL == IR_NEC
#   define IR_DETECT_START      0
#   define IR_REPEAT_CODE       1
#   define IR_INVERT_INPUT      0
#   define IR_SAMPLING_CLK      IR_CLK_DIV512
#   define IR_DEBOUNCE_TMR      10
#   define IR_BURST_LENGTH      IR_MS_TO_VAL_X4(8.5)
#   define IR_SILENCE_LENGTH    IR_MS_TO_VAL_X4(4.2)
#   define IR_REPEAT_LENGTH     IR_MS_TO_VAL_X4(2.1)
#   define IR_MOD_LENGTH        IR_MS_TO_VAL(0.533)
#   define IR_DATA_ZERO_LENGTH  IR_MS_TO_VAL(0.533)
#   define IR_DATA_ONE_LENGTH   IR_MS_TO_VAL(1.62)
#   define IR_CODING_METHOD     IR_LENGTH_CODING
#   define IR_INVERT_CODE       0
#   define IR_BIT_NUMBER        32
#   define IR_ONE_COMMAND_TIME  IR_MS_TO_VAL_X32(109)
#   define IR_IDLE_TIME         IR_MS_TO_VAL_X32(110)
#endif
