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
        parkingLot(int no_spots);

        /**
         * Initialises the corresponding ultrasonic sensors, RFIDs and callbacks for the 
         * ultrasonicSensorClass and RFIDclass that are registered in the classes. Begins the
         * sensor and RFID readings.
         **/
        void park();

        /**
         * Checks the hashmap containing the parking spots and avaliability and @returns 
         * the parking spot id number if a spot is avaliable, otherwise @returns -1.
         **/
        int get_spotavaliability();

        // Keeps track of which user (card_no) is supposed to park at what parking spot.
        // std::string empty if parking spot empty.
        std::unordered_map<int, std::string> check_in_list;

    private:
        // Number of parking spots in this parking lot assigned from the main program.
        int no_spots;

        // Unordered hash map for the parking spots which contains the id number
        // of the spot and the avaliability of the parking spot. Updated by 
        // the class aParkCallback that implements the interface ultrasonicCallback.
        std::unordered_map<int, bool> spots;

        // Vector of pairs of pins that can be used as input and output pins
        // for instances of ultrasonic sensors.
        std::vector<pair<int, int>> pins;
};

#endif //PARKINGLOT_H
