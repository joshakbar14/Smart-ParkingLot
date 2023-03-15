#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <iostream>
#include <string>
#include <ctime>
#include "unistd.h"
#include <pigpio.h>
#include <thread>

using namespace std;

class ultrasonicSensorClass
{
    public:
        ultrasonicSensorClass(int in, int out, int sensor_no);
        void start();
        void stop();
    private:
        double sense_location();
        int sensor_no;
        int input_pin;
        int output_pin;
        bool running;
        std::thread t;
        
};

#endif //ULTRASONIC_H
