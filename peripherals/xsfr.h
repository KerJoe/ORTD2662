#pragma once

#include <stdint.h>

//-----------------------------------------------------------------------------
// Interrupt Control
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF00) IRQ_STATUS;                       // Interrupt Event Status
__xdata volatile uint8_t __at(0xFF01) IRQ_PRIORITY;                     // IRQ Multiplexing to Interrupt 0 and 1

//-----------------------------------------------------------------------------
// Analog to Digital Converter
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF08) ADC_A_CONTROL;                    // 5-bit ADC control register
__xdata volatile uint8_t __at(0xFF09) ADC_A0_DATA;                      // ADC A0 Conversion result
__xdata volatile uint8_t __at(0xFF0A) ADC_A1_DATA;                      // ADC A1 Conversion result
__xdata volatile uint8_t __at(0xFF0B) ADC_A2_DATA;                      // ADC A2 Conversion result
__xdata volatile uint8_t __at(0xFF0C) ADC_A3_DATA;                      // ADC A3 Conversion result
__xdata volatile uint8_t __at(0xFF0D) ADC_A4_DATA;                      // ADC A4 Conversion result

__xdata volatile uint8_t __at(0xFF0E) ADC_B_CONTROL;                    // 10-bit ADC control register
__xdata volatile uint8_t __at(0xFF0F) ADC_B_THRESHOLD;                  // Threshold value for continuous mode
__xdata volatile uint8_t __at(0xFF10) ADC_B0_TARGET_HI;                 // Compare target value for continuous mode of ADC B0
__xdata volatile uint8_t __at(0xFF11) ADC_B1_TARGET_HI;                 // Compare target value for continuous mode of ADC B1
__xdata volatile uint8_t __at(0xFF12) ADC_B2_TARGET_HI;                 // Compare target value for continuous mode of ADC B2
__xdata volatile uint8_t __at(0xFF13) ADC_BX_MEAS_TIME_HI;              // Continius mode sample time, User time / 10us, 0us < User Time < 10ms
__xdata volatile uint8_t __at(0xFF14) ADC_BX_TARGET_LO_MEAS_TIME_LO;    // Compare target value for continuous mode, Continius mode sample time
__xdata volatile uint8_t __at(0xFF15) ADC_B0_DATA_HI;                   // ADC B0 Conversion result, Highest 8 bits
__xdata volatile uint8_t __at(0xFF16) ADC_B1_DATA_HI;                   // ADC B1 Conversion result, Highest 8 bits
__xdata volatile uint8_t __at(0xFF17) ADC_B2_DATA_HI;                   // ADC B2 Conversion result, Highest 8 bits
__xdata volatile uint8_t __at(0xFF18) ADC_BX_DATA_LO;                   // ADC B Conversion result, Lowest 2 bits

//-----------------------------------------------------------------------------
// Display Data Channel (I2C)
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF1B) DDC1_CONTROL0;                    // Display Data Channel 1: Address select, debounce, MCU/DDC Access, Channel enable  // AKA: ADC DCC
__xdata volatile uint8_t __at(0xFF1C) DDC1_CONTROL1;                    // Display Data Channel 1: Debounce
__xdata volatile uint8_t __at(0xFF1D) DDC1_CONTROL2;                    // Display Data Channel 1: Force external SCL bus low

__xdata volatile uint8_t __at(0xFF1E) DDC2_CONTROL0;                    // Display Data Channel 2: Address select, debounce, MCU/DDC Access, Channel enable
__xdata volatile uint8_t __at(0xFF1F) DDC2_CONTROL1;                    // Display Data Channel 2: Debounce
__xdata volatile uint8_t __at(0xFF20) DDC2_CONTROL2;                    // Display Data Channel 2: Force external SCL bus low

__xdata volatile uint8_t __at(0xFF21) DDC_RAM_PARTITION;                // Division of address space between Common XRAM and between DDC Channels
__xdata volatile uint8_t __at(0xFF22) VSYNC_SEL;                        // VSYNC Signal connetion

