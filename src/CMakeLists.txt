add_library (Ultrasonic os/ultrasonicSensorClass.cpp os/ultrasonicSensorClass.h parkingLot.cpp parkingLot.h
             os/RFIDclass.cpp os/RFIDclass.h os/MFRC522.cpp os/MFRC522.h os/BuzzerClass.cpp os/BuzzerClass.h
)
add_executable (demo main.cpp)
set_target_properties(
    demo
    PROPERTIES 
        SUFFIX ".o"
)
target_link_libraries (demo Ultrasonic pigpio pthread bcm2835)
#target_link_libraries (demo pigpio pthread) #for setting linker to PIGPIO library in /usr/lib/

include_directories(/usr/local/include)
