#include <QApplication>
#include <iostream>
#include <pigpio.h>
#include "parkingLot.h"
#include "Window.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    // parkingLot parkinglot(2, &window);
    //RFID_main rfid(1);
    
    window.startTimer(40);
    app.processEvents();
    window.startParkingLot();
    
    //parkinglot.start();

    //sleep(20);
    //getchar();

    //parkinglot.stop();
    return app.exec();
}
