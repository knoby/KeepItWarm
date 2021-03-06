/**
 * @Author: Maximilian Brinkmann <KnobY>
 * @Date:   2017-May-12 21:25:24
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: Config.h
 * @Last modified by:   brinkmannm
 * @Last modified time: 2017-Nov-12 16:18:01
 */

/** In this file the configuration for the program is done.
 * Also some compiler pragmas and defs are done here
 */

#include <Controllino.h>

 #ifndef CONFIG_H
 #define CONFIG_H

/**
 * Configuration of the HW
 *
 * 0  - RXD               - USB Serial
 * 1  - TXD               - USB Serial
 * 2  - IN0               - One Wire Bus Data (DS1820)
 * 3  - IN1
 * 4  - D0 - Relais/DO    - Pump Buffer
 * 5  - D1 - Relais/DO    - Magnetvalve Buffer
 * 6  - D2 - Relais/DO    - Inhibit Burner
 * 7  - D3 - Relais/DO
 * 8  - D4 - Relais/DO
 * 9  - D5 - Relais/DO
 * 10 - RTC SS            - SPI RTC
 * 11 - MOSI              - SPI RTC
 * 12 - MISO              - SPI RTC
 * 13 - SCK               - SPI RTC
 * A0 - A0 - AI/DI        - Pump warm Water
 * A1 - A1 - AI/DI        - Pump Heating
 * A2 - A2 - AI/DI        - Temperature Contact Wood
 * A3 - A3 - AI/DI        - Request Burner
 * A4 - D6/SDA - DO       - I2C
 * A5 - D7/SCL - DO       - I2C
 * A6 - A4 - AI
 * A7 - A5 - AI
 *
 */

//Project Information
#define PRG_VERSION "1.0.0.0"
#define PRG_AUTHOR "M. Brinkmann"
#define PRG_TITLE "KeepItWarm"

 //Global configuration
 #define TEMP_MINIMUM 60
 #define ENABLE_SERIAL_PRINT

 //Definition according to the IO mapping above
 #define IO_OneWire CONTROLLINO_IN0

 #define O_MvBuffer CONTROLLINO_D1
 #define O_PumpBuffer CONTROLLINO_D0
 #define O_InhibitBurner CONTROLLINO_D2

 #define I_PumpWarmWater CONTROLLINO_A0
 #define I_PumpHeating CONTROLLINO_A1
 #define I_TempContactWood CONTROLLINO_A3
 #define I_RequestBurner CONTROLLINO_A2


//Onewire Definitions
//ATTENTION: The numbers must be the same as the initilising in TempSensor.cpp
#define TEMPERATURE_PRECISION 12
#define TEMPERATURE_UPDATE 10000
#define TEMPCONVERSION_TIME 1000
#define NUM_WARMWATER 1
#define ADD_WARMWATER {0x28, 0x5D, 0x03, 0x1F, 0x07, 0x00, 0x00, 0xEC}
#define NUM_BUFFERTOP 2
#define ADD_BUFFERTOP {0x28, 0xff, 0x4b, 0x96, 0x74, 0x16, 0x04, 0x6f}
#define NUM_BUFFERBOTTOM 3
#define ADD_BUFFERBOTTOM {0x28, 0xff, 0x2f, 0x96, 0x74, 0x16, 0x04, 0x61}
#define NUM_HEATING 4
#define ADD_HEATING {0x28, 0x5D, 0x03, 0x1F, 0x07, 0x00, 0x00, 0xEC}
#define NUM_WOOD 5
#define ADD_WOOD {0x28, 0x5D, 0x03, 0x1F, 0x07, 0x00, 0x00, 0xEC}
#define NUM_OUTDOOR 6
#define ADD_OUTDOOR {0x28, 0x5D, 0x03, 0x1F, 0x07, 0x00, 0x00, 0xEC}

//I2C Definitions for Master Mode
#define I2C_ADDRESS 42


#endif /* end of include guard:  */