__xdata volatile uint8_t __at(0xFF23) I2C_SLAVE_CONTROL;                // Slave address of DDC-CI and selection of DDC channel connected to DDC-CI
__xdata volatile uint8_t __at(0xFF24) I2C_SLAVE_SUB_ADDRESS;            // I2C Sub-Address Received
__xdata volatile uint8_t __at(0xFF25) I2C_SLAVE_DATA_IN;                // I2C data received. 16-byte deep buffer
__xdata volatile uint8_t __at(0xFF26) I2C_SLAVE_DATA_OUT;               // I2C data to be transmitted
__xdata volatile uint8_t __at(0xFF27) I2C_SLAVE_STATUS0;                // Status of DDC-CI connection
__xdata volatile uint8_t __at(0xFF28) I2C_SLAVE_IRQ_CONTROL0;           // DDC-CI IRQ Control
__xdata volatile uint8_t __at(0xFF29) I2C_SLAVE_STATUS1;                // Status of DDC-CI connection
__xdata volatile uint8_t __at(0xFF2A) I2C_SLAVE_IRQ_CONTROL1;           // DDC-CI IRQ Control
__xdata volatile uint8_t __at(0xFF2B) I2C_SLAVE_CHANNEL_CONTROL;        // Selection of DDC channel connected to DDC-CI

__xdata volatile uint8_t __at(0xFF2C) DDC3_CONTROL0;                    // Display Data Channel 3: Address select, debounce, MCU/DDC Access, Channel enable
__xdata volatile uint8_t __at(0xFF2D) DDC3_CONTROL1;                    // Display Data Channel 3: Debounce
__xdata volatile uint8_t __at(0xFF2E) DDC3_CONTROL2;                    // Display Data Channel 3: Force external SCL bus low

__xdata volatile uint8_t __at(0xFF2F) DDC1_INDEX;                       // DDC1 SRAM Read/Write Index Register (Used for ISP)
__xdata volatile uint8_t __at(0xFF30) DDC1_DATA;                        // DDC1 SRAM Read/Write Port (Used for ISP)
__xdata volatile uint8_t __at(0xFF31) DDC2_INDEX;                       // DDC2 SRAM Read/Write Index Register (Used for ISP)
__xdata volatile uint8_t __at(0xFF32) DDC2_DATA;                        // DDC2 SRAM Read/Write Port (Used for ISP)
__xdata volatile uint8_t __at(0xFF33) DDC3_INDEX;                       // DDC3 SRAM Read/Write Index Register (Used for ISP)
__xdata volatile uint8_t __at(0xFF34) DDC3_DATA;                        // DDC3 SRAM Read/Write Port (Used for ISP)

//-----------------------------------------------------------------------------
// Pulse Width Modulation
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF3A) PWM_CLK_SEL;                      // PWM Channel clock source select

__xdata volatile uint8_t __at(0xFF3B) PWM0123_DIV1;                     // PWM clock first stage divider
__xdata volatile uint8_t __at(0xFF3C) PWM45_DIV1;                       // PWM clock first stage divider

__xdata volatile uint8_t __at(0xFF3D) PWM01_DIV2_HI;                    // PWM clock Second stage divider, High byte
__xdata volatile uint8_t __at(0xFF3E) PWM0_DIV2_LO;                     // PWM clock Second stage divider, Low byte
__xdata volatile uint8_t __at(0xFF3F) PWM1_DIV2_LO;                     // PWM clock Second stage divider, Low byte
__xdata volatile uint8_t __at(0xFF40) PWM23_DIV2_HI;                    // PWM clock Second stage divider, High byte
__xdata volatile uint8_t __at(0xFF41) PWM2_DIV2_LO;                     // PWM clock Second stage divider, Low byte
__xdata volatile uint8_t __at(0xFF42) PWM3_DIV2_LO;                     // PWM clock Second stage divider, Low byte
__xdata volatile uint8_t __at(0xFF43) PWM45_DIV2_HI;                    // PWM clock Second stage divider, High byte
__xdata volatile uint8_t __at(0xFF44) PWM4_DIV2_LO;                     // PWM clock Second stage divider, Low byte
__xdata volatile uint8_t __at(0xFF45) PWM5_DIV2_LO;                     // PWM clock Second stage divider, Low byte

