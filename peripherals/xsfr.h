#pragma once

#include <stdint.h>

//-----------------------------------------------------------------------------
// Interrupt Control
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF00) IRQ_STATUS;
__xdata volatile uint8_t __at(0xFF01) IRQ_PRIORITY;

//-----------------------------------------------------------------------------
// Analog to Digital Converter
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF08) ADC_A_CONTROL;
__xdata volatile uint8_t __at(0xFF09) ADC_A0_DATA;
__xdata volatile uint8_t __at(0xFF0A) ADC_A1_DATA;
__xdata volatile uint8_t __at(0xFF0B) ADC_A2_DATA;
__xdata volatile uint8_t __at(0xFF0C) ADC_A3_DATA;
__xdata volatile uint8_t __at(0xFF0D) ADC_A4_DATA;

__xdata volatile uint8_t __at(0xFF0E) ADC_B_CONTROL;
__xdata volatile uint8_t __at(0xFF0F) ADC_B_THRESHOLD;
__xdata volatile uint8_t __at(0xFF10) ADC_B0_TARGET_HI;
__xdata volatile uint8_t __at(0xFF11) ADC_B1_TARGET_HI;
__xdata volatile uint8_t __at(0xFF12) ADC_B2_TARGET_HI;
__xdata volatile uint8_t __at(0xFF13) ADC_B_MEAS_T_HI;
__xdata volatile uint8_t __at(0xFF14) ADC_BX_TARGET_LO_MEAS_T_LO;
__xdata volatile uint8_t __at(0xFF15) ADC_B0_DATA_HI;
__xdata volatile uint8_t __at(0xFF16) ADC_B1_DATA_HI;
__xdata volatile uint8_t __at(0xFF17) ADC_B2_DATA_HI;
__xdata volatile uint8_t __at(0xFF18) ADC_BX_DATA_LO;

//-----------------------------------------------------------------------------
// Display Data Channel (I2C)
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF1B) DDC1_CONTROL0; // AKA: ADC DCC
__xdata volatile uint8_t __at(0xFF1C) DDC1_CONTROL1;
__xdata volatile uint8_t __at(0xFF1D) DDC1_CONTROL2;

__xdata volatile uint8_t __at(0xFF1E) DDC2_CONTROL0;
__xdata volatile uint8_t __at(0xFF1F) DDC2_CONTROL1;
__xdata volatile uint8_t __at(0xFF20) DDC2_CONTROL2;

__xdata volatile uint8_t __at(0xFF21) DDC_RAM_PARTITION;
__xdata volatile uint8_t __at(0xFF22) VSYNC_SEL;

__xdata volatile uint8_t __at(0xFF23) I2C_SLAVE_CONTROL;
__xdata volatile uint8_t __at(0xFF24) I2C_SLAVE_SUB_ADDRESS;
__xdata volatile uint8_t __at(0xFF25) I2C_SLAVE_DATA_IN;
__xdata volatile uint8_t __at(0xFF26) I2C_SLAVE_DATA_OUT;
__xdata volatile uint8_t __at(0xFF27) I2C_SLAVE_STATUS0;
__xdata volatile uint8_t __at(0xFF28) I2C_SLAVE_IRQ_CONTROL0;
__xdata volatile uint8_t __at(0xFF29) I2C_SLAVE_STATUS1;
__xdata volatile uint8_t __at(0xFF2A) I2C_SLAVE_IRQ_CONTROL1;
__xdata volatile uint8_t __at(0xFF2B) I2C_SLAVE_CHANNEL_CONTROL;

__xdata volatile uint8_t __at(0xFF2C) DDC3_CONTROL0;
__xdata volatile uint8_t __at(0xFF2D) DDC3_CONTROL1;
__xdata volatile uint8_t __at(0xFF2E) DDC3_CONTROL2;

