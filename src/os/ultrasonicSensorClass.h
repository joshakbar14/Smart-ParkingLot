#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <iostream>
#include <string>
#include <ctime>
#include "unistd.h"
#include <pigpio.h>
#include <thread>
#include <vector>

using namespace std;

/**
 * Sample from ultrasonicSensorClass.
 **/
struct ultrasonicSample {
    /**
     * Bool avaliability to determine state of parking spot.
     **/
    bool avaliability = true;

    /**
     * Ultrasonic sensor id number.
     **/
    int sensor_no = 0;
};

/**
 * Callback interface with callback function to be implemented by host class.
 **/
class ultrasonicCallback {
public:
    /**
     * Called when interrupt from ultrasonic sensor signals that a change is detected.
     * @param sample contains the sensor id number and avaliability bool.
     **/
    virtual void avaliability_changed(ultrasonicSample sample) = 0;
};

/**
 * Main class for the ultrasonic sensors. Registers changes from the input GPIO pin and 
 * sends an interrupt which triggers a callback to the parkingLot class if the distance 
 * is in the range of change for a car leaving or arriving. start() begins a separate 
 * thread for every ultrasonic sensor and stop() ends it. registerCallback needs to be
 * called from host class (parkingLot) to be able to get data.
 **/
class ultrasonicSensorClass
{
    public:
        /**
         * UltrasonicSensorClass constructor. @param in and @param out are 
         * GPIO input and output for the sensor initalised and @param sensor_no is 
         * the sensor's identification number.
         **/
        ultrasonicSensorClass(int in, int out, int sensor_no);

        /**
         * Registers the callback that will recieve the sample data of the changed sensor.
         * @param cb is the callback interface.
         **/
        void registerCallback(ultrasonicCallback* cb);

        /**
         * Sets up GPIO settings for triggering pin for pigpio interrupt function and
         * initializes thread for instance of ultrasonicSensorClass.
         **/
        void start();

        /**
         * Stops thread execution and ends ultrasonic sensor readings.
         **/
        void stop();

    private:
        // Worker function for threads. Reads GPIO input pin and calculates distance.
        // Interrupt sent if the change in distance is in range of car leaving or arriving. 
        void sense_location();

        // Static pigpio interrupt function. @param userdata contains pointer to this class instance.
        static void displayInterrupt(int gpio, int level, uint32_t tick, void* userdata);

        // Callback function which is called by interrupt function displayInterrupt. 
        void dataReady();

        // GPIO input pin for ultrasonic sensor.
        int input_pin;

        // GPIO output pin for ultrasonic sensor.
        int output_pin;

        // Bool used to control while loop in worker function sense_location.
        bool running;

        // Thread which runs sense_location function and registers sensor inputs.
        std::thread t;

        // Callback interface which is registered with parkingLot class.
        ultrasonicCallback* callback = nullptr;

        // State of avaliability of parking spot.
        bool avaliability;

        // Id number of this instance of the class.
        int sensor_no;

        // Pin used to trigger interrupt at correct distance.
	    int led_pin;
};

#endif //ULTRASONIC_H
