#include "os/ultrasonicSensorClass.h"
#include <iostream>
#include <pigpio.h>
#include "parkingLot.h"
#include "os/RFID_main.h"
#include "os/RFIDclass.h"
#include "gui/interface/window.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

	gpioInitialise();    
    Window window;
    window.show();
    parkingLot parkinglot(2);

    gpioTerminate();

    return app.exec();
}