__xdata volatile uint8_t __at(0xFF2F) DDC1_INDEX;
__xdata volatile uint8_t __at(0xFF30) DDC1_DATA;
__xdata volatile uint8_t __at(0xFF31) DDC2_INDEX;
__xdata volatile uint8_t __at(0xFF32) DDC2_DATA;
__xdata volatile uint8_t __at(0xFF33) DDC3_INDEX;
__xdata volatile uint8_t __at(0xFF34) DDC3_DATA;

//-----------------------------------------------------------------------------
// Pulse Width Modulation
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF3A) PWM_CLK_SEL;

__xdata volatile uint8_t __at(0xFF3B) PWM0123_DIV1;
__xdata volatile uint8_t __at(0xFF3C) PWM45_DIV1;

__xdata volatile uint8_t __at(0xFF3D) PWM01_DIV2_HI;
__xdata volatile uint8_t __at(0xFF3E) PWM0_DIV2_LO;
__xdata volatile uint8_t __at(0xFF3F) PWM1_DIV2_LO;
__xdata volatile uint8_t __at(0xFF40) PWM23_DIV2_HI;
__xdata volatile uint8_t __at(0xFF41) PWM2_DIV2_LO;
__xdata volatile uint8_t __at(0xFF42) PWM3_DIV2_LO;
__xdata volatile uint8_t __at(0xFF43) PWM45_DIV2_HI;
__xdata volatile uint8_t __at(0xFF44) PWM4_DIV2_LO;
__xdata volatile uint8_t __at(0xFF45) PWM5_DIV2_LO;

__xdata volatile uint8_t __at(0xFF46) PWM_L;
__xdata volatile uint8_t __at(0xFF47) PWM_DVS_RST;
__xdata volatile uint8_t __at(0xFF48) PWM_CONTROL;
__xdata volatile uint8_t __at(0xFF49) PWM_DIV_SEL;

__xdata volatile uint8_t __at(0xFF4A) PWM0_DATA_HI;
__xdata volatile uint8_t __at(0xFF4B) PWM1_DATA_HI;
__xdata volatile uint8_t __at(0xFF4C) PWM01_DATA_LO;
__xdata volatile uint8_t __at(0xFF4D) PWM2_DATA_HI;
__xdata volatile uint8_t __at(0xFF4E) PWM3_DATA_HI;
__xdata volatile uint8_t __at(0xFF4F) PWM23_DATA_LO;
__xdata volatile uint8_t __at(0xFF50) PWM4_DATA_HI;
__xdata volatile uint8_t __at(0xFF51) PWM5_DATA_HI;
__xdata volatile uint8_t __at(0xFF52) PWM45_DATA_LO;

//-----------------------------------------------------------------------------
// I2C Master
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF55) I2C_MASTER_CR0;
__xdata volatile uint8_t __at(0xFF56) I2C_MASTER_CR1;
__xdata volatile uint8_t __at(0xFF57) I2C_MASTER_CR2;
__xdata volatile uint8_t __at(0xFF58) I2C_MASTER_CR3;
__xdata volatile uint8_t __at(0xFF59) I2C_MASTER_STR0;
__xdata volatile uint8_t __at(0xFF5A) I2C_MASTER_STR1;
__xdata volatile uint8_t __at(0xFF5B) I2C_MASTER_STR2;
__xdata volatile uint8_t __at(0xFF5C) I2C_MASTER_STR3;
__xdata volatile uint8_t __at(0xFF5D) I2C_MASTER_SR;
__xdata volatile uint8_t __at(0xFF5E) I2C_MASTER_DATA;
__xdata volatile uint8_t __at(0xFF5F) I2C_MASTER_DIV;

