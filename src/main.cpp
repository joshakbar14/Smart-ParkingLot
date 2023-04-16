#include <QApplication>
#include <iostream>
#include <pigpio.h>
#include "parkingLot.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    // parkingLot parkinglot(2, &window);
    //RFID_main rfid(1);
    window.startParkingLot();
    window.startTimer(40);
    //parkinglot.start();

    //sleep(20);
    //getchar();

    //parkinglot.stop();
    return app.exec();
}
