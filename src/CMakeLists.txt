cmake_minimum_required(VERSION 3.7.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable (running 
                main.cpp
                window.cpp
                parkingLot.cpp
)
set_target_properties(
    running
    PROPERTIES 
        SUFFIX ".o"
)

target_link_libraries (running Dev pigpio pthread bcm2835 Qt5::Widgets)

add_library (Dev os/ultrasonicSensorClass.cpp os/ultrasonicSensorClass.h
             os/RFIDclass.cpp os/RFIDclass.h os/MFRC522.cpp os/MFRC522.h os/BuzzerClass.cpp os/BuzzerClass.h
)

# parkingLot.cpp parkingLot.h
# src/window.h src/window.cpp

install(TARGETS running)
