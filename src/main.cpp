#include "os/ultrasonicSensorClass.h"
#include <iostream>
#include <pigpio.h>

using namespace std;

int main() {
    gpioInitialise();
    ultrasonicSensorClass ultrasonic(23, 24, 1);
    ultrasonic.sense_location();
    gpioTerminate();
}
