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
        ultrasonicSensorClass(int in, int out, int sensor_no);
        int sense_location();
    private:
        int sensor_no;
        int input_pin;
        int output_pin;
};

#endif //ULTRASONIC_H
