/*
 * Modified Python Code --> CPP for use in ultrasonic sensor
 * HC-SR04
 * Source in Python : https://tutorials-raspberrypi.com/raspberry-pi-ultrasonic-sensor-hc-sr04/
 */

#include <iostream>
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

    this->input_pin = in;
    this->output_pin = out;
    gpioSetMode(input_pin, PI_INPUT);
    gpioSetMode(output_pin, PI_OUTPUT);

}

int ultrasonicSensorClass::sense_location()
{
    // bool checkStatus = true;
    string result = "0";

    time_t startTime = time(&startTime);
    time_t stopTime = time(&stopTime);

    try
    {
        while (true)
        {
            gpioWrite(output_pin, 0);
            sleep(0.00002);
            gpioWrite(output_pin, 1); // trigger high
            sleep(0.00010);
            gpioWrite(output_pin, 0); // trigger low
            // save start time
            
            while (gpioRead(input_pin) == 0)
            {
                // get GPIO read result
                startTime = time(&startTime);
            }

            // save stop time
            
            while (gpioRead(input_pin) == 0)
            {
                stopTime = time(&stopTime);
            }

            // main calculations, speed of sound
            int timeElapsed = startTime - stopTime;
            int distance = (timeElapsed * 34300) / 2;
            cout << distance << endl;
            sleep(5);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
