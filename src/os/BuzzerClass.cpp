#include <stdio.h>
#include <pigpio.h>
#include "BuzzerClass.h"
#include <iostream>
#include <unistd.h>

using namespace std;

BuzzerClass::BuzzerClass(int sensor_pin)
{
  this->buzzer_pin = buzzer_pin;
  gpioSetMode(buzzer_pin, PI_OUTPUT);
}

// int main() {
//   BuzzerClass buzzer(17, 18);
//   while (true) {
//     buzzer.buzz();
//   }
//   return 0;
// }

void BuzzerClass::buzzer_on()
{
  gpioWrite(buzzer_pin, 1); // Turn buzzer on
  cout << "Buzzer turns on" << endl;
}

void BuzzerClass::buzzer_off()
{
  gpioWrite(buzzer_pin, 0); // Turn buzzer off
  cout << "Buzzer turns off" << endl;
}

