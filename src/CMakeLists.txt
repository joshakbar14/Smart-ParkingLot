add_library (Ultrasonic os/ultrasonicSensorClass.cpp os/ultrasonicSensorClass.h)
add_executable (demo parkLed.cpp)
set_target_properties(
    demo
    PROPERTIES 
        SUFFIX ".o"
)
target_link_libraries (demo Ultrasonic pigpio pthread)
target_link_libraries (demo pigpio pthread) #for setting linker to PIGPIO library in /usr/lib/

include_directories(/usr/local/include)
