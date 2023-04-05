#include <iostream>
#include <signal.h>
#include "MFRC522.h"
#include <pigpio.h>
#include "RFIDclass.h"

RFIDclass::RFIDclass(int rfid_no)
{
    this->rfid_no = rfid_no;
}

double RFIDclass::sense_card() 
{
    MFRC522 MIFAREReader;
    MIFAREReader.PCD_Init();
    
    running = true;
    while (running) {
        cardpresent = false;
        gpioWrite(led_pin, 0);
        sleep(1);
        if (!MIFAREReader.PICC_IsNewCardPresent()) {
            continue;
        }
        if (!MIFAREReader.PICC_ReadCardSerial()) {
            continue;
        }
        cardpresent = true;
        gpioWrite(led_pin, 1);
        sleep(1);
        //std::cout << "Card detected" << std::endl;
        MFRC522::Uid uid = MIFAREReader.uid;
        //std::cout << "Card read UID: ";
        card_no = 0;
        for (size_t i = 0; i < uid.size; ++i) {
            card_no = card_no*1000;
            card_no += static_cast<int>(uid.uidByte[i]);
            std::cout << static_cast<int>(uid.uidByte[i]) << ",";
        }
        std::cout << std::endl;
    }
    return 0;
    // it should return card UID callbacks
}

 void RFIDclass::displayInterrupt(int gpio, int level, uint32_t tick, void* userdata) 
 {
    //printf("Interrupt %d\n");
 			((RFIDclass*)userdata)->dataReady();
 }

void RFIDclass::dataReady() {
    if (!callback) {
        return;
    }
    RFIDSample sample;
    sample.rfid_no = rfid_no;
    sample.cardpresent = cardpresent;
    sample.card_no = card_no;
    callback->card_changed(sample);
}

void RFIDclass::registerCallback(RFIDCallback* cb) 
{
    callback = cb;
}

void RFIDclass::start() {
    led_pin = rfid_no;
    gpioSetMode(led_pin, PI_OUTPUT);
    gpioWrite(led_pin, 0);
    gpioSetISRFuncEx(led_pin, RISING_EDGE, 0, displayInterrupt, (void*)this);
    t = thread(&RFIDclass::sense_card,this);
}

void RFIDclass::stop() {
    running = false;
    //std::cout << "Ctrl+C captured, ending read." << std::endl;
    t.join();
}
