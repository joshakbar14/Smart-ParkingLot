#include "os/ultrasonicSensorClass.h"
#include <iostream>
#include <pigpio.h>

#include "parkingLot.h"

using namespace std;

int main() {
    gpioInitialise();
//     ultrasonicSensorClass ultrasonic1(23, 24, 1);
//     ultrasonicSensorClass ultrasonic2(17, 27, 2);
//     ultrasonic1.start();
//     ultrasonic2.start();
//     sleep(10);
//     ultrasonic1.stop();
//     ultrasonic2.stop();
//     gpioTerminate();

    parkingLot parkinglot(1);

    gpioTerminate();
}
