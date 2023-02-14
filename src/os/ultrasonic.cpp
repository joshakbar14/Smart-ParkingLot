/* 
* Modified Python Code --> CPP for use in ultrasonic sensor
* HC-SR04
* Source in Python : https://tutorials-raspberrypi.com/raspberry-pi-ultrasonic-sensor-hc-sr04/
*/

#include <iostream>
#include <ctime>
#include "GPIOClass.h"
#include "unistd.h"

using namespace std;

int main(){
    bool checkStatus = true;
    string result24;
    // char io1 = "18";
    // char io2 = "24";
    string high = "1";
    string low = "0";
    // create object of GPIO connection in pin 18 and 24
    GPIOClass gpio18("18"); //write
    GPIOClass gpio24("24"); //read
    gpio18.export_gpio(); // initialize
    gpio18.setdir_gpio("in");
    gpio24.export_gpio(); // initialize
    gpio24.setdir_gpio("out");

    //trigger high
    gpio18.setval_gpio(high);
    sleep(0.00001);
    //trigger low
    gpio18.setval_gpio(low);

    time_t startTime = time(&startTime);
    time_t stopTime = time(&stopTime);

    //get GPIO read result
    gpio24.getval_gpio(result24);

    //save start time
    while (result24 == "0")
    {
        /* code */
        startTime = time(&startTime);
        
    }

    while (result24 == "1")
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


}
