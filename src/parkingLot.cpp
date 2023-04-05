
#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "parkingLot.h"
#include "os/ultrasonicSensorClass.h"
#include "os/RFIDclass.h"
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

// Class implementing the ultrasonicCallback and avaliability_changed function
// to update the avaliability of parking spots in the parkingLot class.
class aParkCallback : public ultrasonicCallback {
public:
    // Bool that registers the avaliability of a certain parking spot.
	bool* avaliable;

    // Update the avaliability of a certain parking spot. @param sample contains
    // the avaliability and sensor_no from ultrasonicSample.
    virtual void avaliability_changed(ultrasonicSample sample) {
        if (avaliable == nullptr) return;
	    *avaliable = sample.avaliability;
	    cout << "Parking spot:" << sample.sensor_no << "  is avaliable =" << sample.avaliability << endl;
	}

    // Register the @param avaliability that contains the avaliability of 
    // a certain parking spot. Updated in avaliability_changed.
	void registerMap(bool* avaliability) {
	    avaliable = avaliability;
	}
};

class aCallback : public RFIDCallback {
public:
	bool* present;
        virtual void card_changed(RFIDSample sample) {
        if (present == nullptr) return;
	    *present = sample.cardpresent;
	    cout << "RFID read:" << sample.rfid_no << "  is present =" << sample.cardpresent << endl;
	}

	void registerCard(bool* cardpresent) {
	    present = cardpresent;
	}
};

parkingLot::parkingLot(int no_spots)
{
    // number of spots in total for parking lot
    this->no_spots = no_spots;
// }

// void parkingLot::park() {
//     vector<pair<int,int>> fill = {
//         {22, 23},
//         {6,  12}
//     };
//     pins = fill;

//     int no = no_spots;
//     if (no_spots > pins.size()) {
//         cout << "not enough gpio numbers for pins in vector: check 'fill' and add accordingly as connected to rpi" << endl;
//         cout << "will only initialize: " << pins.size() << "sensors." << endl;
//         no = pins.size();
//     }

//     //fill the hash map with number of spot and avaliability bool
//     for (int i = 0; i < no; i++) {
//         bool avaliability = true;
//         spots[i] = avaliability;

//         //instantiate callback
//         aParkCallback callback;
//         callback.registerMap(&avaliability);

//         ultrasonicSensorClass parkSpot(pins[i].first, pins[i].second, i);
//         sensors.push_back(&parkSpot);
//         parkSpot.registerCallback(&callback);
//         parkSpot.start();
//     }

//     try {
//         running = true;
//         while(running);
//     } catch (const std::exception &e) {
//         std::cerr << e.what() << '\n';
//     }

    bool avaliability1 = true;
    bool avaliability2 = true;
    bool card = false;
    spots[0] = avaliability1;
    spots[1] = avaliability2;

    //instantiate callback
    aParkCallback callback1;
    aParkCallback callback2;
    aCallback callback3;
	
    callback1.registerMap(&avaliability1);
    callback2.registerMap(&avaliability2);
    callback3.registerCard(&card);

    ultrasonicSensorClass parkSpot1(22, 23, 0);
    ultrasonicSensorClass parkSpot2(6, 12, 1);
    RFIDclass rfid1(3);
    parkSpot1.registerCallback(&callback1);
    parkSpot2.registerCallback(&callback2);
    rfid1.registerCallback(&callback3);
    parkSpot1.start();
    parkSpot2.start();
    rfid1.start();
    sleep(30);
    parkSpot1.stop();
    parkSpot2.stop();
    rfid1.stop();
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

// void parkingLot::start()
// {
//     t = thread(&parkingLot::park,this);
// }

// void parkingLot::stop()
// {
//     for (ultrasonicSensorClass* parkSpot : sensors) { 
//         parkSpot->stop();
//     }
//     // spot1->stop();
//     // spot2->stop();
//     running = false;
//     t.join();
// }

// void parkingLot::registerCallback()
// {

// }
