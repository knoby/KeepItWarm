/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Oct-30 21:49:29
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: I2CDisplay.cpp
 * @Last modified by:   KnobY
 * @Last modified time: 2018-01-04T14:06:15+01:00
 * @License: MIT
 */

//Include own heaer
#include "I2CDisplay.h"

//External vars to display Status
#include "Controllino.h"
#include "../Config.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern bool xMVBuffer;
extern bool xPumpBuffer;
extern bool xInhibitBurner;
extern bool xPumpHeating;
extern bool xPumpWarmWater;
extern bool xWoodBurner;
extern bool xRequestHeat;
extern int16_t i16TempBufferTop;
extern int16_t i16TempBufferButtom;
extern int16_t i16TempWarmWater;
extern int16_t i16TempHeating;
extern int16_t i16TempWood;
extern int16_t i16TempOutdoor;

LiquidCrystal_I2C lcd(0x27,17,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

uint8_t u8MSG = 0;

void initDisplay()
{
    lcd.init();   // initialize the lcd
    // Print Start Message on Screen
    lcd.backlight();
    updateDisplay();
}


void updateDisplay()
{
    lcd.clear();

    switch(u8MSG)
    {
        case 0:
            lcd.setCursor(0, 0);
            lcd.print(PRG_TITLE);
            lcd.setCursor(0,1);
            lcd.print(PRG_VERSION);
            break;
        case 1:
            lcd.print((int) Controllino_GetHour());
            lcd.print(":");
            lcd.print((int) Controllino_GetMinute());
            break;
        case 2:
            lcd.setCursor(0,0);
            lcd.print("Puffer Oben:");
            lcd.setCursor(0,1);
            lcd.print(((float)i16TempBufferTop)/128.0);
            lcd.print(" Grad C");
            break;
        case 3:
            lcd.setCursor(0,0);
            lcd.print("Puffer Unten:");
            lcd.setCursor(0,1);
            lcd.print(((float)i16TempBufferButtom)/128.0);
            lcd.print(" Grad C");
            break;
        case 4:
            lcd.setCursor(0,0);
            lcd.print("MV Puffer:");
            lcd.setCursor(0,1);
            lcd.print(xMVBuffer);
            break;
        case 5:
            lcd.setCursor(0,0);
            lcd.print("Pumpe Puffer:");
            lcd.setCursor(0,1);
            lcd.print(xPumpBuffer);
            break;
        case 6:
            lcd.setCursor(0,0);
            lcd.print("Brennersperre:");
            lcd.setCursor(0,1);
            lcd.print(xInhibitBurner);
            break;

    }

    u8MSG += 1;
    if (u8MSG > 6)
    {
        u8MSG = 2;
    }



}
