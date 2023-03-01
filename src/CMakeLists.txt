add_library (Ultrasonic os/ultrasonicSensorClass.cpp os/ultrasonicSensorClass.h)
add_executable (demo main.cpp)
set_target_properties(
    demo
    PROPERTIES 
        SUFFIX ".o"
)
target_link_libraries (demo Ultrasonic)