//-----------------------------------------------------------------------------
// SPI Flash
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF60) CUSTOM_INSTRUCTION_CONTROL;
__xdata volatile uint8_t __at(0xFF61) CUSTOM_INSTRUCTION_OPCODE;
__xdata volatile uint8_t __at(0xFF62) WREN_OPCODE;
__xdata volatile uint8_t __at(0xFF63) EWSR_OPCODE;
__xdata volatile uint8_t __at(0xFF64) FLASH_WRITE_HI;
__xdata volatile uint8_t __at(0xFF65) FLASH_WRITE_MD;
__xdata volatile uint8_t __at(0xFF66) FLASH_WRITE_LO;
__xdata volatile uint8_t __at(0xFF67) CUSTOM_INSTRUCTION_READ_HI;
__xdata volatile uint8_t __at(0xFF68) CUSTOM_INSTRUCTION_READ_MD;
__xdata volatile uint8_t __at(0xFF69) CUSTOM_INSTRUCTION_READ_LO;
__xdata volatile uint8_t __at(0xFF6A) FLASH_READ_OPCODE;
__xdata volatile uint8_t __at(0xFF6B) FLASH_FAST_READ_OPCODE;
__xdata volatile uint8_t __at(0xFF6C) FLASH_READ_CONTROL;
__xdata volatile uint8_t __at(0xFF6D) FLASH_WRITE_OPCODE;
__xdata volatile uint8_t __at(0xFF6E) RDSR_OPCODE;
__xdata volatile uint8_t __at(0xFF6F) FLASH_WRITE_CONTROL;
__xdata volatile uint8_t __at(0xFF70) FLASH_WRITE_DATA;
__xdata volatile uint8_t __at(0xFF71) FLASH_WRITE_LENGTH;
__xdata volatile uint8_t __at(0xFF72) FLASH_CRC_END_HI;
__xdata volatile uint8_t __at(0xFF73) FLASH_CRC_END_MD;
__xdata volatile uint8_t __at(0xFF74) FLASH_CRC_END_LO;
__xdata volatile uint8_t __at(0xFF75) FLASH_CRC_RESULT;
__xdata volatile uint8_t __at(0xFF76) FLASH_CHIP_ENABLE_CONTROL;

//-----------------------------------------------------------------------------
// Infrared Reciever
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF80) IR_CONTROL0;
__xdata volatile uint8_t __at(0xFF81) IR_DEBOUNCE;
__xdata volatile uint8_t __at(0xFF82) IR_BURST_LENGTH;
__xdata volatile uint8_t __at(0xFF83) IR_SILENCE_LENGTH;
__xdata volatile uint8_t __at(0xFF84) IR_REPEAT_LENGTH;
__xdata volatile uint8_t __at(0xFF85) IR_MODULATION_LENGTH;
__xdata volatile uint8_t __at(0xFF86) IR_DATA0_LENGTH;
__xdata volatile uint8_t __at(0xFF87) IR_DATA1_LENGTH;
__xdata volatile uint8_t __at(0xFF88) IR_CONTROL1;
__xdata volatile uint8_t __at(0xFF89) IR_STATUS;
__xdata volatile uint8_t __at(0xFF8A) IR_DATA0;
__xdata volatile uint8_t __at(0xFF8B) IR_DATA1;
__xdata volatile uint8_t __at(0xFF8C) IR_DATA2;
__xdata volatile uint8_t __at(0xFF8D) IR_DATA3;
__xdata volatile uint8_t __at(0xFF8E) IR_DATA4;
__xdata volatile uint8_t __at(0xFF8F) IR_DATA5;
__xdata volatile uint8_t __at(0xFF90) IR_ONE_CMD_TIME;
__xdata volatile uint8_t __at(0xFF91) IR_IDLE_TIME;
__xdata volatile uint8_t __at(0xFF92) IR_CONTROL2;
__xdata volatile uint8_t __at(0xFF93) IR_IRQ;

