#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <iostream>
#include <string>
#include <ctime>
#include "unistd.h"
#include <pigpio.h>
#include <thread>
#include <vector>

using namespace std;

struct parkCallback {
public:
	virtual void avaliability_changed(int no, bool avaliability) = 0;
};

class ultrasonicSensorClass
{
    public:
        ultrasonicSensorClass(int in, int out, int sensor_no);
        void displayInterrupt(int gpio, int level, uint32_t tick);
        void registerCallback(parkCallback* callback);
        void start();
        void stop();
    private:
        double sense_location();
        int sensor_no;
        int input_pin;
        int output_pin;
        bool running;
        std::thread t;
        std::vector<parkCallback*> callbacks;
        
};

#endif //ULTRASONIC_H
