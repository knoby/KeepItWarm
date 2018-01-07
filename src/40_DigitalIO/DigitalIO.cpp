/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-30 17:13:52
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: DigitalIO.cpp
 * @Last modified by:   brinkmannm
 * @Last modified time: 2018-01-07T11:17:40+01:00
 * @License: MIT
 */



#include "DigitalIO.h"

#include "Controllino.h"
#include "../Config.h"


extern bool xMVBuffer;
extern bool xPumpBuffer;
extern bool xInhibitBurner;


void initDigitalIO(void)
{
  //Setup the Outputs
  pinMode(O_MvBuffer, OUTPUT);
  pinMode(O_PumpBuffer, OUTPUT);
  pinMode(O_InhibitBurner, OUTPUT);


  //Setupb the inputs
  pinMode(I_PumpWarmWater, INPUT);
  pinMode(I_PumpHeating, INPUT);
  pinMode(I_TempContactWood, INPUT);
  pinMode(I_RequestBurner, INPUT);

}


void updateOutputs(void)
{
  digitalWrite(O_MvBuffer, xMVBuffer);
  digitalWrite(O_PumpBuffer, xPumpBuffer);
  digitalWrite(O_InhibitBurner, xInhibitBurner);
}