__xdata volatile uint8_t __at(0xFF46) PWM_L;                            // PWM Width, Active level
__xdata volatile uint8_t __at(0xFF47) PWM_DVS_RST;                      // PWM reset by DVS signal
__xdata volatile uint8_t __at(0xFF48) PWM_CONTROL;                      // Width select and PWM output enable
__xdata volatile uint8_t __at(0xFF49) PWM_DIV_SEL;                      // Select first or second stage output as clock source for PWM

__xdata volatile uint8_t __at(0xFF4A) PWM0_DATA_HI;                     // PWM Duty width, High byte
__xdata volatile uint8_t __at(0xFF4B) PWM1_DATA_HI;                     // PWM Duty width, High byte
__xdata volatile uint8_t __at(0xFF4C) PWM01_DATA_LO;                    // PWM Duty width, Low byte
__xdata volatile uint8_t __at(0xFF4D) PWM2_DATA_HI;                     // PWM Duty width, High byte
__xdata volatile uint8_t __at(0xFF4E) PWM3_DATA_HI;                     // PWM Duty width, High byte
__xdata volatile uint8_t __at(0xFF4F) PWM23_DATA_LO;                    // PWM Duty width, Low byte
__xdata volatile uint8_t __at(0xFF50) PWM4_DATA_HI;                     // PWM Duty width, High byte
__xdata volatile uint8_t __at(0xFF51) PWM5_DATA_HI;                     // PWM Duty width, High byte
__xdata volatile uint8_t __at(0xFF52) PWM45_DATA_LO;                    // PWM Duty width, Low byte

//-----------------------------------------------------------------------------
// I2C Master
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF55) I2C_MASTER_CONTROL0;              // I2C master, Enable
__xdata volatile uint8_t __at(0xFF56) I2C_MASTER_CONTROL1;              // I2C master, Time out register
__xdata volatile uint8_t __at(0xFF57) I2C_MASTER_CONTROL2;              // I2C master, Burst mode
__xdata volatile uint8_t __at(0xFF58) I2C_MASTER_CONTROL3;              // I2C master, Interrupt enable and repeat count
__xdata volatile uint8_t __at(0xFF59) I2C_MASTER_STR0;                  // I2C master, Debounce and fall time period count
__xdata volatile uint8_t __at(0xFF5A) I2C_MASTER_STR1;                  // I2C master, STA setup time period count
__xdata volatile uint8_t __at(0xFF5B) I2C_MASTER_STR2;                  // I2C master, SCL high period counter
__xdata volatile uint8_t __at(0xFF5C) I2C_MASTER_STR3;                  // I2C master, SCL low period counter
__xdata volatile uint8_t __at(0xFF5D) I2C_MASTER_STATUS;                // I2C master, Status register
__xdata volatile uint8_t __at(0xFF5E) I2C_MASTER_DATA;                  // I2C master, Target Device Data to receive or transmit
__xdata volatile uint8_t __at(0xFF5F) I2C_MASTER_DIV;                   // I2C master, Frequency Divder

