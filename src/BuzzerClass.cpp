//This code is to lead the user to car in the correct spot by informing it through Buzzer
//If user park in the right spot; the buzzer will turn off
//If user has not park in the right spot; the buzzer will turn on until the car park in designated spot

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include <unistd.h>

using namespace std;

class Buzzer {
public:
  Buzzer(int sensor_pin, int buzzer_pin);
  void draw();
private:
  int sensor_pin;
  int buzzer_pin;
};

Buzzer::Buzzer(int sensor_pin, int buzzer_pin)
{
  this->sensor_pin = sensor_pin;
  this->buzzer_pin = buzzer_pin;
  gpioSetMode(sensor_pin, PI_INPUT);
  gpioSetMode(buzzer_pin, PI_OUTPUT);
}

int main() {
  Buzzer buzzer(17, 18);
  while (true) {
    buzzer.draw();
  }
  return 0;
}

void Buzzer::draw()
{
  int sensor_value = gpioRead(sensor_pin);
  if (sensor_value == 1)
  {
    gpioWrite(buzzer_pin, 0); // Buzzer turns off
    cout << "Buzzer turns off" << endl;
  }
  else
  {
    gpioWrite(buzzer_pin, 1); // Buzzer turns on
    cout << "Buzzer turns on" << endl;
    usleep(500000); // delay for 500 ms/ 0.5 second
  }
}

