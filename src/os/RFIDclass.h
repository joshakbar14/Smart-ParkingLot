#ifndef RFIDCLASS_H
#define RFIDCLASS_H

#include <iostream>
#include <string>
#include <ctime>
#include "unistd.h"
#include <thread>
#include <pigpio.h>

using namespace std;

struct RFIDSample {
    bool cardpresent = true;
};

class RFIDCallback {
public:
    virtual void card_changed(RFIDSample sample) = 0;
};

class RFIDclass
{
    public:
        RFIDclass(int sensor_no);
        void registerCallback(RFIDCallback* cb);
        void start();
        void stop();
    private:
        double sense_card();
        static void displayInterrupt(int gpio, int level, uint32_t tick, void* userdata);
        void dataReady();
        int sensor_no;
        int input_pin;
        int output_pin;
        bool running;
        std::thread t;
        RFIDCallback* callback = nullptr;
        bool cardpresent;
};

#endif //RFIDCLASS_H