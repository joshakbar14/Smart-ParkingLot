#ifndef PARKCALLBACK_H
#define PARKCALLBACK_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

struct parkCallback : parkCallback {
public:
	void avaliability_changed(int no, bool avaliability) {

		cout << "Parking spot:" << no << "  is avaliable =" << avaliability << endl;
	}
};

#endif  //PARKCALLBACK_H