/**
 * @Author: Maximilian Brinkmann <KnobY>
 * @Date:   2017-May-12 21:56:13
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: TempSensor.cpp
 * @Last modified by:   brinkmannm
 * @Last modified time: 2018-01-07T11:16:46+01:00
 */



//Hardware Includes
#include <Controllino.h>

 //Configuration
#include "Config.h"

//Programm Includes
#include "10_I2C/I2CDisplay.h"
#include "20_OneWire/TempSensor.h"
#include "30_SignalProcessing/SignalProcessing.h"
#include "40_DigitalIO/DigitalIO.h"
#include "50_StateMachine/Statemachine.h"
#include "90_HelperFunc/Logger.cpp"


//Function prototypes
void UpdateTemperatures();
void UpdateDigitalIOs();

void setup() {

  //Initialising the serial Output to Computer
  Serial.begin(9600);

  //Initialise the LCD display
  initDisplay();

  //Initialising the RTC Chip
  Controllino_RTC_init(0);
  //Controllino_SetTimeDate(Day, Weekday, Month, Year, Hour, Minute, Second);
  //Controllino_SetTimeDate(30, 1, 10, 17, 9, 10, 00);
  Controllino_PrintTimeAndDate();

  //Initialisiere Temperature sensors
  initTempSensor();
  UpdateTemperatures();

  //Initialise digital IOs
  initDigitalIO();
  updateOutputs();
}

//Global Vars

//Timing Vars
uint32_t tempMillis = 0;
uint32_t IOMillis = 0;
uint32_t DisplayMillis = 0;

//Digital Output
bool xMVBuffer = false;
bool xPumpBuffer = false;
bool xInhibitBurner = false;

//Digital Input
bool xPumpHeating;
bool xPumpWarmWater;
bool xWoodBurner;
bool xRequestHeat;

//Temperatures
int16_t i16TempBufferTop;
int16_t i16TempBufferButtom;
int16_t i16TempWarmWater;
int16_t i16TempHeating;
int16_t i16TempWood;
int16_t i16TempOutdoor;

void loop() {
  //Get current Millis for some timing functions
  uint32_t currentMillis = millis();

  //Cyclic update of the Temperature sensors
  if ((currentMillis - tempMillis) >= TEMPERATURE_UPDATE)
  {
    tempMillis = currentMillis;
    UpdateTemperatures();
  }

  if ((currentMillis - IOMillis) >= 1000) //Update Digital IOs in Memorymap every Second
  {
    IOMillis = currentMillis;
    UpdateDigitalIOs();
  }

  if ((currentMillis - DisplayMillis) >= 3000) //Update Display
  {
    DisplayMillis = currentMillis;
    updateDisplay();
  }

  Statemachine();

  updateOutputs();

}

void UpdateDigitalIOs()
{
  Sprintln("Updating Digital IO in Memory map");
  //Digital Inputs
  xPumpHeating = digitalRead(I_PumpHeating);
  xWoodBurner = digitalRead(I_TempContactWood);
  xPumpWarmWater = digitalRead(I_PumpWarmWater);
  xRequestHeat = digitalRead(I_RequestBurner);
}

void UpdateTemperatures()
{
    Sprintln("Updating Tempeartures");
    requestTemperature();
    //Wait for Conversion finished
    delay(TEMPCONVERSION_TIME);
    //Read Sensordata and Store them in I2C Memory
    int16_t i16ActTemp = 0;
    for (uint8_t i = 1; i<=6; i++)
    {
      i16ActTemp = getTemperature(i);
      switch(i)
      { //Set the global Variables
        case NUM_WARMWATER:
            i16TempWarmWater = i16ActTemp;
            Sprint("Temperature Warm Water: ");
            Sprintln(i16ActTemp);
          break;
        case NUM_BUFFERTOP:
            i16TempBufferTop = i16ActTemp;
            Sprint("Temperature Buffer Top: ");
            Sprintln(i16ActTemp);
          break;
        case NUM_BUFFERBOTTOM:
            i16TempBufferButtom = i16ActTemp;
            Sprint("Temperature Buffer Buttom: ");
            Sprintln(i16ActTemp);
          break;
        case NUM_HEATING:
            i16TempHeating = i16ActTemp;
            Sprint("Temperature Heating: ");
            Sprintln(i16ActTemp);
          break;
        case NUM_WOOD:
            i16TempWood = i16ActTemp;
            Sprint("Temperature Wood: ");
            Sprintln(i16ActTemp);
          break;
        case NUM_OUTDOOR:
            i16TempOutdoor = i16ActTemp;
            Sprint("Temperature Outdoor: ");
            Sprintln(i16ActTemp);
          break;
      }
    }
}
