#ifndef PARKCLASS_H
#define PARKCLASS_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include <thread>
#include <vector>

class parkClass
{
    public:
        parkClass(int park_no);
        int spot_avaliability();
        void registerCallback(bool* avaliability);
        //void registerCallback(parkCallback* callback);
        void start();
        void stop();
    private:
        int park_no;
        std::vector<bool*> callbacks;
        std::thread t;
        bool running;
};

#endif //PARKCLASS_H