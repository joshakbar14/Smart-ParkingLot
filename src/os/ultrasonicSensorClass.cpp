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
#include "GPIO/GPIOClass.h"

using namespace std;

ultrasonicSensorClass::ultrasonicSensorClass(string in, string out, int sensor_no)
{
    // create object of GPIO connection in pin gpioIn and gpioOut
    this->sensor_no = sensor_no;
    GPIOClass gpioWrite(in); //write
    GPIOClass gpioRead(out); //read
    this->gpioWrite = gpioWrite;
    this->gpioRead = gpioRead;
    this->gpioWrite.export_gpio(); // initialize
    this->gpioWrite.setdir_gpio("out");
    this->gpioRead.export_gpio(); // initialize
    this->gpioRead.setdir_gpio("in");
}

int ultrasonicSensorClass::sense_location()
{
    bool checkStatus = true;
    string result ="0";
    string high = "1";
    string low = "0";
    
    this->gpioWrite.setval_gpio(high); //trigger high
    sleep(0.00001);
    this->gpioWrite.setval_gpio(low); //trigger low

    time_t startTime = time(&startTime);
    time_t stopTime = time(&stopTime);

    /*
    * trial on distance value
    * when car parked
    * compare to no car parked
    */
    try
    {
        while (true)
        {
            //save start time
            while (result == "0")
            {
                //get GPIO read result
                this->gpioRead.getval_gpio(result);
            }
            startTime = time(&startTime);
            
            //save stop time
            while (result == "1")
            {
                this->gpioRead.getval_gpio(result);
            }
            stopTime = time(&stopTime);
            //main calculations, speed of sound
            int timeElapsed = startTime - stopTime;
            int distance = (timeElapsed * 34300) / 2;
            cout << distance << endl;
            sleep(1);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
   return 0;
}
