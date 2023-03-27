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
    // create object of GPIO connection in pin gpioIn and gpioOut
    this->sensor_no = sensor_no;

    input_pin = in;
    output_pin = out;
}

double ultrasonicSensorClass::sense_location()
{
    using namespace std::chrono;
    
    gpioInitialise();
    int led_pin = 0;
    gpioSetMode(input_pin, PI_INPUT);
    gpioSetMode(output_pin, PI_OUTPUT);
    gpioSetMode(led_pin, PI_OUTPUT); //led pin
    gpioWrite(led_pin, 0);
    gpioSetISRFuncEx(led_pin, 1, 0, displayInterrupt, (void*)this);
    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point stopTime;

    // call aFunction whenever GPIO 4 changes state

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
                // startTime = time(&startTime);
            }

            // save stop time

            while (gpioRead(input_pin) == 1)
            {
                stopTime = high_resolution_clock::now();
                // stopTime = time(&stopTime);
            }

            // main calculations, speed of sound
            auto timeElapsed = duration_cast<microseconds>(stopTime - startTime);
            
            // double timeElapsed = stopTime - startTime;
            
            // double distance = timeElapsed.count() * 17150;
            double distance = 100*((timeElapsed.count()/1000000.0)*340.29)/2;
            // double distance = 100*((timeElapsed/1000000.0)*340.29)/2;
            
            // cout << timeElapsed.count() << endl;
            // cout << timeElapsed << endl;
            cout << this->sensor_no << ": " << distance << " cm" << endl;
            // cout << distance << endl;
            // cout << startTime << endl;
            // cout << stopTime << endl;

            // reset chrono time
            startTime = high_resolution_clock::now();
            stopTime = high_resolution_clock::now();

            if (distance < 2) {
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
    return 0;
}

void ultrasonicSensorClass::displayInterrupt(int gpio, int level, uint32_t tick, void* userdata) 
{
    printf("Interrupt %d\n");
    //for (auto callback : callbacks) {
        callback->avaliability_changed(userdata);
    //}
}

void ultrasonicSensorClass::registerCallback(parkCallback* callback) 
{
    //callbacks.push_back(callback);
    this->callback = callback;
}

void ultrasonicSensorClass::start(){
	t = thread(&ultrasonicSensorClass::sense_location,this);
}

void ultrasonicSensorClass::stop(){
    running = false;
	t.join();
}
