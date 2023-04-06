#include "os/ultrasonicSensorClass.h"
#include <iostream>
#include <pigpio.h>
#include "parkingLot.h"
#include "os/RFID_main.h"
#include "os/RFIDclass.h"

using namespace std;

int main() {
	gpioInitialise();    

    parkingLot parkinglot(2);
    //RFID_main rfid(1);

    //parkinglot.start();

    //sleep(20);
    //getchar();

    //parkinglot.stop();

    gpioTerminate();
}
