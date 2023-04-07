/*
 * Modified Python Code --> CPP for use in ultrasonic sensor
 * HC-SR04
 * Source in Python : https://tutorials-raspberrypi.com/raspberry-pi-ultrasonic-sensor-hc-sr04/
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include "unistd.h"
#include "ultrasonicSensorClass.h"
#include <pigpio.h>
#include <thread>
#include <vector>

using namespace std;

ultrasonicSensorClass::ultrasonicSensorClass(int in, int out, int sensor_no)
{
    this->sensor_no = sensor_no;
    input_pin = in;
    output_pin = out;
}

void ultrasonicSensorClass::sense_location()
{
    using namespace std::chrono;
    
    gpioSetMode(input_pin, PI_INPUT);
    gpioSetMode(output_pin, PI_OUTPUT);
    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point stopTime;

    try
    {
        running = true;
        while (running)
        {
            gpioWrite(output_pin, 0);
            sleep(1);
            gpioWrite(output_pin, 1); // trigger high
            sleep(0.0001);
            gpioWrite(output_pin, 0); // trigger low

            // save start time
            while (gpioRead(input_pin) == 0)
            {
                // get GPIO read result
                startTime = high_resolution_clock::now();
            }

            // save stop time
            while (gpioRead(input_pin) == 1)
            {
                stopTime = high_resolution_clock::now();
            }

            // main calculations, speed of sound
            auto timeElapsed = duration_cast<microseconds>(stopTime - startTime);
            double distance = 100*((timeElapsed.count()/1000000.0)*340.29)/2;
            // cout << this->sensor_no << ": " << distance << " cm" << endl;

            // reset chrono time
            startTime = high_resolution_clock::now();
            stopTime = high_resolution_clock::now();

            if (distance < 5.0) {
                avaliability = false;
                gpioWrite(led_pin, 1);
            } else {
                avaliability = true;
                gpioWrite(led_pin, 0);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void ultrasonicSensorClass::displayInterrupt(int gpio, int level, uint32_t tick, void* userdata) 
{
	((ultrasonicSensorClass*)userdata)->dataReady();
}

void ultrasonicSensorClass::dataReady() {
    if (!callback) {
        return;
    }
    ultrasonicSample sample;
    sample.avaliability = avaliability;
    sample.sensor_no = sensor_no;
    callback->avaliability_changed(sample);
}

void ultrasonicSensorClass::registerCallback(ultrasonicCallback* cb) 
{
    callback = cb;
}

void ultrasonicSensorClass::start(std::thread* th){
	led_pin = sensor_no;
	gpioSetMode(led_pin, PI_OUTPUT);
	gpioWrite(led_pin, 0);
	gpioSetISRFuncEx(led_pin, EITHER_EDGE, 0, displayInterrupt, (void*)this);
	*th = thread(&ultrasonicSensorClass::sense_location,this);
    t = th;
}

void ultrasonicSensorClass::stop(){
    running = false;
    t->join();
	//gpioSetISRFuncEx(led_pin, EITHER_EDGE, -1, NULL, (void*)this);
}
