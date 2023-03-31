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

struct ultrasonicSample {
    bool avaliability = true;
    int sensor_no = 0;
};

class ultrasonicCallback {
public:
    virtual void avaliability_changed(ultrasonicSample sample) = 0;
};

class ultrasonicSensorClass
{
    public:
        ultrasonicSensorClass(int in, int out, int sensor_no);
        void registerCallback(ultrasonicCallback* cb);
        void start();
        void stop();
    private:
        double sense_location();
        static void displayInterrupt(int gpio, int level, uint32_t tick, void* userdata);
        void dataReady();
        int input_pin;
        int output_pin;
        bool running;
        std::thread t;
        ultrasonicCallback* callback = nullptr;
        bool avaliability;
        int sensor_no;
	    int led_pin;
};

#endif //ULTRASONIC_H
