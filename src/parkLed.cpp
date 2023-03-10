// This code is to:
/* turn on LED when the parking lot is occupied*/
/* turn LED off when the parking lot is empty*/

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "parkLed.h"

using namespace std;

parkLed::parkLed(int sensor_pin, int led_pin)
{
  this->sensor_pin = sensor_pin;
  this->led_pin = led_pin;
  gpioSetMode(sensor_pin, PI_INPUT);
  gpioSetMode(led_pin, PI_OUTPUT);
}

void parkLed::draw()
{
  int sensor_value = gpioRead(sensor_pin);
  if (sensor_value == 1)
  {
    gpioWrite(led_pin, 1);
    cout << "Write 1" << endl;
  }
  else
  {
    gpioWrite(led_pin, 0);
    cout << "Write 0" << endl;
  }
}

// int main()
// {
//   int sensor_pin = 24;
//   int led_pin = 0;
//   gpioInitialise();
//   parkLed led(sensor_pin, led_pin);

//   while (true)
//   {
//     led.draw();
//   }

//   gpioTerminate();
//   return 0;
// }
