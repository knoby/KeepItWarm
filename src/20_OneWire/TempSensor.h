/**
 * @Author: Maximilian Brinkmann <brinkmannm>
 * @Date:   2017-Sep-21 21:44:15
 * @Email:  maximilian.brinkmann@gmx.net
 * @Project: KeepItWarm
 * @Filename: TempSensors.h
 * @Last modified by:   brinkmannm
 * @Last modified time: 2017-Sep-21 22:22:00
 * @License: MIT
 */



#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

void initTempSensor();

void requestTemperature();
int16_t getTemperature(uint8_t sensorNum);

int16_t normTemperature(int16_t inTemperature); //Get the normalised Temperture (1/125 °C)


#endif
