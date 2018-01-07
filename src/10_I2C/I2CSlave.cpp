/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-10 11:31:19
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: dataslave.c
 * @Last modified by:   brinkmannm
 * @Last modified time: 2018-01-07T11:22:13+01:00
 * @License: MIT
 */

#include "I2CSlave.hpp"
#include "../Config.hpp"
#include "../90_HelperFunc/Logger.cpp"
#include <Wire.h>

//Prototypes
void reciveEvent(int numBytes);
void requestEvent();
void evalMessage();

uint8_t recBuffer [4];
uint8_t numRecItems;
uint8_t u8Command;
uint8_t u8Register;
uint8_t memoryMap [16];

void initI2CBus(void)
//Initialising the wire lib and attach functions to interrupts
{
  Sprintln("Initialise I2C Bus");
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(reciveEvent);
}


void reciveEvent(int numBytes)
//Recive Items
{
  if (numBytes <= 4) //Only accept messages with max. 4 bytes
  {
    for(numRecItems=0;numRecItems<numBytes;numRecItems++)
    {
      recBuffer[numRecItems] = Wire.read();
    }
    numRecItems = numBytes;
    evalMessage();
  } else {
    for(numRecItems=0;numRecItems<numBytes;numRecItems++)
    {
      Wire.read();
    }
  }
  //First 4 Bytes are the command, the second the Address
  /*
  *  0x1x --> Write byte
  *  0x2x --> Write word
  *  0x4x --> Read byte
  *  0x8x --> Read word
  */
}

void evalMessage()
{
  //Extract the Command
  u8Command = recBuffer[0] & 0xf0;
  //Extract Register
  u8Register = recBuffer[0] & 0x0f;
  if (u8Register >= 16)  //Adress not valid
  {
    u8Command = 0;
  }

  switch (u8Command) {
    case 0x10:
      memoryMap[u8Register] = recBuffer[1];
      break;
    case 0x20:
      if (u8Register < 15)  //Adress valid for word access
      {
        memoryMap[u8Register] = recBuffer[1];
        memoryMap[u8Register+1] = recBuffer[2];
      }
      break;
    case 0x40:
      break;
    case 0x80:
      if (u8Register >= 15)  //Adress not valid for word access
      {
        u8Command = 0;
      }
      break;
    default:
      u8Command = 0;
      break;
  }
}

void requestEvent()
//Write the contont of the buffer
{
  switch (u8Command) {
    case 0x40:
      Wire.write(&memoryMap[u8Register], 1); //Write byte
      break;
    case 0x80:
      Wire.write(&memoryMap[u8Register], 2); //Write word
      break;
    default:
      Wire.write(0x0000); //Return Zero Value
  }

}
