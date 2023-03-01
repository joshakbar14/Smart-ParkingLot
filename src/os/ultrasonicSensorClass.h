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
        ultrasonicSensorClass(std::string in, std::string out);
        int sense_location();
    private:
        static int sensor_no;
        std::string gpioIn;
        std::string gpioOut;
        GPIOClass gpioWrite;
        GPIOClass gpioRead;
};

#endif //ULTRASONIC_H