//-----------------------------------------------------------------------------
// SPI Flash
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF60) CUSTOM_INSTRUCTION_CONTROL;       // SPI Flash custom instruction setup
__xdata volatile uint8_t __at(0xFF61) CUSTOM_INSTRUCTION_OPCODE;        // Opcode of custom instruction
__xdata volatile uint8_t __at(0xFF62) WREN_OPCODE;                      // Opcode of Write Enable register
__xdata volatile uint8_t __at(0xFF63) EWSR_OPCODE;                      // Opcode of Enable Write Status register
__xdata volatile uint8_t __at(0xFF64) FLASH_WRITE_HI;                   // Flash Program/Write/Dummy/CRC High byte
__xdata volatile uint8_t __at(0xFF65) FLASH_WRITE_MD;                   // Flash Program/Write/Dummy/CRC Middle byte
__xdata volatile uint8_t __at(0xFF66) FLASH_WRITE_LO;                   // Flash Program/Write/Dummy/CRC Low byte
__xdata volatile uint8_t __at(0xFF67) CUSTOM_INSTRUCTION_READ_HI;       // Custom instruction read result High byte
__xdata volatile uint8_t __at(0xFF68) CUSTOM_INSTRUCTION_READ_MD;       // Custom instruction read result Middle byte
__xdata volatile uint8_t __at(0xFF69) CUSTOM_INSTRUCTION_READ_LO;       // Custom instruction read result Low byte
__xdata volatile uint8_t __at(0xFF6A) FLASH_READ_OPCODE;                // Opcode of Read command
__xdata volatile uint8_t __at(0xFF6B) FLASH_FAST_READ_OPCODE;           // Opcode of Fast Read command
__xdata volatile uint8_t __at(0xFF6C) FLASH_READ_CONTROL;               // Read command settings
__xdata volatile uint8_t __at(0xFF6D) FLASH_WRITE_OPCODE;               // Opcode of Programm command
__xdata volatile uint8_t __at(0xFF6E) RDSR_OPCODE;                      // Opcode of Read Status register
__xdata volatile uint8_t __at(0xFF6F) FLASH_WRITE_CONTROL;              // Programm command settings
__xdata volatile uint8_t __at(0xFF70) FLASH_WRITE_DATA;                 // Data to programm (Buffered)
__xdata volatile uint8_t __at(0xFF71) FLASH_WRITE_LENGTH;               // Number of bytes to programm
__xdata volatile uint8_t __at(0xFF72) FLASH_CRC_END_HI;                 // CRC end address High byte
__xdata volatile uint8_t __at(0xFF73) FLASH_CRC_END_MD;                 // CRC end address Middle byte
__xdata volatile uint8_t __at(0xFF74) FLASH_CRC_END_LO;                 // CRC end address Low byte
__xdata volatile uint8_t __at(0xFF75) FLASH_CRC_RESULT;                 // CRC result value
__xdata volatile uint8_t __at(0xFF76) FLASH_CHIP_TIMING;                // Flash access timings

//-----------------------------------------------------------------------------
// Infrared Reciever
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF80) IR_CONTROL0;                      // IR Protocol setup register 0
__xdata volatile uint8_t __at(0xFF81) IR_DEBOUNCE;                      // IR Decoder clock rate, debounce time
__xdata volatile uint8_t __at(0xFF82) IR_BURST_LENGTH;                  // IR Protocol burst length
__xdata volatile uint8_t __at(0xFF83) IR_SILENCE_LENGTH;                // IR Protocol silence length
__xdata volatile uint8_t __at(0xFF84) IR_REPEAT_LENGTH;                 // IR Protocol repeat length
__xdata volatile uint8_t __at(0xFF85) IR_MODULATION_LENGTH;             // IR Protocol modulation length
__xdata volatile uint8_t __at(0xFF86) IR_DATA_0_LENGTH;                 // IR Protocol length of 'zero' bit
__xdata volatile uint8_t __at(0xFF87) IR_DATA_1_LENGTH;                 // IR Protocol length of 'one' bit
__xdata volatile uint8_t __at(0xFF88) IR_CONTROL1;                      // IR Protocol setup register 1
__xdata volatile uint8_t __at(0xFF89) IR_STATUS;                        // IR Decoder status
__xdata volatile uint8_t __at(0xFF8A) IR_DATA0;                         // IR Recieved data 0
__xdata volatile uint8_t __at(0xFF8B) IR_DATA1;                         // IR Recieved data 1
__xdata volatile uint8_t __at(0xFF8C) IR_DATA2;                         // IR Recieved data 2
__xdata volatile uint8_t __at(0xFF8D) IR_DATA3;                         // IR Recieved data 3
__xdata volatile uint8_t __at(0xFF8E) IR_DATA4;                         // IR Recieved data 4
__xdata volatile uint8_t __at(0xFF8F) IR_DATA5;                         // IR Recieved data 5
__xdata volatile uint8_t __at(0xFF90) IR_ONE_CMD_TIME;                  // IR Protocol one command length
__xdata volatile uint8_t __at(0xFF91) IR_IDLE_TIME;                     // IR Protocol idle length
__xdata volatile uint8_t __at(0xFF92) IR_CONTROL2;                      // IR Decoder status and Recieved data bit swap
__xdata volatile uint8_t __at(0xFF93) IR_IRQ;                           // IR Interrupt requests

