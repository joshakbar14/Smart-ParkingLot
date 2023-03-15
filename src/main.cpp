#include "os/ultrasonicSensorClass.h"
#include <iostream>
#include <pigpio.h>

using namespace std;

int main() {
    gpioInitialise();
    ultrasonicSensorClass ultrasonic1(23, 24, 1);
    ultrasonicSensorClass ultrasonic2(17, 27, 2);
    ultrasonic1.sense_location();
    ultrasonic2.sense_location();
    gpioTerminate();
}
