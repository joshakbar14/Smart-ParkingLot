#include "RFIDclass.h"
#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "RFID_main.h"
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

class aCallback : public RFIDCallback {
public:
	bool* avaliable;
        virtual void card_changed(RFIDSample sample) {
        if (avaliable == nullptr) return;
	    *avaliable = sample.cardpresent;
	    cout << "RFID read:" << sample.sensor_no << "  is present =" << sample.cardpresent << endl;
	}

	void registerMap(bool* cardpresent) {
	    avaliable = cardpresent;
	}
};

RFID_main::RFID_main(int no_spots)
{
    this->no_spots = no_spots;

    bool avaliability1 = true;
    
    spots[0] = avaliability1;

    //instantiate callback
    aCallback callback1;
	
	callback1.registerMap(&avaliability1);

    RFIDClass rfid1(22, 23, 0);
    
    rfid1.registerCallback(&callback1);

    rfid1.start();

    sleep(30);
    rfid1.stop();

}