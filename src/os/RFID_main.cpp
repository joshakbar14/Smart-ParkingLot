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

RFID_main::RFID_main(int no_rfid)
{
    this->no_rfid = no_rfid;

    bool card = false;

    //instantiate callback
    aCallback callback1;
	
	callback1.registerCard(&card);

    RFIDclass rfid1(3);
    
    rfid1.registerCallback(&callback1);

    rfid1.start();

    sleep(30);
    
    rfid1.stop();

}
