#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <iostream>
#include <string>
#include <ctime>
#include "unistd.h"
#include <pigpio.h>

using namespace std;

class ultrasonicSensorClass
{
    public:
        ultrasonicSensorClass(std::int in, std::in out, int sensor_no);
        int sense_location();
    private:
        int sensor_no;
};

#endif //ULTRASONIC_H