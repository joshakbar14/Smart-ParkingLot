/*
 * Modified Python Code --> CPP for use in ultrasonic sensor
 * HC-SR04
 * Source in Python : https://tutorials-raspberrypi.com/raspberry-pi-ultrasonic-sensor-hc-sr04/
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <ctime>
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

void aFunction(int gpio, int level, uint32_t tick)
    {
        printf("GPIO %d became %d at %d", gpio, level, tick);
        if (level == 1)
        {
            distance = tick;
            cout << distance << endl;
        }
        
    }

int ultrasonicSensorClass::sense_location()
{
    // bool checkStatus = true;
    gpioInitialise();
    gpioSetMode(input_pin, PI_INPUT);
    gpioSetMode(output_pin, PI_OUTPUT);
    time_t startTime = time(&startTime);
    time_t stopTime = time(&stopTime);

    // call aFunction whenever GPIO 4 changes state

    try
    {
        while (true)
        {
            gpioWrite(output_pin, 1); // trigger high
            usleep(100);
            gpioWrite(output_pin, 0); // trigger low
            // save start time

            // while (gpioRead(input_pin) == 1)
            // {
            //     // get GPIO read result
            //     startTime = time(&startTime);
            // }

            // // save stop time

            // while (gpioRead(input_pin) == 0)
            // {
            //     stopTime = time(&stopTime);
            // }

            gpioSetAlertFunc(input_pin, aFunction);

            // main calculations, speed of sound
            // int timeElapsed = startTime - stopTime;
            // int distance = (timeElapsed / 58.2);
            // cout << distance << endl;
            // cout << startTime << endl;
            // cout << stopTime << endl;
            sleep(1);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