//-----------------------------------------------------------------------------
// Pin Function Control
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFF96) PIN_SHARE_CONTROL00;              // Pin Function Share Select Register 0
__xdata volatile uint8_t __at(0xFF97) PIN_SHARE_CONTROL01;              // Pin Function Share Select Register 1
__xdata volatile uint8_t __at(0xFF98) PIN_SHARE_CONTROL02;              // Pin Function Share Select Register 2
__xdata volatile uint8_t __at(0xFF99) PIN_SHARE_CONTROL03;              // Pin Function Share Select Register 3
__xdata volatile uint8_t __at(0xFF9A) PIN_SHARE_CONTROL04;              // Pin Function Share Select Register 4
__xdata volatile uint8_t __at(0xFF9B) PIN_SHARE_CONTROL05;              // Pin Function Share Select Register 5
__xdata volatile uint8_t __at(0xFF9C) PIN_SHARE_CONTROL06;              // Pin Function Share Select Register 6
__xdata volatile uint8_t __at(0xFF9D) PIN_SHARE_CONTROL07;              // Pin Function Share Select Register 7
__xdata volatile uint8_t __at(0xFF9E) PIN_SHARE_CONTROL08;              // Pin Function Share Select Register 8
__xdata volatile uint8_t __at(0xFF9F) PIN_SHARE_CONTROL09;              // Pin Function Share Select Register 9
__xdata volatile uint8_t __at(0xFFA0) PIN_SHARE_CONTROL10;              // Pin Function Share Select Register 10
__xdata volatile uint8_t __at(0xFFA1) PIN_SHARE_CONTROL11;              // Pin Function Share Select Register 11
__xdata volatile uint8_t __at(0xFFA2) PIN_SHARE_CONTROL12;              // Pin Function Share Select Register 12
__xdata volatile uint8_t __at(0xFFA3) PIN_SHARE_CONTROL13;              // Pin Function Share Select Register 13
__xdata volatile uint8_t __at(0xFFA4) PIN_SHARE_CONTROL14;              // Pin Function Share Select Register 14
__xdata volatile uint8_t __at(0xFFA5) CLK_TEST_CONTROL;                 // Internal clock output control
__xdata volatile uint8_t __at(0xFFA6) PIN_DRIVING_CURRENT_CONTROL0;     // Driving current of pin ranges 0
__xdata volatile uint8_t __at(0xFFA7) PIN_DRIVING_CURRENT_CONTROL1;     // Driving current of pin ranges 1
__xdata volatile uint8_t __at(0xFFA8) PIN_PULLUP_CONTROL0;              // Internal pull-up resistors of pin ranges 0
__xdata volatile uint8_t __at(0xFFA9) PIN_PULLUP_CONTROL1;              // Internal pull-up resistors of pin ranges 1

