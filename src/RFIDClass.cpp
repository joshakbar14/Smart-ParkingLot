/*This code is to read RFID Card continuously and permit the system to run*/

#include <iostream>
#include <signal.h>
#include "MFRC522.h"
#include "pigpio.h"

bool continue_reading = true; 
//If there is no signal, the program continue to read//

void end_read(int signal) 
//to handle a signal event that is sent to the program//
{ 
    if (continue_reading = true)
    {
    std::cout << "Please Tap Your Card" << std::endl;
    }
    
    if (continue_reading = false) 
    //if end_read read signal, then the program should not a continue to read//
    {
    std::cout << "Reading The signal" << std::endl;
    //Statement if the reader is reading the signal//
    }
}

int main() 
{
    MFRC522 MIFAREReader;
    //RFID reader module
    MIFAREReader.PCD_Init();
    //RFID reader module is set up for reading

    while (continue_reading) 
    {
        if (!MIFAREReader.PICC_IsNewCardPresent()) 
        //if a new RFID card is present in the reader//
        {
            continue;
        }

        if (!MIFAREReader.PICC_ReadCardSerial())
        //reads the serial number of the card and stores it in a variable named uid//
        {
            continue;
        }
        
        std::cout << "Card detected" << std::endl;
        //indicating that a card has been detected//

        MFRC522::Uid uid = MIFAREReader.uid;
        //retrieves the unique identifier of the detected card from the RFID module//

        std::cout << "Welcome to iSpace Parking Spot " << std::endl;
        std::cout << "Card read UID: ";
        for (size_t i = 0; i < uid.size; ++i) 
        {
            std::cout << static_cast<int>(uid.uidByte[i]) << ",";
        }
        //prints the UID of the card to the console, byte by byte//
            std::cout << std::endl;

        MFRC522::MIFARE_Key key;
        for (size_t i = 0; i < 6; ++i) 
        {
            key.keyByte[i] = 0xFF;
        }
        //initializes a key for authentication to a default value of all 1s//
        
        MIFAREReader.PICC_Select(&uid);
        //selects the scanned tag for further communication with the RFID module//
        
            MFRC522::Uid my_uid;
        my_uid.size = 5;
        my_uid.uidByte[0] = 61;
        my_uid.uidByte[1] = 84;
        my_uid.uidByte[2] = 4;
        my_uid.uidByte[3] = 114;
        my_uid.uidByte[4] = 31;
        //creates a new UID to be compared with the detected card's UID
        
    }
    return 0;
}