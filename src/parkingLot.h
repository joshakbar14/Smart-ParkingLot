#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "../os/ultrasonicSensorClass.h"
#include <unordered_map>
#include <thread>
#include <unistd.h>

class parkingLot
{
    public:
        parkingLot(int no_spots);
        int get_spotavaliability();
    private:
        int no_spots;
        std::unordered_map<int, bool> spots;
};

#endif //PARKINGLOT_H