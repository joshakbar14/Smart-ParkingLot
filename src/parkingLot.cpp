
#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "parkingLot.h"
#include "os/ultrasonicSensorClass.h"
#include "os/RFIDclass.h"
#include "os/BuzzerClass.h"
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

    // Pointer to buzzer class.
    BuzzerClass* bz;

    // Update the avaliability of a certain parking spot. @param sample contains
    // the avaliability and sensor_no from ultrasonicSample.
    virtual void avaliability_changed(ultrasonicSample sample) {
        if (avaliable == nullptr) return;
        if (pl == nullptr) return;
        if (bz == nullptr) return;

        if (sample.avaliability == false) {
            *avaliable = sample.avaliability;
            if (pl->check_in_list.find(sample.sensor_no) != pl->check_in_list.end() && pl->check_in_list[sample.sensor_no] != "") {
                cout << "Parking spot:" << sample.sensor_no << "  is now full. Avaliability =" << sample.avaliability << endl;
            }
            else {
                bz->buzzer_on();
                cout << "Wrong spot. Start buzzer." << endl;
            }
        }
        else {
            pl->check_in_list[sample.sensor_no] = "";
            bz->buzzer_off();                           //Check if this is the best way
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

    // Register the pointer instance to the @param buzzer class.
    void registerBuzzer(BuzzerClass* buzzer) {
	    bz = buzzer;
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
        pl->lot_no = sample.rfid_no;
        pl->uid = sample.card_no;
        pl->to_window();
	}

    // Register the pointer instance to the @param parkingLot class.
	void registerClass(parkingLot* parkinglot) {
	    pl = parkinglot;
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

    spots[0] = true;
    spots[1] = true;
    BuzzerClass buzzer1(26);
    BuzzerClass buzzer2(27);

    //instantiate callback
    aParkCallback callback1;
    aParkCallback callback2;
    aCallback callback3;
	
    callback1.registerMap(&spots[0]);
    callback2.registerMap(&spots[1]);
    callback1.registerClass((parkingLot*)this);
    callback2.registerClass((parkingLot*)this);
    callback3.registerClass((parkingLot*)this);
    callback1.registerBuzzer(&buzzer1);
    callback2.registerBuzzer(&buzzer2);

    ultrasonicSensorClass parkSpot1(22, 23, 0);
    ultrasonicSensorClass parkSpot2(6, 12, 1);
    RFIDclass rfid1(3);
    parkSpot1.registerCallback(&callback1);
    parkSpot2.registerCallback(&callback2);
    rfid1.registerCallback(&callback3);

    // Running Thread
    gpioInitialise();
    parkSpot1.start();
    parkSpot2.start();
    rfid1.start();
    sleep(30);
    //getchar();
    parkSpot1.stop();
    parkSpot2.stop();
    rfid1.stop();
    gpioTerminate();
}

int parkingLot::get_spotavaliability()
{
    //return free spot from hash map
    for (auto spot : spots) {
        if (spot.second == true) {
            if (check_in_list[spot.first] == "") {
                return spot.first;
            }
        }
    }
    //or value not found
    return -1;
}

void parkingLot::to_window()
{
    if (!windowcallback){
        return;
    }

    parkSample sample;
    sample.occupiedspace = occupiedspace;
    sample.emptyspace = emptyspace;
    sample.lot_no = lot_no;
    sample.uid = uid;
    windowcallback->change_window(sample);

}

void parkingLot::registerWindowCallback(parkCallback* cb)
{
    windowcallback = cb;
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
