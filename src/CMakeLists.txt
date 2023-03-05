add_library (Ultrasonic os/ultrasonicSensorClass.cpp os/ultrasonicSensorClass.h os/GPIO/GPIOClass.cpp 
             os/GPIO/GPIOClass.h lib/pigpio/pigpio.h lib/pigpio/pigpio.c lib/pigpio/command.h lib/pigpio/command.c)
add_executable (demo parkLed.cpp)
set_target_properties(
    demo
    PROPERTIES 
        SUFFIX ".o"
)
target_link_libraries (demo Ultrasonic)
target_link_libraries (demo pigpio pthread) #for setting linker to PIGPIO library in /usr/lib/

include_directories(/usr/local/include)
