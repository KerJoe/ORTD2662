#pragma once

#include <stdint.h>

// Compile only for firmware
#ifdef __SDCC
#define XSFRWriteByte(__adr, __data) (*(__xdata volatile uint8_t*)(0xFF00 | (__adr)) = (__data))
#define XSFRReadByte(__adr)          (*(__xdata volatile uint8_t*)(0xFF00 | (__adr)))
#else // Compile only for native
void XSFRWriteByte(uint8_t address, uint8_t data);
uint8_t XSFRReadByte(uint8_t address);
#endif

//-----------------------------------------------------------------------------
// Interrupt Control
//-----------------------------------------------------------------------------
#define IRQ_STATUS				        0x00 // Interrupt Event Status
#define IRQ_PRIORITY				    0x01 // IRQ Multiplexing to Interrupt 0 and 1

//-----------------------------------------------------------------------------
// Analog to Digital Converter
//-----------------------------------------------------------------------------
#define ADC_A_CONTROL				    0x08  // 5-bit ADC control register
#define ADC_A0_DATA				        0x09  // ADC A0 Conversion result
#define ADC_A1_DATA				        0x0A  // ADC A1 Conversion result
#define ADC_A2_DATA				        0x0B  // ADC A2 Conversion result
#define ADC_A3_DATA				        0x0C  // ADC A3 Conversion result
#define ADC_A4_DATA				        0x0D  // ADC A4 Conversion result

#define ADC_B_CONTROL				    0x0E  // 10-bit ADC control register
#define ADC_B_THRESHOLD				    0x0F  // Threshold value for continuous mode
#define ADC_B0_TARGET_HI				0x10  // Compare target value for continuous mode of ADC B0
#define ADC_B1_TARGET_HI				0x11  // Compare target value for continuous mode of ADC B1
#define ADC_B2_TARGET_HI				0x12  // Compare target value for continuous mode of ADC B2
#define ADC_BX_MEAS_TIME_HI				0x13  // Continius mode sample time, User time / 10us, 0us < User Time < 10ms
#define ADC_BX_TARGET_LO_MEAS_TIME_LO	0x14  // Compare target value for continuous mode, Continius mode sample time
#define ADC_B0_DATA_HI				    0x15  // ADC B0 Conversion result, Highest 8 bits
#define ADC_B1_DATA_HI				    0x16  // ADC B1 Conversion result, Highest 8 bits
#define ADC_B2_DATA_HI				    0x17  // ADC B2 Conversion result, Highest 8 bits
#define ADC_BX_DATA_LO				    0x18  // ADC B Conversion result, Lowest 2 bits

//-----------------------------------------------------------------------------
// Display Data Channel (I2C)
//-----------------------------------------------------------------------------
#define DDC1_CONTROL0				    0x1B  // AKA: ADC DCC
#define DDC1_CONTROL1				    0x1C  // Display Data Channel 1: Debounce
#define DDC1_CONTROL2				    0x1D  // Display Data Channel 1: Force external SCL bus low

#define DDC2_CONTROL0				    0x1E  // Display Data Channel 2: Address select, debounce, MCU/DDC Access, Channel enable
#define DDC2_CONTROL1				    0x1F  // Display Data Channel 2: Debounce
#define DDC2_CONTROL2				    0x20  // Display Data Channel 2: Force external SCL bus low

#define DDC_RAM_PARTITION			    0x21  // Division of address space between Common XRAM and between DDC Channels
#define VSYNC_SEL				        0x22  // VSYNC Signal connetion

#define I2C_SLAVE_CONTROL			    0x23  // Slave address of DDC-CI and selection of DDC channel connected to DDC-CI
#define I2C_SLAVE_SUB_ADDRESS		    0x24  // I2C Sub-Address Received
#define I2C_SLAVE_DATA_IN			    0x25  // I2C data received. 16-byte deep buffer
#define I2C_SLAVE_DATA_OUT			    0x26  // I2C data to be transmitted
#define I2C_SLAVE_STATUS0			    0x27  // Status of DDC-CI connection
#define I2C_SLAVE_IRQ_CONTROL0		    0x28  // DDC-CI IRQ Control
#define I2C_SLAVE_STATUS1			    0x29  // Status of DDC-CI connection
#define I2C_SLAVE_IRQ_CONTROL1		    0x2A  // DDC-CI IRQ Control
#define I2C_SLAVE_CHANNEL_CONTROL	    0x2B  // Selection of DDC channel connected to DDC-CI

