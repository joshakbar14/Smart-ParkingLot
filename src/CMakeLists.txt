cmake_minimum_required(VERSION 3.7.0)

add_library (Dev os/ultrasonicSensorClass.cpp os/ultrasonicSensorClass.h parkingLot.cpp parkingLot.h
             os/RFIDclass.cpp os/RFIDclass.h os/RFID_main.cpp os/RFID_main.h
             os/MFRC522.cpp os/MFRC522.h
             gui/interface/window.cpp gui/interface/window.h
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable (demo main.cpp)
set_target_properties(
    demo
    PROPERTIES 
        SUFFIX ".o"
)
target_link_libraries (demo Dev pigpio pthread bcm2835)
target_link_libraries (demo Qt5::Widgets)
target_link_libraries (demo qwt-qt5)
#target_link_libraries (demo pigpio pthread) #for setting linker to PIGPIO library in /usr/lib/
#
install(TARGETS demo)
