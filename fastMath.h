#pragma once
//
//    FILE: fastMath.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino collection of fast math algorithms
//     URL: https://github.com/RobTillaart/fastMath


#ifdef ESP_PLATFORM
  #include <math.h>
  #include <stdint.h>
  #include <stdbool.h>
#endif

#include "Arduino.h"

#define FASTMATH_LIB_VERSION          (F("0.2.0"))


#ifdef __cplusplus
extern "C"
{
#endif


//////////////////////////////////////////////////////////////////////////
//
//  ROUTINE: divmod10
//  PURPOSE: fast routine that provides both /10 and %10 for integer math.
//      URL: https://forum.arduino.cc/t/divmod10-a-fast-replacement-for-10-and-10-unsigned/163586
//  AUTHORS: see URL
//     NOTE: assembler version for AVR exists (by Stimmer) - see URL
//
void divmod10(uint32_t in, uint32_t &div, uint8_t &mod);


//////////////////////////////////////////////////////////////////////////
//
//  ROUTINE: dec2bcd and bcd2dec
//  PURPOSE: conversion
//
uint8_t dec2bcd(uint8_t value);
uint8_t dec2bcdRTC(uint8_t value);
uint8_t bcd2dec(uint8_t value);


//////////////////////////////////////////////////////////////////////////
//
//  ROUTINE: polynome
//  PURPOSE: routine to evaluate a polynome and be able to change weights runtime.
//
//  assumes degree >= 1, and ar[0] exists, and could be 0.
//
//  e.g y = 3x^2 + 5x + 7 ==> ar[] = { 7, 5, 3 };  degree = 2;
//
float polynome(float x, float ar[], uint8_t degree);


//////////////////////////////////////////////////////////////////////////
//
//  16 BIT PING MATH - for distances up to ~20 meter
//
//////////////////////////////////////////////////////////
//
//  ROUTINE: ping2cm
//  PURPOSE: fast routines to calculate the distance in cm / mm for a ping sensor
//
uint16_t ping2cm(uint16_t in);
uint16_t ping2mm(uint16_t in);
uint16_t ping2inch(uint16_t in);
uint16_t ping2sixteenths(uint16_t in);

//////////////////////////////////////////////////////////
//
//  32 BIT PING MATH - for longer distances 
//
uint32_t ping2cm32(uint32_t in);
uint32_t ping2mm32(uint32_t in);


//  temperature compensated speed of sound distance
float ping2cm_temp(uint16_t duration, int Celsius);
float ping2inch_temp(uint16_t duration, int Celsius);


#ifdef __cplusplus
}
#endif


//  -- END OF FILE --

