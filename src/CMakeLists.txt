add_library (Dev os/ultrasonicSensorClass.cpp os/ultrasonicSensorClass.h parkingLot.cpp parkingLot.h
             os/RFIDclass.cpp os/RFIDclass.h os/RFID_main.cpp os/RFID_main.h
             os/MFRC522.cpp os/MFRC522.h
             gui/interface/window.cpp gui/interface/window.h
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable (demo main.cpp)
set_target_properties(
    demo
    PROPERTIES 
        SUFFIX ".o"
)
target_link_libraries (demo Dev pigpio pthread bcm2835 Qt5::Widgets qwt-qt5)
#target_link_libraries (demo pigpio pthread) #for setting linker to PIGPIO library in /usr/lib/

include_directories(/usr/local/include)
