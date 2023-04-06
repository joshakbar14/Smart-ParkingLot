#ifndef BUZZERCLASS_H
#define BUZZERCLASS_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include <unistd.h>

/**
 * Main class for the BuzzerClass. Informs car that has parked in wrong spot that it should move.
 * Buzzer turns on if car is in wrong spot. Buzzer turns off when car moves away.
 **/
class BuzzerClass 
{
    public:
        /**
         * BuzzerClass constructor. @param sensor_pin and @param buzzer_pin are 
         * GPIO input and output for the buzzer initalised.
         **/
        BuzzerClass(int sensor_pin, int buzzer_pin);

        /**
         * Turn buzzer on.
         **/
        void buzzer_on();

        /**
         * Turn buzzer off.
         **/
        void buzzer_off();

    private:
        // GPIO input pin for buzzer.
        int sensor_pin;

        // GPIO output pin for buzzer.
        int buzzer_pin;
};

#endif //BUZZERCLASS_H