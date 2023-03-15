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

using namespace std;

ultrasonicSensorClass::ultrasonicSensorClass(int in, int out, int sensor_no)
{
    // create object of GPIO connection in pin gpioIn and gpioOut
    this->sensor_no = sensor_no;

    // GPIOClass gpioWrite(in); // write
    // GPIOClass gpioRead(out); // read
    // this->gpioWrite = gpioWrite;
    // this->gpioRead = gpioRead;
    // this->gpioWrite.export_gpio(); // initialize
    // this->gpioWrite.setdir_gpio("out");
    // this->gpioRead.export_gpio(); // initialize
    // this->gpioRead.setdir_gpio("in");

    /*
     * Re-create the whole GPIOClass using PIGPIO library
     * For common language and easy-to-use library
     */
    input_pin = in;
    output_pin = out;
}

int ultrasonicSensorClass::sense_location()
{
    using namespace std::chrono;
    
    // bool checkStatus = true;
    gpioInitialise();
    gpioSetMode(input_pin, PI_INPUT);
    gpioSetMode(output_pin, PI_OUTPUT);
    // high_resolution_clock::time_point startTime;
    // high_resolution_clock::time_point stopTime;
    time_t startTime;
    time_t stopTime;

    // call aFunction whenever GPIO 4 changes state

    try
    {
        while (true)
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
                // startTime = high_resolution_clock::now();
                startTime = time(&startTime);
            }

            // save stop time

            while (gpioRead(input_pin) == 1)
            {
                // stopTime = high_resolution_clock::now();
                stopTime = time(&stopTime);
            }

            // main calculations, speed of sound
            // auto timeElapsed = duration_cast<microseconds>(stopTime - startTime);
            
            double timeElapsed = stopTime - startTime;
            
            // double distance = timeElapsed.count() * 17150;
            // double distance = 100*((timeElapsed.count()/1000000.0)*340.29)/2;
            double distance = 100*((timeElapsed/1000000.0)*340.29)/2;
            
            // cout << timeElapsed.count() << endl;
            cout << timeElapsed;
            cout << distance << endl;
            // cout << startTime << endl;
            // cout << stopTime << endl;

            // reset chrono time
            // startTime = high_resolution_clock::now();
            // stopTime = high_resolution_clock::now();

            sleep(0.60);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
