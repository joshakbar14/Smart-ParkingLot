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
#include "Window.h"

class Window;
class parkingLot
{

    public:
        parkingLot(int no_spots, Window* window);
        int get_spotavaliability();
        std::unordered_map<int, std::string> check_in_list;
        void start();
        void stop();

    private:
        int no_spots;
        std::unordered_map<int, bool> spots;
        std::vector<pair<int, int>> pins;
        int occupiedspace;
        int emptyspace;
        

};

#endif //PARKINGLOT_H
