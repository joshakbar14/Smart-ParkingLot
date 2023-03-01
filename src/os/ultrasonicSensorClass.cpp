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
}

int ultrasonicSensorClass::sensorCheck()
{
    bool checkStatus = true;
    string result;
    // char io1 = "18";
    // char io2 = "24";
    string high = "1";
    string low = "0";
    // create object of GPIO connection in pin gpioIn and gpioOut
    GPIOClass gpioWrite(this->gpioIn); //write
    GPIOClass gpioRead(this->gpioOut); //read
    gpioWrite.export_gpio(); // initialize
    gpioWrite.setdir_gpio("in");
    gpioRead.export_gpio(); // initialize
    gpioRead.setdir_gpio("out");

    //trigger high
    gpioWrite.setval_gpio(high);
    sleep(0.00001);
    //trigger low
    gpioWrite.setval_gpio(low);

    time_t startTime = time(&startTime);
    time_t stopTime = time(&stopTime);

    //get GPIO read result
    gpioRead.getval_gpio(result);

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
