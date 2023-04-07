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

/**
 * Sample from RFIDclass.
 **/
struct RFIDSample {
    /**
     * Bool cardpresent to determine state of card.
     **/
    bool cardpresent = true;

    /**
     * Card number.
     **/
    std::string card_no = "";

    /**
     * RFID id number.
     **/
    int rfid_no = 0;
};

/**
 * Callback interface with callback function to be implemented by host class.
 **/
class RFIDCallback {
public:
    /**
     * Called when interrupt from RFID signals that a change is detected.
     * @param sample contains the RFID id number and cardpresent bool.
     **/
    virtual void card_changed(RFIDSample sample) = 0;
};

/**
 * Main class for the RFID.
 **/
class RFIDclass
{
    public:
        /**
         * RFIDclass constructor. @param rfid_no is the RFID's identification number.
         **/
        RFIDclass(int rfid_no);

        /**
         * Registers the callback that will recieve the sample data. @param cb is 
         * the callback interface.
         **/
        void registerCallback(RFIDCallback* cb);

        /**
         * Sets up GPIO settings for triggering pin for pigpio interrupt function and
         * starts thread for instance of RFIDclass.
         **/
        void start(std::thread* th);

        /**
         * Stops thread execution and ends RFID readings.
         **/
        void stop();

    private:
        // Worker function for threads. Reads..
        // Interrupt sent if the change in 
        double sense_card();

        // Static pigpio interrupt function. @param userdata contains pointer to this class instance.
        static void displayInterrupt(int gpio, int level, uint32_t tick, void* userdata);

        // Callback function which is called by interrupt function displayInterrupt. 
        void dataReady();

        // Id number of this instance of the class.
        int rfid_no;

        // Card number from the card that is read.
        std::string card_no = "";

        // Bool used to control while loop in worker function sense_card.
        bool running = false;

        // Pointer to thread which runs sense_card function.
        std::thread* t;

        // Callback interface which is registered with parkingLot class.
        RFIDCallback* callback = nullptr;

        // State of card.
        bool cardpresent;

        // Pin used to trigger interrupt.
        int led_pin;
};

#endif //RFIDCLASS_H
