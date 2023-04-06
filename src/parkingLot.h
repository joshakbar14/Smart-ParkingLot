#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "os/ultrasonicSensorClass.h"
#include "os/RFIDclass.h"
#include <unordered_map>
#include <thread>
#include <unistd.h>
#include <vector>

/**
 * Main class for the parking lot. Initialises the ultrasonic sensors and RFIDs and 
 * stores the corresponding parking spots connected to the sensors in an allocated 
 * hashmap which keeps track of the avaliability of the parking spots.
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
         * parkingLot class constructor. @param no_spots determines the number of 
         * parking spots that will be allocated in this parking lot. @param no_rfid
         * determines the number of RFID readers that will be allocated.
         **/
        parkingLot(int no_spots, int no_rfid);

        /**
         * Initialises the corresponding ultrasonic sensors, RFIDs and callbacks for the 
         * ultrasonicSensorClass and RFIDclass that are registered in the classes. Begins the
         * sensor and RFID readings (((and puts the instances of the sensors in the sensors vector))).
         **/
        void park();

        /**
         * Checks the hashmap containing the parking spots and avaliability and @returns 
         * the parking spot id number if a spot is avaliable, otherwise @returns -1.
         **/
        int get_spotavaliability();

        // /**
        //  * Begins the thread that runs the park function.
        //  **/
        // void start();

        // /**
        //  * Stops the sensor readings and ends them when called. Joins the thread.
        //  **/
        // void stop();

        // /**
        //  * 
        //  **/
        // void registerCallback();

        // Keeps track of which user (card_no) is supposed to park at what parking spot.
        // std::string empty if parking spot empty or car correcly parked.
        std::unordered_map<int, std::string> check_in_list;

    private:
        // Number of parking spots in this parking lot assigned from the main program.
        int no_spots;

        // Number of RFID readers in this parking lot assigned from the main program.
        int no_rfid = 1;

        // Unordered hashmap for the parking spots which contains the id number
        // of the spot and the avaliability of the parking spot. Updated by 
        // the class aParkCallback that implements the interface ultrasonicCallback.
        std::unordered_map<int, bool> spots;

        // Vector of pairs of pins that can be used as input and output pins
        // for instances of ultrasonic sensors.
        std::vector<pair<int, int>> pins;

        //  Vector of pointer to instances of sensors.
        std::vector<ultrasonicSensorClass*> sensors;

        //  Vector of pointer to instances of RFID readers.
        std::vector<RFIDclass*> rfids;

        // //  Thread which runs the park function that initialises all sensors and callbacks.
        // std::thread t;

        // // Bool used to keep thread alive until stop is called.
        // bool running;


};

#endif //PARKINGLOT_H
