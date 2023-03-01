#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <iostream>
#include <string>
#include <ctime>
#include "GPIO/GPIOClass.h"
#include "unistd.h"

using namespace std;

class ultrasonicSensorClass
{
    public:
        ultrasonicSensorClass(std::string in, std::string out, int sensor_no);
        int sense_location();
    private:
        int sensor_no;
        GPIOClass gpioWrite;
        GPIOClass gpioRead;
};

#endif //ULTRASONIC_H