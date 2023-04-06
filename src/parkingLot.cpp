
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

    // Pointer to instance of parkingLot class.
    parkingLot* pl;

    // Update the avaliability of a certain parking spot. @param sample contains
    // the avaliability and sensor_no from ultrasonicSample.
    virtual void avaliability_changed(ultrasonicSample sample) {
        if (avaliable == nullptr) return;
        if (pl == nullptr) return;

        if (sample.avaliability == false) {
            *avaliable = sample.avaliability;
            if (pl->check_in_list.find(sample.sensor_no) != pl->check_in_list.end() && pl->check_in_list[sample.sensor_no] != "") {
                cout << "Parking spot:" << sample.sensor_no << "  is now full. Avaliability =" << sample.avaliability << endl;
            }
            else {
                cout << "Wrong spot. Start buzzer." << endl;
            }
        }
        else {
            pl->check_in_list[sample.sensor_no] = "";
            *avaliable = sample.avaliability;
            cout << "Parking spot:" << sample.sensor_no << "  is now avaliable. Avaliability =" << sample.avaliability << endl;
        }
	}

    // Register the @param avaliability that contains the avaliability of 
    // a certain parking spot. Updated in avaliability_changed.
	void registerMap(bool* avaliability) {
	    avaliable = avaliability;
	}

    // Register the pointer instance to the @param parkingLot class.
    void registerClass(parkingLot* parkinglot) {
	    pl = parkinglot;
	}
};

// Class implementing the RFIDCallback and card_changed function
// to update if a card is present in the parkingLot class.
class aCallback : public RFIDCallback {
public:
    // Pointer to instance of parkingLot class.
	parkingLot* pl;

    // Update if a card is present. @param sample contains
    // the rfid_no and the cardpresent bool from RFIDsample.
    virtual void card_changed(RFIDSample sample) {
        if (pl == nullptr) return;
        int spot = pl->get_spotavaliability();
        if (spot != -1) {
            pl->check_in_list[spot] = sample.card_no;
            cout << "Check in point: " << sample.rfid_no << " . Welcome user " << sample.card_no << endl;
            cout << "Parking spot number " << spot << " is avaliable. Please proceed and park there." << endl;
        }
        else {
            cout << "Check in point: " << sample.rfid_no << " . Welcome user " << sample.card_no << endl;
            cout << "No avaliable parking at this moment, please return another time." << endl;
        }
	}

    // Register the pointer instance to the @param parkingLot class.
	void registerClass(parkingLot* parkinglot) {
	    pl = parkinglot;
	}
};

parkingLot::parkingLot(int no_spots)
{
    this->no_spots = no_spots;
}

parkingLot::parkingLot(int no_spots, int no_rfid) {
    this->no_spots = no_spots;
    this->no_rfid = no_rfid;
}

void parkingLot::park() {
    vector<pair<int,int>> fill = {
        {22, 23},
        {6,  12}
    };
    pins = fill;

    int no = no_spots;
    if (no_spots > pins.size()) {
        cout << "not enough gpio numbers for pins in vector: check 'fill' and add accordingly as connected to rpi" << endl;
        cout << "will only initialize: " << pins.size() << "sensors." << endl;
        no = pins.size();
    }

    //fill the spot hasp map with number of spot and avaliability bool
    //fill sensors vector with the created instances of sensors
    for (int i = 0; i < no; i++) {
        spots[i] = true;

        //instantiate callback
        aParkCallback callback;
        callback.registerMap(&spots[i]);
        callback.registerClass((parkingLot*)this);

        ultrasonicSensorClass parkSpot(pins[i].first, pins[i].second, i);
        sensors.push_back(&parkSpot);
        parkSpot.registerCallback(&callback);
        parkSpot.start();
    }

    //fill rfids vector with the created instances of rfids
    for (int i = 0; i < no_rfid; i++) {
        aCallback callback;
        callback.registerClass((parkingLot*)this);

        RFIDclass rfid(no+i);
        rfids.push_back(&rfid);
        rfid.registerCallback(&callback);
        rfid.start();
    }
    sleep(30);

    for (ultrasonicSensorClass* parkSpot : sensors) { 
        parkSpot->stop();
    }
    for (RFIDclass* rfid : rfids) { 
        rfid->stop();
    }

//     try {
//         running = true;
//         while(running);
//     } catch (const std::exception &e) {
//         std::cerr << e.what() << '\n';
//     }

    // spots[0] = true;
    // spots[1] = true;

    // //instantiate callback
    // aParkCallback callback1;
    // aParkCallback callback2;
    // aCallback callback3;
	
    // callback1.registerMap(&spots[0]);
    // callback2.registerMap(&spots[1]);
    // callback1.registerClass((parkingLot*)this);
    // callback2.registerClass((parkingLot*)this);
    // callback3.registerClass((parkingLot*)this);

    // ultrasonicSensorClass parkSpot1(22, 23, 0);
    // ultrasonicSensorClass parkSpot2(6, 12, 1);
    // RFIDclass rfid1(3);
    // parkSpot1.registerCallback(&callback1);
    // parkSpot2.registerCallback(&callback2);
    // rfid1.registerCallback(&callback3);
    // parkSpot1.start();
    // parkSpot2.start();
    // rfid1.start();
    // sleep(30);
    // parkSpot1.stop();
    // parkSpot2.stop();
    // rfid1.stop();
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
