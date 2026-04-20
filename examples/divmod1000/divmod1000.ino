//
//    FILE: divmod1000.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: divmod1000 develop
//     URL: https://github.com/RobTillaart/fast_math


#include "Arduino.h"
// #include "fast_math.h"

uint32_t start, stop;

//  work in progress
void divmod1000(uint32_t in, uint32_t *div, uint16_t *mod)
{
  uint32_t n = in;
  n = (in >> 10);
  uint32_t q = n;   //  q = in / 1024
  uint16_t p = n >> 6; q += p;
  p >>= 1; q += p;
  p >>= 4; q += p;
  p >>= 3; q += p;
  p >>= 2; q += p;
  p >>= 5; q -= p;

  n = q * 1000UL;
  // while (n < in) { q++; n += 1000; };
  while (n > in) { q--; n -= 1000; };
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
  for (uint32_t i = 0; i < 10000000; i++)
  {
    uint32_t x = random(4000000000);
    uint32_t d;
    uint16_t m;
    divmod1000(x, &d, &m);
    if (x != (d * 1000 + m))
    {
      Serial.print(x / 1000);
      Serial.print('\t');
      Serial.print(x % 1000);
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

// old code
//
//  work in progress
// void divmod1000(uint32_t in, uint32_t *div, uint16_t *mod)
// {
  // uint32_t n = in;
  // n = (in >> 10);
  // uint32_t q = n;   //  q = in / 1024
  // n >>= 6; q += n;
  // n >>= 1; q += n;
  // n >>= 4; q += n;
  // n >>= 3; q += n;
  // n >>= 2; q += n;
  // n >>= 5; q -= n;

  // n = q * 1000UL;
  // // while (n < in) { q++; n += 1000; };
  // while (n > in) { q--; n -= 1000; };
  // *div = q;
  // *mod = in - n;
// }

/*
void divmod1000(uint32_t in, uint32_t *div, uint16_t *mod)
{
  uint32_t n = (in >> 10);
  uint32_t q = n;   //  q = in / 1024
  n = (n >> 6); q = q + n;
  n = (n >> 1); q = q + n;
  n = (n >> 4); q = q + n;
  n = (n >> 3); q = q + n;
  n = (n >> 2); q = q + n;
  n = (n >> 5); q = q - n;

  while (q * 1000UL < in) q++;
  while (q * 1000UL > in) q--;
  *div = q;
  *mod = in - (q * 1000UL);
}
*/

/*
void divmod1000(uint32_t in, uint32_t *div, uint16_t *mod)
{
  uint32_t n = (in >> 8);
  uint32_t q = (n >> 2);   //  q = in / 1024
  n = (n >> 8);
  q = q + n;
  q = q + (n >> 1);
  q = q + (n >> 5);
  n = n >> 8;
  q = q + n;
  q = q + (n >> 2) - (n >> 7);
  // q = q + (n >> 3);
  // q = q + (n >> 4);
  // q = q + (n >> 5);
  // q = q + (n >> 6);
  // q = q + (n >> 7);

//  Serial.println(q);
//  Serial.println(n >> 6);

  while (q * 1000UL < in) q++;
  if (q * 1000UL > in) q--;
  *div = q;
  *mod = in - (q * 1000UL);
}
*/

//  -- END OF FILE --
