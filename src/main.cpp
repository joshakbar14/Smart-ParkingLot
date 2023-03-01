#include "os/ultrasonicSensorClass.h"
#include <iostream>

using namespace std;

int main() {
    ultrasonicSensorClass ultrasonic("18","24");
    ultrasonic.sensorCheck();
}