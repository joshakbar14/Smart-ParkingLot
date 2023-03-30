
#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "parkingLot.h"
#include "os/ultrasonicSensorClass.h"
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

struct aParkCallback : ultrasonicCallback {
public:
        parkingLot *pl = nullptr;
	    //void avaliability_changed(int no, bool avaliability) {
        void avaliability_changed(ultrasonicSample sample) {
            if (pl == nullptr) return;
            //pl->spots[no] = avaliability;
            pl->spots[sample.sensor_no] = sample.avaliability;
		    cout << "Parking spot:" << sample.sensor_no << "  is avaliable =" << sample.avaliability << endl;
	    }
    
};

/*Class that keeps track of all parking spots, 
constructor assigns number of parking spots and 
fills a hash map parkSpots with number and avaliability bool*/
parkingLot::parkingLot(int no_spots)
{
    vector<pair<int,int>> fill = {
        {22, 23},
        {6,  12}
    };
    pins = fill;

    // number of spots in total for parking lot
    this->no_spots = no_spots;
    int no = no_spots;

    if (no_spots > pins.size()) {
        cout << "not enough gpio numbers for pins in vector: check 'fill' and add accordingly as connected to rpi" << endl;
        cout << "will only initialize: " << pins.size() << "sensors." << endl;
        no = pins.size();
    }

    //vector with all instantiated sensors
    vector<ultrasonicSensorClass> sensors_list;

    //fill the hash map with number of spot and avaliability bool
    for (int i = 0; i < no; i++) {
        spots[i] = true;

        //instantiate callback
        aParkCallback callback;

        ultrasonicSensorClass parkSpot(pins[i].first, pins[i].second, i);
        sensors_list.push_back(parkSpot);
        parkSpot.registerCallback(&callback);
        parkSpot.start();
    }

    sleep(30);

    for (ultrasonicSensorClass& parkSpot : sensors_list) { 
        parkSpot.stop();
    }

    /*for testing only
        spots[0] = true;
        spots[1] = true;

        //instantiate callback
        aParkCallback callback1;
        aParkCallback callback2;

        ultrasonicSensorClass parkSpot1(22, 23, 0);
        ultrasonicSensorClass parkSpot2(6, 12, 1);
        //parkSpot.registerCallback(&avaliability);
        parkSpot1.registerCallback(&callback1);
        parkSpot2.registerCallback(&callback2);
        parkSpot1.start();
        parkSpot2.start();
        sleep(30);
        parkSpot1.stop();
        parkSpot2.stop();
    */
    
}

int parkingLot::get_spotavaliability()
{
    //return free spot from hash map
    for (auto spot : spots) {
        if (spot.second == true) {
            return spot.first;
        }
    }
    //or value not found
    return -1;
}