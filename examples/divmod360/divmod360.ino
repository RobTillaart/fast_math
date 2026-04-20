//
//    FILE: divmod360.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: divmod360 develop
//     URL: https://github.com/RobTillaart/fast_math


#include "Arduino.h"
// #include "fast_math.h"

uint32_t start, stop;

//  work in progress
void divmod360(uint32_t in, uint32_t *div, uint16_t *mod)
{
  uint32_t n = in;
  n = (in >> 9);
  uint32_t q = n;   //  q = in / 512
  n >>= 2; q += n;
  n >>= 1; q += n;
  n >>= 2; q += n;
  n >>= 1; q += n;
  uint16_t p = n >> 6; q += p;
  p >>= 2; q += p;
  p >>= 1; q += p;
  p >>= 2; q += p;
  p >>= 1; q += p;

  n = q * 360UL;
  while (n < in) {
    q++;
    n += 360;
  };
  while (n > in) {
    q--;
    n -= 360;
  };
  *div = q;
  *mod = in - n;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  //  Serial.print("FASTMATH_LIB_VERSION: ");
  //  Serial.println(FASTMATH_LIB_VERSION);
  //  Serial.println();
  //  delay(1000);

  uint32_t cnt = 0;
  start = millis();
  for (uint32_t i = 0; i < 1000000; i++)
  {
    uint32_t x = random(4000000000);
    uint32_t d;
    uint16_t m;
    divmod360(x, &d, &m);
    if (x != (d * 360 + m))
    {
      Serial.print(x / 360);
      Serial.print('\t');
      Serial.print(x % 360);
      Serial.print('\t');
      Serial.print(d);
      Serial.print('\t');
      Serial.println(m);
      cnt++;
    }
  }
  stop = millis();
  Serial.println(cnt);
  Serial.print("TIME: ");
  Serial.println(stop - start);
}


void loop()
{
}


//  -- END OF FILE --
