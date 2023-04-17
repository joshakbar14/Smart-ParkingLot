#include <stdio.h>
#include <pigpio.h>
#include "BuzzerClass.h"
#include <iostream>
#include <unistd.h>

using namespace std;

BuzzerClass::BuzzerClass(int buzzer_pin)
{
  this->buzzer_pin = buzzer_pin;
  gpioSetMode(buzzer_pin, PI_OUTPUT);
}

void BuzzerClass::buzzer_on()
{
  gpioWrite(buzzer_pin, 1); // Turn buzzer on
  cout << "Buzzer on" << endl;
}

void BuzzerClass::buzzer_off()
{
  gpioWrite(buzzer_pin, 0); // Turn buzzer off
  cout << "Buzzer off" << endl;
}

