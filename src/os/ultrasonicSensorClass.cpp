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
    using namespace std::chrono
    
    // bool checkStatus = true;
    gpioInitialise();
    gpioSetMode(input_pin, PI_INPUT);
    gpioSetMode(output_pin, PI_OUTPUT);
    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point stopTime;

    // call aFunction whenever GPIO 4 changes state

    try
    {
        while (true)
        {
            gpioWrite(output_pin, 1); // trigger high
            usleep(10);
            gpioWrite(output_pin, 0); // trigger low
            // save start time

            while (gpioRead(input_pin) == 1)
            {
                // get GPIO read result
                startTime = high_resolution_clock::now();
            }

            // save stop time

            while (gpioRead(input_pin) == 0)
            {
                stopTime = high_resolution_clock::now();
            }

            // main calculations, speed of sound
            auto timeElapsed = duration_cast<microseconds>(stopTime - startTime);
            int distance = timeElapsed.count() * 0.0343 / 2;
            cout << distance << endl;
            // cout << startTime << endl;
            // cout << stopTime << endl;

            // reset chrono time
            startTime = high_resolution_clock::now();
            stopTime = high_resolution_clock::now();

            sleep(1);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
