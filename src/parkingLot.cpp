
#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "parkingLot.h"
#include "../os/ultrasonicSensorClass.h"
#include <thread>
#include <unistd.h>

using namespace std;

struct parkCallback : parkCallback {
public:
	void avaliability_changed(int no, bool avaliability) {
        spots[no] = avaliability;
		cout << "Parking spot:" << no << "  is avaliable =" << avaliability << endl;
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
    for (int i = 0; i < no_spots; i++) {
        bool avaliability = false;
        spots[i] = avaliability;

        //instantiate callback
        parkCallback callback;

        // // instantiate parkClass which is the driver class between the ultrasonic sensors and parkingLot
        // parkClass parkSpot(i);
        ultrasonicSensorClass parkSpot(18, 24, i);
        //parkSpot.registerCallback(&avaliability);
        parkSpot.registerCallback(&callback);
        parkSpot.start();
        sleep(5);
        parkSpot.stop();
    }
}

int parkingLot::get_spotavaliability()
{
    //return free spot from hash map
}