#define DDC3_CONTROL0				    0x2C  // Display Data Channel 3: Address select, debounce, MCU/DDC Access, Channel enable
#define DDC3_CONTROL1				    0x2D  // Display Data Channel 3: Debounce
#define DDC3_CONTROL2				    0x2E  // Display Data Channel 3: Force external SCL bus low

#define DDC1_INDEX				        0x2F  // DDC1 SRAM Read/Write Index Register (Used for ISP)
#define DDC1_DATA				        0x30  // DDC1 SRAM Read/Write Port (Used for ISP)
#define DDC2_INDEX				        0x31  // DDC2 SRAM Read/Write Index Register (Used for ISP)
#define DDC2_DATA				        0x32  // DDC2 SRAM Read/Write Port (Used for ISP)
#define DDC3_INDEX				        0x33  // DDC3 SRAM Read/Write Index Register (Used for ISP)
#define DDC3_DATA				        0x34  // DDC3 SRAM Read/Write Port (Used for ISP)

//-----------------------------------------------------------------------------
// Pulse Width Modulation
//-----------------------------------------------------------------------------
#define PWM_CLK_SEL				        0x3A  // PWM Channel clock source select

#define PWM0123_DIV1				    0x3B  // PWM clock first stage divider
#define PWM45_DIV1				        0x3C  // PWM clock first stage divider

#define PWM01_DIV2_HI				    0x3D  // PWM clock Second stage divider, High byte
#define PWM0_DIV2_LO				    0x3E  // PWM clock Second stage divider, Low byte
#define PWM1_DIV2_LO				    0x3F  // PWM clock Second stage divider, Low byte
#define PWM23_DIV2_HI				    0x40  // PWM clock Second stage divider, High byte
#define PWM2_DIV2_LO				    0x41  // PWM clock Second stage divider, Low byte
#define PWM3_DIV2_LO				    0x42  // PWM clock Second stage divider, Low byte
#define PWM45_DIV2_HI				    0x43  // PWM clock Second stage divider, High byte
#define PWM4_DIV2_LO				    0x44  // PWM clock Second stage divider, Low byte
#define PWM5_DIV2_LO				    0x45  // PWM clock Second stage divider, Low byte

#define PWM_L				            0x46  // PWM Width, Active level
#define PWM_DVS_RST				        0x47  // PWM reset by DVS signal
#define PWM_CONTROL				        0x48  // Width select and PWM output enable
#define PWM_DIV_SEL				        0x49  // Select first or second stage output as clock source for PWM

#define PWM0_DATA_HI				    0x4A  // PWM Duty width, High byte
#define PWM1_DATA_HI				    0x4B  // PWM Duty width, High byte
#define PWM01_DATA_LO				    0x4C  // PWM Duty width, Low byte
#define PWM2_DATA_HI				    0x4D  // PWM Duty width, High byte
#define PWM3_DATA_HI				    0x4E  // PWM Duty width, High byte
#define PWM23_DATA_LO				    0x4F  // PWM Duty width, Low byte
#define PWM4_DATA_HI				    0x50  // PWM Duty width, High byte
#define PWM5_DATA_HI				    0x51  // PWM Duty width, High byte
#define PWM45_DATA_LO				    0x52  // PWM Duty width, Low byte

//-----------------------------------------------------------------------------
// I2C Master
//-----------------------------------------------------------------------------
#define I2C_MASTER_CONTROL0				0x55  // I2C master, Enable
#define I2C_MASTER_CONTROL1				0x56  // I2C master, Time out register
#define I2C_MASTER_CONTROL2				0x57  // I2C master, Burst mode
#define I2C_MASTER_CONTROL3				0x58  // I2C master, Interrupt enable and repeat count
#define I2C_MASTER_STR0				    0x59  // I2C master, Debounce and fall time period count
#define I2C_MASTER_STR1				    0x5A  // I2C master, STA setup time period count
#define I2C_MASTER_STR2				    0x5B  // I2C master, SCL high period counter
#define I2C_MASTER_STR3				    0x5C  // I2C master, SCL low period counter
#define I2C_MASTER_STATUS				0x5D  // I2C master, Status register
#define I2C_MASTER_DATA				    0x5E  // I2C master, Target Device Data to receive or transmit
#define I2C_MASTER_DIV				    0x5F  // I2C master, Frequency Divder

