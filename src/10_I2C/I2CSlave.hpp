/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-10 11:26:19
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: dataslave.h
 * @Last modified by:   brinkmannm
 * @Last modified time: 2017-Oct-30 21:54:05 
 * @License: MIT
 */

#ifndef I2CSLAVE_H
#define I2CSLAVE_H
#include "Arduino.h"

extern uint8_t memoryMap [16];
/*
byte 0 -- Digital Inputs
byte 1 -- Digital Outputs
byte 2,3 -- Temperature Warm water
byte 4,5 -- Temperature Buffer Top
byte 6,7 -- Temperature Buffer Button
byte 8,9 -- Temperature Heating
byte 10,11 -- Temperature wood
byte 12,13 -- Temperature From Buffer
byte 14 -- Statemachine Step
byte 15 --
*/


void initI2CBus(void);

#endif
