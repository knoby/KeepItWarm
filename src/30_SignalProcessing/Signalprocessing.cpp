/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-24 14:59:18
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: Signalprocessing.cpp
 * @Last modified by:   brinkmannm
 * @Last modified time: 2017-Sep-24 15:29:01
 * @License: MIT
 */

 #include "Controllino.h"
#include "SignalProcessing.h"

///// Compare with Hysteresis and 16 bit

cmpHysU16::cmpHysU16(int16_t i16LowIn, int16_t i16HighIn)
{
  i16High = i16HighIn;
  i16Low = i16LowIn;
  bOldState = 0;
}

bool cmpHysU16::update(int16_t i16Input)
{
  if (i16Input >= i16High)
  {
    bOldState = 1;
  } else if (i16Input <= i16Low)
  {
    bOldState = 0;
  }
  return bOldState;
}
