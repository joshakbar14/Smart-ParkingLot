#ifndef RFIDCLASS_H
#define RFIDCLASS_H

#include <iostream>
#include <string>
#include <ctime>
#include "unistd.h"
#include <thread>
#include <pigpio.h>
#include <vector>

using namespace std;

struct RFIDSample {
    bool cardpresent = true;
    int rfid_no=0;
};

class RFIDCallback {
public:
    virtual void card_changed(RFIDSample sample) = 0;
};

class RFIDclass
{
    public:
        RFIDclass(int rfid_no);
        void registerCallback(RFIDCallback* cb);
        void start();
        void stop();
    private:
        double sense_card();
        static void displayInterrupt(int gpio, int level, uint32_t tick, void* userdata);
        void dataReady();
        int rfid_no;
        bool running;
        std::thread t;
        RFIDCallback* callback = nullptr;
        bool cardpresent;
        int led_pin;
};

#endif //RFIDCLASS_H
