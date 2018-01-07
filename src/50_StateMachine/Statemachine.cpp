/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-30 19:00:45
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: Statemachine.cpp
 * @Last modified by:   brinkmannm
 * @Last modified time: 2018-01-07T11:18:22+01:00
 * @License: MIT
 */



#include "Statemachine.hpp"
#include "Controllino.h"
#include "../Config.hpp"
#include "../30_SignalProcessing/SignalProcessing.hpp"
#include "../90_HelperFunc/Logger.cpp"

//Digital Outputs
extern bool xMVBuffer;
extern bool xPumpBuffer;
extern bool xInhibitBurner;

//Digital inputs
extern bool xRequestHeat;
extern bool xPumpWarmWater;
extern bool xWoodBurner;
extern bool xPumpHeating;

extern int16_t i16TempBufferTop;
extern int16_t i16TempBufferButtom;
extern int16_t i16TempWarmWater;
extern int16_t i16TempHeating;
extern int16_t i16TempWood;
extern int16_t i16TempOutdoor;

//Switch to activate the buffer tank
cmpHysU16 tempSwitchOn = cmpHysU16((TEMP_MINIMUM-5)*128,TEMP_MINIMUM*128);

enum eStates {Idle_Buderus, Idle_Buffer, WarmWater, Heating};

//Statemachine Variables
eStates eState = Idle_Buderus;
eStates eOldstate = Idle_Buderus;
bool xEnteringState = false;

void Statemachine()
{
  //Global goto Idle_Buderus Statemachine if temperature in buffer is to low
  if (!(tempSwitchOn.update(i16TempBufferTop)))
  {
    eState = Idle_Buderus;
  }

  xEnteringState = (eState != eOldstate);
  eOldstate = eState;

  switch (eState) {
    case Idle_Buderus:
    //Buffer not active (temperature to low)
      if (xEnteringState)
      {
        Sprintln("Switched to state Idle_Buderus");
        xMVBuffer = false;
        xPumpBuffer = false;
        xInhibitBurner = false;
      }
      if (tempSwitchOn.update(i16TempBufferTop) and (!xRequestHeat) )
      {
        eState = Idle_Buffer;
      }
      break;


    case Idle_Buffer:
    //Buffer active, no warm water and temp is ok
      if (xEnteringState)
      {
        Sprintln("Switched to state Idle_Buffer");
        xMVBuffer = true;
        xPumpBuffer = false;
        xInhibitBurner = true;
      }
      //Request for warmwater
      if (xPumpWarmWater or (xRequestHeat and (!xPumpHeating)))
      {
        eState = WarmWater;
      }
      //Request for heating
      if (xPumpHeating)
      {
        eState = Heating;
      }
      break;


    case WarmWater:
    //warm water making
      if (xEnteringState)
      {
        Sprintln("Switched to state Warmwater");
        xMVBuffer = false;
        xPumpBuffer = false;
        xInhibitBurner = false;
      }
      //Water is warm
      if ((!(xPumpWarmWater or (xRequestHeat and (!xPumpHeating))))  and (!xRequestHeat))
      {
        eState = Idle_Buffer;
      }
      break;



    case Heating:
    //heating the house
      if (xEnteringState)
      {
        Sprintln("Switched to state Heating");
        xMVBuffer = true;
        xPumpBuffer = false;
        xInhibitBurner = true;
      }
      xPumpBuffer = xRequestHeat;
      if (!xPumpHeating)
      {
        eState = Idle_Buffer;
      }
      break;
  }

}
