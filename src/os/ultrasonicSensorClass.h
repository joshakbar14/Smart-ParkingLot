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
	//virtual void avaliability_changed(int no, bool avaliability) = 0;
    virtual void avaliability_changed(ultrasonicSensorClass s) = 0;
};

class ultrasonicSensorClass
{
    public:
        ultrasonicSensorClass(int in, int out, int sensor_no);
        static void displayInterrupt(int gpio, int level, uint32_t tick, void* userdata);
        void registerCallback(parkCallback* callback);
        void start();
        void stop();
        bool avaliability;
        int sensor_no;
    private:
        double sense_location();
        int input_pin;
        int output_pin;
        bool running;
        std::thread t;
        //std::vector<parkCallback*> callbacks;
        parkCallback* callback;
        
};

#endif //ULTRASONIC_H
