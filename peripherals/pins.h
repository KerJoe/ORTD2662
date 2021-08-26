#pragma once

#include <stdint.h>

#include "peripherals/sfr.h"
#include "peripherals/xsfr.h"

// Pin No.  GPIO Name   Special functions (Pin share value)
// 50       P6_0        ADCA0 (0b011), AVOUT (0b100), VCLK (0b101)
// 51       P6_1        ADCA1 (0b11)
// 52       P6_2        ADCA2 (0b11)
// 53       P6_3        ADCA3 (0b11)
// 54       P6_4        ADCA4 (0b11)
// 55       P6_5        ADCA0 (0b11)
// 56       P6_6        ADCB2 (0b11)
// 57       P6_7        ADCA0 (0b11)
// 58       P3_0        RXD (0b11)
// 59       P3_1        TXD (0b11)
// 64       P1_0        T2 (0b011), SD0 (0b100), SPDIF0 (0b101), TCON[0] (0b110), IrDA (0b111)
// 65       P1_1        T2EX (0b011), TCON[1] (0b100), TCON[7] (0b101), WS (0b110), PWM1 (0b111)
// 66       P1_2        CLKO (0b011), SCK (0b100), TCON[2] (0b101), TCON[4] (0b110), BLU7 (If single-port 8-bit TTL)
// 67       P1_3        MCK (0b011), TCON[5] (0b100), TCON[9] (0b101), BLU6 (If single-port 8-bit TTL)
// 68       P1_4        SD0 (0b011), TCON[3] (0b100), TCON[13] (0b101), SPDIF0 (0b110), I2CSCL (0b111), BLU5 (If single-port 8-bit TTL)
// 69       P1_5        SD1 (0b011), TCON[3] (0b100), TCON[7] (0b101), SPDIF1 (0b110), I2CSCL (0b111), BLU4 (If single-port 8-bit TTL)
// 70       P1_6        SD2 (0b011), TCON[9] (0b100), TCON[11] (0b101), SPDIF2 (0b110), I2CSDA (0b111), BLU3 (If single-port 8-bit TTL)
// 71       P1_7        SD3 (0b0011), TCON[8] (0b0100), TCON[10] (0b0101), SPDIF3 (0b0110), PWM1 (0b0111), PWM5 (0b1000), BLU2 (If single-port 8-bit TTL)
// 74       P9_0        TTL BLU1/BLU7, LVDS TXO3+
// 75       P9_1        TTL BLU0/BLU6, LVDS TXO3-
// 76       P9_2        TTL GRN7/BLU5, LVDS TXOC+
// 77       P9_3        TTL GRN6/BLU4, LVDS TXOC-
// 78       P9_4        TTL GRN5/BLU3, LVDS TXO2+
// 79       PA_0        TTL GRN4/BLU2, LVDS TXO2-
// 80       PA_1        TTL GRN3/GRN7, LVDS TXO1+
// 81       PA_2        TTL GRN2/GRN6, LVDS TXO1-
// 82       PA_3        TTL GRN1/GRN5, LVDS TXO0+
// 83       PA_4        TTL GRN0/GRN4, LVDS TXO0-
// 96       P5_2        PWM0 (0b011), DCLK (0b100)
// 97       P5_3        PWM1 (0b011), DVS (0b100)
// 98       P5_4        PWM2 (0b11)
// 99       P5_5        PWM3 (0b011), TCON[6] (0b100), TCON[11] (0b101)
// 100      P5_6        PWM4 (0b011), TCON[3] (0b100), TCON[12] (0b101)
// 101      P5_7        PWM5 (0b011), TCON[0] (0b100)
// 102      P7_6        SD3 (0b011), SPDIF3 (0b100), TCON[10] (0b101)
// 103      P7_5        PWM1 (0b011), SD2 (0b100), SPDIF2 (0b101), TCON[8] (0b110), I2CSCL (0b111)
// 104      P7_4        SD1 (0b011), IRQ (0b100), TCON[5] (0b101), SPDIF1 (0b110), I2CSDA (0b111)
// 105      P8_0        TCON[9] (0b011), SD0 (0b100), SPDIF0 (0b101),
// 108      P8_1        CLKO (0b011), MCK (0b100), TCON[7] (0b101)
// 109      P3_2        INT0 (0b011), TCON[3] (0b100), SCK (0b101)
// 110      P3_3        INT1 (0b011), TCON[6] (0b100), WS (0b101)
// 111      P3_4        T0 (0b011), TCON[4] (0b100), SD0 (0b101), SPDIF0 (0b110)
// 112      P3_5        T1 (0b011), TCON[9] (0b100), SD1 (0b101), SPDIF1 (0b110)
// 113      P3_6        TCON[1] (0b011), SD2 (0b100), SPDIF2 (0b101), IrDA (0b110)
// 114      P3_7        TCON[13] (0b011), SD3 (0b100), SPDIF3 (0b101), VCLK (0b110)
// 121      P7_3        DDCSCL3 (0b00 -> 0b11) // Pass 0b11 to SetGPIOShare function
// 122      P7_2        DDCSDA3 (0b00 -> 0b11) // to enable DDC I2C
// 123      P7_1        DDCSDA2 (0b00 -> 0b11) // Changed for consistency
// 124      P7_0        DDCSCL2 (0b00 -> 0b11)

