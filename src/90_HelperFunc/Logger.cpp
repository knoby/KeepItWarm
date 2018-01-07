/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-21 21:29:04
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: Logger.c++
 * @Last modified by:   brinkmannm
 * @Last modified time: 2017-Nov-11 23:10:10
 * @License: MIT
 */

#ifndef LOGGER_H
#define LOGGER_H

//Very simple Makro to disable Print

#ifdef ENABLE_SERIAL_PRINT
  #define Sprintln(a) (Serial.println(a))
  #define Sprint(a) (Serial.println(a))
#else
  #define Sprintln(a)
  #define Sprint(a)
#endif


#endif