//-----------------------------------------------------------------------------
// SPI Flash
//-----------------------------------------------------------------------------
#define CUSTOM_INSTRUCTION_CONTROL		0x60  // SPI Flash custom instruction setup
#define CUSTOM_INSTRUCTION_OPCODE		0x61  // Opcode of custom instruction
#define WREN_OPCODE				        0x62  // Opcode of Write Enable register
#define EWSR_OPCODE				        0x63  // Opcode of Enable Write Status register
#define FLASH_WRITE_HI				    0x64  // Flash Program/Write/Dummy/CRC High byte
#define FLASH_WRITE_MD				    0x65  // Flash Program/Write/Dummy/CRC Middle byte
#define FLASH_WRITE_LO				    0x66  // Flash Program/Write/Dummy/CRC Low byte
#define CUSTOM_INSTRUCTION_READ_HI		0x67  // Custom instruction read result High byte
#define CUSTOM_INSTRUCTION_READ_MD		0x68  // Custom instruction read result Middle byte
#define CUSTOM_INSTRUCTION_READ_LO		0x69  // Custom instruction read result Low byte
#define FLASH_READ_OPCODE				0x6A  // Opcode of Read command
#define FLASH_FAST_READ_OPCODE			0x6B  // Opcode of Fast Read command
#define FLASH_READ_CONTROL				0x6C  // Read command settings
#define FLASH_WRITE_OPCODE				0x6D  // Opcode of Programm command
#define RDSR_OPCODE				        0x6E  // Opcode of Read Status register
#define FLASH_WRITE_CONTROL				0x6F  // Programm command settings
#define FLASH_WRITE_DATA				0x70  // Data to programm (Buffered)
#define FLASH_WRITE_LENGTH				0x71  // Number of bytes to programm
#define FLASH_CRC_END_HI				0x72  // CRC end address High byte
#define FLASH_CRC_END_MD				0x73  // CRC end address Middle byte
#define FLASH_CRC_END_LO				0x74  // CRC end address Low byte
#define FLASH_CRC_RESULT				0x75  // CRC result value
#define FLASH_CHIP_TIMING				0x76  // Flash access timings

//-----------------------------------------------------------------------------
// Infrared Reciever
//-----------------------------------------------------------------------------
#define IR_CONTROL0				        0x80  // IR Protocol setup register 0
#define IR_DEBOUNCE				        0x81  // IR Decoder clock rate, debounce time
#define IR_BURST_LENGTH			    	0x82  // IR Protocol burst length
#define IR_SILENCE_LENGTH				0x83  // IR Protocol silence length
#define IR_REPEAT_LENGTH				0x84  // IR Protocol repeat length
#define IR_MODULATION_LENGTH			0x85  // IR Protocol modulation length
#define IR_DATA_0_LENGTH				0x86  // IR Protocol length of 'zero' bit
#define IR_DATA_1_LENGTH				0x87  // IR Protocol length of 'one' bit
#define IR_CONTROL1				        0x88  // IR Protocol setup register 1
#define IR_STATUS				        0x89  // IR Decoder status
#define IR_DATA0				        0x8A  // IR Recieved data 0
#define IR_DATA1				        0x8B  // IR Recieved data 1
#define IR_DATA2				        0x8C  // IR Recieved data 2
#define IR_DATA3				        0x8D  // IR Recieved data 3
#define IR_DATA4				        0x8E  // IR Recieved data 4
#define IR_DATA5				        0x8F  // IR Recieved data 5
#define IR_ONE_CMD_TIME				    0x90  // IR Protocol one command length
#define IR_IDLE_TIME				    0x91  // IR Protocol idle length
#define IR_CONTROL2				        0x92  // IR Decoder status and Recieved data bit swap
#define IR_IRQ				            0x93  // IR Interrupt requests