//-----------------------------------------------------------------------------
// Consumer Electronics Control
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFAA) CEC_CONTROL0;                     // CEC Control Register 0
__xdata volatile uint8_t __at(0xFFAB) CEC_CONTROL1;                     // CEC Control Register 1
__xdata volatile uint8_t __at(0xFFAC) CEC_CONTROL2;                     // CEC Control Register 2
__xdata volatile uint8_t __at(0xFFAD) CEC_CONTROL3;                     // CEC Control Register 3
__xdata volatile uint8_t __at(0xFFAE) CEC_CONTROL4;                     // CEC Control Register 4
__xdata volatile uint8_t __at(0xFFAF) CEC_RT0;                          // CEC Retry Wait Time
__xdata volatile uint8_t __at(0xFFB0) CEC_RT1;                          // CEC Max number of retries
__xdata volatile uint8_t __at(0xFFB1) CEC_RX0;                          // CEC Reciever Control and Status
__xdata volatile uint8_t __at(0xFFB2) CEC_RX1;                          // CEC Reciever Status
__xdata volatile uint8_t __at(0xFFB3) CEC_TX0;                          // CEC Transmitter Control and Status
__xdata volatile uint8_t __at(0xFFB4) CEC_TX1;                          // CEC Transmitter Status
__xdata volatile uint8_t __at(0xFFB5) CEC_TX_FIFO;                      // CEC Transmitter output buffer
__xdata volatile uint8_t __at(0xFFB6) CEC_RX_FIFO;                      // CEC Reciever input buffer
__xdata volatile uint8_t __at(0xFFB7) CEC_RX_START0;                    // CEC RX Start low
__xdata volatile uint8_t __at(0xFFB8) CEC_RX_START1;                    // CEC RX Start period
__xdata volatile uint8_t __at(0xFFB9) CEC_RX_DATA0;                     // CEC RX Data sample
__xdata volatile uint8_t __at(0xFFBA) CEC_RX_DATA1;                     // CEC RX Data period
__xdata volatile uint8_t __at(0xFFBB) CEC_TX_START0;                    // CEC TX Start low
__xdata volatile uint8_t __at(0xFFBC) CEC_TX_START1;                    // CEC TX Start high
__xdata volatile uint8_t __at(0xFFBD) CEC_TX_DATA0;                     // CEC TX Data low
__xdata volatile uint8_t __at(0xFFBE) CEC_TX_DATA1;                     // CEC TX Data middle
__xdata volatile uint8_t __at(0xFFBF) CEC_TX_DATA2;                     // CEC TX Data high

//-----------------------------------------------------------------------------
// GPIO Input/Output registers
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFC0) PORT_READ_CONTROL;                // Read back source selection for pins
__xdata volatile uint8_t __at(0xFFC1) P5_2;                             // Port 5 Pin 2
__xdata volatile uint8_t __at(0xFFC2) P5_3;                             // Port 5 Pin 3
__xdata volatile uint8_t __at(0xFFC3) P5_4;                             // Port 5 Pin 4
__xdata volatile uint8_t __at(0xFFC4) P5_5;                             // Port 5 Pin 5
__xdata volatile uint8_t __at(0xFFC5) P5_6;                             // Port 5 Pin 6
__xdata volatile uint8_t __at(0xFFC6) P5_7;                             // Port 5 Pin 7
__xdata volatile uint8_t __at(0xFFC7) P6_0;                             // Port 6 Pin 0
__xdata volatile uint8_t __at(0xFFC8) P6_1;                             // Port 6 Pin 1
__xdata volatile uint8_t __at(0xFFC9) P6_2;                             // Port 6 Pin 2
__xdata volatile uint8_t __at(0xFFCA) P6_3;                             // Port 6 Pin 3
__xdata volatile uint8_t __at(0xFFCB) P6_4;                             // Port 6 Pin 4
__xdata volatile uint8_t __at(0xFFCC) P6_5;                             // Port 6 Pin 5
__xdata volatile uint8_t __at(0xFFCD) P6_6;                             // Port 6 Pin 6
__xdata volatile uint8_t __at(0xFFCE) P6_7;                             // Port 6 Pin 7
__xdata volatile uint8_t __at(0xFFCF) P7_0;                             // Port 7 Pin 0
__xdata volatile uint8_t __at(0xFFD0) P7_1;                             // Port 7 Pin 1
__xdata volatile uint8_t __at(0xFFD1) P7_2;                             // Port 7 Pin 2
__xdata volatile uint8_t __at(0xFFD2) P7_3;                             // Port 7 Pin 3
__xdata volatile uint8_t __at(0xFFD3) P7_4;                             // Port 7 Pin 4
__xdata volatile uint8_t __at(0xFFD4) P7_5;                             // Port 7 Pin 5
__xdata volatile uint8_t __at(0xFFD5) P7_6;                             // Port 7 Pin 6
__xdata volatile uint8_t __at(0xFFD6) P8_0;                             // Port 8 Pin 0
__xdata volatile uint8_t __at(0xFFD7) P8_1;                             // Port 8 Pin 1
__xdata volatile uint8_t __at(0xFFD8) P9_0;                             // Port 9 Pin 0
__xdata volatile uint8_t __at(0xFFD9) P9_1;                             // Port 9 Pin 1
__xdata volatile uint8_t __at(0xFFDA) P9_2;                             // Port 9 Pin 2
__xdata volatile uint8_t __at(0xFFDB) P9_3;                             // Port 9 Pin 3
__xdata volatile uint8_t __at(0xFFDC) P9_4;                             // Port 9 Pin 4
__xdata volatile uint8_t __at(0xFFDD) PA_0;                             // Port A Pin 0
__xdata volatile uint8_t __at(0xFFDE) PA_1;                             // Port A Pin 1
__xdata volatile uint8_t __at(0xFFDF) PA_2;                             // Port A Pin 2
__xdata volatile uint8_t __at(0xFFE0) PA_3;                             // Port A Pin 3
__xdata volatile uint8_t __at(0xFFE1) PA_4;                             // Port A Pin 4

