//
//    FILE: bcd_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: bcd test
//     URL: https://github.com/RobTillaart/fastMath


#include "Arduino.h"
#include "fastMath.h"


uint32_t start, stop;
volatile uint8_t z;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTMATH_LIB_VERSION: ");
  Serial.println(FASTMATH_LIB_VERSION);
  Serial.println();
  delay(100);

  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = dec2bcd(x);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = dec2bcd_2(x);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  // not 100% correct but it is about performance
  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = bcd2dec(x);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = dec2bcd(x);
    if (x != bcd2dec(z))
    {
      Serial.print(".");
    }
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);



  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