//-----------------------------------------------------------------------------
// Pin Function Control
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF96) PIN_SHARE_CONTROL00;
__xdata volatile uint8_t __at(0xFF97) PIN_SHARE_CONTROL01;
__xdata volatile uint8_t __at(0xFF98) PIN_SHARE_CONTROL02;
__xdata volatile uint8_t __at(0xFF99) PIN_SHARE_CONTROL03;
__xdata volatile uint8_t __at(0xFF9A) PIN_SHARE_CONTROL04;
__xdata volatile uint8_t __at(0xFF9B) PIN_SHARE_CONTROL05;
__xdata volatile uint8_t __at(0xFF9C) PIN_SHARE_CONTROL06;
__xdata volatile uint8_t __at(0xFF9D) PIN_SHARE_CONTROL07;
__xdata volatile uint8_t __at(0xFF9E) PIN_SHARE_CONTROL08;
__xdata volatile uint8_t __at(0xFF9F) PIN_SHARE_CONTROL09;
__xdata volatile uint8_t __at(0xFFA0) PIN_SHARE_CONTROL10;
__xdata volatile uint8_t __at(0xFFA1) PIN_SHARE_CONTROL11;
__xdata volatile uint8_t __at(0xFFA2) PIN_SHARE_CONTROL12;
__xdata volatile uint8_t __at(0xFFA3) PIN_SHARE_CONTROL13;
__xdata volatile uint8_t __at(0xFFA4) PIN_SHARE_CONTROL14;
__xdata volatile uint8_t __at(0xFFA5) CLK_TEST_CONTROL;
__xdata volatile uint8_t __at(0xFFA6) PIN_DRIVING_CURRENT_CONTROL0;
__xdata volatile uint8_t __at(0xFFA7) PIN_DRIVING_CURRENT_CONTROL1;
__xdata volatile uint8_t __at(0xFFA8) PIN_PULLUP_CONTROL0;
__xdata volatile uint8_t __at(0xFFA9) PIN_PULLUP_CONTROL1;

//-----------------------------------------------------------------------------
// Consumer Electronics Control
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFAA) CEC_CR0;
__xdata volatile uint8_t __at(0xFFAB) CEC_CR1;
__xdata volatile uint8_t __at(0xFFAC) CEC_CR2;
__xdata volatile uint8_t __at(0xFFAD) CEC_CR3;
__xdata volatile uint8_t __at(0xFFAE) CEC_CR4;
__xdata volatile uint8_t __at(0xFFAF) CEC_RT0;
__xdata volatile uint8_t __at(0xFFB0) CEC_RT1;
__xdata volatile uint8_t __at(0xFFB1) CEC_RX0;
__xdata volatile uint8_t __at(0xFFB2) CEC_RX1;
__xdata volatile uint8_t __at(0xFFB3) CEC_TX0;
__xdata volatile uint8_t __at(0xFFB4) CEC_TX1;
__xdata volatile uint8_t __at(0xFFB5) CEC_TX_FIFO;
__xdata volatile uint8_t __at(0xFFB6) CEC_RX_FIFO;
__xdata volatile uint8_t __at(0xFFB7) CEC_RX_START0;
__xdata volatile uint8_t __at(0xFFB8) CEC_RX_START1;
__xdata volatile uint8_t __at(0xFFB9) CEC_RX_DATA0;
__xdata volatile uint8_t __at(0xFFBA) CEC_RX_DATA1;
__xdata volatile uint8_t __at(0xFFBB) CEC_TX_START0;
__xdata volatile uint8_t __at(0xFFBC) CEC_TX_START1;
__xdata volatile uint8_t __at(0xFFBD) CEC_TX_DATA0;
__xdata volatile uint8_t __at(0xFFBE) CEC_TX_DATA1;
__xdata volatile uint8_t __at(0xFFBF) CEC_TX_DATA2;

