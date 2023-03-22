
#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "parkClass.h"
#include "../os/ultrasonicSensorClass.h"
#include <thread>

/* Driver Class */
parkClass::parkClass(int park_no)
{
    this->park_no = park_no;
}

/* Callback method */
int parkClass::spot_avaliability()
{   
    //which pins are connected to which sensor?
    running = true;
    while(running){
        
        ultrasonicSensorClass sensor(18, 24, park_no);
        int sensor_result = sensor.sense_location();
        if (sensor_result == 1) {
            for (auto callback : callbacks) {
                callback->avaliability_changed(park_no, true);
            }
            return 1;
        } else {
            return 0;
        }
    }
}

void parkClass::registerCallback(bool* avaliability) 
{
    callbacks.push_back(avaliability);
}
// void parkClass::registerCallback(parkCallback* callback) 
// {
//     callbacks.push_back(callback);
// }

void parkClass::start() 
{
    t = thread(&parkClass::spot_avaliability,this);
}

void parkClass::stop() 
{
    running = false;
	t.join();
}