//-----------------------------------------------------------------------------
// Watch Dog Timer
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFEA) WDT_CONTROL;                      // Watch Dog Timer Control Register
__xdata volatile uint8_t __at(0xFFEB) WDT_TEST;                         // Watch Dog Timer Signal Bypass Selection

//-----------------------------------------------------------------------------
// I2C In System Programming
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFEC) ISP_SLAVE_ADDRESS;                // Address of device on I2C slave bus
__xdata volatile uint8_t __at(0xFFED) ISP_MCU_CONTROL;                  // Control of internal MCU
__xdata volatile uint8_t __at(0xFFEE) ISP_MCU_CLOCK_CONTROL;            // MCU Clock Control and reset
__xdata volatile uint8_t __at(0xFFEF) ISP_RAM_TEST;                     // Internal RAM Test

//-----------------------------------------------------------------------------
// Scaler Interface
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFF3) SCALER_CONTROL;                   // Scaler data gate control
__xdata volatile uint8_t __at(0xFFF4) SCALER_ADDRESS;                   // Scaler data address
__xdata volatile uint8_t __at(0xFFF5) SCALER_DATA;                      // Scaler data byte
__xdata volatile uint8_t __at(0xFFF6) SCALER_BURST_WRITE_ADDRESS_HI;    // Burst Write Command Start Address High byte
__xdata volatile uint8_t __at(0xFFF7) SCALER_BURST_WRITE_ADDRESS_MD;    // Burst Write Command Start Address Middle byte
__xdata volatile uint8_t __at(0xFFF8) SCALER_BURST_WRITE_ADDRESS_LO;    // Burst Write Command Start Address Low byte
__xdata volatile uint8_t __at(0xFFF9) SCALER_BURST_WRITE_COUNT_HI;      // Burst Write Command Data Length High byte
__xdata volatile uint8_t __at(0xFFFA) SCALER_BURST_WRITE_COUNT_LO;      // Burst Write Command Data Length Low byte
__xdata volatile uint8_t __at(0xFFFA) SCALER_PERIOD;                    // Scaler access delay

//-----------------------------------------------------------------------------
// Bank Swtiching
//-----------------------------------------------------------------------------
__xdata volatile uint8_t __at(0xFFFC) BANK_CONTROL;                     // Control of mapping of external memory and Control of bank switching
__xdata volatile uint8_t __at(0xFFFD) BANK_XDATA_START;                 // The start bank number for XDATA access
__xdata volatile uint8_t __at(0xFFFE) BANK_XDATA_SELECT;                // First bank number for XDATA access
__xdata volatile uint8_t __at(0xFFFF) BANK_PBANK_SWITCH;                // Bank number for program code access