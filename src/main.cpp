#include "os/ultrasonicSensorClass.h"
#include <iostream>
#include <pigpio.h>
#include "parkingLot.h"
#include "os/RFIDclass.h"

using namespace std;

int main() {
	gpioInitialise();    

    parkingLot parkinglot(2);
    parkinglot.park();

    gpioTerminate();
}