//-----------------------------------------------------------------------------
// GPIO Input/Output registers
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFC0) PORT_READ_CONTROL;
__xdata volatile uint8_t __at(0xFFC1) P5_2;
__xdata volatile uint8_t __at(0xFFC2) P5_3;
__xdata volatile uint8_t __at(0xFFC3) P5_4;
__xdata volatile uint8_t __at(0xFFC4) P5_5;
__xdata volatile uint8_t __at(0xFFC5) P5_6;
__xdata volatile uint8_t __at(0xFFC6) P5_7;
__xdata volatile uint8_t __at(0xFFC7) P6_0;
__xdata volatile uint8_t __at(0xFFC8) P6_1;
__xdata volatile uint8_t __at(0xFFC9) P6_2;
__xdata volatile uint8_t __at(0xFFCA) P6_3;
__xdata volatile uint8_t __at(0xFFCB) P6_4;
__xdata volatile uint8_t __at(0xFFCC) P6_5;
__xdata volatile uint8_t __at(0xFFCD) P6_6;
__xdata volatile uint8_t __at(0xFFCE) P6_7;
__xdata volatile uint8_t __at(0xFFCF) P7_0;
__xdata volatile uint8_t __at(0xFFD0) P7_1;
__xdata volatile uint8_t __at(0xFFD1) P7_2;
__xdata volatile uint8_t __at(0xFFD2) P7_3;
__xdata volatile uint8_t __at(0xFFD3) P7_4;
__xdata volatile uint8_t __at(0xFFD4) P7_5;
__xdata volatile uint8_t __at(0xFFD5) P7_6;
__xdata volatile uint8_t __at(0xFFD6) P8_0;
__xdata volatile uint8_t __at(0xFFD7) P8_1;
__xdata volatile uint8_t __at(0xFFD8) P9_0;
__xdata volatile uint8_t __at(0xFFD9) P9_1;
__xdata volatile uint8_t __at(0xFFDA) P9_2;
__xdata volatile uint8_t __at(0xFFDB) P9_3;
__xdata volatile uint8_t __at(0xFFDC) P9_4;
__xdata volatile uint8_t __at(0xFFDD) PA_0;
__xdata volatile uint8_t __at(0xFFDE) PA_1;
__xdata volatile uint8_t __at(0xFFDF) PA_2;
__xdata volatile uint8_t __at(0xFFE0) PA_3;
__xdata volatile uint8_t __at(0xFFE1) PA_4;

//-----------------------------------------------------------------------------
// Watch Dog Timer
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFEA) WDT_CONTROL;
__xdata volatile uint8_t __at(0xFFEB) WDT_TEST;

//-----------------------------------------------------------------------------
// I2C In System Programming
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFEC) ISP_SLAVE_ADDRESS;
__xdata volatile uint8_t __at(0xFFED) ISP_MCU_CONTROL;
__xdata volatile uint8_t __at(0xFFEE) ISP_MCU_CLOCK_CONTROL;
__xdata volatile uint8_t __at(0xFFEF) ISP_RAM_TEST;

//-----------------------------------------------------------------------------
// Scaler Interface
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFF3) SCALER_CONTROL;
__xdata volatile uint8_t __at(0xFFF4) SCALER_ADDRESS;
__xdata volatile uint8_t __at(0xFFF5) SCALER_DATA;
__xdata volatile uint8_t __at(0xFFF6) SCALER_BURST_WRITE_ADDRESS_HI;
__xdata volatile uint8_t __at(0xFFF7) SCALER_BURST_WRITE_ADDRESS_MD;
__xdata volatile uint8_t __at(0xFFF8) SCALER_BURST_WRITE_ADDRESS_LO;
__xdata volatile uint8_t __at(0xFFF9) SCALER_BURST_WRITE_COUNT_HI;
__xdata volatile uint8_t __at(0xFFFA) SCALER_BURST_WRITE_COUNT_LO;
__xdata volatile uint8_t __at(0xFFFA) SCALER_PERIOD;

//-----------------------------------------------------------------------------
// Bank Swtiching
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFFC) BANK_CONTROL;
__xdata volatile uint8_t __at(0xFFFC) BANK_XDATA_START;
__xdata volatile uint8_t __at(0xFFFC) BANK_XDATA_SELECT;
__xdata volatile uint8_t __at(0xFFFC) BANK_PBANK_SWITCH;