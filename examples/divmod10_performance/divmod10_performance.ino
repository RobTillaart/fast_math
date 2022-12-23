//
//    FILE: divmod10_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: divmod10 performance test
//     URL: https://github.com/RobTillaart/fastMath


#include "Arduino.h"
#include "fastMath.h"


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

  x = random();
  start = micros();
  y = x / 10;
  z = x % 10;
  stop = micros();
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
  divmod10(x, y, z);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
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
