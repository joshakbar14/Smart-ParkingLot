#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "os/ultrasonicSensorClass.h"
#include "os/RFIDclass.h"
#include "os/BuzzerClass.h"
#include <unordered_map>
#include <thread>
#include <unistd.h>
#include <vector>
#include <string>

struct parkSample {
    int occupiedspace = 0;
    int emptyspace = 0;
    int lot_no = 0;
    string uid = "";
}

class parkCallback
{
    public:
    virtual void change_window(parkSample sample) = 0;

}

class parkingLot
{

    public:
        parkingLot(int no_spots);
        int get_spotavaliability();
        void registerWindowCallback(parkCallback* cb);

    private:
        int no_spots;
        std::unordered_map<int, bool> spots;
        std::vector<pair<int, int>> pins;

        // Callback function that is called by RFID scans
        void to_window();
        parkCallback* windowcallback = nullptr;

};

#endif //PARKINGLOT_H
