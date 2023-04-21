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

/**
 * Forward Declaration of Window class
 **/
class Window;

/**
 * Main class for the parking lot. Initialises the ultrasonic sensors and RFIDs and 
 * stores the corresponding parking spots connected to the sensors in an allocated 
 * hash map which keeps track of the avaliability of the parking spots.
 **/
class parkingLot
{
    public:
       /**
         * parkingLot class constructor. @param no_spots determines the number of 
         * parking spots that will be allocated in this parking lot. 
         **/
        parkingLot(int no_spots, Window* window);
        
        // Keeps track of which user (card_no) is supposed to park at what parking spot.
        int get_spotavaliability();

        // std::string empty if parking spot empty.
        std::unordered_map<int, std::string> check_in_list;
        
        void start();
        void stop();

    private:
        int no_spots;

        // Unordered hash map for the parking spots which contains the id number
        // of the spot and the avaliability of the parking spot. Updated by 
        // the class aParkCallback that implements the interface ultrasonicCallback.
        std::unordered_map<int, bool> spots;
        std::vector<pair<int, int>> pins;
        
        int occupiedspace;
        int emptyspace;
        
};

#endif //PARKINGLOT_H