//-----------------------------------------------------------------------------
// Pin Function Control
//-----------------------------------------------------------------------------
#define PIN_SHARE_CONTROL00				0x96  // Pin Function Share Select Register 0
#define PIN_SHARE_CONTROL01				0x97  // Pin Function Share Select Register 1
#define PIN_SHARE_CONTROL02				0x98  // Pin Function Share Select Register 2
#define PIN_SHARE_CONTROL03				0x99  // Pin Function Share Select Register 3
#define PIN_SHARE_CONTROL04				0x9A  // Pin Function Share Select Register 4
#define PIN_SHARE_CONTROL05				0x9B  // Pin Function Share Select Register 5
#define PIN_SHARE_CONTROL06				0x9C  // Pin Function Share Select Register 6
#define PIN_SHARE_CONTROL07				0x9D  // Pin Function Share Select Register 7
#define PIN_SHARE_CONTROL08				0x9E  // Pin Function Share Select Register 8
#define PIN_SHARE_CONTROL09				0x9F  // Pin Function Share Select Register 9
#define PIN_SHARE_CONTROL10				0xA0  // Pin Function Share Select Register 10
#define PIN_SHARE_CONTROL11				0xA1  // Pin Function Share Select Register 11
#define PIN_SHARE_CONTROL12				0xA2  // Pin Function Share Select Register 12
#define PIN_SHARE_CONTROL13				0xA3  // Pin Function Share Select Register 13
#define PIN_SHARE_CONTROL14				0xA4  // Pin Function Share Select Register 14
#define CLK_TEST_CONTROL				0xA5  // Internal clock output control
#define PIN_DRIVING_CURRENT_CONTROL0	0xA6  // Driving current of pin ranges 0
#define PIN_DRIVING_CURRENT_CONTROL1	0xA7  // Driving current of pin ranges 1
#define PIN_PULLUP_CONTROL0				0xA8  // Internal pull-up resistors of pin ranges 0
#define PIN_PULLUP_CONTROL1				0xA9  // Internal pull-up resistors of pin ranges 1

//-----------------------------------------------------------------------------
// Consumer Electronics Control
//-----------------------------------------------------------------------------
#define CEC_CONTROL0				    0xAA  // CEC Control Register 0
#define CEC_CONTROL1				    0xAB  // CEC Control Register 1
#define CEC_CONTROL2				    0xAC  // CEC Control Register 2
#define CEC_CONTROL3				    0xAD  // CEC Control Register 3
#define CEC_CONTROL4				    0xAE  // CEC Control Register 4
#define CEC_RT0				            0xAF  // CEC Retry Wait Time
#define CEC_RT1				            0xB0  // CEC Max number of retries
#define CEC_RX0				            0xB1  // CEC Reciever Control and Status
#define CEC_RX1				            0xB2  // CEC Reciever Status
#define CEC_TX0				            0xB3  // CEC Transmitter Control and Status
#define CEC_TX1				            0xB4  // CEC Transmitter Status
#define CEC_TX_FIFO				        0xB5  // CEC Transmitter output buffer
#define CEC_RX_FIFO				        0xB6  // CEC Reciever input buffer
#define CEC_RX_START0				    0xB7  // CEC RX Start low
#define CEC_RX_START1				    0xB8  // CEC RX Start period
#define CEC_RX_DATA0				    0xB9  // CEC RX Data sample
#define CEC_RX_DATA1				    0xBA  // CEC RX Data period
#define CEC_TX_START0				    0xBB  // CEC TX Start low
#define CEC_TX_START1				    0xBC  // CEC TX Start high
#define CEC_TX_DATA0				    0xBD  // CEC TX Data low
#define CEC_TX_DATA1				    0xBE  // CEC TX Data middle
#define CEC_TX_DATA2				    0xBF  // CEC TX Data high

