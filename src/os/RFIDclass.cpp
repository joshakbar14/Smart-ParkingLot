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
        MFRC522::Uid uid = MIFAREReader.uid;
        for (size_t i = 0; i < uid.size; ++i) {
            card_no.append(std::to_string(static_cast<int>(uid.uidByte[i])));
            card_no.append(".");
        }
        cardpresent = true;
        gpioWrite(led_pin, 1);
        sleep(1);
        card_no = "";
        }
    return 0;
}

 void RFIDclass::displayInterrupt(int gpio, int level, uint32_t tick, void* userdata) 
 {
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

void RFIDclass::start(std::thread* th) {
    led_pin = rfid_no;
    gpioSetMode(led_pin, PI_OUTPUT);
    gpioWrite(led_pin, 0);
    gpioSetISRFuncEx(led_pin, RISING_EDGE, 0, displayInterrupt, (void*)this);
	*th = thread(&RFIDclass::sense_card,this);
    this->t = th;
}

void RFIDclass::stop() {
    running = false;
    t->join();
}
