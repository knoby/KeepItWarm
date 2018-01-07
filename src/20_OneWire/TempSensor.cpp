/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-21 21:44:23
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: TempSensors.cpp
 * @Last modified by:   brinkmannm
 * @Last modified time: 2018-01-07T11:17:32+01:00
 * @License: MIT
 */


#include "../Config.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "TempSensor.h"
#include "../90_HelperFunc/Logger.cpp"


//Setup One Wire and Tempsensor Objects
OneWire oneWire(IO_OneWire);
DallasTemperature sensors(&oneWire);

//Device mapping
//ATTENTION Order of Adresses must be the same as in the config File
DeviceAddress sensorAdd[] = {ADD_WARMWATER,
                            ADD_BUFFERTOP,
                            ADD_BUFFERBOTTOM,
                            ADD_HEATING,
                            ADD_WOOD,
                            ADD_OUTDOOR};

void initTempSensor()
{
  sensors.begin();

  //Set Resoultion of the Sensros
  sensors.setResolution(sensorAdd[0], TEMPERATURE_PRECISION);
  sensors.setResolution(sensorAdd[1], TEMPERATURE_PRECISION);
  sensors.setResolution(sensorAdd[2], TEMPERATURE_PRECISION);
  sensors.setResolution(sensorAdd[3], TEMPERATURE_PRECISION);
  sensors.setResolution(sensorAdd[4], TEMPERATURE_PRECISION);
  sensors.setResolution(sensorAdd[5], TEMPERATURE_PRECISION);

  //Set Wait for conversion off --> Async call we have to wait in Programm
  sensors.setWaitForConversion(false);

}


void requestTemperature()
{
  Sprintln("Request global conversion");
  sensors.requestTemperatures();
}


int16_t getTemperature(uint8_t sensorNum){
//Select the device and get the Temperature
  int16_t i16Temperature = 0;
  if ((sensorNum >=1) & (sensorNum <= 6))
  {
    i16Temperature = sensors.getTemp(sensorAdd[sensorNum-1]);
  } else {
    i16Temperature = -255;
  }
  return i16Temperature;
}


int16_t normTemperature(int16_t inTemperature)
{ //Check if a conversion is possible without overflow
  if ((inTemperature <= 255) & (inTemperature >= -256))
  {
    return (inTemperature * 128);
  } else //If an overflow would occure return highst value
  {
    if (inTemperature > 256)
    {
      return 32767;
    } else
    {
      return -32768;
    }
  }
}
