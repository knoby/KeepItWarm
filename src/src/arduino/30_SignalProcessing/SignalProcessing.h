/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-24 14:59:11
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: SignalProcessing.h
 * @Last modified by:   brinkmannm
 * @Last modified time: 2017-Sep-24 15:26:16
 * @License: MIT
 */

#ifndef SIGNALPROCESSING_H
#define SIGNALPROCESSING_H

 class cmpHysU16 {
 private:
   bool bOldState;
   int16_t i16High;
   int16_t i16Low;
 public:
   cmpHysU16 (int16_t low, int16_t high);
   bool update(int16_t i16Input);
 };

 #endif
