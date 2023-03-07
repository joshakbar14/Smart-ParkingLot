//This code is to test wether the RFID is working or not
/*This code is not made by team member, meanwhile it was downloaded from the other webpage*/
/*This code is not to submit for the task, it is only to check the RFID module*/

#include <iostream>
#include <signal.h>
#include "MFRC522.h"
#include "pigpio.h"

bool continue_reading = true;

void end_read(int signal) {
    continue_reading = false;
    std::cout << "Ctrl+C captured, ending read." << std::endl;
}

int main() {
    signal(SIGINT, end_read);
    std::cout << "Welcome to the MFRC522 data read example" << std::endl;
    std::cout << "Press Ctrl-C to stop." << std::endl;

    MFRC522 MIFAREReader;
    MIFAREReader.PCD_Init();

    while (continue_reading) {
        if (!MIFAREReader.PICC_IsNewCardPresent()) {
            continue;
        }
        if (!MIFAREReader.PICC_ReadCardSerial()) {
            continue;
        }
        std::cout << "Card detected" << std::endl;
        MFRC522::Uid uid = MIFAREReader.uid;
        std::cout << "Card read UID: ";
        for (size_t i = 0; i < uid.size; ++i) {
            std::cout << static_cast<int>(uid.uidByte[i]) << ",";
        }
        std::cout << std::endl;

        // This is the default key for authentication
        MFRC522::MIFARE_Key key;
        for (size_t i = 0; i < 6; ++i) {
            key.keyByte[i] = 0xFF;
        }
        
        // Select the scanned tag
        MIFAREReader.PICC_Select(&uid);
        
        // ENTER Your Card UID here
        MFRC522::Uid my_uid;
        my_uid.size = 5;
        my_uid.uidByte[0] = 61;
        my_uid.uidByte[1] = 84;
        my_uid.uidByte[2] = 4;
        my_uid.uidByte[3] = 114;
        my_uid.uidByte[4] = 31;
        
        // Configure LED Output Pin
        const int LED = 1;
        wiringPiSetup();
        pinMode(LED, OUTPUT);
        digitalWrite(LED, LOW);
        
        // Check to see if card UID read matches your card UID
        if (uid == my_uid) {  // Open the Doggy Door if matching UIDs
            std::cout << "Access Granted" << std::endl;
            digitalWrite(LED, HIGH);  // Turn on LED
            delay(5000);              // Wait 5 Seconds
            digitalWrite(LED, LOW);   // Turn off LED
            
        } else {                // Don't open if UIDs don't match
            std::cout << "Access Denied, YOU SHALL NOT PASS!" << std::endl;
        }
    }
    return 0;
}
