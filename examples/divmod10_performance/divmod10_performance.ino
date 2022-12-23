//
//    FILE: divmod10_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: divmod10 performance test
//     URL: https://github.com/RobTillaart/fast_math


#include "Arduino.h"
#include "fast_math.h"


uint32_t start, stop;
uint32_t x, y;
uint8_t z;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTMATH_LIB_VERSION: ");
  Serial.println(FASTMATH_LIB_VERSION);
  Serial.println();
  delay(1000);

  x = random(2000000000ULL);
  start = micros();
  y = x / 10;
  z = x % 10;
  stop = micros();
  Serial.print("div + mod: ");
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  start = micros();
  divmod10(x, &y, &z);
  stop = micros();
  Serial.print("divmod10:  ");
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  Serial.println("\nTest 0 .. 1 million (1 minute UNO, < 1second ESP32)");
  start = micros();
  for (uint32_t x = 0; x <= 1000000; x++)
  {
    if (x % 100000 == 0) Serial.println(x);
    divmod10(x, &y, &z);
    if (x != (y * 10 + z))
    {
      Serial.print(x);
      Serial.print("\t");
      Serial.print(y);
      Serial.print("\t");
      Serial.print(z);
      Serial.print("\n");
    }
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\n");

  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
