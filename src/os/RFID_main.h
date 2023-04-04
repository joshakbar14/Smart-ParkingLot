#ifndef RFIDMAIN_H
#define RFIDMAIN_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "os/ultrasonicSensorClass.h"
#include <unordered_map>
#include <thread>
#include <unistd.h>
#include <vector>

class RFID_main
{
    public:
        RFID_main(int no_spots);
        // int get_spotavaliability();
    private:
        int no_spots;
        std::unordered_map<int, bool> spots;
};

#endif //RFIDMAIN_H
