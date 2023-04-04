#ifndef RFIDMAIN_H
#define RFIDMAIN_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <unistd.h>
#include <vector>
#include "RFIDclass.h"

class RFID_main
{
    public:
        RFID_main(int no_rfid);
    private:
        int no_rfid;
};

#endif //RFIDMAIN_H
