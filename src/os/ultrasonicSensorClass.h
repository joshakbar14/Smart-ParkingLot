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
        int sensorCheck();
    private:
        std::string gpioIn;
        std::string gpioOut;
};

#endif //ULTRASONIC_H