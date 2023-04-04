//This code is to test wether the RFID is working or not
/*This code is not made by team member, meanwhile it was downloaded from the other webpage*/
/*This code is not to submit for the task, it is only to check the RFID module*/

#include <iostream>
#include <signal.h>
#include "MFRC522.h"
#include <pigpio.h>
#include "RFIDclass.h"

RFIDClass::RFIDClass(int sensor_no)
{
    this->sensor_no = sensor_no;
}

double RFIDClass::sense_card() 
{
    signal(SIGINT, end_read);
    MFRC522 MIFAREReader;
    MIFAREReader.PCD_Init();


    while (running) {
        cardpresent = False;
        if (!MIFAREReader.PICC_IsNewCardPresent()) {
            continue;
        }
        }
        if (!MIFAREReader.PICC_ReadCardSerial()) {
            continue;
        }
        cardpresent = True;
        std::cout << "Card detected" << std::endl;
        MFRC522::Uid uid = MIFAREReader.uid;
        std::cout << "Card read UID: ";
        for (size_t i = 0; i < uid.size; ++i) {
            std::cout << static_cast<int>(uid.uidByte[i]) << ",";
        }
        std::cout << std::endl;
    }
    return 0;
    // it should return card UID callbacks
}

// void RFIDClass::displayInterrupt(int gpio, int level, uint32_t tick, void* userdata) 
// {
//     printf("Interrupt %d\n");
// 			((RFIDClass*)userdata)->dataReady();
// }

void RFIDClass::dataReady() {
    if (!callback) {
        return;
    }
    RFIDSample sample;
    sample.cardpresent = cardpresent;
    callback->card_changed(sample);
}//;

void RFIDClass::registerCallback(RFIDCallback* cb) 
{
    callback = cb;
}

void start(int signal) {
    t = thread(&RFIDClass::sense_card,this);
}

void stop(int signal) {
    running = false;
    std::cout << "Ctrl+C captured, ending read." << std::endl;
    t.join();
}
