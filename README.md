
[![Arduino CI](https://github.com/RobTillaart/fastMath/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/fastMath/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/fastMath/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/fastMath/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/fastMath/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/fastMath/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/fastMath.svg?maxAge=3600)](https://github.com/RobTillaart/fastMath/releases)


# fastMath

Arduino library for fast math algorithms.


## Description

The **experimental** fastMath library is a collection of algorithms that are faster than the default code. 
These algorithms are to be used when you are in a need for speed. 
Only tested on Arduino UNO.

**Warning:** verify if the code works for your project. (no warranty)

Note: I'm interested in your feedback e.g. results on other platforms.
Also improvements or other fast code is welcome. Please open an issue.


## Interface

#### BCD

- **uint8_t dec2bcd(uint8_t value)**
- **uint8_t bcd2dec(uint8_t value)**

Two conversion modules, typical used in an RTC to convert register values
in **BCD** = binary coded decimal, to normal integer values.

- **dec2bcdRTC(uint8_t value)**
Even faster version, for the range 0..60. Typical to be used in RTC's.


#### divmod10

- **void divmod10(uint32_t in, uint32_t &div, uint8_t &mod)**
function calculates both div and modulo faster than normal /10 and %10.

This function is very useful for extracting the individual digits.
Typical use is print digits on a display, in a file or send them as ASCII.

Indicative performance Arduino UNO.

|  function  |   us   |  factor |  notes  |
|:-----------|:------:|:-------:|:-------:|
|  i % 10    |  38.2  |   1.0   |
|  i / 10    |  38.1  |   1.0   |
|  divmod10  |   9.1  |   4.1   | 


#### PING

For distance sensors that work with a acoustic pulse, one often see the formula:
```cm = us / 29;``` to calculate the distance in cm.
In float it should be ``cm = us / 29.15;``` or ``cm = us * 0.0345;```
Note that as this is the turnaround distance (forth & back) so one 
need a divide by two often. (maybe I should include that)

This library has functions to improve on speed.
The maximum input is 65535 us ==> 2250 cm or 22500 mm.
This is enough range for most ping sensors, typical < 10 mtr.
(the functions can be extended to uint32_t)

The functions assume a speed of sound of 340 m/sec.

- **uint16_t ping2cm(uint16_t in)** sos = 340 m/sec
- **uint16_t ping2mm(uint16_t in)** sos = 340 m/sec
- **float ping2cm_temp(uint16_t duration, int temp)** temperature corrected speed of sound.
  - duration in us, temp in Celsius.
  - this function is relative slow, a faster version is not tested.
- **uint16_t ping2inch(uint16_t in)** sos = 340 m/sec
- **uint16_t ping2sixteenths(uint16_t in)** sos = 340 m/sec


Indicative performance Arduino UNO.

|  function         |   us   |  factor |  notes  |
|:------------------|:------:|:-------:|:-------:|
|  us / 29  (ref)   |  38.1  |   1.0   | sos == 345 m/s  (integer only)
|  us \* 0.0345     |  18.5  |   2.0   |
|  ping2cm          |  3.08  |  12.4   | sos == 340 m/s
|  ping2mm          |  5.66  |   6.7   | sos == 340 m/s
|  ping2cm_temp     |  36.8  |   1.0   | adds temperature correction.
|                   |        |         |
|  ping2inch        |  3.90  |   9.8   | not as exact as inches are rather large units
|  ping2sixteenths  |  8.11  |   4.8   | way more accurate than inches


#### polynome

Routine to evaluate a polynome and be able to change its weights runtime.
E.g   y = 3x^2 + 5x + 7 ==> ar\[3] = { 7, 5, 3 };  degree = 2;
- **double polynome(double x, double ar[], uint8_t degree)**
  - degree >= 1, ar\[0] exists, and could be 0.
  
This function is useful for evaluating a polynome many times and be able to
adjust the weights. This can be used for finding the optimal weights to fit
a curve for a polynome of degree N.

See example.


## Operation

See examples.

## Future

#### must
- update documentation

#### should
- split up in multiple .h files, one per group.
  - fastMath.h includes all individual .h files.
- unit tests
- examples

#### could
- There are several divide functions to be included.
  div3(), div5(), div7(), div10(), mod10()
  These need more testing.
- **float ping2inch_temp(uint16_t in, int temp)** Fahrenheit
- constants?
  - GOLDEN_RATIO 1.61803398875

