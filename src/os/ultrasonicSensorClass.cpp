/* 
* Modified Python Code --> CPP for use in ultrasonic sensor
* HC-SR04
* Source in Python : https://tutorials-raspberrypi.com/raspberry-pi-ultrasonic-sensor-hc-sr04/
*/

#include <iostream>
#include <string>
#include <ctime>
#include "GPIO/GPIOClass.h"
#include "unistd.h"
#include "ultrasonicSensorClass.h"

using namespace std;

ultrasonicSensorClass::ultrasonicSensorClass(string in, string out)
{
    this->gpioIn = in;
    this->gpioOut = out;
    // set unique sensor_no for each instance of class
    if (this->sensor_no == NULL) {
        this->sensor_no = 0;
    } else {
        this->sensor_no++;
    }

    // create object of GPIO connection in pin gpioIn and gpioOut
    GPIOClass gpioWrite(in); //write
    GPIOClass gpioRead(out); //read
    this->gpioRead = gpioWrite;
    this->gpioRead = gpioRead;
    this->gpioWrite.export_gpio(); // initialize
    this->gpioWrite.setdir_gpio("in");
    this->gpioRead.export_gpio(); // initialize
    this->gpioRead.setdir_gpio("out");
}

int ultrasonicSensorClass::sense_location()
{
    bool checkStatus = true;
    string result;
    // char io1 = "18";
    // char io2 = "24";
    string high = "1";
    string low = "0";
    

    //trigger high
    this->gpioWrite.setval_gpio(high);
    sleep(0.00001);
    //trigger low
    this->gpioWrite.setval_gpio(low);

    time_t startTime = time(&startTime);
    time_t stopTime = time(&stopTime);

    //get GPIO read result
    this->gpioRead.getval_gpio(result);

    //save start time
    while (result == "0")
    {
        /* code */
        startTime = time(&startTime);
    }

    while (result == "1")
    {
        /* code */
        stopTime = time(&stopTime);
    }

    //main calculations, speed of sound
    int timeElapsed = startTime - stopTime;
    int distance = (timeElapsed * 34300) / 2;

    /*
    * trial on distance value
    * when car parked
    * compare to no car parked
    */

   try
   {
    while (true)
    {
        /* code */
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