//-----------------------------------------------------------------------------
// GPIO Input/Output registers
//-----------------------------------------------------------------------------
#define PORT_READ_CONTROL				0xC0  // Read back source selection for pins
#define P5_2				            0xC1  // Port 5 Pin 2
#define P5_3				            0xC2  // Port 5 Pin 3
#define P5_4				            0xC3  // Port 5 Pin 4
#define P5_5				            0xC4  // Port 5 Pin 5
#define P5_6				            0xC5  // Port 5 Pin 6
#define P5_7				            0xC6  // Port 5 Pin 7
#define P6_0				            0xC7  // Port 6 Pin 0
#define P6_1				            0xC8  // Port 6 Pin 1
#define P6_2				            0xC9  // Port 6 Pin 2
#define P6_3				            0xCA  // Port 6 Pin 3
#define P6_4				            0xCB  // Port 6 Pin 4
#define P6_5				            0xCC  // Port 6 Pin 5
#define P6_6				            0xCD  // Port 6 Pin 6
#define P6_7				            0xCE  // Port 6 Pin 7
#define P7_0				            0xCF  // Port 7 Pin 0
#define P7_1				            0xD0  // Port 7 Pin 1
#define P7_2				            0xD1  // Port 7 Pin 2
#define P7_3				            0xD2  // Port 7 Pin 3
#define P7_4				            0xD3  // Port 7 Pin 4
#define P7_5				            0xD4  // Port 7 Pin 5
#define P7_6				            0xD5  // Port 7 Pin 6
#define P8_0				            0xD6  // Port 8 Pin 0
#define P8_1				            0xD7  // Port 8 Pin 1
#define P9_0				            0xD8  // Port 9 Pin 0
#define P9_1				            0xD9  // Port 9 Pin 1
#define P9_2				            0xDA  // Port 9 Pin 2
#define P9_3				            0xDB  // Port 9 Pin 3
#define P9_4				            0xDC  // Port 9 Pin 4
#define PA_0				            0xDD  // Port A Pin 0
#define PA_1				            0xDE  // Port A Pin 1
#define PA_2				            0xDF  // Port A Pin 2
#define PA_3				            0xE0  // Port A Pin 3
#define PA_4				            0xE1  // Port A Pin 4
#define P1X				                0xE2  // Port 1 (External access)
#define P3X				                0xE3  // Port 3 (External access)

//-----------------------------------------------------------------------------
// Watch Dog Timer
//-----------------------------------------------------------------------------
#define WDT_CONTROL				        0xEA  // Watch Dog Timer Control Register
#define WDT_TEST				        0xEB  // Watch Dog Timer Signal Bypass Selection

//-----------------------------------------------------------------------------
// I2C In System Programming
//-----------------------------------------------------------------------------
#define ISP_SLAVE_ADDRESS				0xEC  // Address of device on I2C slave bus
#define ISP_MCU_CONTROL				    0xED  // Control of internal MCU
#define ISP_MCU_CLOCK_CONTROL			0xEE  // MCU Clock Control and reset
#define ISP_RAM_TEST				    0xEF  // Internal RAM Test

//-----------------------------------------------------------------------------
// Scaler Interface
//-----------------------------------------------------------------------------
#define SCALER_CONTROL				    0xF3  // Scaler data gate control
#define SCALER_ADDRESS				    0xF4  // Scaler data address
#define SCALER_DATA				        0xF5  // Scaler data byte
#define SCALER_BURST_WRITE_ADDRESS_HI	0xF6  // Burst Write Command Start Address High byte
#define SCALER_BURST_WRITE_ADDRESS_MD	0xF7  // Burst Write Command Start Address Middle byte
#define SCALER_BURST_WRITE_ADDRESS_LO	0xF8  // Burst Write Command Start Address Low byte
#define SCALER_BURST_WRITE_COUNT_HI		0xF9  // Burst Write Command Data Length High byte
#define SCALER_BURST_WRITE_COUNT_LO		0xFA  // Burst Write Command Data Length Low byte
#define SCALER_PERIOD				    0xFA  // Scaler access delay

//-----------------------------------------------------------------------------
// Bank Swtiching
//-----------------------------------------------------------------------------
#define BANK_CONTROL				    0xFC  // Control of mapping of external memory and Control of bank switching
#define BANK_XDATA_START				0xFD  // The start bank number for XDATA access
#define BANK_XDATA_SELECT				0xFE  // First bank number for XDATA access
#define BANK_PBANK_SWITCH				0xFF  // Bank number for program code access