typedef struct
{
    uint16_t PIN_SHARE_ADDRESS;
    uint8_t  BIT_OFFSET;
    uint8_t  ENTRY_SIZE;
} _PIN_SHARE_GPIO_STRUCT;

/*
typedef struct
{
    uint16_t ADDRESS;
    uint8_t  BIT_OFFSET;
    uint8_t  BIT_SIZE;
} AOS_STRUCT; // Address Offset Size struct
*/

#define INPUT           0b00
#define OPEN_DRAIN_OUT  0b01
#define PUSH_PULL_OUT   0b10

enum _GPIO
{
    GPIO10, PIN064 = GPIO10,
    GPIO11, PIN065 = GPIO11,
    GPIO12, PIN066 = GPIO12,
    GPIO13, PIN067 = GPIO13,
    GPIO14, PIN068 = GPIO14,
    GPIO15, PIN069 = GPIO15,
    GPIO16, PIN070 = GPIO16,
    GPIO17, PIN071 = GPIO17,
    GPIO30, PIN058 = GPIO30,
    GPIO31, PIN059 = GPIO31,
    GPIO32, PIN109 = GPIO32,
    GPIO33, PIN110 = GPIO33,
    GPIO34, PIN111 = GPIO34,
    GPIO35, PIN112 = GPIO35,
    GPIO36, PIN113 = GPIO36,
    GPIO37, PIN114 = GPIO37,
    GPIO52, PIN096 = GPIO52,
    GPIO53, PIN097 = GPIO53,
    GPIO54, PIN098 = GPIO54,
    GPIO55, PIN099 = GPIO55,
    GPIO56, PIN100 = GPIO56,
    GPIO57, PIN101 = GPIO57,
    GPIO60, PIN050 = GPIO60,
    GPIO61, PIN051 = GPIO61,
    GPIO62, PIN052 = GPIO62,
    GPIO63, PIN053 = GPIO63,
    GPIO64, PIN054 = GPIO64,
    GPIO65, PIN055 = GPIO65,
    GPIO66, PIN056 = GPIO66,
    GPIO67, PIN057 = GPIO67,
    GPIO70, PIN124 = GPIO70,
    GPIO71, PIN123 = GPIO71,
    GPIO72, PIN122 = GPIO72,
    GPIO73, PIN121 = GPIO73,
    GPIO74, PIN104 = GPIO74,
    GPIO75, PIN103 = GPIO75,
    GPIO76, PIN102 = GPIO76,
    GPIO80, PIN105 = GPIO80,
    GPIO81, PIN108 = GPIO81,
    GPIO90, PIN074 = GPIO90,
    GPIO91, PIN075 = GPIO91,
    GPIO92, PIN076 = GPIO92,
    GPIO93, PIN077 = GPIO93,
    GPIO94, PIN078 = GPIO94,
    GPIOA0, PIN079 = GPIOA0,
    GPIOA1, PIN080 = GPIOA1,
    GPIOA2, PIN081 = GPIOA2,
    GPIOA3, PIN082 = GPIOA3,
    GPIOA4, PIN083 = GPIOA4,
    GPIO_P9_PA, // Ports 9 and A can only be set as a whole for Input or Push-Pull Output
    // Non GPIO (Scaler) pins
    PIN41,
    PIN42,
    PIN43,
    PIN44,
    PIN45,
    PIN46,
    PIN47,
    PIN48,
};

void SetGPIO(uint8_t gpio, uint8_t state);
uint8_t GetGPIO(uint8_t gpio);

#define PIN_SHARE_NUMBER(__num) (0xFF96 + __num)

extern const _PIN_SHARE_GPIO_STRUCT PIN_SHARE_GPIO_STRUCT[];

void SetGPIOShare(uint8_t share_gpio, uint8_t portType);

#define DRIVE_50_TO_54   0x07
#define DRIVE_55_TO_57   0x06
#define DRIVE_58_TO_59   0x05
#define DRIVE_64_TO_67   0x04
#define DRIVE_68_TO_71   0x03
#define DRIVE_74_TO_95   0x01
#define DRIVE_96_TO_97   0x00
#define DRIVE_98_TO_103  0x17
#define DRIVE_104_TO_105 0x16
#define DRIVE_108_TO_114 0x15
#define DRIVE_115_TO_118 0x14
#define DRIVE_121_TO_124 0x13

#define DRIVE_LOW  0
#define DRIVE_HIGH 1
#define DRIVE_LVDS_2500UA 0
#define DRIVE_LVDS_3000UA 1
#define DRIVE_LVDS_3500UA 2
#define DRIVE_LVDS_4000UA 3

void SetGPIODrivingCurrent(uint8_t pin_range, uint8_t current);