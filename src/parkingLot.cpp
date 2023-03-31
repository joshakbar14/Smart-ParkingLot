
#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "parkingLot.h"
#include "os/ultrasonicSensorClass.h"
#include <thread>
#include <unistd.h>

using namespace std;

class aParkCallback : public ultrasonicCallback {
public:

	bool* avaliable;
        virtual void avaliability_changed(ultrasonicSample sample) {
            if (avaliable == nullptr) return;
	    *avaliable = sample.avaliability;
	    cout << "Parking spot:" << sample.sensor_no << "  is avaliable =" << sample.avaliability << endl;
	}

	void registerMap(bool* avaliability) {
	    avaliable = avaliability;
	}
    
};

/*Class that keeps track of all parking spots, 
constructor assigns number of parking spots and 
fills a hash map parkSpots with number and avaliability bool*/
parkingLot::parkingLot(int no_spots)
{
    // number of spots in total for parking lot
    this->no_spots = no_spots;

    // fill the hash map with number of spot and avaliability bool
    // for (int i = 0; i < no_spots; i++) {
    //     bool avaliability = true;
    //     spots[i] = avaliability;

    //     //instantiate callback
    //     aParkCallback callback;

    //     // // instantiate parkClass which is the driver class between the ultrasonic sensors and parkingLot
    //     // parkClass parkSpot(i);
    //     ultrasonicSensorClass parkSpot(i+22, i+23, i);
    //     //parkSpot.registerCallback(&avaliability);
    //     parkSpot.registerCallback(&callback);
    //     parkSpot.start();
    //     sleep(20);
    //     parkSpot.stop();
    // }
        bool avaliability1 = true;
	bool avaliability2 = true;
        spots[0] = avaliability1;
        spots[1] = avaliability2;

        //instantiate callback
        aParkCallback callback1;
        aParkCallback callback2;
	
	callback1.registerMap(&avaliability1);
	callback2.registerMap(&avaliability2);

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
    
}

int parkingLot::get_spotavaliability()
{
    //return free spot from hash map
    for (auto spot : spots) {
        if (spot.second == true) {
            return spot.first;
        }
    }
    return -1;
    // or value not found
}
